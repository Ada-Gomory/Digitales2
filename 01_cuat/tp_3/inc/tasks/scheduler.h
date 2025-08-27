#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../define.h"

#define TET        30      // Tiempo de ejecucion total (segun enunciado)
#define TICKS_1    8       // Cantidad de ticks asignados para la task 1
#define TICKS_2    12      // Cantidad de ticks asignados para la task 2
#define TICKS_3    5       // Cantidad de ticks asignados para la task 3 t
#define TICKS_IDLE 5       // Cantidad de ticks asignados para la task 3 t

#define MAX_TASK   4  

void* scheduler(void* sp);
void __scheduler_init(void );

#endif