    #include<stdio.h>
    
    struct test1 {
        unsigned char a;
        unsigned b;
        unsigned long long c;
    };

    struct test2 {
        unsigned char a;
        unsigned long long c;
        unsigned b;
    };

    struct test3 {
        unsigned b;
        unsigned char a;
        unsigned long long c;
    };

    struct test4 {
        unsigned b;        
        unsigned long long c;
        unsigned char a;
    };

    struct test5 {
        unsigned long long c;
        unsigned char a;
        unsigned b;
    };

    struct test6 {
        unsigned long long c;
        unsigned b;
        unsigned char a;        
    };

void main(){
    struct test1 first = {
        .a = 'a',
        .b = 1,
        .c = 2,
    };
    struct test2 second = {
        .a = 'a',
        .b = 1,
        .c = 2,
    };
    struct test3 third = {
        .a = 'a',
        .b = 1,
        .c = 2,
    };
    struct test4 fourth = {
        .a = 'a',
        .b = 1,
        .c = 2,
    };
    struct test5 fifth= {
        .a = 'a',
        .b = 1,
        .c = 2,    
    };
    struct test6 sixth = {
        .a = 'a',
        .b = 1,
        .c = 2,
    };
    printf("Size of the full structures:\n");
    printf("-------------------------\n");
    printf("size 1: %zu\n", sizeof(first));     //16
    printf("size 2: %zu\n", sizeof(second));    //24
    printf("size 3: %zu\n", sizeof(third));     //16
    printf("size 4: %zu\n", sizeof(fourth));    //24
    printf("size 5: %zu\n", sizeof(first));     //16
    printf("size 6: %zu\n", sizeof(first));     //16

    printf("Sum of the size of the each element:\n");
    printf("-------------------------\n");      // all same, 13
    printf("size 1: %zu\n", sizeof(first.a)+sizeof(first.b)+sizeof(first.c));
    printf("size 2: %zu\n", sizeof(second.a)+sizeof(second.b)+sizeof(second.c));
    printf("size 3: %zu\n", sizeof(third.a)+sizeof(third.b)+sizeof(third.c));
    printf("size 4: %zu\n", sizeof(fourth).a+sizeof(fourth.b)+sizeof(fourth.c));
    printf("size 5: %zu\n", sizeof(fifth.a)+sizeof(fifth.b)+sizeof(fifth.c));
    printf("size 6: %zu\n", sizeof(sixth.a)+sizeof(sixth.b)+sizeof(sixth.c));
}