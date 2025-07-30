
#include "../inc/gic.h"
#include "../inc/console_utils.h"

void __kernle_handler_irq(void );

__attribute__((section(".kernel_text"))) void __kernle_handler_irq() {

  _gicc_t* const GICC0 = (_gicc_t*)GICC0_ADDR;  //TODO: can this be moved to *.h?
  _gicd_t* const GICD0 = (_gicd_t*)GICD0_ADDR;

  uint32_t interrupt_id = (GICC0->IAR & 0x0000001FF);
  GICC0->EOIR = (interrupt_id & 0x0000001FF);
  
  #ifdef debug
    Printf("Interrupcion %d atendida",interrupt_id);
  #endif
  /*
  wtv goes here
  */ 

  //notif device
  
  return;
}