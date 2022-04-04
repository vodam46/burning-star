
## variables for ease of change
CC=cc
OUT=out
CFLAGS=-Wall -Wextra -pedantic

## default target
default: $(OUT)

## compile the debug version
debug: CFLAGS+=-D
debug: CFLAGS+=DEBUG
debug: clean $(OUT)

## generate the binary file
$(OUT): main.o entity.o tile.o map.o drawing.o vector.o ai.o entity_type.h tile_type.h
	$(CC) $(CFLAGS) main.o entity.o tile.o map.o drawing.o vector.o ai.o -lncurses -o $(OUT)

## compile the main.c file
main.o: main.c tile.o entity.o map.o vector.o ai.o tile_type.h
	$(CC) $(CFLAGS) -c main.c

## compile the entity.c file
entity.o: entity.c entity.h entity_type.h vector.o
	$(CC) $(CFLAGS) -c entity.c
	
## compile the tile.c file
tile.o: tile.c tile.h tile_type.h entity.o vector.o
	$(CC) $(CFLAGS) -c tile.c

## compile the map.c file
map.o: map.c map.h tile.o entity.o vector.o tile_type.h
	$(CC) $(CFLAGS) -c map.c

## compile the drawing.c file
drawing.o: drawing.c drawing.h tile.o
	$(CC) $(CFLAGS) -c drawing.c -lncurses

## compile the vector.c file
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

## compile the ai.c file
ai.o: ai.c ai.h
	$(CC) $(CFLAGS) -c ai.c

## remove the object file and the binary file
clean:
	rm -Rf *.o $(OUT)

## count the number of lines
count: clean
	wc *

## run the program
run: $(OUT)
	./$(OUT)
