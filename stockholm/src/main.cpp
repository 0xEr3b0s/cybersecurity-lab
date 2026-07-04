#include <iostream>
#include "Discovering.hpp"
#include "Parser.hpp"

int main(int ac, char **av) {
	if (ac < 2) {
		std::cerr << "AssertionError: need atleast 1 argument and max 2 "
					 "(option - key)."
				  << std::endl;
		exit(1);
	}
	std::cout << "Hello stockholm" << std::endl;
	Parser p;
	p.parse(ac, av);
	std::cout << p.getKey() << " :: " << p.getOptionfield() << std::endl;
	Discovering d;
	d.discover();
	return 0;
}
