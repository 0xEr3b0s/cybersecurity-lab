#ifndef INQUISITOR_H
#define INQUISITOR_H

typedef struct s_config {
	char *spoof_ip;
	char *spoof_mac;

	char *target_ip;
	char *target_mac;

	char *local_ip;
	char *local_mac;

	int ifindex;

	char iface;
	int verbose;
} t_config;

#endif
