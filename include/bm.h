#ifndef BERLEKAMP_MASSEY_H
#define BERLEKAMP_MASSEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Structure for the result of the Berlekamp-Massey algorithm
typedef struct {
	int *coefficients;   // Coefficients of the minimal polynomial
	size_t degree;       // Degree of the minimal polynomial
} BMResult;

/**
 * Finds the shortest linear feedback shift register (LFSR) for a given sequence.
 * 
 * @param sequence Input sequence of integers (e.g., binary sequence)
 * @param length Length of the input sequence
 * @param result Pointer to the BMResult structure to store the result
 * @return 0 on success, -1 on error
 */
int berlekamp_massey(const int *sequence, size_t length, BMResult *result);

/**
 * Frees the resources used by the BMResult structure.
 * 
 * @param result Pointer to the BMResult structure to be freed
 */
void bm_result_free(BMResult *result);

#ifdef __cplusplus
}
#endif

#endif // BERLEKAMP_MASSEY_H
