
#include "../../inc/include.h" 

void* __kernel_handler_irq(void* sp); //TODO move to app .h
void* __kernel_handler_swi(const void* sp, int code);  //NOTE prolly unncesary tu return sp

extern _gicc_t* const GICC0; 
extern _timer_t* const TIMER0;

#ifdef debug
  extern uint32_t iter;
  extern int8_t id;
#endif

__attribute__((section(".kernel_text"))) void* __kernel_handler_irq(void* sp) {

  uint32_t interrupt_id = (GICC0->IAR & 0x0000001FF);
  GICC0->EOIR = (interrupt_id & 0x0000001FF);

  if (interrupt_id == 36) {
    TIMER0->Timer1IntClr = 0x01;
    sp = scheduler(sp);                   //sp -= sizeof(context);
  }

  #ifdef debug
    Printf("Task %d, tick %d\n",id, iter);
  #endif
  
  return sp;
}

__attribute__((section(".kernel_text")))void* __kernel_handler_swi(const void* sp, int code) {
  /* Stack pointer structure on kernel_handler_irq call
    sp_svc   <-*sp
    spsr     <-*(sp+1)
    ..rX..   <-*(sp+2+X)
    lr       <-*(sp+15)
  */

  if (code == 2){
    char*s = (char*)(*(((uint32_t* )sp)+2));  //more fun pointer bs
    uint32_t d = *(((uint32_t* )sp)+3);       //(to get r0 and r1)

    Printf(s, d);
  }

  return sp;
}