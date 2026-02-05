// Example of utilization of switch selection statement.
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./%s <option char>\n", argv[0]);
        return 1;
    }
    // char arg = malloc(sizeof(char));
    // arg = argv[1][0];
    char arg = argv[1][0];
    if (arg == NULL)
    {
        printf("Error whent trying to set option");
        return 1;
    } 
    // This if statement has the same function as the switch afterwards.
    /*
    if (arg == 'm') {
        puts("this is a magpie");
    } else if (arg == 'r') {
        puts("this is a raven");
    } else if (arg == 'j') {
        puts("this is a jay");
    } else if (arg == 'c') {
        puts("this is a chough");
    } else {
        puts("this is an unknown corvid");
    }
    */
    /* If one break is removed, then the next case is executed aswell
    until either the end of the switch or the one break statement is found*/
    switch (arg) {
    case 'm' : puts("this is a magpie");
               break;
    case 'r' : puts("this is a raven");
               break;
    case 'j' : puts("this is a jay");
               break;
    case 'c' : puts("this is a chough");
               break;
    default: puts("this is an unknown corvid");
    }
    return 0;

}