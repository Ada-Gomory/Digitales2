CHAIN=arm-none-eabi
CFLAGS=-std=gnu99 -Wno-unused -Wno-discarded-qualifiers -mfpu=neon -mhard-float -mcpu=cortex-a8 -DCPU_A8 -g -c -Ddebug
#CFLAGS=-std=gnu99 -Wno-unused -mfpu=neon -mhard-float -mcpu=cortex-a8 -DCPU_A8 -g -c
AFLAGS=-mfpu=neon -g
OBJ=obj/
BIN=bin/
INC=inc/
SRC=src/
LST=lst/

all: $(BIN)bios.bin $(OBJ)bios.elf

$(BIN)bios.bin: $(OBJ)bios.elf
	$(CHAIN)-objcopy -O binary $< $@

 #TODO: clean up ffs
$(OBJ)bios.elf: $(OBJ)board/gic.o $(OBJ)board/timer.o $(OBJ)board/uart.o $(OBJ)irq/handlers.o $(OBJ)irq/kernel_handlers.o $(OBJ)kernel/board_init.o $(OBJ)kernel/reset_vector.o $(OBJ)kernel/startup.o $(OBJ)tasks/tasks.o $(OBJ)tasks/scheduler.o $(OBJ)utils/console_utils.o $(OBJ)utils/low_level_cpu_access.o $(OBJ)utils/utils.o 
	@echo "Linkeando..."
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils
	$(CHAIN)-ld  -T mmap.ld $(OBJ)*/*.o -o $(OBJ)bios.elf -Map $(LST)bios_ld_map.map 
# $(CHAIN)-ld -T td3_memmap.ld $(OBJ)*.o -o $(OBJ)bios.elf -Map $(LST)bios_ld_map.map 
# $(CHAIN)-gcc -T td3_memmap.ld -lgcc --specs=nosys.specs -lm $(OBJ)*.o -o $(OBJ)bios.elf -Wl,-Map=bios_ld_map.map 
	@echo "Linkeo finalizado!!"
	@echo ""
	@echo "Generando archivos de información: mapa de memoria y simbolos"
	readelf -a $(OBJ)bios.elf > $(LST)bios_readelf.txt
	$(CHAIN)-objdump -D $(OBJ)bios.elf > $(LST)bios.lst

#
# Ensamblado de código assembler
#

# Ensamblamos: kernel/startup.s
$(OBJ)kernel/startup.o: $(SRC)kernel/startup.s
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils
	@echo "Ensamblando kernel/startup.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)kernel/startup.s -o $(OBJ)kernel/startup.o -a > $(LST)kernel/startup.lst

# Ensamblamos: kernel/reset_vector.s
$(OBJ)kernel/reset_vector.o: $(SRC)kernel/reset_vector.s
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Ensamblando kernel/reset_vector.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)kernel/reset_vector.s -o $(OBJ)kernel/reset_vector.o -a > $(LST)kernel/reset_vector.lst

# Ensamblamos: /irq/handlers.s
$(OBJ)irq/handlers.o: $(SRC)irq/handlers.s
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Ensamblando /irq/handlers.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)irq/handlers.s -o $(OBJ)irq/handlers.o -a > $(LST)irq/handlers.lst

# Compilamos: utils/low_level_cpu_access.s
$(OBJ)utils/low_level_cpu_access.o: $(SRC)utils/low_level_cpu_access.s
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Ensamblando utils/low_level_cpu_access.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)utils/low_level_cpu_access.s -o $(OBJ)utils/low_level_cpu_access.o -a > $(LST)utils/low_level_cpu_access.lst

# Compilamos: utils/utils.s
$(OBJ)utils/utils.o: $(SRC)utils/utils.s
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Ensamblando utils/utils.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)utils/utils.s -o $(OBJ)utils/utils.o -a > $(LST)utils/utils.lst


#
# Compilado de codigo c
#

# Compilamos: board/gic.o
$(OBJ)board/gic.o : $(SRC)board/gic.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando /board/gic.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/gic.c -o $(OBJ)board/gic.o -Wa,-a > $(LST)board/gic.lst

# Compilamos: board/timer.o
$(OBJ)board/timer.o : $(SRC)board/timer.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando /board/timer.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/timer.c -o $(OBJ)board/timer.o -Wa,-a > $(LST)board/timer.lst

# Compilamos: board/uart.o
$(OBJ)board/uart.o : $(SRC)board/uart.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando /board/uart.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/uart.c -o $(OBJ)board/uart.o -Wa,-a > $(LST)board/uart.lst

# Compilamos: kernel/board_init.o
$(OBJ)kernel/board_init.o : $(SRC)kernel/board_init.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils
	@echo "Compilando kernel/.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)kernel/board_init.c -o $(OBJ)kernel/board_init.o -Wa,-a > $(LST)board_init.lst

# Compilamos: utils/console_utils.o
$(OBJ)utils/console_utils.o : $(SRC)utils/console_utils.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando utils/console_utils.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)utils/console_utils.c -o $(OBJ)utils/console_utils.o -Wa,-a > $(LST)utils/console_utils.lst

# Compilamos: irq/kernel_handlers.o
$(OBJ)irq/kernel_handlers.o : $(SRC)irq/kernel_handlers.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando irq/kernel_handlers.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)irq/kernel_handlers.c -o $(OBJ)irq/kernel_handlers.o  -Wa,-a > $(LST)irq/kernel_handlers.lst

# Compilamos: tasks/scheduler.o
$(OBJ)tasks/scheduler.o : $(SRC)tasks/scheduler.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando tasks/scheduler.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)tasks/scheduler.c -o $(OBJ)tasks/scheduler.o  -Wa,-a > $(LST)tasks/scheduler.lst

# Compilamos: tasks/tasks.o
$(OBJ)tasks/tasks.o : $(SRC)tasks/tasks.c
	@echo ""
	mkdir -p bin
	mkdir -p obj/board obj/irq obj/kernel obj/tasks obj/utils
	mkdir -p lst/board lst/irq lst/kernel lst/tasks lst/utils	
	@echo "Compilando tasks/tasks.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)tasks/tasks.c -o $(OBJ)tasks/tasks.o  -Wa,-a > $(LST)tasks/tasks.lst


clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.objstart
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.bin
	rm -rf $(LST)*.lst 
	rm -rf $(LST)*.txt 
	rm -rf $(LST)*.map 

	rm -rf $(OBJ)*/*.o
	rm -rf $(OBJ)*/*.objstart
	rm -rf $(OBJ)*/*.elf
	rm -rf $(BIN)*/*.bin
	rm -rf $(LST)*/*.lst 
	rm -rf $(LST)*/*.txt 
	rm -rf $(LST)*/*.map 