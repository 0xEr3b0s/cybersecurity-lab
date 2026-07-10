#ifndef PARSING_H
#define PARSING_H

#include "inquisitor.h"

int is_ipv4(char *src);
int is_mac_addr(char *src);
int discover_interface(t_config *config);

void print_config(t_config *config);

#endif
