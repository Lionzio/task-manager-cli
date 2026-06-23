#ifndef FILE_IO_H
#define FILE_IO_H

#include "../include/task.h"

int save_tasks_to_file(const Task *tasks_array, int count,
                       const char *filepath);
int load_tasks_from_file(Task *tasks_array, int *count, int max_capacity,
                         const char *filepath);

#endif /* FILE_IO_H */