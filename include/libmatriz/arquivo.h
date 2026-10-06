#ifndef _arquivo_h
#define _arquivo_h

MtzStatus mtz_de_vetor(size_t linhas, size_t colunas, const double *dados, Matriz **saida);

MtzStatus mtz_imprimir(const Matriz *m, FILE *arquivo);

MtzStatus mtz_carregar(const char *caminho, Matriz **saida);

MtzStatus mtz_salvar(const Matriz *m, const char *caminho);

#endif