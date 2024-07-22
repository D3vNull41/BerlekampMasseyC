#include <stdio.h>
#include <stdlib.h>
#include "bm.h"

static void print_result(const BMResult *result);
static void print_polynomial(const BMResult *result);
static void handle_error(const char *message);

int main(void) {
	// Example input sequence
	int sequence[] = {1, 0, 0, 1, 1, 0, 1, 1};
	size_t length = sizeof(sequence) / sizeof(sequence[0]);

	// Result structure for the Berlekamp-Massey algorithm
	BMResult result;

	// Execute the Berlekamp-Massey algorithm
	if (berlekamp_massey(sequence, length, &result) == 0) {
		print_result(&result);

		// Free allocated resources
		bm_result_free(&result);
	} else {
		handle_error("Failed to execute Berlekamp-Massey algorithm");
	}

	return 0;
}

static void print_result(const BMResult *result) {
	printf("Minimal Linear Feedback Shift Register Found:\n");
	printf("Degree: %zu\n", result->degree);
	printf("Coefficients: ");
	for (size_t i = 0; i <= result->degree; ++i) {
		printf("%d ", result->coefficients[i]);
	}
	printf("\n");
	
	printf("Coefficients (Polynomial Representation): ");
	print_polynomial(result);
	printf("\n");
}

static void print_polynomial(const BMResult *result) {
	size_t degree = result->degree;
	
	// Print polynomial terms from highest degree to lowest
	for (size_t i = degree; i > 0; --i) {
		if (result->coefficients[degree-i] != 0) {
			printf("x^%zu ", i);
			if (result->coefficients[degree - (i - 1)] != 0) {
				printf("+ ");
			}
		}
	}

	// Print the constant term
	if (result->coefficients[degree] != 0) {
		if (degree > 0 && result->coefficients[degree] > 0) {
			printf("+ ");
		}
		printf("%d", result->coefficients[degree]);
	}
}
 
static void handle_error(const char *message) {
	fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

