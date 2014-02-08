
CC = xc8

TARGET = 16F1824
OBJ_EXT = p1
OUT_DIR = out

RELEASE_EXT = hex

SOURCE_DIRS = src/components/ src/drivers-pic16f1824/ src/target-pic16f1824-xc8/

include make/sources.mk

CC_OPTS = --pass1 --chip=$(TARGET) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf 

LD_OPTS = --chip=$(TARGET) -G -m$(basename $(RELEASE)).map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf --ram=default,-165-16f

include make/generic.mk

