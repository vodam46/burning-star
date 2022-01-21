
## variables for ease of change
CC=cc
OUT=out

## default target
default: $(OUT)

## generate the binary file
$(OUT): main.o entity.o tile.o map.o drawing.o entity_type.h tile_type.h
	$(CC) main.o entity.o tile.o map.o drawing.o -lncurses -o $(OUT)

## compile the main.c file
main.o: main.c tile.o entity.o map.o tile_type.h
	$(CC) -c main.c

## compile the entity.c file
entity.o: entity.c entity.h entity_type.h
	$(CC) -c entity.c
	
## compile the tile.c file
tile.o: tile.c tile.h tile_type.h entity.o
	$(CC) -c tile.c

## compile the map.c file
map.o: map.c map.h tile.o entity.o tile_type.h
	$(CC) -c map.c

## compile the drawing.c file
drawing.o: drawing.c drawing.h tile.o
	$(CC) -c drawing.c -lncurses

## remove the object file and the binary file
clean:
	rm -Rf *.o $(OUT)

## count the number of lines
count:
	wc -l *

## run the program
run: $(OUT)
	./$(OUT)
