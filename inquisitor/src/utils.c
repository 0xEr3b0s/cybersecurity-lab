#include "utils.h"

void free_ressources(t_config *config) {
	(void)config;
	return;
}

void usage(char *msg) {
	printf("%s\n", msg);
	exit(0);
}

void error(char *msg, int error_code, t_config *config) {
	fprintf(stderr, "Error: %s\n", msg);
	free_ressources(config);
	exit(error_code);
}
