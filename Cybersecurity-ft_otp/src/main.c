#include <stdio.h>
#include <stdlib.h>

#include "ft_otp.h"

int main(int ac, char **av) {
	params_t params;

	if (ac != 3) error("Should get atleast one option (-g/-k) and it's related argument.");
	parse_option(&params, av);

	if (params.g_flag)
		check_key(&params);

	decode_hex(&params);
	if (DEBUG_FLAG)
		debug_hexdump("key", params.decoded_key, params.decoded_key_size);

	encode_counter(&params);
	if (DEBUG_FLAG)
		debug_hexdump("counter", params.counter, 8);

	free(params.key);
	free(params.decoded_key);
	return (0);
}
