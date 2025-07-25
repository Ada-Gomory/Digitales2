.global undef_handler
.global softirq_hanlder
.global pref_abort
.global data_abort
.global irq_handler
.global fiq_handler

.section text_hands
undef_handler:
  B .
  
softirq_hanlder:
  B .

pref_abort:
  B .

data_abort:
  B .  
  
irq_handler:
  SUB LR, LR, #4
  PUSH {R0-R12, LR}
  MOV R7, SP
  MRS R8, SPSR
  PUSH {R7, R8}

  MOV R0, SP
  BL kernel_handler_irq       //k_h_i(*sp);

  POP {R7, R8}
  MSR {SPSR, R8}
  MOV {SP, R7}
  LDMFD SP!, {RO-R12, PC}

fiq_handler:
  B .
