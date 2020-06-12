# Définitions des outils de cross-compilation
CROSSCOMPILE=arm-none-eabi-
LD = $(CROSSCOMPILE)ld
AS = $(CROSSCOMPILE)as
CC = $(CROSSCOMPILE)gcc
OBJCOPY = $(CROSSCOMPILE)objcopy

# Définition des flags de compilation pour le compilateur C et l'assembleur
ARCH = -mcpu=cortex-m3 -mthumb
CFLAGS  = -g -Wall -Wextra -Wall -O0 -std=gnu99 $(ARCH)
ASFLAGS = -g -mcpu=cortex-m3
LDFLAGS = $(ARCH) -nostdlib -T ld_ram.lds
LDLIBS = -lgcc

# Définition de l'exécutable et des objets le composant
EXE  = main
IMG  = main.bin
OBJS = main.o crt0.o init_bss.o irq.o

# Cible par défaut
all: $(EXE) $(IMG)

# Règles spécifiques à nous
$(EXE): $(OBJS) ld_ram.lds
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o$@

$(IMG): $(EXE)
	$(OBJCOPY) -O binary $< $@

clean:
	-rm -f $(OBJS) $(EXE) $(EXE).lst $(EXE).map $(IMG) *~

