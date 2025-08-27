.global memcpy

.code 32

.section .kernel_text
  memcpy:                 //memcpy(*dest, *source, size)

    AND r4, r2, #0b11     //r4 = r2 % 4
    SUB r2, r2, r4        //r2 -= r4; now r2 % 4 = 0

    align:
      CMP r4, #0
      BEQ after_aligned     

      LDRB r3, [r1], #1      
      STRB r3, [r0], #1
      SUB r4, r4, #1
      B align

    after_aligned:
      CMP r2, #0
      BXEQ LR                     //} while(r0 != 0)

      LDR r3, [r1], #4      
      STR r3, [r0], #4
      SUB r2, r2, #4        
      
      B after_aligned            //} while(r0 != 0)

.end
