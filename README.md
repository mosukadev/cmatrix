# Projeto C

Biblioteca de matrizes em C, armazena matrizes e executa diversas operações matriciais.

## Pré-requisitos

- GCC
- Linux (ou WSL)
- Make

## Estrutura de Pastas

projeto_c/
├── include/                 # Interface pública da biblioteca
│   ├── libmatriz.h          # Cabeçalho padrão da matriz com todos os modulos
│   └── libmatriz/
│       ├── arquivo.h        # Manipula arquivos de matrizes e gera matrizes de vetor
│       ├── erro.h           # Lida com erros no funcionamento
│       ├── matriz.h         # criação, destruição, cópia e acesso de matrizes
│       ├── operacoes.h      # Soma, subtração, transposta e multiplicação
│       └── propriedades.h   # Determinante, traço e verificações
├── src/                     # Implementação dos modulos
│   ├── matriz_interno.h     # Cabeçalho privado da matriz (tipo opaco)
│   ├── arquivo.c
│   ├── erro.c
│   ├── matriz.c
│   ├── operacoes.c
│   └── propriedades.c
├── app/                     # Aplicação do Cliente
│   ├── principal.c          # Programa de exemplo
│   └── exemplo.txt          # Entrada de exemplo
├── tests/                   # Códigos de teste do programa
│   ├── teste.h              # Macros para testes
│   ├── teste.c              # Executor dos testes
│   ├── teste_*.c / .h       # Testes para cada modulo
│   └── dados/               # Arquivos de matrizes de teste, validas e invalidas
├── scripts/
│   └── demo.sh              # Demonstração do projeto
├── Makefile                 # Automatização de compilação
├── README.md                # Instruções do projeto
└── .gitignore               # Indicação de arquivos ignorados pelo git

## Alvos do make e Compilação

make / make all Compila as bibliotecas estáticas (lib/libmatriz.a) e dinâmicas (lib/libmatriz.so), executável dinâmico e estático do cliente são gerados em bin/.
make clean Remove artefatos de compilação (build/, lib/, bin/).
make run Compila o projeto se necessário e roda a aplicação dinâmica por padrão.
make run-estatico roda a aplicação estática do cliente.
make run-dinamico roda a aplicação dinâmica do cliente (-Wl,-rpath).
make test Compila e roda todos os testes de (tests/).
make install instala a biblioteca (.a, .so) e os cabeçalhos públicos em $(PREFIX) (padrão /usr/local).
make uninstall desinstala arquivos do prefixo dado.
make valgrind Executa testes de (tests/) sob o valgrind para autoria de memória.

## Exemplos
compila o projeto:
    make
Roda a Aplicação, roda estático e dinâmico:
    make run-dinamico
    make run-estatico
    make run-dinamico
Roda testes sob ou sem valgrind:
    make valgrind
    make test
Instala bibliotecas e Desinstala:
    make install PREFIX=$HOME/.local
    make uninstall PREFIX=$HOME/.local