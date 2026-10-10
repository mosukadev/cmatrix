#include <libmatriz/operacoes.h>
#include "matriz_interno.h"
/* Soma duas matrizes de mesma dimensao. */
MtzStatus mtz_somar(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    *saida = NULL;
    if (a == NULL || b == NULL) return MTZ_ERRO_NULO;
    if (a->linhas != b->linhas || a->colunas != b->colunas) return MTZ_ERRO_DIMENSAO;
    Matriz *resultado = NULL;
    if (mtz_criar(a->linhas, a->colunas, &resultado) != MTZ_OK) return MTZ_ERRO_MEMORIA;
    for (size_t i = 0; i < a->linhas; i++) {
        for (size_t j = 0; j < a->colunas; j++) {
            resultado->dados[i * a->colunas + j] = a->dados[i * a->colunas + j] + b->dados[i * a->colunas + j];
        }
    }
    *saida = resultado;
    return MTZ_OK;
}

/* Subtrai duas matrizes de mesma dimensao. */
MtzStatus mtz_subtrair(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    *saida = NULL;
    if (a == NULL || b == NULL) return MTZ_ERRO_NULO;
    if (a->linhas != b->linhas || a->colunas != b->colunas) return MTZ_ERRO_DIMENSAO;
    Matriz *resultado = NULL;
    if (mtz_criar(a->linhas, a->colunas, &resultado) != MTZ_OK) return MTZ_ERRO_MEMORIA;
    for (size_t i = 0; i < a->linhas; i++) {
        for (size_t j = 0; j < a->colunas; j++) {
            resultado->dados[i * a->colunas + j] = a->dados[i * a->colunas + j] - b->dados[i * a->colunas + j];
        }
    }
    *saida = resultado;
    return MTZ_OK;
}

/* Multiplica duas matrizes compativeis. */
MtzStatus mtz_multiplicar(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    *saida = NULL;
    if (a == NULL || b == NULL) return MTZ_ERRO_NULO;
    if (a->colunas != b->linhas) return MTZ_ERRO_DIMENSAO;
    Matriz *resultado = NULL;
    MtzStatus status = mtz_criar(a->linhas, b->colunas, &resultado);
    if (status != MTZ_OK) return status;
    for (size_t i = 0; i < a->linhas; i++) {
        for (size_t j = 0; j < b->colunas; j++) {
            double soma = 0.0;
            for (size_t k = 0; k < a->colunas; k++) {
                soma += a->dados[i * a->colunas + k] * b->dados[k * b->colunas + j];
            }
            resultado->dados[i * resultado->colunas + j] = soma;
        }
    }
    *saida = resultado;
    return MTZ_OK;
}

/* Multiplica todos os elementos por um escalar. */
MtzStatus mtz_escalar(
    const Matriz *m,
    double k,
    Matriz **saida
) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    *saida = NULL;
    if (m == NULL) return MTZ_ERRO_NULO;
    Matriz *resultado = NULL;
    if (mtz_criar(m->linhas, m->colunas, &resultado) != MTZ_OK) return MTZ_ERRO_MEMORIA;
    for (size_t i = 0; i < m->linhas; i++) {
        for (size_t j = 0; j < m->colunas; j++) {
            resultado->dados[i * m->colunas + j] = m->dados[i * m->colunas + j] * k;
        }
    }
    *saida = resultado;
    return MTZ_OK;
}

/* Troca linhas por colunas. */
MtzStatus mtz_transpor(
    const Matriz *m,
    Matriz **saida
) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    *saida = NULL;
    if (m == NULL) return MTZ_ERRO_NULO;
    Matriz *resultado = NULL;
    MtzStatus status = mtz_criar(m->colunas, m->linhas, &resultado);
    if (status != MTZ_OK) return status;
    for (size_t i = 0; i < m->linhas; i++) {
        for (size_t j = 0; j < m->colunas; j++) {
            resultado->dados[j * resultado->colunas + i] = m->dados[i * m->colunas + j];
        }
    }
    *saida = resultado;
    return MTZ_OK;
}
