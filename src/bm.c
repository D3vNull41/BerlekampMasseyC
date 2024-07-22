#include "bm.h"

/* Initializes the BMResult structure */
static void bm_result_init(BMResult *result) {
	if (result) {
		result->coefficients = NULL;
		result->degree = 0;
	}
}

/* Frees the resources used by the BMResult structure */
void bm_result_free(BMResult *result) {
	if (result) {
		free(result->coefficients);
		result->coefficients = NULL;
		result->degree = 0;
	}
}

/* Implements the Berlekamp-Massey algorithm */
int berlekamp_massey(const int *sequence, size_t length, BMResult *result) {
	if (!sequence || !result || length == 0) {
		return -1; // Invalid input
	}

	bm_result_init(result);

	// Allocate and initialize coefficient arrays
	int *C = (int *)calloc(length, sizeof(int));
	int *B = (int *)calloc(length, sizeof(int));
	if (!C || !B) {
		free(C);
		free(B);
		return -1; // Memory allocation error
	}

	C[0] = 1;
	B[0] = 1;
	size_t L = 0;
	int m = -1, b = 1;

	for (size_t n = 0; n < length; ++n) {
		int d = sequence[n];
		for (size_t i = 1; i <= L; ++i) {
			if (n >= i) {
				d ^= C[i] * sequence[n - i];
			}
		}

		if (d != 0) {
			// Allocate and initialize temporary array for coefficient updates
			int *T = (int *)calloc(length, sizeof(int));
			if (!T) {
				free(C);
				free(B);
				return -1; // Memory allocation error
			}

			// Update C using temporary array T
			memcpy(T, C, length * sizeof(int));
			for (size_t i = 0; i <= L; ++i) {
				if (n - m + i < length) {
					C[n - m + i] ^= B[i] * d / b;
				}
			}

			// Update length, shift register, and temporary array
			if (L <= n / 2) {
				L = n + 1 - L;
				m = n;
				b = d;
				memcpy(B, T, length * sizeof(int));
			}

			free(T);
		}
	}

	// Allocate and store the result
	result->coefficients = (int *)calloc(L + 1, sizeof(int));
	if (!result->coefficients) {
		free(C);
		free(B);
		return -1; // Memory allocation error
	}
	memcpy(result->coefficients, C, (L + 1) * sizeof(int));
	result->degree = L;

	free(C);
	free(B);

	return 0; // Success
}

