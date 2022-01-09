
CC=cc
OUT=out

default: $(OUT)

$(OUT): main.o entity.o tile.o map.o drawing.o entity_type.h tile_type.h
	$(CC) main.o entity.o tile.o map.o drawing.o -lncurses -o $(OUT)

main.o: main.c tile.o entity.o map.o tile_type.h
	$(CC) -c main.c

entity.o: entity.c entity.h entity_type.h
	$(CC) -c entity.c
	
tile.o: tile.c tile.h tile_type.h entity.o
	$(CC) -c tile.c

map.o: map.c map.h tile.o entity.o tile_type.h
	$(CC) -c map.c

drawing.o: drawing.c drawing.h tile.o
	$(CC) -c drawing.c -lncurses

clean:
	rm -Rf *.o $(OUT)

count:
	wc -l *

run: $(OUT)
	./$(OUT)
