#ifndef MTZ_OPERACOES_H
#define MTZ_OPERACOES_H

#include "erro.h"
#include "matriz.h"

/**
 * @brief Soma duas matrizes de mesma dimensao.
 * @param a Primeira matriz.
 * @param b Segunda matriz, com as mesmas dimensoes de a.
 * @param saida Recebe a matriz resultante, com as mesmas dimensoes de a e b.
 *              Em caso de erro, recebe NULL.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se algum parametro for nulo.
 * @retval MTZ_ERRO_DIMENSAO se as matrizes tiverem dimensoes diferentes.
 * @retval MTZ_ERRO_MEMORIA se nao houver memoria disponivel.
 */
MtzStatus mtz_somar(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Subtrai duas matrizes de mesma dimensao (a - b).
 * @param a Matriz da qual os valores serao subtraidos.
 * @param b Matriz subtraida, com as mesmas dimensoes de a.
 * @param saida Recebe a matriz resultante, com as mesmas dimensoes de a e b.
 *              Em caso de erro, recebe NULL.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se algum parametro for nulo.
 * @retval MTZ_ERRO_DIMENSAO se as matrizes tiverem dimensoes diferentes.
 * @retval MTZ_ERRO_MEMORIA se nao houver memoria disponivel.
 */
MtzStatus mtz_subtrair(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Multiplica duas matrizes.
 * @param a Matriz da esquerda, de dimensao m por n.
 * @param b Matriz da direita, de dimensao n por p.
 * @param saida Recebe a matriz resultante, de dimensao m por p.
 *              Em caso de erro, recebe NULL.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se algum parametro for nulo.
 * @retval MTZ_ERRO_DIMENSAO se o numero de colunas de a for diferente
 *         do numero de linhas de b.
 * @retval MTZ_ERRO_MEMORIA se nao houver memoria disponivel.
 */
MtzStatus mtz_multiplicar(const Matriz *a, const Matriz *b, Matriz **saida);

/**
 * @brief Multiplica todos os valores de uma matriz por um numero.
 * @param m Matriz de entrada.
 * @param k Numero pelo qual cada valor sera multiplicado.
 * @param saida Recebe a matriz resultante, com as mesmas dimensoes de m.
 *              Em caso de erro, recebe NULL.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se m ou saida for nulo.
 * @retval MTZ_ERRO_MEMORIA se nao houver memoria disponivel.
 */
MtzStatus mtz_escalar(const Matriz *m, double k, Matriz **saida);

/**
 * @brief Troca as linhas pelas colunas de uma matriz.
 * @param m Matriz de entrada, de dimensao m por n.
 * @param saida Recebe a matriz transposta, de dimensao n por m.
 *              Em caso de erro, recebe NULL.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se m ou saida for nulo.
 * @retval MTZ_ERRO_MEMORIA se nao houver memoria disponivel.
 */
MtzStatus mtz_transpor(const Matriz *m, Matriz **saida);

#endif /* MTZ_OPERACOES_H */
