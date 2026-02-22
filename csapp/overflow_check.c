#include <stdio.h>

int uadd_ok(unsigned x, unsigned y);

void main(){
    printf("first: %d", uadd_ok(999999999999999, 999999999999999));
    printf("second: %d", uadd_ok(999999999999, 999999999999999));
    printf("third: %d", uadd_ok(9, 9999));

}



int uadd_ok(unsigned x, unsigned y)
{
    unsigned sum = x + y;
    if (sum < x)
        return 1;
    else
        return 0;

    /* Resposta do livro.*/ 
    //return sum >= x;
}

