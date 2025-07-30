/* 
    Definiciones necesarias: formato de salida, arquitectura y punto de entrada
*/
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)


/* 
    Definiciones de simbolos necesarios
*/
_PUBLIC_RAM_INIT = 0x70010000;
_PUBLIC_STACK_INIT = 0x70020000;
_USER_STACK_INIT = 0x70030000;
_FIQ_STACK_INIT = 0x70040000;
_IRQ_STACK_INIT = 0x70050000;
_SVC_STACK_INIT = 0x70060000;
_ABORT_STACK_INIT = 0x70070000;
_UNDEF_STACK_INIT = 0x70080000;
_SYSTEM_STACK_INIT = 0x70090000;

/* 
    Definición del mapa de memoria
*/
MEMORY
{
    public_ram	: org = _PUBLIC_RAM_INIT, len = 0x1000
    public_stack : org = _PUBLIC_STACK_INIT, len = 0x1000
    user_stack : org = _USER_STACK_INIT, len =0x1000 
    fiq_stack : org = _FIQ_STACK_INIT, len =0x1000 
    irq_stack : org = _IRQ_STACK_INIT, len =0x1000 
    svc_stack : org = _SVC_STACK_INIT, len =0x1000 
    abort_stack : org = _ABORT_STACK_INIT, len =0x1000 
    undef_stack : org = _UNDEF_STACK_INIT, len =0x1000 
    system_stack : org = _SYSTEM_STACK_INIT, len =0x1000 
}

/* 
    Definición de las secciones
*/
SECTIONS
{
    . = _PUBLIC_RAM_INIT;
    .text : { 
        *(.reset_vector_code*)
        *(.handlers*) 
        *(.start*)
        *(.text*) 
        } > public_ram
    
    .data : { *(.data*) } > public_ram

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
        } > public_ram
}