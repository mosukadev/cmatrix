#ifndef _matriz_h
#define _matriz_h

MtzStatus mtz_criar(size_t linhas, size_t colunas, Matriz **saida);

void mtz_destruir(Matriz *m);

MtzStatus mtz_copiar(const Matriz *origem, Matriz **saida);

MtzStatus mtz_obter(const Matriz *m, size_t i, size_t j, double **saida);

MtzStatus mtz_definir(Matriz *m, size_t i, size_t j, double valor);

size_t mtz_linhas(const Matriz *m);

size_t mtz_colunas(const Matriz *m);

#endif