#include <stdio.h>

#include "ft_otp.h"

int main(int ac, char **av) {
	(void)av;
	if (ac != 3) error("Should get atleast one option (-g/-k) and it's related argument.");
	return (0);
}
