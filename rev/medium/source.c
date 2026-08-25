#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char buff[24];
	char char_dec[4];
	char result[9];
	int index = 1;

	printf("Please enter key: ");
	// FIXED: Limit to 23 chars + null terminator
	if (scanf("%23s", buff) != 1) {
		printf("Nope.\n");
		return 1;
	}
	result[0] = 'd';
	if (buff[0] != '0' || buff[1] != '0') {
		printf("Nope.\n");
		exit(1);
	}
	
	for (int i = 2; i < 23; i += 3) {  // FIXED: Use 23 not 24 to avoid out of bounds
		// Check we have enough remaining chars
		if ((i + 3) > 23) break;  // Safety check
		
		for (int j = 0; j < 3; j++) {
			if ((i + j) >= 23) {
				printf("Nope.\n");
				exit(1);
			}
			char_dec[j] = buff[i + j];
		}
		char_dec[3] = '\0';
		
		int tmp = atoi(char_dec);
		if (index >= 8) {  // Array bounds check
			printf("Nope.\n");
			exit(1);
		}
		result[index] = (char)tmp;
		index++;
	}
	
	result[8] = '\0';  // Ensure null termination
	
	if (strcmp(result, "delabere") != 0) {
		printf("Nope.\n");
		return 1;
	}
	printf("Good job.\n");
	return 0;
}
