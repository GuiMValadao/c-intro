/* Challenge 6 (Linear algebra). Some of the most important problems for which arrays are
 used stem from linear algebra.
 Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
 What about Gaussian elimination or iterative algorithms for matrix inversion?*/

#include <stdio.h>

int main(void) {
    int A[3] = { 2, 4, 0, };
    int B[3] = { 3, 5, 0, };
    int inner_product[3];
    int cross_product[3];
    for (int i = 0; i < 3; i++) {
        inner_product[i] = A[i] * B[i];
        switch(i) {
            case 0: {
                cross_product[i] = A[i+1]*B[i+2]-A[i+2]*B[i+1];
                continue;
            }
            case 1: {
                cross_product[i] = A[i+1]*B[i-1]-A[i-1]*B[i+1];
                continue;
            }
            case 2: {
                cross_product[i] = A[i-2]*B[i-1]-A[i-1]*B[i-2];
            }
        }
    }
    printf("inner_product = (");
    for (int i = 0; i < 3; i++) {
        printf(" %i, ", inner_product[i]);
    }
    printf(")\n");

    printf("cross_product = (");
    for (int i = 0; i < 3; i++) {
        printf(" %i, ", cross_product[i]);
    }
    printf(")\n");
}