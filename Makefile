
CC=cc
OUT=output

default: $(OUT)

$(OUT): main.o entity.o tile.o tile.h entity.h
	$(CC) main.o entity.o tile.o -I tile.h -I entity.h -o $(OUT)

main.o: main.c
	$(CC) -c main.c

entity.o: entity.c entity.h
	$(CC) -c entity.c
	
tile.o: tile.c tile.h
	$(CC) -c tile.c

clean:
	rm -Rf *.o $(OUT)

run: $(OUT)
	./$(OUT)