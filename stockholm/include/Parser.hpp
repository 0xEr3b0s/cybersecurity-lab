#pragma once

#include <string>

#define OPT_SILENT (1 << 0)
#define OPT_REVERSE (1 << 1)
#define OPT_VERSION (1 << 2)
#define OPT_HELP (1 << 3)

#define PROGRAM_VERSION "0.0.1"

class Parser {
	private:
		int option_field;
		char *key;

		static char *getCmdOption(char ** begin, char ** end, const std::string & option);
		static bool cmdOptionExists(char** begin, char** end, const std::string& option);

	public:
		Parser *parse(int ac, char **av);
		int getOptionfield(void) const;
		std::string getKey(void) const;
};
