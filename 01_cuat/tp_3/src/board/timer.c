
#include "../../inc/include.h"

void __timer_init(void );

_timer_t* const TIMER0 = ( _timer_t* )TIMER0_ADDR;

__attribute__((section(".kernel_text"))) void __timer_init() {

        TIMER0->Timer1Load     = 0x00010000; // Setea el timer 0x10000 ciclos de clock
        TIMER0->Timer1Ctrl     = 0x00000002; // {[0] = 0} => Wrapping mode; {[1] = 1} => contador de 32 bit; {[2-3] = 0b00} => Timer sin prescale
        TIMER0->Timer1Ctrl    |= 0x00000040; // {[6] = 1} => Modo periodico
        TIMER0->Timer1Ctrl    |= 0x00000020; // {[5] = 1} => Habilita interrupcion
        TIMER0->Timer1Ctrl    |= 0x00000080; // {[8] = 1} => Larga el contador 
    }