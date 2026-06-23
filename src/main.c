#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  Task minhas_tarefas[MAX_TASKS] = {0};
  int total = 0;

  printf("=== TESTE DA SPRINT 5: O CEIFADOR DE MEMÓRIA ===\n\n");

  /* Criando 3 tarefas sequenciais */
  create_task(minhas_tarefas, &total, MAX_TASKS, "Comprar Cafe", "Grao moido",
              1);
  create_task(minhas_tarefas, &total, MAX_TASKS, "Estudar Alocacao",
              "Ponteiros", 3);
  create_task(minhas_tarefas, &total, MAX_TASKS, "Pagar Boleto", "Faculdade",
              2);

  printf("-> CENÁRIO 1: Lista original com 3 itens:\n");
  list_tasks(minhas_tarefas, total);

  /* O teste de fogo: Vamos deletar a do MEIO (ID 2).
     Se o shift left falhar, a tabela vai quebrar ou duplicar itens. */
  printf("\n-> Executando Ceifador no ID 2 ('Estudar Alocacao')...\n");
  int res_del = delete_task_by_id(minhas_tarefas, &total, 2);

  printf("\n-> CENÁRIO 2: Lista após a deleção (Esperado: IDs 1 e 3 | Total: 2 "
         "itens):\n");
  list_tasks(minhas_tarefas, total);

  /* Testando a resiliência contra um ID fantasma */
  int res_fantasma = delete_task_by_id(minhas_tarefas, &total, 888);

  printf("\n-> AUDITORIA DE RETORNO:\n");
  printf("   - Status Delecao ID 2 (Esperado 0): %d\n", res_del);
  printf("   - Status Delecao ID 888 (Esperado -2): %d\n", res_fantasma);

  return EXIT_SUCCESS;
}