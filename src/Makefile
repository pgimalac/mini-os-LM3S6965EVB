# Définitions des outils de cross-compilation
CROSSCOMPILE=arm-none-eabi-
LD = $(CROSSCOMPILE)ld
AS = $(CROSSCOMPILE)as
CC = $(CROSSCOMPILE)gcc
OBJCOPY = $(CROSSCOMPILE)objcopy

# Définition des flags de compilation pour le compilateur C et l'assembleur
ARCH = -mcpu=cortex-m3 -mthumb
CFLAGS  = -g -Wall -Wextra -Wall -O0 -I. -std=gnu99 $(ARCH)
ASFLAGS = -g -mcpu=cortex-m3
LDFLAGS = $(ARCH) -nostdlib -T ld_ram.lds
LDLIBS = -lgcc

# Définition de l'exécutable et des objets le composant
EXE  = main
IMG  = main.bin

FOLDER_PERIPH = periphs/
OBJS_PERIPH = systick.o uart.o

FOLDER_IRQ = irq/
OBJS_IRQ = irq.o handlers.o default_handlers.o icsr.o

FOLDER_PROC = proc/
OBJS_PROC = process.o scheduler.o

OBJS = main.o crt0.o init_bss.o $(addprefix $(FOLDER_IRQ), $(OBJS_IRQ)) \
								$(addprefix $(FOLDER_PERIPH), $(OBJS_PERIPH)) \
								$(addprefix $(FOLDER_PROC), $(OBJS_PROC))
# Cible par défaut
all: $(EXE) $(IMG)

crt0.o: crt0.s
	@echo "Assembling main"
	@$(AS) $(ASFLAGS) -o $@ $?

%.o: %.c
	@echo "Compiling $?"
	@$(CC) $(LDFLAGS) $(CFLAGS) -c $? -o $@

# Règles spécifiques à nous
$(EXE): $(OBJS) ld_ram.lds
	@echo "Build main"
	@$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o$@

$(IMG): $(EXE)
	@echo "Converting main to binary"
	@$(OBJCOPY) -O binary $< $@

clean:
	@echo "Clean objects"
	@rm -f $(OBJS) $(EXE) $(EXE).lst $(EXE).map $(IMG) *~

run: all
	@qemu-system-arm -M lm3s6965evb -nographic -kernel main.bin

re: clean all

rerun: re run
