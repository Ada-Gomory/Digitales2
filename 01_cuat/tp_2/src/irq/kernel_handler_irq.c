
#include "../../inc/include.h"

void __kernel_handler_irq(void* sp);

extern _gicc_t* const GICC0; 

__attribute__((section(".kernel_text"))) void __kernel_handler_irq(void* sp) {

  uint32_t interrupt_id = (GICC0->IAR & 0x0000001FF);
  GICC0->EOIR = (interrupt_id & 0x0000001FF);
  
  #ifdef debug
    Printf("Interrupcion %d atendida\n",interrupt_id);
  #endif

  if (interrupt_id = 36) {
    sp -= 4; //two pos down; scheduler doesnt modify SP_irq
    scheduler(((context*) sp) - 1);  //sp -= sizeof(context);
  }

  4+4;
  
  return;
}