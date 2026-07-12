#include <stdio.h>

#include "parsing.h"
#include "inquisitor.h"

int main(int ac, char **av) {
	t_config config;
	parse_arguments(ac, av, &config);

	return 0;
}
