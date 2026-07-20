#include <cstdint>
#include <stdio.h>

typedef struct s_eth_header {
	unsigned char dst[6];
	unsigned char src[6];
	unsigned short type;
} __attribute__((__packed__)) s_eth_header;

typedef struct s_arp_msg {

} t_arp_msg;

typedef struct s_arp_frame {

} __attribute__((__packed__)) t_arp_frame;
