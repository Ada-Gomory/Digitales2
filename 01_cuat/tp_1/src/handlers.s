.extern __kernle_handler_irq
.extern __idle
.global undef_handler
.global softirq_hanlder
.global pref_abort
.global data_abort
.global irq_handler
.global fiq_handler
.code 32
.section .handlers

undef_handler:
  B __idle
  
softirq_hanlder:
  B __idle

pref_abort:
  B __idle

data_abort:
  B __idle
  
irq_handler:
  SUB LR, LR, #4
  STMFD SP!, {R0-R12, LR}
  MOV R7, SP
  MRS R8, CPSR                  //MRS R8, SPSR causes undef exep FIXME: maybe, perhaps this is fine idfk
  PUSH {R7, R8}                                                //NOTE: prolly it's me testing this by doing BL 0x18

  MOV R0, SP
  BL __kernel_handler_irq       //k_h_i(*sp);


  POP {R7, R8}
  MSR CPSR, R8                  //MSR SPSR, R8 causes undef exep
  MOV SP, R7
  LDMFD SP!, {R0-R12, PC}

fiq_handler:
  B __idle
.end
