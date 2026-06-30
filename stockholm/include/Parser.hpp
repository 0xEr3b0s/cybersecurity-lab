#pragma once

#include <string>

class Parser {
	private:
		int option_code;
		std::string key;

		char *getCmdOption(char ** begin, char ** end, const std::string & option);
		bool cmdOptionExists(char** begin, char** end, const std::string& option);

	public:
		Parser *parse(int ac, char **av);
		int getOptionCode(void);
		std::string getKey(void);
};
