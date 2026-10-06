#ifndef _operacoes_h
#define _operacoes_h

MtzStatus mtz_somar(const Matriz *a, const Matriz *b, Matriz **saida);

MtzStatus mtz_subtrair(const Matriz *a, const Matriz *b, Matriz **saida);

MtzStatus mtz_multiplicar(const Matriz *a, const Matriz *b, Matriz **saida);

MtzStatus mtz_escalar(const Matriz *m, double k, Matriz **saida);

MtzStatus mtz_transpor(const Matriz *m, Matriz **saida);

#endif