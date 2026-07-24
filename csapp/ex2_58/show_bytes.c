#include <stdio.h>

typedef unsigned char *byte_pointer;
int show_int(int x);
void show_float(float y);
void show_pointer(void *x);
void show_short(short x);
void show_long(long x);
void show_double(double x);

int main(int argc) {
    
    int x = 12345678;
    printf("%i\n", x & 1);
    float y = 234.;
    printf("x = \t %i\n", x);
    printf("Int: \t");
    show_int(x);
    printf("Float: \t");
    show_float(x);
    printf("Pointer:");
    show_pointer(&x);
    printf("Short: \t");
    show_short(x);
    printf("Long: \t");
    show_long(x);
    printf("Double:\t");
    show_double(x);
    return 0;
}
int show_bytes(byte_pointer start, size_t len) {
int i;
for (i = 0; i < len; i++)
printf(" %.2x", start[i]);
printf("\n");
return start[0];
}

int show_int(int x) {
return show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float y) {
show_bytes((byte_pointer) &y, sizeof(float));
}

void show_pointer(void *x) {
show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_short(short x) {
show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
show_bytes((byte_pointer) &x, sizeof(double));
}