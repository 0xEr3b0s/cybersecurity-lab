#include <stdio.h>
#include <stdlib.h>

#include "ft_otp.h"

int main(int ac, char **av) {
	params_t params;

	if (ac != 3) error("Should get atleast one option (-g/-k) and it's related argument.");
	parse_option(&params, av);

	if (params.g_flag)
		check_key(&params);

	printf("All went good finishing the program\nkey: %s\nsize: %ld", params.key, params.key_size);

	free(params.key);
	return (0);
}
