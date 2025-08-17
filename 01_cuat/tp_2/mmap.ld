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

SYSTEM_STACK_SIZE = 0x1000;
USER_STACK_SIZE = 0x200;
FIQ_STACK_SIZE = 0x200;
IRQ_STACK_SIZE = 0x200;
SVC_STACK_SIZE = 0x200;
ABORT_STACK_SIZE = 0x200;
UNDEF_STACK_SIZE = 0x200;

TASK0_SIZE = 0x100;     /*idle */
TASK1_SIZE = 0x100;
TASK2_SIZE = 0x100;
TASK3_SIZE = 0x100;

/* 
    Definición del mapa de memoria
*/
MEMORY
{
    public_ram	: org = _PUBLIC_RAM_INIT, len = 0x4000  /*0x1000 se queda corto */
    public_stack : org = _PUBLIC_STACK_INIT, len = 0x4000
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
        *(.kernel_text*)
        *(.text*) 
        } > public_ram
    
    .data : { *(.data*) } > public_ram

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
        } > public_ram


    . = _PUBLIC_STACK_INIT;
    .stack :  {
      
        . += IRQ_STACK_SIZE;
        . = ALIGN(4);    
        _IRQ_STACK_INIT = .;  

        . += FIQ_STACK_SIZE;
        . = ALIGN(4);    
        _FIQ_STACK_INIT = .;  

        . += SVC_STACK_SIZE;
        . = ALIGN(4);   
        _SVC_STACK_INIT = .;  

        . += ABORT_STACK_SIZE;
        . = ALIGN(4);    
        _ABORT_STACK_INIT = .;  

        . += UNDEF_STACK_SIZE;
        . = ALIGN(4);    
        _UNDEF_STACK_INIT = .;  
        
        . += SYSTEM_STACK_SIZE;
        . = ALIGN(4);     
        _SYSTEM_STACK_INIT = .;  



        /*IRQ STACKS*/
        . += TASK0_SIZE;
        . = ALIGN(4);     
        _TASK0_IRQ_STACK_INIT = .;    
        . += TASK1_SIZE;
        . = ALIGN(4);     
        _TASK1_IRQ_STACK_INIT = .;     

        . += TASK2_SIZE;
        . = ALIGN(4);     
        _TASK2_IRQ_STACK_INIT = .;       

        . += TASK3_SIZE;
        . = ALIGN(4);     
        _TASK3_IRQ_STACK_INIT = .;   
        
        /*SYS STACKS*/
        . += TASK0_SIZE;
        . = ALIGN(4);     
        _TASK0_SYS_STACK_INIT = .;    
        . += TASK1_SIZE;
        . = ALIGN(4);     
        _TASK1_SYS_STACK_INIT = .;     

        . += TASK2_SIZE;
        . = ALIGN(4);     
        _TASK2_SYS_STACK_INIT = .;       

        . += TASK3_SIZE;
        . = ALIGN(4);     
        _TASK3_SYS_STACK_INIT = .;   


        /*SVC STACKS*/
        . += TASK0_SIZE;
        . = ALIGN(4);     
        _TASK0_SVC_STACK_INIT = .;    

        . += TASK1_SIZE;
        . = ALIGN(4);     
        _TASK1_SVC_STACK_INIT = .;       

        . += TASK2_SIZE;
        . = ALIGN(4);     
        _TASK2_SVC_STACK_INIT = .;      

        . += TASK3_SIZE;
        . = ALIGN(4);     
        _TASK3_SVC_STACK_INIT = .;       
          
    } > public_stack    
}