
CC=cc
# CC=clang
OUT=basic-roguelike
OUT_DEBUG=$(OUT)-debug
CFLAGS=-Wall -Wextra -pedantic

sources=action.c ai.c drawing.c entity.c entity_type.c main.c map.c menu.c tile.c tile_type.c vector.c

.PHONY: default debug clean count run

default: $(OUT)
clean:
	-rm -Rf *.o *.d $(OUT) $(OUT_DEBUG)
run: $(OUT)
	./$(OUT)
debug: clean
	make 'CFLAGS=$(CFLAGS) -g' OUT=$(OUT_DEBUG)
	gdb $(OUT_DEBUG)
count: clean
	cloc *
test: clean
	$(CC) test.c vector.c ai.c entity.c tile.c -o $(OUT)
	./$(OUT)

%.d: %.c
	$(CC) $(CFLAGS) -M $^ > $@

ifeq (,$(filter clean, $(MAKECMDGOALS)))
include $(sources:.c=.d)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(sources:.c=.o)
	$(CC) $(CFLAGS) -lncurses -o $@ $^

