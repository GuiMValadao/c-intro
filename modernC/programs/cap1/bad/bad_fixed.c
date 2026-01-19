#include <stdlib.h>
#include <stdio.h>
int main(int argc) {
    // Declarations
    int i;
    double A[5] = {
    [0] = 9.0,
    [1] = 2.9,
    [4] = 3.E+25,
    [3] = .00007,
    };
    // Doing some work
    for (i = 0; i < 5; ++i) {
        printf("element %d is %g, \tits square is %g\n",
        i,
        A[i],
        A[i] * A[i]);
    }
    return EXIT_SUCCESS;
}