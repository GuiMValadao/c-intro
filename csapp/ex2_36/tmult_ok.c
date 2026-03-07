#include <stdint.h>
#include <stdio.h>

void main() {
    printf("first calc %d\n", tmult_ok(INT32_MIN, 5));
    printf("second calc %d\n", tmult_ok(INT32_MIN, 0));
    printf("third calc %d\n", tmult_ok(INT32_MIN/10, 5));
    printf("fourth calc %d\n", tmult_ok(INT32_MIN/25, 12));
    printf("first calc %d\n", tmult2(INT32_MIN, 5));
    printf("second calc %d\n", tmult2(INT32_MIN, 0));
    printf("third calc %d\n", tmult2(INT32_MIN/10, 5));
    printf("fourth calc %d\n", tmult2(INT32_MIN/25, 12));
}

/* Verifies if x and y can be multiplied without. Return 
1 if they can, 0 otherwise.*/
int tmult_ok(int x, int y) {
    // Cast x*y as int64_t from stdint.h header
    int64_t result = (int64_t) x*y;
    /* Cast result as int (32 bits) and verify if the value 
if the same as the 64 bit version*/
    return result == (int) result;
}

// Doesn't account for negative values.
int tmult2(int x, int y) { 
    // Cast x*y as int64_t
    int64_t pll = (int64_t) x*y;
    /* Realizes a right bitwise shift of 32 bits.
If it is zero, the multiplication can be done without overflow*/
/* For negative numbers this shift is not zero due sign extension.*/
return pll >> 32 == 0;
}
