#include <stdio.h>
#include <stdint.h>

int tadd_ok(int x, int y);

int main(void)
{
    printf("result = %i\n", tadd_ok(1, 1));
    printf("result = %i\n", tadd_ok(100000, 100000));
    printf("result = %i\n", tadd_ok(INT32_MAX/2, INT32_MAX));
    printf("result = %i\n", tadd_ok(-121, -1123));
    printf("result = %i\n", tadd_ok(INT32_MIN/2, INT32_MIN));
}


int tadd_ok(int x, int y)
{
    int sum = x + y;
    printf("x = %i, y = %i, sum = %i\n", x, y, sum);
    if ((x < 0 && y < 0 && sum >= 0) || (x >= 0 && y >= 0 && sum < 0))
    {
        printf("Overflow\n");
        return 0;
    }
    else
    {
        printf("No overflow\n");
        return 1;
    }

    /* Resposta do livro*/
    // int sum = x+y;
    // int neg_over = x < 0 && y < 0 && sum >= 0;
    // int pos_over = x >= 0 && y >= 0 && sum < 0;
    // return !neg_over && !pos_over;

}