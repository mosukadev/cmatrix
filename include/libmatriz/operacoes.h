#ifndef OPERACOES_H
#define OPERACOES_H

#include "erro.h"
#include "matriz.h"

/**
 * @brief Soma duas matrizes.
 *
 * As matrizes devem possuir as mesmas dimensões.
 *
 * @param a Primeira matriz da soma.
 * @param b Segunda matriz da soma.
 * @param saida Recebe o endereço da matriz resultante.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `a`, `b` ou `saida` for nulo.
 * @retval MTZ_ERRO_DIMENSAO se as matrizes possuírem dimensões diferentes.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_somar(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Subtrai uma matriz de outra.
 *
 * As matrizes devem possuir as mesmas dimensões.
 *
 * @param a Matriz da qual será subtraída `b`.
 * @param b Matriz a ser subtraída de `a`.
 * @param saida Recebe o endereço da matriz resultante.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `a`, `b` ou `saida` for nulo.
 * @retval MTZ_ERRO_DIMENSAO se as matrizes possuírem dimensões diferentes.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_subtrair(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Multiplica duas matrizes.
 *
 * A multiplicação é possível quando a quantidade de colunas de `a`
 * é igual à quantidade de linhas de `b`.
 *
 * @param a Primeira matriz da multiplicação.
 * @param b Segunda matriz da multiplicação.
 * @param saida Recebe o endereço da matriz resultante.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `a`, `b` ou `saida` for nulo.
 * @retval MTZ_ERRO_DIMENSAO se as dimensões das matrizes forem incompatíveis.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_multiplicar(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Multiplica uma matriz por um escalar.
 *
 * Cada elemento da matriz é multiplicado pelo valor de `k`.
 *
 * @param m Matriz a ser multiplicada.
 * @param k Escalar pelo qual a matriz será multiplicada.
 * @param saida Recebe o endereço da matriz resultante.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `saida` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_escalar(const Matriz *m, double k, Matriz **saida);

/**
 * @brief Calcula a matriz transposta.
 *
 * A matriz resultante possui as linhas e colunas invertidas em relação
 * à matriz original.
 *
 * @param m Matriz a ser transposta.
 * @param saida Recebe o endereço da matriz transposta.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `saida` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_transpor(const Matriz *m, Matriz **saida);

#endif