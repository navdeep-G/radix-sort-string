#include "radix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int max(int *tab, long size) {
	int max_val = INT_MIN;
	for (long i = 0; i < size; i++) {
		if (tab[i] > max_val) {
			max_val = tab[i];
		}
	}
	return max_val;
}

static void compute_lengths(char **input, long input_size, int *lengths) {
	for (long i = 0; i < input_size; i++) {
		lengths[i] = strlen(input[i]);
	}
}

static int char_to_index(char character) {
	int index;

	if (character >= 'a') {
		index = character - 'a';
	} else {
		index = character - 'A';
	}

	// '0' index is reserved for 'not existing' character (word shorter than sorted position)
	return index + 1;
}

static char** counting_sort(char **input, long input_size, int *lengths, int sorted_position) {

	long i;

	const int counts_size = 26 * 2 + 1;
	int *counts = calloc(counts_size, sizeof(int));
	if (counts == NULL) {
		fprintf(stderr, "Allocation error!\n");
		exit(-1);
	}

	// counting
	char curr_char;
	int index;
	for (i = 0; i < input_size; i++) {
		// check if word has character at given position (may be shorter)
		if (sorted_position < lengths[i]) {
			curr_char = input[i][sorted_position];
			index = char_to_index(curr_char);
			counts[index]++;
		} else {
			counts[0]++;
		}
	}

	// compute first positions in output array for each bucket
	int total = 0;
	int curr_count;
	for (i = 0; i < counts_size; i++) {
		curr_count = counts[i];
		counts[i] = total;
		total += curr_count;
	}

	char **output = malloc(input_size * sizeof(char*));
	if (output == NULL) {
		fprintf(stderr, "Allocation error!\n");
		exit(-1);
	}

	int *output_lengths = malloc(input_size * sizeof(int));
	if (output_lengths == NULL) {
		fprintf(stderr, "Allocation error!\n");
		exit(-1);
	}

	// computing element positions
	for (i = 0; i < input_size; i++) {
		if (sorted_position >= lengths[i]) {
			output[counts[0]] = input[i];
			counts[0]++;
		} else {
			index = char_to_index(input[i][sorted_position]);
			int output_index = counts[index];
			output[output_index] = input[i];
			output_lengths[output_index] = lengths[i];
			counts[index]++;
		}
	}

	free(counts);

	// copying positions to 'input' table
	for (i = 0; i < input_size; i++) {
		input[i] = output[i];
		lengths[i] = output_lengths[i];
	}

	free(output);
	free(output_lengths);

	return input;
}

void radix(long input_size, char **input) {
	int *lengths = malloc(input_size * sizeof(int));
	if (lengths == NULL) {
		fprintf(stderr, "Allocation error!\n");
		exit(-1);
	}

	compute_lengths(input, input_size, lengths);

	int max_length = max(lengths, input_size);

	// sorting from least significant character
	for (int position = max_length - 1; position >= 0; position--) {
		counting_sort(input, input_size, lengths, position);
	}

	free(lengths);
}
