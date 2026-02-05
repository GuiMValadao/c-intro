#include <stdlib.h>
#include <stdio.h>

/* limites de iteração mínimo e máximo centrados em 1.0 */
// 'constexpr' foi implementado em C com o C23.
constexpr double eps1m01 = 1.0 - 0x1P-01;
constexpr double eps1p01 = 1.0 + 0x1P-01;
constexpr double eps1m24 = 1.0 - 0x1P-24;
constexpr double eps1p24 = 1.0 + 0x1P-24;

/* argv: takes an array input with argc number of elements.
argv[argc+1] changes the array indexing to 1 instead of zero (why?)
argc: is the lenght of the array/numer of arguments provided. */

int main (int argc, char* argv[argc+1]) {
    for (int i = 1; i < argc; ++i) {
        double const a = strtod(argv[i], nullptr);
        double x = 1.0;
        for (;;) {
            double prod = a*x;
            if (prod < eps1m01) {
                x *= 2.0;
            } else if (eps1p01 < prod) {
                x *= 0.5;
            } else {
                break;
            }
	    // Intermediary values of x:
	    // printf("Intermediary x value: %.5e\n", x);
        }
        for (;;) {
            double prod = a*x;
            if ((prod < eps1m24) || (eps1p24 < prod)) {
                x *= (2.0 - prod);
            } else{
                break;
            }
        }
        printf("heron: a=%.5e,\tx=%.5e,\ta*x=%.12f\n",
                a, x, a*x);
    }
    return EXIT_SUCCESS;
}