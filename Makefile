
CC=cc
OUT=out
OUT_DEBUG=out_debug
CFLAGS=-Wall -Wextra -pedantic

.PHONY: default debug clean count run

default: $(OUT)

debug: clean
	make 'CFLAGS=$(CFLAGS) -g' OUT=$(OUT_DEBUG)
	gdb out_debug

$(OUT): main.o
	$(CC) $(CFLAGS) main.o entity.o tile.o map.o drawing.o vector.o ai.o entity_type.o tile_type.o -lncurses -o $(OUT)

main.o: main.c tile.o entity.o map.o vector.o ai.o drawing.o tile_type.h
	$(CC) $(CFLAGS) -c main.c

entity.o: entity.c entity.h entity_type.o vector.o
	$(CC) $(CFLAGS) -c entity.c
	
tile.o: tile.c tile.h tile_type.o entity.o vector.o
	$(CC) $(CFLAGS) -c tile.c

tile_type.o: tile_type.h tile_type.c
	$(CC) $(CFLAGS) -c tile_type.c

entity_type.o: entity_type.h entity_type.c
	$(CC) $(CFLAGS) -c entity_type.c

map.o: map.c map.h tile.o entity.o vector.o tile_type.h
	$(CC) $(CFLAGS) -c map.c

drawing.o: drawing.c drawing.h tile.o
	$(CC) $(CFLAGS) -c drawing.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

ai.o: ai.c ai.h vector.o 
	$(CC) $(CFLAGS) -c ai.c

## remove the object file and the binary file
clean:
	@rm -Rf *.o $(OUT) $(OUT_DEBUG)

## count the number of lines
count: clean
	cloc *

## run the program
run: $(OUT)
	./$(OUT)

## run tests
test:
	$(CC) test.c vector.c ai.c entity.c tile.c -o $(OUT)
	./$(OUT)
