#include <stdio.h>

#include "ft_otp.h"

int main(int ac, char **av) {
	params_t params;

	if (ac != 3) error("Should get atleast one option (-g/-k) and it's related argument.");
	parse_option(&params, av);

	if (DEBUG_FLAG)
		printf("option: %d(-g) %d(-k)\nfilename: %s\n", params.g_flag, params.k_flag, params.filename);

	if (params.g_flag)
		check_key(params);

	return (0);
}
