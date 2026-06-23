#include "../include/file_io.h"
#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  const char *db_path = "data/tasks.txt";
  Task minhas_tarefas[MAX_TASKS] = {0};
  int total = 0;

  printf("=== TESTE DA SPRINT 6: PERSISTÊNCIA EM DISCO (I/O) ===\n\n");

  /* 1. Criando dados na RAM */
  create_task(minhas_tarefas, &total, MAX_TASKS, "Dominar I/O em C",
              "fget e fprintf", 3);
  create_task(minhas_tarefas, &total, MAX_TASKS, "Tarefa sem Descricao", "",
              1); /* Testando o "-" */
  minhas_tarefas[0].status = STATUS_IN_PROGRESS;

  printf("-> 1. ESTADO ORIGINAL NA RAM ANTES DE SALVAR:\n");
  list_tasks(minhas_tarefas, total);

  /* 2. Gravando no SSD */
  printf("\n-> 2. Salvando dados em '%s'...\n", db_path);
  int res_save = save_tasks_to_file(minhas_tarefas, total, db_path);
  if (res_save == 0)
    printf("   [OK] Arquivo gravado com sucesso!\n");

  /* 3. SIMULANDO O APOCALIPSE (Limpando a RAM) */
  printf("\n-> 3. SIMULANDO QUEDA DE ENERGIA (Limpando a Stack de Memória)...");
  memset(minhas_tarefas, 0, sizeof(minhas_tarefas));
  total = 0;
  printf(" [MEMÓRIA ZERADA]\n");

  /* 4. A Ressurreição */
  printf("\n-> 4. Carregando dados do HD de volta para a RAM...\n");
  int res_load =
      load_tasks_from_file(minhas_tarefas, &total, MAX_TASKS, db_path);

  /* Tratando a variável res_load para eliminar o erro de compilação */
  if (res_load == 0) {
    printf("   [OK] Arquivo lido e desserializado com sucesso!\n");
  } else {
    printf("   [ERRO] Falha catastrófica ao ler o arquivo. Codigo: %d\n",
           res_load);
  }

  printf("\n-> 5. TABELA RECONSTRUÍDA A PARTIR DO DISCO RÍGIDO:\n");
  list_tasks(minhas_tarefas, total);

  return EXIT_SUCCESS;
}