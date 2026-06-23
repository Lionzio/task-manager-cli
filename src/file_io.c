#include "../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save_tasks_to_file(const Task *tasks_array, int count,
                       const char *filepath) {
  if (tasks_array == NULL || filepath == NULL)
    return -1;

  FILE *file = fopen(filepath, "w");
  if (file == NULL)
    return -2; /* Erro de permissão ou caminho */

  for (int i = 0; i < count; i++) {
    const Task *t = &tasks_array[i];

    /* Proteção contra o buraco do strtok */
    const char *desc = (t->description[0] == '\0') ? "-" : t->description;

    /* %lld garante que o time_t caiba mesmo em Windows 64 bits */
    fprintf(file, "%d|%s|%s|%d|%d|%lld\n", t->id, t->title, desc, t->priority,
            (int)t->status, (long long)t->created_at);
  }

  fclose(file);
  return 0;
}

int load_tasks_from_file(Task *tasks_array, int *count, int max_capacity,
                         const char *filepath) {
  if (tasks_array == NULL || count == NULL || filepath == NULL)
    return -1;

  *count = 0;
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    return 0; /* Banco de dados virgem. Retorna sucesso com 0 itens. */
  }

  char line[512];
  while (fgets(line, sizeof(line), file) != NULL) {
    if (*count >= max_capacity)
      break;

    /* Aniquila o \n ou \r\n do Windows do final da string */
    line[strcspn(line, "\r\n")] = '\0';
    if (line[0] == '\0')
      continue;

    Task t = {0};

    char *token = strtok(line, "|");
    if (!token)
      continue;
    t.id = atoi(token);

    token = strtok(NULL, "|");
    if (!token)
      continue;
    strncpy(t.title, token, sizeof(t.title) - 1);

    token = strtok(NULL, "|");
    if (!token)
      continue;
    if (strcmp(token, "-") != 0) {
      strncpy(t.description, token, sizeof(t.description) - 1);
    } else {
      t.description[0] = '\0'; /* Era vazia, restaura o vazio */
    }

    token = strtok(NULL, "|");
    if (!token)
      continue;
    t.priority = atoi(token);

    token = strtok(NULL, "|");
    if (!token)
      continue;
    t.status = (TaskStatus)atoi(token);

    token = strtok(NULL, "|");
    if (!token)
      continue;
    t.created_at = (time_t)atoll(token);

    tasks_array[*count] = t;
    (*count)++;
  }

  fclose(file);
  return 0;
}