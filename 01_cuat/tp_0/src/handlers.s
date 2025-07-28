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
  B idle

fiq_handler:
  B idle

.end
