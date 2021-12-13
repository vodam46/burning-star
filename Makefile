
CC=cc
OUT=output

default: $(OUT)

main.o: main.c
	$(CC) -c main.c

$(OUT): main.o
	$(CC) main.o -o $(OUT)

clean:
	rm -Rf *.o $(OUT)

run: output
	./$(OUT)