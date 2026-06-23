#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* Como ativamos a flag -Werror, se declararmos argc/argv e não usarmos, 
       o compilador trata o 'warning' como erro fatal. 
       Fazer um cast para (void) é a técnica padrão em C para dizer: "Eu sei que está aqui". */
    (void)argc;
    (void)argv;

    printf("Task Manager CLI v0.1.0 - [Build: PASSED] Motor de compilação operacional.\n");
    return EXIT_SUCCESS;
}