#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "radix.h"

void print(char **input, long input_size) {
	for (long i = 0; i < input_size; i++) {
		printf("%s\n", input[i]);
	}
}

void generate_data(char ***input, long n) {
	srand(time(NULL));

	*input = malloc(n * sizeof(char**));
	if (*input == NULL) {
		fprintf(stderr, "Allocation error!\n");
		exit(-1);
	}

	for (long i = 0; i < n; i++) {
		int length = 5 + rand()%6;
		(*input)[i] = malloc(length * sizeof(char));
		if ((*input)[i] == NULL) {
			fprintf(stderr, "Allocation error!\n");
			exit(-1);
		}

		for (int j = 0; j < length - 1; j++) {
			(*input)[i][j] = (char) (rand() % 26 + 97);
		}
		(*input)[i][length - 1] = '\0';
	}
}

int main(int argc, char *argv[]) {
	
	if (argc != 2) {
		char* input[] = {"z","a","b","c"};
		long n = sizeof(input) / sizeof(char*);

		printf("INPUT:\n");
		print(input, n);

		radix(n, input);

		printf("\nOUTPUT:\n");
		print(input, n);

		return 0;
	}

	else {
		char **input;
		long n = atol(argv[1]);
		generate_data(&input, n);
      	
		printf("INPUT:\n");
		print(input, n);

		radix(n, input);

		printf("\nOUTPUT:\n");
		print(input, n);

		return 0;
	}
}
