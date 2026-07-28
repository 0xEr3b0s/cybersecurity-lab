#include "poisoning.h"
#include <netinet/in.h>

void build_arp_trame(t_arp_frame *frame, char *sender_mac_str, char *sender_ip_str, char *target_mac_str, char *target_ip_str, char *local_mac_str) {
	frame->eth.mac_dst = ntohl(target_ip_str);
}
