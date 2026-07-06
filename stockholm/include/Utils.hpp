#include <iostream>

#define OPT_SILENT (1 << 0)
#define OPT_REVERSE (1 << 1)
#define OPT_VERSION (1 << 2)
#define OPT_HELP (1 << 3)

#define PROGRAM_VERSION "0.0.1"

namespace utils {

void usage(char *av);
void error(std::string s);

} // namespace utils
