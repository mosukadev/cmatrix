#ifndef MATRIZ_INTERNO_H
#define MATRIZ_INTERNO_H

struct Matriz {
    size_t linhas;
    size_t colunas;
    double *dados;
};

#define MTZ_EM(m, i, j) ((m)->dados[(i) * (m)->colunas + (j)])

#endif