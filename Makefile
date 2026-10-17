CC = gcc

#Flags pra ver erros, incremental etc
CFLAGS = -Wall -Wextra -Iinclude -Iinclude/libmatriz -Wpedantic -g
#GLags para grantir o inncrmental, especialmente cabeçalho dos .o
DFLAGS = -MMD -MP

PREFIX ?= $(HOME)/.local

#Pastas e nome das bibliotecas
DINAMICA = lib/libmatriz.so
ESTATICA = lib/libmatriz.a

# Arquivos fonte
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/est/%.o,$(SRC))
OBJ_DIN = $(patsubst src/%.c,build/din/%.o,$(SRC))
TEST_SRC = $(wildcard tests/teste_*.c)
TEST_HEADERS = $(wildcard tests/teste_*.h) tests/teste.h

# Declarar alvos que não são arquivos
.PHONY: all clean run test install run-static run-dynamic valgrind uninstall docs clean-docs

all: $(ESTATICA) $(DINAMICA)  bin/app_estatico bin/app_dinamico


#Criação da lib estática
$(ESTATICA): $(OBJ)
	@mkdir -p lib
	ar rcs $@ $^

build/est/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@


# Criação da lib dinâmica
$(DINAMICA): $(OBJ_DIN)
	@mkdir -p lib
	$(CC) -shared -o $@ $^ -lm 

build/din/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) -c -fPIC $< -o $@

# Gera executável da principal.c linkando com a lib estatica
bin/app_estatico: app/principal.c $(ESTATICA)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(DFLAGS) -MF $@.d -MT $@ app/principal.c $(ESTATICA) -lm -o $@

# Gera executável da principal.c linkando com a lib dinamica
bin/app_dinamico: app/principal.c $(DINAMICA)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(DFLAGS) -MF $@.d -MT $@ app/principal.c $(DINAMICA) -lm -Wl,-rpath,'$$ORIGIN/../lib' -o $@


# Include dos .d pra incremental
-include $(OBJ:.o=.d) $(OBJ_DIN:.o=.d) bin/app_estatico.d bin/app_dinamico.d

# Por padrão, rodamos com estáticos, mas acho que isso seja mudável
run: run-static

# Compila o runner e todas as suítes em um único executável
build/test_runner: tests/teste.c $(TEST_SRC) $(TEST_HEADERS) $(ESTATICA)
	@mkdir -p build
	$(CC) $(CFLAGS) -Itests tests/teste.c $(TEST_SRC) $(ESTATICA) -lm -o $@

# Apenas roda o test_runner por padrão
test: build/test_runner
	./build/test_runner

# Instala as libs no $(HOME)/local
install: $(ESTATICA) $(DINAMICA)
	install -d $(PREFIX)/lib $(PREFIX)/include/libmatriz
	install -m 644 $(ESTATICA) $(DINAMICA) $(PREFIX)/lib/
	install -m 644 include/libmatriz.h $(PREFIX)/include/
	install -m 644 include/libmatriz/*.h $(PREFIX)/include/libmatriz/

# Roda estático
run-static: bin/app_estatico
	./bin/app_estatico

# Roda dinâmico
run-dynamic: bin/app_dinamico
	./bin/app_dinamico

# Confere vazamentos, ou seja, malloc sem free etc.
valgrind: all build/test_runner
	valgrind --leak-check=full --error-exitcode=1 ./build/test_runner

# Tira do usr/local
uninstall:
	rm -f $(PREFIX)/lib/libmatriz.a $(PREFIX)/lib/libmatriz.so
	rm -rf $(PREFIX)/include/libmatriz

# Cleana as pastas
clean: 
	rm -rf build lib bin

docs:
	doxygen Doxyfile

clean-docs:
	rm -rf docs/