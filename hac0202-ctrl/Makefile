MCP2200 = ../mcp2200

all: bin/hac0202ctrl

clear:
	rm -R bin

bin/mcp2200.o: bin $(MCP2200)/src/mcp2200.c $(MCP2200)/src/mcp2200.h
	$(CC) -c -Wall $(MCP2200)/src/mcp2200.c -o bin/mcp2200.o

bin:
	mkdir -p bin

bin/hac0202ctrl.o: bin src/hac0202ctrl.c
	$(CC) $(MARCH) $(INCLUDE) -I$(MCP2200)/src -c -Wall src/hac0202ctrl.c -o bin/hac0202ctrl.o

bin/hac0202ctrl: bin/mcp2200.o bin/hac0202ctrl.o
	$(CC) -o bin/hac0202ctrl bin/mcp2200.o bin/hac0202ctrl.o -lrt -lpthread -ludev -lusb-1.0


