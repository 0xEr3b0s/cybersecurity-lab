#ifndef INQUISITOR_H
#define INQUISITOR_H

typedef struct s_config {
	char *ip_src;
	char *mac_src;
	char *ip_dest;
	char *mac_dest;

	char *ip_local;
	char *mac_local;
} t_config;

#endif
