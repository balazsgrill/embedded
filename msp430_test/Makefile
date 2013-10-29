OBJDIR := obj
OUTDIR := release
OBJS := $(addprefix $(OBJDIR)/,main.o FR_EXP.o)

TARGET := msp430fr5739
NAME := test

CC := msp430-gcc
LD := msp430-ld
OBJCPY := msp430-objcopy

$(OBJDIR)/%.o : %.c
	$(CC) -c -mcpu=430 -mmcu=$(TARGET) -o $@ $<

$(OUTDIR)/$(NAME).out : $(OBJS) $(OUTDIR)
	$(LD) -o $(OUTDIR)/$(NAME).out -Map $(OUTDIR)/$(NAME).map $(OBJS)
	
$(OUTDIR)/$(NAME).hex : $(OUTDIR)/$(NAME).out $(OUTDIR)
	$(OBJCPY) -O ihex $(OUTDIR)/$(NAME).out $(OUTDIR)/$(NAME).hex

all: $(OUTDIR)/$(NAME).hex
     
$(OBJS): | $(OBJDIR)
     
$(OUTDIR):
	mkdir $(OUTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)
