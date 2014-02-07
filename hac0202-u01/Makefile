
CC = xc8

CC_OPTS = --pass1 --chip=pic16f1824 -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s" 
OBJ_DIR = obj

SOURCES = $(wildcard src/components/*.c) $(wildcard src/drivers-pic16f1824/*.c) $(wildcard src/target-pic16f1824-xc8/*.c)
OBJECTS = $(SOURCES:.c=.$(OBJ_EXT))

