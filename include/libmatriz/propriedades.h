#ifndef MTZ_PROPRIEDADES_H
#define MTZ_PROPRIEDADES_H

#include <stdbool.h>

#include "erro.h"
#include "matriz.h"

/**
 * @brief Calcula o traço de uma matriz.
 *
 * O traço é a soma dos elementos da diagonal principal.
 * A operação é definida apenas para matrizes quadradas.
 *
 * @param m Matriz da qual será calculado o traço.
 * @param saida Recebe o valor do traço.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `saida` for nulo.
 * @retval MTZ_ERRO_NAO_QUADRADA se a matriz não for quadrada.
 */
MtzStatus mtz_traco(const Matriz *m, double *saida);

/**
 * @brief Calcula o determinante de uma matriz.
 *
 * O determinante é definido apenas para matrizes quadradas.
 *
 * @param m Matriz da qual será calculado o determinante.
 * @param saida Recebe o valor do determinante.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `saida` for nulo.
 * @retval MTZ_ERRO_NAO_QUADRADA se a matriz não for quadrada.
 */
MtzStatus mtz_determinante(const Matriz *m, double *saida);

/**
 * @brief Verifica se uma matriz é quadrada.
 *
 * Uma matriz é quadrada quando possui a mesma quantidade de linhas
 * e colunas.
 *
 * @param m Matriz a ser verificada.
 * @return true se a matriz for quadrada e false caso contrário.
 *
 * @note Retorna false se `m` for nulo.
 */
bool mtz_e_quadrada(const Matriz *m);

/**
 * @brief Verifica se uma matriz é simétrica.
 *
 * Uma matriz é simétrica quando é quadrada e seus elementos satisfazem
 * A[i][j] = A[j][i] para todos os índices válidos.
 *
 * A comparação utiliza `eps` como tolerância para diferenças decorrentes
 * de cálculos com ponto flutuante.
 *
 * @param m Matriz a ser verificada.
 * @param eps Tolerância utilizada na comparação dos elementos.
 * @return true se a matriz for simétrica e false caso contrário.
 *
 * @note Retorna false se `m` for nulo.
 */
bool mtz_e_simetrica(const Matriz *m, double eps);

/**
 * @brief Verifica se duas matrizes são iguais.
 *
 * Duas matrizes são consideradas iguais quando possuem as mesmas
 * dimensões e a diferença entre elementos correspondentes não excede
 * `eps`.
 *
 * @param a Primeira matriz a ser comparada.
 * @param b Segunda matriz a ser comparada.
 * @param eps Tolerância utilizada na comparação dos elementos.
 * @return true se as matrizes forem iguais e false caso contrário.
 *
 * @note Retorna false se `a` ou `b` for nulo.
 */
bool mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps);

#endif