#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  /* O pulo do gato: '= {0}' garante que todos os 22.000 bytes do vetor nasçam
   * como ZERO limpo */
  Task minhas_tarefas[MAX_TASKS] = {0};
  int total = 0;

  printf("=== TESTE DA SPRINT 3: MOTOR DE LISTAGEM ASCII ===\n\n");

  /* Teste A: Comportamento com a lista vazia */
  printf("-> CENARIO A: Imprimindo banco de dados vazio:\n");
  list_tasks(minhas_tarefas, total);
  printf("\n");

  /* Populando com dados variados */
  create_task(minhas_tarefas, &total, MAX_TASKS, "Configurar Neovim",
              "Instalar LSP de C", 3);
  create_task(minhas_tarefas, &total, MAX_TASKS, "Comprar Cafe moido",
              "Grao 100% Arabica", 1);

  /* Teste B de Estresse: Um título gigante que tentará quebrar a tabela! */
  create_task(
      minhas_tarefas, &total, MAX_TASKS,
      "Ler a especificacao do POSIX sobre manipulacao de arquivos no Linux",
      "Capitulo 4", 2);

  /* Simulando que a segunda tarefa já foi iniciada */
  minhas_tarefas[1].status = STATUS_IN_PROGRESS;

  printf("-> CENARIO B: Imprimindo tabela com %d itens:\n", total);
  list_tasks(minhas_tarefas, total);

  return EXIT_SUCCESS;
}