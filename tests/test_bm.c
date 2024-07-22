#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "bm.h"

/* Test case structure to hold sequence data, expected results, and actual results. */
typedef struct {
	int *sequence;
	size_t length;
	size_t expected_degree;
	int *expected_coefficients;
} TestCase;

/* Function to perform a single test case */
static void run_test_case(const TestCase *test_case) {
	BMResult result;
    
	// Initialize result and perform the Berlekamp-Massey algorithm
	int status = berlekamp_massey(test_case->sequence, test_case->length, &result);
	assert(status == 0);  // Ensure that the algorithm completes successfully

	// Validate degree of the result
	assert(result.degree == test_case->expected_degree);

	// Validate coefficients of the result
	for(size_t i=0;i<=result.degree;++i) {
		assert(result.coefficients[i] == test_case->expected_coefficients[i]);
	}

	bm_result_free(&result);
}

/* Main function to define and execute test cases */
void test_berlekamp_massey() {
	// Defined test cases
	int sequence1[] = {1, 0, 0, 1, 1, 0, 1, 1};
	int expected_coefficients1[] = {1, 1, 1, 0, 0};
	TestCase test_case1 = {
		.sequence = sequence1,
		.length = sizeof(sequence1) / sizeof(sequence1[0]),
		.expected_degree = 4,
		.expected_coefficients = expected_coefficients1
	};

	int sequence2[] = {1, 1, 0, 0, 1, 1, 0, 0};
	int expected_coefficients2[] = {1, 1, 1, 1};
	TestCase test_case2 = {
		.sequence = sequence2,
		.length = sizeof(sequence2) / sizeof(sequence2[0]),
		.expected_degree = 3,
		.expected_coefficients = expected_coefficients2
	};

	// Run test cases
	run_test_case(&test_case1);
	run_test_case(&test_case2);

	printf("All tests passed.\n");
}

int main(void) {
	test_berlekamp_massey();
	return 0;
}

