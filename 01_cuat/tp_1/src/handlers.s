.global undef_handler
.global softirq_hanlder
.global pref_abort
.global data_abort
.global irq_handler
.global fiq_handler
.global idle
.code 32


.section .handlers

idle: 
  WFI
  B idle

undef_handler:
  B idle
  
softirq_hanlder:
  B idle

pref_abort:
  B idle

data_abort:
  B idle
  
irq_handler:
  SUB LR, LR, #4
  STMFD SP!, {R0-R12, LR}
  MOV R7, SP
  MRS R8, SPSR
  PUSH {R7, R8}

  MOV R0, SP
  //BL kernel_handler_irq       //k_h_i(*sp);

  POP {R7, R8}
  MSR SPSR, R8
  MOV SP, R7
  LDMFD SP!, {R0-R12, PC}

fiq_handler:
  B idle
.end
