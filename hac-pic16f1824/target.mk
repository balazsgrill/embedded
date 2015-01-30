
CC = xc8

TARGET = 16F1824
OBJ_EXT = p1
LIB_EXT = lpp
RELEASE_EXT = hex

CC_OPTS = ---chip=$(TARGET) --output=lpp 
LD_OPTS = --chip=$(TARGET) -G -m$(basename $(RELEASE)).map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf --ram=default,-165-16f


