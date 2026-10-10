#include "matriz_interno.h"
#include <libmatriz/matriz.h>

MtzStatus mtz_criar(size_t linhas, size_t colunas, Matriz **saida) {
    if (saida == NULL) return MTZ_ERRO_NULO;
    if (linhas == 0 || colunas == 0) return MTZ_ERRO_DIMENSAO;
    
    *saida = calloc(1, sizeof **saida);
    
    if (*saida == NULL) return MTZ_ERRO_MEMORIA;
    
    (*saida)->linhas = linhas;
    (*saida)->colunas = colunas;
    (*saida)->dados = malloc(linhas * colunas * sizeof *((*saida)->dados));

    if ((*saida)->dados == NULL) {
        free(*saida);
        *saida =NULL;
        return MTZ_ERRO_MEMORIA;
    }
    
    return MTZ_OK;
}

void mtz_destruir(Matriz *m) {
    if (m == NULL) return;
    
    free(m->dados);
    free(m);
}

MtzStatus mtz_copiar(const Matriz *origem, Matriz **saida) {
    if (origem == NULL || saida == NULL) return MTZ_ERRO_NULO;
    
    MtzStatus status = mtz_criar(origem->linhas, origem->colunas, saida);

    if (status != MTZ_OK) return status;
    
    for (int i = 0; i < origem->linhas * origem->colunas; i++) {
        ((*saida)->dados)[i] = origem->dados[i];
    }

    return MTZ_OK;
}

MtzStatus mtz_obter(const Matriz *m, size_t i, size_t j, double *saida) {
    if (m == NULL || saida == NULL) return MTZ_ERRO_NULO;
    if (i >= m->linhas || j >= m->colunas) return MTZ_ERRO_INDICE;
    
    *saida = MTZ_EM(m, i, j);

    return MTZ_OK;
}

MtzStatus mtz_definir(Matriz *m, size_t i, size_t j, double valor) {
    if (m == NULL) return MTZ_ERRO_NULO;
    if (i >= m->linhas || j >= m->colunas) return MTZ_ERRO_INDICE;
    
    MTZ_EM(m, i, j) = valor;

    return MTZ_OK;
}

size_t mtz_linhas(const Matriz *m) {
    if (m == NULL) return 0;
    
    return m->linhas;
}

size_t mtz_colunas(const Matriz *m) {
    if (m == NULL) return 0;
    
    return m->colunas;
}
