#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    size_t const len = strlen(argv[0]); //Computa o comprimento
    printf("arg size is: %zi\n", len);
    
    // Não funciona com o compilador do VSCode, pode ser que seja funcional apenas com C23
    //char name[len + 1] = { };
    char name[20];

    // Copia o nome do programa
    memcpy(name, argv[0], len);
    if (!strcmp(name, argv[0])) {
        printf("program name \"%s\" successfully copied\n", name);
    } else {
        printf("Copying %s leads to different string %s\n", argv[0], name);
    }
}