#include "Discovering.hpp"
#include <cstdlib>
#include <cstring>

void Discovering::discover() {
	this->getenv_result = std::getenv(this->home.c_str());
	if (this->getenv_result == nullptr) {
		std::cout << "Error: getenv failed ( env not existing )" << std::endl;
		exit(1);
	}
	this->complete_path = this->getenv_result + this->infection_folder_name;
	std::cout << "this->home: " << this->home << std::endl << "this->result: " << this->getenv_result << std::endl << "concatenate path: " << this->complete_path << std::endl;
}
