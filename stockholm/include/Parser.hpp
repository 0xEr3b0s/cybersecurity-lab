#pragma once

#include <string>

class Parser {
	private:
		int option_code;
		std::string key;

		static char *getCmdOption(char ** begin, char ** end, const std::string & option);
		static bool cmdOptionExists(char** begin, char** end, const std::string& option);

	public:
		Parser *parse(int ac, char **av);
		int getOptionCode(void) const;
		std::string getKey(void) const;
};
