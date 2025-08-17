
#include "../../inc/include.h"

void __board_init(void );

__attribute__((section(".kernel_text"))) void __board_init() {
  __gic_init();
  __timer_init();
  __uart_init(0);
  __scheduler_init();
}

__attribute__((section(".kernel_text"))) void __idle() {
  idle:
    HALT_CPU_m;
  goto idle;     
}