
CC=cc
# CC=clang
OUT=bin/basic-roguelike
OUT_DEBUG=bin/basic-roguelike-debug
CFLAGS=-Wall -Wextra -pedantic -DPROJECT_DIR='"$(shell pwd)"'

sources=action.c ai.c drawing.c entity.c main.c map.c menu.c tile.c vector.c

.PHONY: default debug clean count run

default: $(OUT)
clean:
	-rm -Rf obj dep bin
run: $(OUT)
	./$(OUT)
debug: CFLAGS+=-g
debug: OUT=$(OUT_DEBUG)
debug:  | obj dep bin
	$(CC) $(CFLAGS) -lncurses $(addprefix src/, $(sources)) -o $(OUT)
	gdb $(OUT)
count:
	cloc src/*
test: clean | dep obj bin
	$(CC) $(CFLAGS) -lncurses $(addprefix src/, $(filter-out main.c, $(sources))) src/test.c -o bin/test
	./bin/test

ifeq (,$(filter $(MAKECMDGOALS), clean count test))
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
