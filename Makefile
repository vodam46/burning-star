
CC=cc
# CC=clang
OUT=bin/basic-roguelike
OUT_DEBUG=$(OUT)-debug
CFLAGS=-Wall -Wextra -pedantic

sources=action.c ai.c drawing.c entity.c entity_type.c main.c map.c menu.c tile.c tile_type.c vector.c

.PHONY: default debug clean count run

default: $(OUT)
clean:
	-rm -Rf obj dep bin
run: $(OUT)
	./$(OUT)
debug: clean
	make 'CFLAGS=$(CFLAGS) -g' OUT=$(OUT_DEBUG)
	gdb $(OUT_DEBUG)
count:
	cloc src/*
test: clean | dep obj bin
	$(CC) -lncurses $(addprefix src/, $(filter-out main.c, $(sources))) src/test.c -o bin/test
	./bin/test

ifeq (,$(filter $(MAKECMDGOALS), clean count))
include $(addprefix dep/, $(sources:.c=.d))
endif

dep/%.d: src/%.c | dep
	$(CC) $(CFLAGS) -M $^ > $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c -o $@ $(realpath $<)

obj dep bin:
	mkdir -p $@

$(OUT): $(addprefix obj/, $(sources:.c=.o)) | bin
	$(CC) $(CFLAGS) -lncurses -o $@ $^
