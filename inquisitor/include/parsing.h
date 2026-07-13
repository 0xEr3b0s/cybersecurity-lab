#ifndef PARSING_H
#define PARSING_H

#include "inquisitor.h"

void parse_arguments(int ac, char **av, t_config *config);

int is_ipv4(char *src);
int is_mac_addr(char *src);
int discover_interface(t_config *config);

void print_config(t_config *config);

#endif
