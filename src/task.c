#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/task.h"

int create_task(Task *tasks_array, int *current_count, int max_capacity, const char *title, const char *description, int priority) {
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
    new_task->title[sizeof(new_task->title) - 1] = '\0'; /* Tranca a string à força */

    if (description != NULL) {
        strncpy(new_task->description, description, sizeof(new_task->description) - 1);
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