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

  STMFD SP!, {r0-r12, LR}   
  MRS r9, SPSR
  MOV r8, SP                      //Save SP_svc

  STMFD SP!, {r8-r9}              

  //detect svc call nro and put it on r1
  LDR r1, [LR, #-4]                           
  BIC r1, r1, #0xFF000000

  MOV r0, SP
  BL __kernel_handler_swi         //k_h_s(*sp, code);
  MOV SP, r0

  LDMFD SP!, {r8-r9}     

  MOV SP, r8  
  MSR SPSR, r9

  LDMFD SP!, {r0-r12, PC}^        //returns procesor in wtv


/* Stack pointer structure on kernel_handler_irq call
  sp_svc    <- *sp (in r0)
  spsr
  r0        <- sp_svc que esta en el stack apunta aca
  ...
  r12
  lr
*/


pref_abort:
  B __idle

data_abort:
  B __idle
  
irq_handler:
  SUB LR, LR, #4

  STMFD SP!, {r0-r12, LR}         //

  MRS r9, SPSR   
  
  //TODO maybe add more SPs here
  CPS         #(0x13)             //Go to svc
  MOV r8, SP                      //Save SP_svc
  MOV r7, LR                      //Save LR_svc

  CPS         #(0x1f)             //Go to sys                
  MOV r6, SP                      //Save SP_sys
  MOV r5, LR                      //Save LR_sys

  CPS         #(0x12)             //Back to irq             
  MOV r4, SP                      //Save SP_irq

  STMFD SP!, {r4-r9}                                                

  MOV r0, SP   
  BL __kernel_handler_irq         //k_h_i(*sp);
  MOV SP, r0

  LDMFD SP!, {r4-r9}     

  MOV SP, r4                      //Get SP_irq   

  CPS         #(0x1f)             //Go to sys                    
  MOV LR, r5                      //Get LR_sys
  MOV SP, r6                      //Get SP_Sys

  CPS         #(0x13)             //Go to svc 
  MOV LR, r7                      //Get LR_svc      
  MOV SP, r8                      //Get SP_svc
  CPS         #(0x12)             
            
  MSR SPSR, r9
  LDMFD SP!, {r0-r12, PC}^        

/* Stack pointer structure on kernel_handler_irq call
  sp_irq    <- *sp (in r0)
  lr_sys
  sp_sys
  lr_svc
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
