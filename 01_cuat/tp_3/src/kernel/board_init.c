
#include "../../inc/include.h"

#ifdef debug
  extern uint32_t _TASK0_IRQ_STACK_INIT, _TASK0_SVC_STACK_INIT, _TASK0_SYS_STACK_INIT;
  extern uint32_t _TASK1_IRQ_STACK_INIT, _TASK1_SVC_STACK_INIT, _TASK1_SYS_STACK_INIT;
  extern uint32_t _TASK2_IRQ_STACK_INIT, _TASK2_SVC_STACK_INIT, _TASK2_SYS_STACK_INIT;
  extern uint32_t _TASK3_IRQ_STACK_INIT, _TASK3_SVC_STACK_INIT, _TASK3_SYS_STACK_INIT;
      
  extern uint32_t _IRQ_STACK_INIT;  
  extern uint32_t _FIQ_STACK_INIT;  
  extern uint32_t _SVC_STACK_INIT;  
  extern uint32_t _ABORT_STACK_INIT;  
  extern uint32_t _UNDEF_STACK_INIT;  
  extern uint32_t _SYSTEM_STACK_INIT;  
#endif

void __board_init(void ); //TODO move to appt .h

__attribute__((section(".kernel_text"))) void __board_init() {
  __uart_init(0);

  #ifdef debug
    Printf("IRQ\t%x\n", &_IRQ_STACK_INIT);
    Printf("FIQ\t%x\n", &_FIQ_STACK_INIT);
    Printf("SVC\t%x\n", &_SVC_STACK_INIT);
    Printf("ABORT\t%x\n", &_ABORT_STACK_INIT);
    Printf("UNDEF\t%x\n", &_UNDEF_STACK_INIT);
    Printf("SYSTEM\t%x\n", &_SYSTEM_STACK_INIT);
    Printf("\tIRQ\t\tSVC\t\tSYS\n");
    Printf("Task0\t%x\t%x\t%x\n", &_TASK0_IRQ_STACK_INIT, &_TASK0_SVC_STACK_INIT, &_TASK0_SYS_STACK_INIT);
    Printf("Task1\t%x\t%x\t%x\n", &_TASK1_IRQ_STACK_INIT, &_TASK1_SVC_STACK_INIT, &_TASK1_SYS_STACK_INIT);
    Printf("Task2\t%x\t%x\t%x\n", &_TASK2_IRQ_STACK_INIT, &_TASK2_SVC_STACK_INIT, &_TASK2_SYS_STACK_INIT);
    Printf("Task3\t%x\t%x\t%x\n", &_TASK3_IRQ_STACK_INIT, &_TASK3_SVC_STACK_INIT, &_TASK3_SYS_STACK_INIT);
    #endif//*/
    __timer_init();
    __gic_init();
    __scheduler_init();
}

__attribute__((section(".kernel_text"))) void __idle() { //TODO move to appt .c
  idle:
    HALT_CPU_m;
  goto idle;     
}

//TODO move to oppt .c
__attribute__((section(".kernel_text"))) void printf_usr(char* s, uint32_t d) { //TODO variable args for printf
  //Printf(s,d); return;
  //ensure the vars in the register I want (gcc should do this but ⁻\_('_')_/⁻ )
  register char* r0 asm("r0") = s;
  register uint32_t r1 asm("r1") = d;  
  
  asm volatile(
    "SVC #2"
    ::
    //"r"(data_r1),"r"(data_r2)/*in*/
    "r"(r0),"r"(r1)/*in*/
  );

  return;
}