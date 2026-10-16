#include "teste.h"
#include "teste_matriz.h"
#include <libmatriz.h>

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

void mtz_criar_3x4(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(3, 5, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_criar_3x4");
        return;
    }

    bool correto = mtz_linhas(m) == 3 && mtz_colunas(m) == 4;

    mtz_destruir(m);
    VERIFICA(correto, "mtz_criar_3x4");
}

void mtz_verificar_3x4_zeros(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(3, 4, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_verificar_3x4_zeros");
        return;
    }

    bool correto = true;

    for (size_t i = 0; i < 3 && correto; i++) {
        for (size_t j = 0; j < 4; j++) {
            double valor = 0.0;
            status = mtz_obter(m, i, j, &valor);

            if (status != MTZ_OK || fabs(valor) >= EPSILON) {
                correto = false;
                break;
            }
        }
    }

    mtz_destruir(m);
    VERIFICA(correto, "mtz_verificar_3x4_zeros");
}

void mtz_criar_1x1(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(1, 1, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_criar_1x1");
        return;
    }

    bool correto = mtz_linhas(m) == 1 && mtz_colunas(m) == 1;

    mtz_destruir(m);
    VERIFICA(correto, "mtz_criar_1x1");
}

void mtz_criar_0_linhas(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(0, 7, &m);

    VERIFICA(status == MTZ_ERRO_DIMENSAO, "mtz_criar_0_linhas");
}

void mtz_criar_0_colunas(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 0, &m);

    VERIFICA(status == MTZ_ERRO_DIMENSAO, "mtz_criar_0_colunas");
}

void mtz_criar_saida_nula(void) {
    MtzStatus status = mtz_criar(6, 7, NULL);

    VERIFICA(status == MTZ_ERRO_NULO, "mtz_criar_saida_nula");
}

void mtz_destruir_nulo(void) {
    mtz_destruir(NULL);

    VERIFICA(true, "mtz_destruir_nulo");
}

void mtz_criar_e_destruir_100(void) {
    bool correto = true;

    for (int i = 0; i < 100; i++) {
        Matriz *m = NULL;
        MtzStatus status = mtz_criar(6, 7, &m);

        if (status != MTZ_OK) {
            correto = false;
            break;
        }

        mtz_destruir(m);
    }

    VERIFICA(correto, "mtz_criar_e_destruir_100");
}

void mtz_copiar_2x2(void) {
    Matriz *m = NULL;
    Matriz *n = NULL;

    MtzStatus status = mtz_criar(2, 2, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_copiar_2x2");
        return;
    }

    bool correto =
        mtz_definir(m, 0, 0, 6) == MTZ_OK &&
        mtz_definir(m, 0, 1, 7) == MTZ_OK &&
        mtz_definir(m, 1, 0, 6) == MTZ_OK &&
        mtz_definir(m, 1, 1, 9) == MTZ_OK;

    if (correto) {
        correto = mtz_copiar(m, &n) == MTZ_OK;
    }

    if (correto) {
        for (size_t i = 0; i < 2 && correto; i++) {
            for (size_t j = 0; j < 2; j++) {
                double valor_m;
                double valor_n;

                MtzStatus status_m = mtz_obter(m, i, j, &valor_m);
                MtzStatus status_n = mtz_obter(n, i, j, &valor_n);

                if (status_m != MTZ_OK || status_n != MTZ_OK || fabs(valor_m - valor_n) >= EPSILON) {
                    correto = false;
                    break;
                }
            }
        }
    }

    mtz_destruir(n);
    mtz_destruir(m);

    VERIFICA(correto, "mtz_copiar_2x2");
}

void mtz_copiar_e_mudar_valor(void) {
    Matriz *m = NULL;
    Matriz *n = NULL;

    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_copiar_e_mudar_valor");
        return;
    }

    bool correto = mtz_definir(m, 0, 0, 67) == MTZ_OK;

    if (correto) {
        correto = mtz_copiar(m, &n) == MTZ_OK;
    }

    if (correto) {
        correto = mtz_definir(n, 0, 0, 69) == MTZ_OK;
    }

    double valor_obtido = 0.0;

    if (correto) {
        correto = mtz_obter(m, 0, 0, &valor_obtido) == MTZ_OK;
    }

    if (correto) {
        correto = fabs(valor_obtido - 67.0) < EPSILON;
    }

    mtz_destruir(n);
    mtz_destruir(m);

    VERIFICA(correto, "mtz_copiar_e_mudar_valor");
}

void mtz_copiar_origem_nula(void) {
    Matriz *n = NULL;
    MtzStatus status = mtz_copiar(NULL, &n);

    VERIFICA(status == MTZ_ERRO_NULO, "mtz_copiar_origem_nula");
}

void mtz_obter_1_1(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_obter_1_1");
        return;
    }

    bool correto = mtz_definir(m, 1, 1, 67) == MTZ_OK;
    double valor_obtido = 0.0;

    if (correto) {
        correto = mtz_obter(m, 1, 1, &valor_obtido) == MTZ_OK;
    }

    if (correto) {
        correto = fabs(valor_obtido - 67.0) < EPSILON;
    }

    mtz_destruir(m);
    VERIFICA(correto, "mtz_obter_1_1");
}

void mtz_obter_ultima_posicao(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_obter_ultima_posicao");
        return;
    }

    double valor_obtido;
    status = mtz_obter(m, 5, 6, &valor_obtido);

    mtz_destruir(m);
    VERIFICA(status == MTZ_OK, "mtz_obter_ultima_posicao");
}

void mtz_obter_linha_pelo_numero_de_linhas(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_obter_linha_pelo_numero_de_linhas");
        return;
    }

    double valor_obtido;
    status = mtz_obter(m, 6, 0, &valor_obtido);

    mtz_destruir(m);
    VERIFICA(status == MTZ_ERRO_INDICE, "mtz_obter_linha_pelo_numero_de_linhas");
}

void mtz_obter_matriz_nula(void) {
    double valor_obtido;
    MtzStatus status = mtz_obter(NULL, 4, 0, &valor_obtido);

    VERIFICA(status == MTZ_ERRO_NULO, "mtz_obter_matriz_nula");
}

void mtz_definir_7_em_0_1(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_definir_7_em_0_1");
        return;
    }

    bool correto = mtz_definir(m, 0, 1, 7) == MTZ_OK;
    double valor_obtido = 0.0;

    if (correto) {
        correto = mtz_obter(m, 0, 1, &valor_obtido) == MTZ_OK;
    }

    if (correto) {
        correto = fabs(valor_obtido - 7.0) < EPSILON;
    }

    mtz_destruir(m);
    VERIFICA(correto, "mtz_definir_7_em_0_1");
}

void mtz_definir_coluna_inexistente(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(6, 7, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_definir_coluna_inexistente");
        return;
    }

    status = mtz_definir(m, 0, 67, 67);

    mtz_destruir(m);
    VERIFICA(status == MTZ_ERRO_INDICE, "mtz_definir_coluna_inexistente");
}

void mtz_linhas_colunas_2x5(void) {
    Matriz *m = NULL;
    MtzStatus status = mtz_criar(2, 5, &m);

    if (status != MTZ_OK) {
        VERIFICA(false, "mtz_linhas_colunas_2x5");
        return;
    }

    size_t linhas = mtz_linhas(m);
    size_t colunas = mtz_colunas(m);
    bool correto = linhas == 2 && colunas == 5;

    mtz_destruir(m);
    VERIFICA(correto, "mtz_linhas_colunas_2x5");
}

void mtz_linhas_colunas_matriz_nula(void) {
    size_t linhas = mtz_linhas(NULL);
    size_t colunas = mtz_colunas(NULL);

    VERIFICA(linhas == 0 && colunas == 0, "mtz_linhas_colunas_matriz_nula");
}
