.extern reset_vector
.extern undef_handler
.extern softirq_hanlder
.extern pref_abort
.extern data_abort
.extern irq_handler
.extern fiq_handler

.global _start

.section start
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
    
    MOV r1, #_start
    MOV r0, #table_length
    loop_tablecpy:              //{
      LDR r2, [r1, #-4]!        //*(r0 -= 4) = *(r1 -= 4) //preindexed, r1 es 1-idexado
      STR r2, [r0, #-4]!
      CMP r0, #0
      BNE loop_tablecpy         //} while(r0 != 0)
  
  stack_pointer_init:
    MSR cpsr_c, #()
    LDR SP,= 