#ifndef TASK_H
#define TASK_H

#include <time.h>

/**
 * @enum TaskStatus
 * @brief Representa o estado de progresso de uma tarefa.
 */
typedef enum {
  STATUS_TODO = 0,    /**< Tarefa pendente / aguardando execução */
  STATUS_IN_PROGRESS, /**< Tarefa sendo executada no momento */
  STATUS_DONE         /**< Tarefa finalizada */
} TaskStatus;

/**
 * @struct Task
 * @brief Entidade central de domínio que define uma Tarefa no sistema.
 */
typedef struct {
  int id;         /**< Identificador único sequencial */
  char title[50]; /**< Título curto (máximo de 49 caracteres + \0) */
  char
      description[150]; /**< Detalhamento da tarefa (máx 149 caracteres + \0) */
  int priority;      /**< Nível de urgência: 1 (Baixa), 2 (Média), 3 (Alta) */
  TaskStatus status; /**< Estado atual da tarefa */
  time_t created_at; /**< Timestamp UTC de quando a tarefa nasceu */
} Task;

#define MAX_TASKS 100

int create_task(Task *tasks_array, int *current_count, int max_capacity,
                const char *title, const char *description, int priority);
void list_tasks(const Task *tasks_array, int count);

Task *find_task_by_id(Task *tasks_array, int count, int task_id);
int update_task_status(Task *tasks_array, int count, int task_id,
                       TaskStatus new_status);

/* A LINHA QUE FALTAVA: Assinatura do contrato para o main.c poder enxergar */
int delete_task_by_id(Task *tasks_array, int *current_count, int task_id);

#endif /* TASK_H */