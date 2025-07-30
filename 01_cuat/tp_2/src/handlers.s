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
  MRS R8, SPSR                  
  PUSH {R7, R8}                                                

  MOV R0, SP
  BL __kernel_handler_irq       //k_h_i(*sp);

  POP {R7, R8}
  MSR SPSR, R8                
  MOV SP, R7
  MSR cpsr_c, #(0x1f)             //Enable irqs
  LDMFD SP!, {R0-R12, PC}

fiq_handler:
  B __idle
.end
