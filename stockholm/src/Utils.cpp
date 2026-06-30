#include "Utils.hpp"
#include <iostream>

void utils::usage(char *av) {
	std::cout << "Usage: " << std::endl;
	std::cout << "\t./" << av << " <option> [arguments]" << std::endl;
	exit(0);
}
