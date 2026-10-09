#include "teste.h"
#include <libmatriz.h>

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void mtz_criar_3x4() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    VERIFICA(status == MTZ_OK && mtz_linhas(m) == 3 && mtz_colunas(m) == 4, "mtz_criar_3x4");
}

void mtz_verificar_3x4_zeros() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    bool zero = false;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int valor;
            mtz_obter(m, 3, 4, &valor);

            if (valor != 0) {
                zero = true;
                break;
            }
        }
    }

    VERIFICA(!zero, "mtz_verificar_3x4_zeros");
}

void mtz_criar_1x1() {
    Matriz *m;
    MtzStatus status = mtz_criar(1, 1, &m);

    VERIFICA(status == MTZ_OK && mtz_linhas(m) == 1 && mtz_colunas(m) == 1, "mtz_criar_1x1");
}

void mtz_criar_0_linhas() {
    Matriz *m;
    MtzStatus status = mtz_criar(0, 4, &m);

    VERIFICA(status == MTZ_ERRO_DIMENSAO, "mtz_criar_0_linhas");   
}

void mtz_criar_0_colunas() {
    Matriz *m;
    MtzStatus status = mtz_criar(4, 0, &m);

    VERIFICA(status == MTZ_ERRO_DIMENSAO, "mtz_criar_0_colunas");   
}

void mtz_criar_saida_nula() {
    MtzStatus status = mtz_criar(3, 4, NULL);

    VERIFICA(status == MTZ_ERRO_NULO, "mtz_criar_saida_nula");   
}

void mtz_destruir_nulo() {
    //É esperado que o programa quebre caso o valor nulo seja aceito
    mtz_destruir(NULL);

    VERIFICA(true, "mtz_destruir_nulo");
}

void mtz_criar_e_destruir_100() {
    bool erro = false;

    for (int i = 0; i < 100; i++) {
        Matriz *m;
        int linhas = (rand() % 100) + 1;
        int colunas = (rand() % 100) + 1;

        MtzStatus status_criar = mtz_criar(linhas, colunas, &m);
        
        if (status_criar != MTZ_OK) {
            erro = true;
            break;
        }

        mtz_destruir(m);
    }

    VERIFICA(!erro, "mtz_criar_e_destruir_100");
}

void mtz_copiar_2x2() {
    Matriz *m;
    mtz_criar(4, 4, &m);

    mtz_definir(m, 0, 0, (rand() % 101));
    mtz_definir(m, 0, 1, (rand() % 101));
    mtz_definir(m, 1, 0, (rand() % 101));
    mtz_definir(m, 1, 1, (rand() % 101));

    Matriz *n;
    
    mtz_copiar(m, &n);

    bool erro = false;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            double valor_m;
            double valor_n;

            mtz_obter(m, i, j, &valor_m);
            mtz_obter(n, i, j, &valor_n);

            if (valor_m != valor_n) {
                erro = true;
                break;
            }
        }
    }

    VERIFICA(!erro, "mtz_copiar_2x2");
}