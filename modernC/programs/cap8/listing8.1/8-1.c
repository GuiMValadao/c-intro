#include<stdio.h>

/* Atrasa a execução com algum código grosseiro*/

void delay(double secs) {
    double const magic = 4E8;
    unsigned long long const nano = secs * magic;
    for (unsigned long volatile count = 0;
        count < nano;
        ++count) {
            /* Nada aqui */
        }
}

int main(int argc, char* argv[]) {
    fputs("Esperando 10 segundos para você me interromper", stdout);
    if (argc < 3) fflush(stdout);
    for (unsigned i = 0; i < 10; ++i) {
        fputc(' .', stdout);
        if (argc < 2) fflush(stdout);
        delay(1.0);
    }
    fputs("\n", stdout);
    fputs("Você me ignorou, então tchau\n", stdout);
}