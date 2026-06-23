#include "../include/file_io.h"
#include "../include/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Painel de Ajuda Profissional (Exibido quando o usuário digita errado ou pede
 * help) */
static void print_usage(const char *prog_name) {
  printf("=================================================================\n");
  printf("                    TASK MANAGER CLI v1.0                        \n");
  printf("=================================================================\n");
  printf("Uso: %s <comando> [argumentos]\n\n", prog_name);
  printf("Comandos disponiveis:\n");
  printf("  list                         Lista todas as tarefas abertas\n");
  printf("  add <titulo> <desc> <prior>  Cadastra uma nova tarefa (Priorid: "
         "1=Baixa, 2=Media, 3=Alta)\n");
  printf("  done <id>                    Marca a tarefa especificada como "
         "[Concluido]\n");
  printf("  delete <id>                  Remove a tarefa permanentemente do "
         "disco\n");
  printf("=================================================================\n");
}

int main(int argc, char *argv[]) {
  const char *db_path = "data/tasks.txt";
  Task minhas_tarefas[MAX_TASKS] = {0};
  int total = 0;

  /* 1. O RITO DE INICIALIZAÇÃO: Sempre carrega o estado do disco para a RAM
   * primeiro */
  int res_load =
      load_tasks_from_file(minhas_tarefas, &total, MAX_TASKS, db_path);
  if (res_load != 0) {
    printf("[ERRO CRÍTICO] Falha ao ler o banco de dados em '%s'.\n", db_path);
    return EXIT_FAILURE;
  }

  /* 2. Validação de Argumentos: Se rodou o .exe sozinho, exibe o painel de uso
   */
  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_SUCCESS;
  }

  /* Capturando o comando principal (ex: "add", "list", "done") */
  const char *command = argv[1];

  /* =========================================================================
   */
  /* ROTEADOR DE TRÁFEGO (CLI PARSER)                      */
  /* =========================================================================
   */

  if (strcmp(command, "list") == 0) {
    list_tasks(minhas_tarefas, total);
  } else if (strcmp(command, "add") == 0) {
    /* Blindagem contra falta de parâmetros */
    if (argc < 5) {
      printf("[ERRO] Argumentos insuficientes para o comando 'add'.\n\n");
      printf("Exemplo correto:\n");
      printf("  %s add \"Comprar Cafe\" \"Grao 100%% Arabica\" 3\n", argv[0]);
      return EXIT_FAILURE;
    }

    const char *title = argv[2];
    const char *desc = argv[3];
    int priority = atoi(argv[4]); /* Converte a string "3" para o inteiro 3 */

    int res_create =
        create_task(minhas_tarefas, &total, MAX_TASKS, title, desc, priority);
    if (res_create == 0) {
      /* Se a RAM aceitou, joga imediatamente para o SSD */
      if (save_tasks_to_file(minhas_tarefas, total, db_path) == 0) {
        printf("[OK] Tarefa '%s' cadastrada com sucesso! (ID: %d)\n", title,
               total);
      } else {
        printf("[ERRO] Tarefa criada na RAM, mas falhou ao salvar no arquivo "
               ".txt!\n");
      }
    } else {
      printf("[ERRO] Falha nas regras de negócio ao criar tarefa. Codigo: %d\n",
             res_create);
    }
  } else if (strcmp(command, "done") == 0) {
    if (argc < 3) {
      printf("[ERRO] Faltou informar o ID da tarefa.\n");
      printf("Uso correto: %s done <id>\n", argv[0]);
      return EXIT_FAILURE;
    }

    int id = atoi(argv[2]);
    int res_up = update_task_status(minhas_tarefas, total, id, STATUS_DONE);
    if (res_up == 0) {
      save_tasks_to_file(minhas_tarefas, total, db_path);
      printf("[OK] Tarefa ID %d marcada como [Concluido]!\n", id);
    } else {
      printf("[ERRO] Nenhuma tarefa pendente encontrada com o ID %d.\n", id);
    }
  } else if (strcmp(command, "delete") == 0) {
    if (argc < 3) {
      printf("[ERRO] Faltou informar o ID da tarefa a ser ceifada.\n");
      printf("Uso correto: %s delete <id>\n", argv[0]);
      return EXIT_FAILURE;
    }

    int id = atoi(argv[2]);
    int res_del = delete_task_by_id(minhas_tarefas, &total, id);
    if (res_del == 0) {
      save_tasks_to_file(minhas_tarefas, total, db_path);
      printf("[OK] Tarefa ID %d removida permanentemente do disco!\n", id);
    } else {
      printf("[ERRO] Falha ao deletar. O ID %d nao existe no banco de dados.\n",
             id);
    }
  } else {
    printf("[ERRO] Comando '%s' desconhecido.\n\n", command);
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}