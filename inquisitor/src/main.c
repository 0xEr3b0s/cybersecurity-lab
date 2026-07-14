#include <stdio.h>

#include "parsing.h"
#include "inquisitor.h"

int main(int ac, char **av) {
	t_config config = {0};
	parse_arguments(ac, av, &config);
	print_config(&config);

	return 0;
}
