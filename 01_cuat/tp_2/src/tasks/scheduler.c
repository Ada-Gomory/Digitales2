
#include "../../inc/include.h"

#define TASK_SP_BASE 0x700a0000 
#define TASK_SP_SPACING 0x1000

extern uint32_t _TASK0_IRQ_STACK_INIT, _TASK0_SVC_STACK_INIT, _TASK0_SYS_STACK_INIT;
extern uint32_t _TASK1_IRQ_STACK_INIT, _TASK1_SVC_STACK_INIT, _TASK1_SYS_STACK_INIT;
extern uint32_t _TASK2_IRQ_STACK_INIT, _TASK2_SVC_STACK_INIT, _TASK2_SYS_STACK_INIT;
extern uint32_t _TASK3_IRQ_STACK_INIT, _TASK3_SVC_STACK_INIT, _TASK3_SYS_STACK_INIT;
    
uint32_t ticks[MAX_TASK];
task_t tcb[MAX_TASK];
uint8_t id = 0;
uint8_t ids = MAX_TASK;

#ifdef debug
  uint32_t i = 1;
#endif

__attribute__((section(".kernel_text"))) void* scheduler(void* sp) {

  #ifndef debug
    static uint32_t i = 1;
  #endif

  i--;
  if (i == 0){
    (tcb+id)->sp_irq = sp;

    id++;
    if (id==ids) id = 0;

    i = (tcb+id)->ticks;
  }
  return (tcb+id)->sp_irq;
}

__attribute__((section(".kernel_text"))) void __scheduler_init(void){
  (tcb+0)->ticks = TICKS_IDLE;
  (tcb+0)->ptr = __idle;
  (tcb+0)->sp_irq = (uint32_t* )_TASK0_IRQ_STACK_INIT;

  (tcb+1)->ticks = TICKS_1;
  (tcb+1)->ptr = task1;
  (tcb+1)->sp_irq = (uint32_t* )_TASK1_IRQ_STACK_INIT;

  (tcb+2)->ticks = TICKS_2;
  (tcb+2)->ptr = task2;
  (tcb+2)->sp_irq = (uint32_t* )_TASK2_IRQ_STACK_INIT;

  (tcb+3)->ticks = TICKS_3;
  (tcb+3)->ptr = task3;
  (tcb+3)->sp_irq = (uint32_t* )_TASK3_IRQ_STACK_INIT;

  *((tcb+0)->sp_irq) = (uint32_t) __idle; (tcb+0)->sp_irq--;          
  *((tcb+1)->sp_irq) = (uint32_t) task1;  (tcb+1)->sp_irq--; 
  *((tcb+2)->sp_irq) = (uint32_t) task2;  (tcb+2)->sp_irq--; 
  *((tcb+3)->sp_irq) = (uint32_t) task3;  (tcb+3)->sp_irq--; //lr

  for (int tsk = 0; tsk < MAX_TASK; tsk++){
    for (int i = 0; i < 12; i++){
      *((tcb+tsk)->sp_irq) = 0; (tcb+tsk)->sp_irq--;     //r0-r12
    }
    *((tcb+tsk)->sp_irq) = 0x1f; (tcb+tsk)->sp_irq--;    //spsr     
  }

  *((tcb+0)->sp_irq) = _TASK0_SVC_STACK_INIT; (tcb+0)->sp_irq--;          
  *((tcb+1)->sp_irq) = _TASK1_SVC_STACK_INIT;  (tcb+1)->sp_irq--; 
  *((tcb+2)->sp_irq) = _TASK2_SVC_STACK_INIT;  (tcb+2)->sp_irq--; 
  *((tcb+3)->sp_irq) = _TASK3_SVC_STACK_INIT;  (tcb+3)->sp_irq--; //sp_svc

  *((tcb+0)->sp_irq) = _TASK0_SYS_STACK_INIT; (tcb+0)->sp_irq--;          
  *((tcb+1)->sp_irq) = _TASK1_SYS_STACK_INIT;  (tcb+1)->sp_irq--; 
  *((tcb+2)->sp_irq) = _TASK2_SYS_STACK_INIT;  (tcb+2)->sp_irq--; 
  *((tcb+3)->sp_irq) = _TASK3_SYS_STACK_INIT;  (tcb+3)->sp_irq--; //sp_sys

  *((tcb+0)->sp_irq) = (uint32_t)(tcb+0)->sp_irq+3; (tcb+0)->sp_irq--;          
  *((tcb+1)->sp_irq) = (uint32_t)(tcb+0)->sp_irq+3;  (tcb+1)->sp_irq--; 
  *((tcb+2)->sp_irq) = (uint32_t)(tcb+0)->sp_irq+3;  (tcb+2)->sp_irq--; 
  *((tcb+3)->sp_irq) = (uint32_t)(tcb+0)->sp_irq+3;  (tcb+3)->sp_irq--; //sp_irq

}