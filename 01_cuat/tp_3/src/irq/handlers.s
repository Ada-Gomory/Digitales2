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

  STMFD SP!, {r0-r12, LR}         //

  MRS r9, SPSR   
  
  //TODO maybe add more SPs here
  CPS         #(0x13)              
  MOV r8, SP                      //Save SP_svc
  CPS         #(0x1f)                     
  MOV r7, SP                      //Save SP_sys
  CPS         #(0x12)             
  MOV r6, SP                      //Save SP_irq

  STMFD SP!, {r6-r9}                                                

  MOV r0, SP   
  BL __kernel_handler_irq         //k_h_i(*sp);
  MOV SP, r0

  LDMFD SP!, {r6-r9}     

  MOV SP, r6                      //Get SP_irq                        
  CPS         #(0x1f)                     
  MOV SP, r7                      //Get SP_sys
  CPS         #(0x13)                    
  MOV SP, r8                      //Get SP_svc
  CPS         #(0x12)             
            
  MSR SPSR, r9
  
  LDMFD SP!, {r0-r12, PC}^        //returns procesor in sys mode

/* Stack pointer structure on kernel_handler_irq call
  sp_irq    <- *sp (in r0)
  sp_sys
  sp_svc
  spsr
  r0        <- sp_irq que esta en el stack apunta aca
  ...
  r12
  lr
*/


fiq_handler:
  B __idle
.end
