CC=cc
# CC=clang
NAME=burning-star
OUT=bin/$(NAME)
OUT_DEBUG=bin/$(NAME)-debug
CFLAGS=-Wall -Wextra -pedantic -DPROJECT_DIR='"$(shell pwd)"' -Wunreachable-code
CLIBS=-lncurses -lm

sources=action.c ai.c drawing.c entity.c item.c key_val_reader.c main.c map.c menu.c noise.c tile.c vector.c

.PHONY: clean count debug debug-build default run

default: $(OUT)
build: $(OUT)

clean:
	-rm -Rf obj dep bin valgrind

run: $(OUT)
	./$(OUT)




debug-build: CFLAGS+=-g
debug-build:  | obj dep bin
	$(CC) $(CFLAGS) $(addprefix src/, $(sources)) -o $(OUT_DEBUG) $(CLIBS)

debug: debug-build
	gdb $(OUT_DEBUG)

valgrind: debug-build
	valgrind --log-file="valgrind" --track-fds=yes --track-origins=yes --leak-check=full ./$(OUT_DEBUG)

count:
	cloc src/*

test: clean | dep obj bin
	$(CC) $(CFLAGS) $(addprefix src/, $(filter-out main.c, $(sources))) src/test.c -o bin/test $(CLIBS)
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
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
