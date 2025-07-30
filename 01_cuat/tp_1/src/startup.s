.global _start
.extern reset_vector
.extern undef_handler
.extern softirq_hanlder
.extern pref_abort
.extern data_abort
.extern irq_handler
.extern fiq_handler
.extern __idle
//LD
.extern _USER_STACK_INIT
.extern _FIQ_STACK_INIT
.extern _IRQ_STACK_INIT
.extern _SVC_STACK_INIT
.extern _ABORT_STACK_INIT
.extern _UNDEF_STACK_INIT
.extern _SYSTEM_STACK_INIT
//ABI
.extern __board_init
.code 32

.section .start
table:
  LDR PC, _reset_vector
  LDR PC, _undef_handler
  LDR PC, _softirq_hanlder
  LDR PC, _pref_abort
  LDR PC, _data_abort
  LDR PC, _reset_vector
  LDR PC, _irq_handler
  LDR PC, _fiq_handler

  _reset_vector: .word reset_vector
  _undef_handler: .word undef_handler
  _softirq_hanlder: .word softirq_hanlder
  _pref_abort: .word pref_abort
  _data_abort: .word data_abort
  _irq_handler: .word irq_handler
  _fiq_handler: .word fiq_handler

_start:
  table_copy:
    table_length: #_start - #table

    SUB r1, pc, #8     
    MOV r0, #table_length
    loop_tablecpy:              //{
      LDR r2, [r1, #-4]!        //*(r0 -= 4) = *(r1 -= 4) //preindexed, r1 es 1-idexado
      STR r2, [r0, #-4]!
      CMP r0, #0
      BNE loop_tablecpy         //} while(r0 != 0)


  stack_pointer_init:
    MSR cpsr_c, #(0x11|0x80|0x40)   //FIQ; 0xd1
    LDR SP,=_FIQ_STACK_INIT

    MSR cpsr_c, #(0x12|0x80|0x40)   //IRQ; 0xd2
    LDR SP,=_IRQ_STACK_INIT

    MSR cpsr_c, #(0x13|0x80|0x40)   //SVC; 0xd3
    LDR SP,=_SVC_STACK_INIT

    MSR cpsr_c, #(0x17|0x80|0x40)   //Abort; 0xd7
    LDR SP,=_ABORT_STACK_INIT

    MSR cpsr_c, #(0x1b|0x80|0x40)   //Undef; 0xdb
    LDR SP,=_UNDEF_STACK_INIT 

    MSR cpsr_c, #(0x1f|0x80|0x40)   //Sys; 0xdf
    LDR SP,=_SYSTEM_STACK_INIT

    MSR cpsr_c, #(0x1f)             //Enable irqs
  
  board_init:
    BL __board_init

  //test_irq_hands:       //NOTE:branching to irq handler as opposed to interruptiong causes bx to return to this instruction, executing it again.
  //BL 0x70000018         //TODO:test this like, properly
                          
  B __idle
.end






