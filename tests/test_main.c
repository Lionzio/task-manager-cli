#include "../include/file_io.h"
#include "../include/task.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bateria 1: Validações de Domínio */
static void test_task_creation_validations(void) {
  Task lista[MAX_TASKS] = {0};
  int total = 0;

  /* Rejeição de ponteiro NULL */
  assert(create_task(NULL, &total, MAX_TASKS, "Titulo", "Desc", 1) == -1);

  /* Rejeição de título vazio */
  assert(create_task(lista, &total, MAX_TASKS, "", "Desc", 1) == -3);

  /* Criação de sucesso */
  assert(create_task(lista, &total, MAX_TASKS, "Tarefa Validacao", "Descricao",
                     2) == 0);
  assert(total == 1);
  assert(lista[0].id == 1);
  assert(lista[0].priority == 2);
  assert(lista[0].status == STATUS_TODO);
}

/* Bateria 2: Validações de Deslocamento de Memória */
static void test_task_deletion_shift(void) {
  Task lista[MAX_TASKS] = {0};
  int total = 0;

  create_task(lista, &total, MAX_TASKS, "T1", "D1", 1);
  create_task(lista, &total, MAX_TASKS, "T2", "D2", 2);
  create_task(lista, &total, MAX_TASKS, "T3", "D3", 3);
  assert(total == 3);

  /* Remoção do meio (ID 2) */
  assert(delete_task_by_id(lista, &total, 2) == 0);
  assert(total == 2);

  /* O ID 3 deve ter escorregado para o índice 1 */
  assert(lista[1].id == 3);
  assert(strcmp(lista[1].title, "T3") == 0);

  /* Tentativa de deleção de ID fantasma */
  assert(delete_task_by_id(lista, &total, 999) == -2);
}

/* Bateria 3: Camada de Persistência */
static void test_file_persistence(void) {
  const char *test_db = "data/test_persistence.txt";
  Task lista[MAX_TASKS] = {0};
  int total = 0;

  create_task(lista, &total, MAX_TASKS, "Persistir", "-", 3);
  assert(save_tasks_to_file(lista, total, test_db) == 0);

  /* Zerando a memória para testar recarga */
  memset(lista, 0, sizeof(lista));
  int recarregado_total = 0;

  assert(load_tasks_from_file(lista, &recarregado_total, MAX_TASKS, test_db) ==
         0);
  assert(recarregado_total == 1);
  assert(strcmp(lista[0].title, "Persistir") == 0);

  /* Limpeza do arquivo temporário de testes */
  remove(test_db);
}

int main(void) {
  printf("=== EXECUTANDO SUÍTE DE TESTES UNITÁRIOS (assert.h) ===\n");

  test_task_creation_validations();
  printf("  [PASSED] Validações de Domínio (Rejeição NULL e vazios)\n");

  test_task_deletion_shift();
  printf("  [PASSED] Mecanismo de Compactação e Shift Left\n");

  test_file_persistence();
  printf("  [PASSED] Motores de Serialização e Desserialização (I/O)\n\n");

  printf("-> SUÍTE APROVADA: O código está matematicamente seguro.\n");
  return EXIT_SUCCESS;
}