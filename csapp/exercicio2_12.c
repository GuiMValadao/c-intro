#include <stdio.h>

int main(int argc)
{
    int x = 0x87654321;
    printf("x: %.8x\n", x);
    int mask1 = 0xff;
    int mask1x = x & mask1;
    printf("A: %.8x\n", mask1x);    // 00000021

    int mask2 = x ^ ~mask1;
    printf("B: %.8x\n", mask2);     // 789abc21

    int mask3 = x | mask1; 
    printf("C: %.8x\n", mask3);     // 876543ff

}