
#include "../../inc/include.h"

void __board_init(void );

__attribute__((section(".kernel_text"))) void __board_init() {
  __gic_init();
  __timer_init();
  scheduler_add(tarea1, 8);
  scheduler_add(tarea2, 12);
  scheduler_add(tarea3, 5);
}

__attribute__((section(".kernel_text"))) void __idle() {
  idle:
    HALT_CPU_m;
  goto idle;     
}