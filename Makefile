CC = gcc
CFLAGS = -Wall -Iinclude -Wextra -Wpedantic -g

PREFIX ?= /usr/local

DINAMICA = lib/libmatriz.so
ESTATICA = lib/libmatriz.a

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

all: $(ESTATICA) $(DINAMICA)  bin/app_estatico bin/app_dinamico

clean: 
	rm -rf build lib bin

run: run-static

test: $(ESTATICA)
	@mkdir -p build
	@fail=0; for f in testes/teste_*.c; do \
		$(CC) $(FLAGS) -Itests $$f $(ESTATICA) -lm -o build/teste && build/teste || fail=1; \
	done; exit $$fail

install: $(ESTATICA) $(DINAMICA)
	install -d $(PREFIX)/lib $(PREFIX)/include/libmatriz
	install -m 644 $(ESTATICA) $(DINAMICA) $(PREFIX)/lib


run-static:

run-dynamic:

valgrind:

docs:

uninstall:
	rm -f $(PREFIX)/lib/libmatriz.a $(PREFIX)/lib/libmatriz.so
