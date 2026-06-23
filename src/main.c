#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    /* Alocando nosso "Banco de Dados em Memória" na Stack */
    Task minhas_tarefas[MAX_TASKS];
    int total_tarefas = 0;

    printf("=== TESTE DA SPRINT 2: MOTOR DE CADASTRO ===\n");

    /* Teste 1: Caminho Feliz */
    int res1 = create_task(minhas_tarefas, &total_tarefas, MAX_TASKS, "Estudar C", "Entender ponteiros", 3);
    if (res1 == 0) {
        printf("[OK] Tarefa 1 criada com sucesso! (Total de itens: %d)\n", total_tarefas);
        printf("     -> ID: %d | Titulo: '%s' | Prioridade: %d\n", 
               minhas_tarefas[0].id, minhas_tarefas[0].title, minhas_tarefas[0].priority);
    } else {
        printf("[ERRO] Falha no Teste 1. Codigo: %d\n", res1);
    }

    /* Teste 2: Inserir segunda tarefa para testar o incremento do ID */
    int res2 = create_task(minhas_tarefas, &total_tarefas, MAX_TASKS, "Pagar a Luz", "Vence dia 15", 2);
    if (res2 == 0) {
        printf("[OK] Tarefa 2 criada! (Total de itens: %d)\n", total_tarefas);
        printf("     -> ID: %d | Titulo: '%s'\n", 
               minhas_tarefas[1].id, minhas_tarefas[1].title);
    }

    /* Teste 3: Tentar criar tarefa sem titulo (O sistema TEM que barrar) */
    int res3 = create_task(minhas_tarefas, &total_tarefas, MAX_TASKS, "", "Descricao fantasma", 1);
    if (res3 == -3) {
        printf("[OK] Seguranca ativa: O sistema recusou uma tarefa sem titulo! (Erro -3 capturado)\n");
    } else {
        printf("[ALERTA CRITICO] O sistema aceitou uma tarefa com titulo vazio!\n");
    }

    return EXIT_SUCCESS;
}