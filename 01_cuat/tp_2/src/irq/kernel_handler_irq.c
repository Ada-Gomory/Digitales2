
#include "../../inc/include.h"

void* __kernel_handler_irq(void* sp);

extern _gicc_t* const GICC0; 
extern _timer_t* const TIMER0;

#ifdef debug
  extern uint32_t iter;
  extern int8_t id;
  extern  int int_global1;
  extern  int int_global2;
#endif

__attribute__((section(".kernel_text"))) void* __kernel_handler_irq(void* sp) {

  uint32_t interrupt_id = (GICC0->IAR & 0x0000001FF);
  GICC0->EOIR = (interrupt_id & 0x0000001FF);

  if (interrupt_id == 36) {
    TIMER0->Timer1IntClr = 0x01;
    sp = scheduler(sp);                   //sp -= sizeof(context);
  }

  #ifdef debug
    Printf("Task %d, tick %d\t\t globals: %d & %d\n",id, iter, int_global1, int_global2);
  #endif
  
  return sp;
}