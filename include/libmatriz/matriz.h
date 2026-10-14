#ifndef MATRIZ_H
#define MATRIZ_H

#include "erro.h"

#include <stdlib.h>

typedef struct Matriz Matriz;

/**
 * @brief Cria uma matriz e armazena seu endereço em `saida`.
 * @param linhas Quantidade de linhas da matriz.
 * @param colunas Quantidade de colunas da matriz.
 * @param saida Recebe o endereço da matriz criada.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `saida` for nulo.
 * @retval MTZ_ERRO_DIMENSAO se `linhas` ou `colunas` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_criar(size_t linhas, size_t colunas, Matriz **saida);

/**
 * @brief Libera a memória ocupada pela matriz.
 * @param m Matriz a ser destruída.
 */
void mtz_destruir(Matriz *m);

/**
 * @brief Cria uma cópia de uma matriz.
 * @param origem Matriz a ser copiada.
 * @param saida Recebe o endereço da matriz criada.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `origem` ou `saida` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_copiar(const Matriz *origem, Matriz **saida);

/**
 * @brief Obtém o valor de um elemento da matriz.
 * @param m Matriz que contém o elemento.
 * @param i Índice da linha.
 * @param j Índice da coluna.
 * @param saida Recebe o endereço do valor obtido.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `saida` for nulo.
 * @retval MTZ_ERRO_INDICE se `i` ou `j` estiver fora dos limites da matriz.
 */
MtzStatus mtz_obter(const Matriz *m, size_t i, size_t j, double *saida);

/**
 * @brief Define o valor de um elemento da matriz.
 * @param m Matriz que terá o elemento definido.
 * @param i Índice da linha.
 * @param j Índice da coluna.
 * @param valor Valor a ser inserido na posição `(i,j)`.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` for nulo.
 * @retval MTZ_ERRO_INDICE se `i` ou `j` estiver fora dos limites da matriz.
 */
MtzStatus mtz_definir(Matriz *m, size_t i, size_t j, double valor);

/**
 * @brief Obtém a quantidade de linhas da matriz.
 * @param m Matriz da qual serão obtidas as linhas.
 * @return A quantidade de linhas da matriz ou 0 se `m` for nulo.
 */
size_t mtz_linhas(const Matriz *m);

/**
 * @brief Obtém a quantidade de colunas da matriz.
 * @param m Matriz da qual serão obtidas as colunas.
 * @return A quantidade de colunas da matriz ou 0 se `m` for nulo.
 */
size_t mtz_colunas(const Matriz *m);

#endif