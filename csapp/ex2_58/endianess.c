/* Function that returns 1 if the machine is littleendian and 0 if is bigendian.
It compares the first byte of the hexadecimal representation of 1 in the system
with the mask 1. If it is littleendian, the first byte should be 1, and the function
is_little_endian returns 1; otherwise, for bigendian systems, the last byte holds 1, 
and the first byte holds 00, so is_little_endian returns 0. 
*/

#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian(int value);

int main(int argc) {
    int x = 1;
    printf("%i",is_little_endian(x));
    return is_little_endian(x);
}

int is_little_endian(int value) {
    return ((byte_pointer) &value)[0];      
    // Carefull: it's necessary to use parentheses to cast &value to byte_pointer before indexing [0], 
    // as otherwise value[0] fails the compilation before anything else does anything.
}