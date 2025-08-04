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
  STMFD SP!, {R0-R12, LR}         //
  MOV R8, SP
  MRS R7, SPSR 

  MSR cpsr_c, #(0xdf)             //        
  MOV R5, LR
  MOV R6, SP 
  MSR cpsr_c, #(0xd2)             //Guardo LR_sys y SP_sys

  PUSH {R5-R8}                                                

  MOV R0, SP   
  BL __kernel_handler_irq         //k_h_i(*sp);

  POP {R5-R8}

  MSR cpsr_c, #(0xdf)             //Seteo LR_sys y SP_sys
  MOV LR, R5
  MOV SP, R6                      //FIXME: no se si es necesario guardar SP_irq ademas de SP_sys
  MSR cpsr_c, #(0xd2)             //anyhow i still need LR_sys and LR_irq for task_LR and TASK_PC

  MSR SPSR, R7                
  MOV SP, R8
  MSR cpsr_c, #(0x1f)             //Enable irqs; exist irq mode
  LDMFD SP!, {R0-R12, PC}

fiq_handler:
  B __idle
.end
