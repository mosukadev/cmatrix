#ifndef PROPRIEDADES_H
#define PROPRIEDADES_H

MtzStatus mtz_traco(const Matriz *m, double *saida);

int mtz_e_quadrada(const Matriz *m);

int mtz_e_simetrica(const Matriz *m, double eps);

int mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps);

#endif