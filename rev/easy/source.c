#include <stdio.h>
#include <string.h>

int main(void) {
	char buff[64];
	printf("Please enter key:");
	// FIXED: Use width limit to prevent buffer overflow
	if (scanf("%63s", buff) != 1) {
		printf("Nope.\n");
		return 1;
	}
	if (strcmp(buff, "__stack_check") != 0) {
		printf("Nope.\n");
		return 1;
	}
	printf("Good job.\n");
	return 0;
}
