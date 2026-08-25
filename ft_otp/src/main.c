#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ft_otp.h"

int main(int ac, char **av) {
	params_t params;
	memset(&params, 0, sizeof(params));

	if (ac != 3)
		error("Should get one option (-g/-k) and its related argument.");

	parse_option(&params, av);

	if (params.g_flag) {
		check_key(&params);
		store_key(&params);
		free(params.key);
		params.key = NULL;  // Prevent double free
	} else if (params.k_flag) {
		load_key(&params);
		printf("%06d\n", generate_otp(&params));
		free(params.key);
		params.key = NULL;  // Clean up
	} else {
		// Neither flag set - should not happen due to parse_option validation
		error("Invalid option, use -g or -k");
	}

	return (0);
}
