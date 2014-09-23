all: release

include config.mk

TARGET = LM3S3748
PART = $(TARGET)

#
# The flags passed to the assembler.
#
AFLAGS=-mthumb         \
       -mcpu=cortex-m3 \
       -MD

#
# The flags passed to the compiler.
#
CFLAGS=-mthumb             \
       -mcpu=cortex-m3     \
       -Os                 \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -Wall               \
       -pedantic           \
       -DPART_${PART}      \
       -DENC28J60_USE_PBUF \
       -DTARGET_IS_DUSTDEVIL_RA0	\
       -c

#
# The flags passed to the linker.
#
LD_OPTS=--gc-sections

SRC_NAME = ethcangw
ELF_NAME = $(SRC_NAME)_$(TARGET).elf
BIN_NAME = $(SRC_NAME)_$(TARGET).bin

BOARD = $(STELLARIS_WARE)/boards/ek-lm3s3748
BOARD_DRIVERS = $(BOARD)/drivers

#
# Get the location of libgcc.a from the GCC front-end.
#
#LIBGCC=${shell ${CC} -mthumb -mcpu=cortex-m3 -print-libgcc-file-name}
#LIBGCC="C:\Company\gcc-arm-none-eabi\lib\gcc\arm-none-eabi\4.8.4\thumb\libgcc.a"

#
# Get the location of libc.a from the GCC front-end.
#
#LIBC=${shell ${CC} -mthumb -mcpu=cortex-m3 -print-file-name=libc.a}
#LIBC=""

LD_LIBS = $(STELLARIS_WARE)/driverlib/gcc/libdriver.a $(STELLARIS_WARE)/grlib/gcc/libgr.a -lc -lnosys

OUT_DIR = out
OBJ_DIR = $(OUT_DIR)/obj

RELEASE_ELF = $(OUT_DIR)/$(ELF_NAME)
RELEASE_BIN = $(OUT_DIR)/$(BIN_NAME)

$(OUT_DIR) : 
	mkdir -p $(OUT_DIR)
	
$(OBJ_DIR) : $(OUT_DIR)
	mkdir -p $(OBJ_DIR)

include lwip.mk
include app.mk

LD_OPTS += -L"C:\Company\gcc-arm-none-eabi\arm-none-eabi\lib\thumb"
LD_OPTS += -T src-app/hello.ld
LD_OPTS += --entry ResetISR

$(RELEASE_ELF) : $(APP_LIB) $(LWIP_LIB)
	@echo LD $@
	@$(LD) $(LD_OPTS) -o $@ $+  $(LD_LIBS)

$(RELEASE_BIN) : $(RELEASE_ELF)
	@echo OBJCOPY $@
	@$(OBJCOPY) -O binary $< $@

release : $(RELEASE_BIN)

info :
	@echo $(ENC28J60_DRIVER)
	@echo $(LWIP_SOURCES)
	@echo $(LIBC)
	@echo $(LIBGCC)
