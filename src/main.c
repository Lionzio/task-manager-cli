#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  Task minhas_tarefas[MAX_TASKS] = {0};
  int total = 0;

  printf("=== TESTE DA SPRINT 4: MUTAÇÃO DE ESTADO ===\n\n");

  /* Cadastrando 2 tarefas no estado padrão (STATUS_TODO = [Pendente]) */
  create_task(minhas_tarefas, &total, MAX_TASKS, "Estudar Modelagem de Banco",
              "Formas Normais", 3);
  create_task(minhas_tarefas, &total, MAX_TASKS, "Corrigir bug no Makefile",
              "Tabulacoes", 2);

  printf("-> ANTES DA MUTAÇÃO (Ambas devem estar [Pendente]):\n");
  list_tasks(minhas_tarefas, total);

  /* Disparando as mutações */
  printf("\n-> Aplicando mutações no Banco de Dados em Memória...\n");

  int res1 = update_task_status(minhas_tarefas, total, 1, STATUS_IN_PROGRESS);
  int res2 = update_task_status(minhas_tarefas, total, 2, STATUS_DONE);

  /* Testando a segurança contra um ID fantasma */
  int res_fantasma =
      update_task_status(minhas_tarefas, total, 999, STATUS_DONE);

  printf("\n-> DEPOIS DA MUTAÇÃO:\n");
  list_tasks(minhas_tarefas, total);

  printf("\n-> AUDITORIA DE CÓDIGOS DE RETORNO:\n");
  printf("   - Mutação ID 1 (Esperado 0): %d\n", res1);
  printf("   - Mutação ID 2 (Esperado 0): %d\n", res2);
  printf("   - Mutação ID Fantasma 999 (Esperado -2): %d\n", res_fantasma);

  return EXIT_SUCCESS;
}