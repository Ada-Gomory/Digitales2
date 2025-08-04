#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../define.h"

#define TAREAS_MAX 4

void scheduler(context* sp);
void scheduler_add(void (*ptr)(void), uint8_t tks);
void scheduler_remove(void );

#endif