
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
    
    for (size_t i = 0; i < origem->linhas * origem->colunas; i++) {
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
