#include "teste.h"
#include <libmatriz.h>

#include <stdbool.h>

void mtz_criar_3x4() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    VERIFICA(status == MTZ_OK && M->linhas == 3 && m->colunas == 4, "mtz_criar_3x4");
}

void mtz_verificar_3x4_zeros() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    bool nao_zero = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int valor;
            mtz_obter(m, 3, 4, &valor);

            if (valor != 0) {
                nao_zero = false;
                break;
            }
        }
    }

    VERIFICA(nao_zero, "mtz_verificar_3x4_zeros");
}

void mtz_criar_1x1() {
    Matriz *m;
    MtzStatus status = mtz_criar(1, 1, &m);

    VERIFICA(status == MTZ_OK && M->linhas == 1 && m->colunas == 1, "mtz_criar_1x1");
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
    //É esperado que o programa quebre sem a verificação de nulidade.
    mtz_destruir(NULL);

    VERIFICA(true, "mtz_destruir_nulo");
}