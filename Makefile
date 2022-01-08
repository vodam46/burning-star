
CC=cc
OUT=out

default: $(OUT)

$(OUT): main.o entity.o tile.o map.o tile.h entity.h map.h entity_type.h tile_type.h
	$(CC) main.o entity.o tile.o map.o -I tile.h -I entity.h -I map.h -I tile_type.h -lncurses -o $(OUT)

main.o: main.c
	$(CC) -c main.c

entity.o: entity.c entity.h
	$(CC) -c entity.c
	
tile.o: tile.c tile.h
	$(CC) -c tile.c

map.o: map.c map.h
	$(CC) -c map.c

clean:
	rm -Rf *.o $(OUT)

run: $(OUT)
	./$(OUT)
