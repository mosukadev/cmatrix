#include "operacoes.h"

/* Libera a matriz criada e deixa a saida como NULL. */
static MtzStatus falha_operacao(
    Matriz *resultado,
    Matriz **saida,
    MtzStatus status
) {
    /* liberar resultado */
    /* *saida = NULL */
    /* devolver status */
}

/* Soma duas matrizes de mesma dimensao. */
MtzStatus mtz_somar(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    /* conferir saida */
    /* *saida = NULL */
    /* conferir a e b */
    /* conferir se tem o mesmo tamanho */
    /* criar resultado */
    /* percorrer e gravar a + b */
    /* entregar resultado */
}

/* Subtrai duas matrizes de mesma dimensao. */
MtzStatus mtz_subtrair(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    /* igual a soma, gravando a - b */
}

/* Multiplica duas matrizes compativeis. */
MtzStatus mtz_multiplicar(
    const Matriz *a,
    const Matriz *b,
    Matriz **saida
) {
    /* conferir saida, *saida = NULL, conferir a e b */
    /* conferir colunas de a == linhas de b */
    /* criar resultado: linhas de a x colunas de b */
    /* para cada (i, j): somar a(i,k) * b(k,j) e gravar */
    /* entregar resultado */
}

/* Multiplica todos os elementos por um escalar. */
MtzStatus mtz_escalar(
    const Matriz *m,
    double k,
    Matriz **saida
) {
    /* conferir saida, *saida = NULL, conferir m */
    /* criar resultado do mesmo tamanho */
    /* percorrer e gravar valor * k */
    /* entregar resultado */
}

/* Troca linhas por colunas. */
MtzStatus mtz_transpor(
    const Matriz *m,
    Matriz **saida
) {
    /* conferir saida, *saida = NULL, conferir m */
    /* criar resultado: colunas x linhas */
    /* ler (i, j) e gravar em (j, i) */
    /* entregar resultado */
}
