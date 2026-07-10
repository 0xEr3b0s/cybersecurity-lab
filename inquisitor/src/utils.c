#include "util.h"

void usage(char *msg) {
	printf("%s\n", msg);
	exit(0);
}

void error(char *msg, int error_code) {
	printf("%s\n", msg);
	exit(error_code);
}
