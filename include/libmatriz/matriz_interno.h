#ifndef matriz_interno_h
#define matriz_interno_h

struct Matriz {
    size_t linhas;
    site_t colunas;
    double *dados;
};

#define MTZ_EM(m, i, j) ((m)->dados[(i) * (m)->colunas + (j)])

#endif