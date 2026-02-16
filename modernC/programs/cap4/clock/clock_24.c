#include <stdio.h>

int main(void)
{
    size_t clock_size = 24;             // Clock size: 24, could be 12
    size_t a = 18, b = 10;              // a: current time, b: elapsed time
    size_t hour = (a + b) % clock_size; // final time

    printf("It's %zu o'clock!", hour);  // outputs result

}