#ifndef _propriedades_h
#define _propriedades_h

MtzStatus mtz_traco(const Matriz *m, double *saida);

MtzStatus mtz_determinante(const Matriz *m, double *saida);

bool mtz_e_quadrada(const Matriz *m);

bool mtz_e_simetrica(const Matriz *m, double eps);

bool mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps);

#endif