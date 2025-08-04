
#include "../../inc/include.h"

#define TASK_SP_BASE 0x700a0000 
#define TASK_SP_SPACING 0x1000

const uint32_t tet_ticks = 30; 
uint32_t idle_ticks = tet_ticks; 

uint32_t ticks[TAREAS_MAX];
context tcb[TAREAS_MAX];
uint8_t id = 0;
uint8_t ids = 0;

__attribute__((section(".kernel_text"))) void scheduler(context* sp) {

  static uint32_t i = 1;

  i--;
  if (i == 0){
    if (id != 0)              //id 0 -> idle
      *(tcb+id-1) = *(sp);

    if (id == ids){
      if (idle_ticks == 0)
        id = 1;
      else id = 0;
    } else id++;

    if (id == 0) {
      *(sp - 1)->pc == __idle;
      i = idle_ticks;
      return;
    }

    *(sp) = *(tcb+id-1);
    i = *(ticks+id-1);

  }
  return;
}

__attribute__((section(".kernel_text"))) void scheduler_add(void (*ptr)(void), uint8_t tks) {
  if (ids==TAREAS_MAX) return;          //TODO err handling
  
  for (int i = 0; i < 13; i++){
    *(((tcb+ids)->r0a12) + i) = 0;
  }
  (tcb+ids)->sp = TASK_SP_BASE + (ids * TASK_SP_SPACING);     //FIXME: 
  (tcb+ids)->spsr = 0x4000011f;                               //FIXME: esto u otro valor qcyo
  (tcb+ids)->pc = ptr;
  (tcb+ids)->lr = scheduler_remove;     //when ptr() ends with BX LR it gets removed from scheuler

  ids++;
  ticks[ids] = tks;
  
  if (tks > idle_ticks)
    idle_ticks = 0;
  else
    idle_ticks -= tks;

  return;

}

__attribute__((section(".kernel_text"))) void scheduler_remove() {
  //por como esta armado el sch_add(), a esta funcion se entra si una task termina con BX LR, con el contexto de esa tarea cargado
  if (ids == 0) return;              //TODO err handling

  if (id != ids) {
    *(ticks+id-1) = *(ticks+ids-1);
    *(tcb+id-1) = *(tcb+ids-1);
  }

  ids--;

  int tks = 0;
  for (int i = 0; i < ids; i++)
    tks += *(ticks+i);
  if (tks > tet_ticks)
    idle_ticks = 0;
  else
    idle_ticks = tet_ticks - tks;
}