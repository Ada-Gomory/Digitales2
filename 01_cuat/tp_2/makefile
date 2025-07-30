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

 
$(OBJ)bios.elf: $(OBJ)startup.o $(OBJ)reset_vector.o $(OBJ)handlers.o $(OBJ)low_level_cpu_access.o $(OBJ)timer.o $(OBJ)gic.o $(OBJ)uart.o $(OBJ)board_init.o $(OBJ)console_utils.o $(OBJ)kernel_handler_irq.o $(OBJ)scheduler.o 
	@echo "Linkeando..."
	mkdir -p obj
	mkdir -p lst
	$(CHAIN)-ld  -T mmap.ld $(OBJ)*.o -o $(OBJ)bios.elf -Map $(LST)bios_ld_map.map 
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

# Ensamblamos: startup.s
$(OBJ)startup.o: $(SRC)kernel/startup.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst
	@echo "Ensamblando startup.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)kernel/startup.s -o $(OBJ)startup.o -a > $(LST)startup.lst

# Ensamblamos: reset_vector.s
$(OBJ)reset_vector.o: $(SRC)kernel/reset_vector.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Ensamblando reset_vector.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)kernel/reset_vector.s -o $(OBJ)reset_vector.o -a > $(LST)reset_vector.lst

# Ensamblamos: handlers.s
$(OBJ)handlers.o: $(SRC)irq/handlers.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Ensamblando handlers.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)irq/handlers.s -o $(OBJ)handlers.o -a > $(LST)handlers.lst

# Compilamos: low_level_cpu_access.s
$(OBJ)low_level_cpu_access.o: $(SRC)utils/low_level_cpu_access.s
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Ensamblando low_level_cpu_access.s ..."
	$(CHAIN)-as $(AFLAGS) $(SRC)utils/low_level_cpu_access.s -o $(OBJ)low_level_cpu_access.o -a > $(LST)low_level_cpu_access.lst


#
# Compilado de codigo c
#

# Compilamos: timer.o
$(OBJ)timer.o : $(SRC)board/timer.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando timer.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/timer.c -o $(OBJ)timer.o -Wa,-a > $(LST)timer.lst

# Compilamos: gic.o
$(OBJ)gic.o : $(SRC)board/gic.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando gic.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/gic.c -o $(OBJ)gic.o -Wa,-a > $(LST)gic.lst

# Compilamos: uart.o
$(OBJ)uart.o : $(SRC)board/uart.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando uart.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)board/uart.c -o $(OBJ)uart.o -Wa,-a > $(LST)uart.lst

# Compilamos: board_init.o
$(OBJ)board_init.o : $(SRC)kernel/board_init.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando board_init.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)kernel/board_init.c -o $(OBJ)board_init.o -Wa,-a > $(LST)board_init.lst

# Compilamos: console_utils.o
$(OBJ)console_utils.o : $(SRC)utils/console_utils.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando console_utils.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)utils/console_utils.c -o $(OBJ)console_utils.o -Wa,-a > $(LST)console_utils.lst

# Compilamos: kernel_handler_irq.o
$(OBJ)kernel_handler_irq.o : $(SRC)irq/kernel_handler_irq.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando kernel_handler_irq.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)irq/kernel_handler_irq.c -o $(OBJ)kernel_handler_irq.o  -Wa,-a > $(LST)kernel_handler_irq.lst

# Compilamos: scheduler.o
$(OBJ)scheduler.o : $(SRC)tasks/scheduler.c
	@echo ""
	mkdir -p bin
	mkdir -p obj
	mkdir -p lst	
	@echo "Compilando scheduler.c ..."
	$(CHAIN)-gcc $(CFLAGS) $(SRC)tasks/scheduler.c -o $(OBJ)scheduler.o  -Wa,-a > $(LST)scheduler.lst




clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.objstart
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.bin
	rm -rf $(LST)*.lst 
	rm -rf $(LST)*.txt 
	rm -rf $(LST)*.map 