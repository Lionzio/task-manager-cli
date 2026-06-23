#include "../include/task.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int create_task(Task *tasks_array, int *current_count, int max_capacity,
                const char *title, const char *description, int priority) {
  /* Regra A: Proteção rigorosa contra ponteiros nulos (Segurança) */
  if (tasks_array == NULL || current_count == NULL || title == NULL) {
    return -1;
  }

  /* Regra B: Verificação de estouro de memória */
  if (*current_count >= max_capacity) {
    return -2; /* Erro: Array lotado */
  }

  /* Regra C: O título não pode ser uma string vazia */
  if (title[0] == '\0') {
    return -3; /* Erro: Título vazio */
  }

  /* Capturando o endereço da struct exata que está livre no array */
  Task *new_task = &tasks_array[*current_count];

  /* Regra D: ID sequencial (1-based) */
  new_task->id = (*current_count) + 1;

  /* Regra E: Cópia cirúrgica de strings protegendo contra Buffer Overflow */
  strncpy(new_task->title, title, sizeof(new_task->title) - 1);
  new_task->title[sizeof(new_task->title) - 1] =
      '\0'; /* Tranca a string à força */

  if (description != NULL) {
    strncpy(new_task->description, description,
            sizeof(new_task->description) - 1);
    new_task->description[sizeof(new_task->description) - 1] = '\0';
  } else {
    new_task->description[0] = '\0';
  }

  /* Regra F: Higienização da prioridade (se o usuário passar 99, vira 1) */
  new_task->priority = (priority >= 1 && priority <= 3) ? priority : 1;

  /* Regra G: Estado inicial padrão */
  new_task->status = STATUS_TODO;

  /* Regra H: Carimbo de tempo UTC */
  new_task->created_at = time(NULL);

  /* Regra I: Incrementa a variável que mora lá na Stack da main() */
  (*current_count)++;

  return 0; /* Sucesso */
}

/* Funções estáticas: visíveis apenas dentro deste arquivo .c (Encapsulamento)
 */
static const char *get_priority_str(int priority) {
  switch (priority) {
  case 1:
    return "Baixa";
  case 2:
    return "Media";
  case 3:
    return "Alta";
  default:
    return "???";
  }
}

static const char *get_status_str(TaskStatus status) {
  switch (status) {
  case STATUS_TODO:
    return "[Pendente]";
  case STATUS_IN_PROGRESS:
    return "[Em Progresso]";
  case STATUS_DONE:
    return "[Concluido]";
  default:
    return "[Invalido]";
  }
}

void list_tasks(const Task *tasks_array, int count) {
  if (tasks_array == NULL)
    return;

  if (count == 0) {
    printf("+------------------------------------------------------------------"
           "--------------+\n");
    printf("|                 Nenhuma tarefa cadastrada no banco de dados.     "
           "              |\n");
    printf("+------------------------------------------------------------------"
           "--------------+\n");
    return;
  }

  /* Linha horizontal calculada pixel a pixel para fechar com as colunas */
  const char *hline = "+------+--------------------------------+----------+----"
                      "------------+------------+\n";

  printf("%s", hline);
  printf("| %-4s | %-30s | %-8s | %-14s | %-10s |\n", "ID", "Titulo",
         "Priorid.", "Status", "Data");
  printf("%s", hline);

  for (int i = 0; i < count; i++) {
    const Task *t = &tasks_array[i];

    /* Convertendo o carimbo UTC para uma string local legível */
    char date_str[11];
    struct tm *tm_info = localtime(&t->created_at);
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", tm_info);

    /* O segredo do alinhamento: %-30.30s significa "alinhe à esquerda, ocupe no
     * mínimo 30 espaços, e corte no 30º caractere" */
    printf("| %-4d | %-30.30s | %-8s | %-14s | %-10s |\n", t->id, t->title,
           get_priority_str(t->priority), get_status_str(t->status), date_str);
  }

  printf("%s", hline);
}

/* --- ADICIONE ESTE BLOCO AO FINAL DE src/task.c --- */

Task *find_task_by_id(Task *tasks_array, int count, int task_id) {
  if (tasks_array == NULL || count <= 0) {
    return NULL;
  }

  for (int i = 0; i < count; i++) {
    if (tasks_array[i].id == task_id) {
      return &tasks_array[i]; /* Retorna o endereço exato da struct na Stack */
    }
  }

  return NULL; /* Alvo não encontrado */
}

int update_task_status(Task *tasks_array, int count, int task_id,
                       TaskStatus new_status) {
  if (tasks_array == NULL || count <= 0) {
    return -1; /* Erro: Parâmetros inválidos */
  }

  Task *target = find_task_by_id(tasks_array, count, task_id);
  if (target == NULL) {
    return -2; /* Erro: Tarefa inexistente */
  }

  target->status = new_status;
  return 0; /* Mutação realizada com sucesso */
}