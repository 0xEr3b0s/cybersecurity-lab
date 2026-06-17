#ifndef FT_OTP
# define FT_OTP

# define DEBUG_FLAG 1

#include <stdio.h>

typedef struct params_s {
	int g_flag;
	int k_flag;
	char *filename;
} params_t;

void parse_option(params_t *params, char **av);
void check_key(params_t params);

/* UTILS */
void error(char *msg);

#endif
