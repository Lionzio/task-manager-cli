#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h" /* Importando o contrato que você acabou de criar */

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    /* Declarando uma variável 't' do tipo Task na Stack (Pilha de memória) */
    Task t;

    /* Populando a struct para testar se os tipos batem com o contrato */
    t.id = 1001;
    t.priority = 3;
    t.status = STATUS_TODO;

    printf("Task Manager CLI v0.1.0\n");
    printf("-> Contrato de Dominio (task.h) validado com sucesso!\n");
    printf("-> Teste de Atribuicao: ID %d | Prioridade %d | Status %d\n", t.id, t.priority, t.status);
    
    /* O %zu é o formatador nativo do C99 para o tipo 'size_t' devolvido pelo sizeof() */
    printf("-> Tamanho da struct 'Task' em memoria: %zu bytes.\n", sizeof(Task));

    return EXIT_SUCCESS;
}