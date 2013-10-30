OUTDIR := release
SRC := main.c FR_EXP.c

TARGET := msp430fr5739
NAME := test

CC := msp430-gcc
LD := msp430-ld
OBJCPY := msp430-objcopy

$(OUTDIR)/$(NAME).out : $(OUTDIR)
	$(CC) -g -mcpu=430 -mmcu=$(TARGET) -o $(OUTDIR)/$(NAME).out "-Wl,-Map=$(OUTDIR)/$(NAME).map" $(SRC)
	
$(OUTDIR)/$(NAME).hex : $(OUTDIR)/$(NAME).out $(OUTDIR)
	$(OBJCPY) -O ihex $(OUTDIR)/$(NAME).out $(OUTDIR)/$(NAME).hex

all: $(OUTDIR)/$(NAME).hex

$(OUTDIR):
	mkdir $(OUTDIR)

