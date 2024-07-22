## Berlekamp-Massey Algorithm Library

## Overview

This library provides a simple implementation of the Berlekamp-Massey algorithm in C. The algorithm is used to find the shortest linear feedback shift register (LFSR) for a given binary sequence, this is usefull for decoding BCH-code sequences or some cryptographic applications (i.e. get the liniar complexity of a LFSR).

### How the Berlekamp-Massey Algorithm Works (Overview)
The Berlekamp-Massey Algorithm operates in the GF(2), which means all arithmetic is performed modulo 2.

**Initialization:**

*   Start with two polynomials C(x) and B(x), both initially set to 1.
*   Set the length L of the LFSR to 0 and a variable m to -1.

**Update Loop:**

*   For each bit in the sequence, compute the discrepancy between the expected and actual values based on the current polynomial.
*   Update C(x) and B(x) as needed to correct any discrepancies.
*   Adjust L and mmm to ensure C(x) remains the minimal polynomial.

**Completion:**

*   Continue until all bits are processed. The polynomial C(x) at the end is the minimal polynomial representing the shortest LFSR for the sequence.

### Operation in GF(2)

*   **Addition and Subtraction:** Performed as XOR operations.
*   **Multiplication:** Performed using standard binary multiplication rules.

For more explanation the following paper was very usefull for understanding the algorithm:

[https://www-users.cse.umn.edu/~garrett/students/reu/MB_algorithm.pdf](https://www-users.cse.umn.edu/~garrett/students/reu/MB_algorithm.pdf)

### Complexity

The Berlekamp-Massey algorithm runs in O(n²) time complexity, where n is the length of the input sequence.

## Prerequisites

To build the library, you need to have a C compiler installed on your system (e.g., GCC).

## Building

Navigate to the project directory and run the following command:

```bash
make
```
This will compile the library and generate a static library file libbm.a which you can include in your binaries. Furthermore it will build example_bm and test_suite for demonstration of the functionality and unit testing.

## Usage

To use the Berlekamp-Massey Algorithm library in your project, include the bm.h header file and link against the libbm.a static library.

Here is an simple example of how to use the library:

your_program.c:
```C
#include <stdio.h>
#include "bm.h"

int main() {
	int sequence[] = {1, 0, 0, 1, 1, 0, 1, 1};
	size_t length = sizeof(sequence) / sizeof(sequence[0]);

	// Result structure for the Berlekamp-Massey algorithm
	BMResult result;

	// Execute the Berlekamp-Massey algorithm
	if (berlekamp_massey(sequence, length, &result) == 0) {

        printf("The length of the shortest LFSR is: %ld\n", result.degree);
		// Free allocated resources
		bm_result_free(&result);

	} else {
		fprintf(stderr, "Failed to execute Berlekamp-Massey algorithm\n");
        return -1;
    }
    
    return 0;
}
```

**Linking the static library into your project:**
```bash
gcc -o your_program your_program.c -L. -lbm -Iinclude
```
Another example was included in the example directory.
If you wish to only build the example and static library without unit tests build the lib with:
```bash
make examples
```

### Running Unit Tests

The library includes unit tests to ensure functionality. These tests are automatically run during the build process. Additionally, you can run the tests manually by executing the test_suite binary:

```bash
./build/test_suite
```
This will run the unit tests and provide feedback on the library's correctness.

If you wish to only build the unit tests build the lib with:
```bash
make tests
```
This will compile and run the unit tests, providing feedback on the library's correctness.

## License
This project is licensed under the GNU General Public License v3.0.

## Contributions
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request. Keep in mind that this is a very basic implementation. Maybe I will improve this in the future...
