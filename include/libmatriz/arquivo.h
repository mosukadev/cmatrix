#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "erro.h"
#include "matriz.h"

#include <stdio.h>

/**
 * @brief Cria uma matriz a partir de um vetor de dados.
 * @param linhas Quantidade de linhas da matriz.
 * @param colunas Quantidade de colunas da matriz.
 * @param dados Vetor contendo os elementos da matriz.
 * @param saida Recebe o endereço da matriz criada.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `dados` ou `saida` for nulo.
 * @retval MTZ_ERRO_DIMENSAO se `linhas` ou `colunas` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 */
MtzStatus mtz_de_vetor(size_t linhas, size_t colunas, const double *dados, Matriz **saida);


/**
 * @brief Imprime uma matriz em um arquivo.
 * @param m Matriz a ser impressa.
 * @param arquivo Arquivo onde a matriz será impressa.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `arquivo` for nulo.
 * @retval MTZ_ERRO_ARQUIVO se houver falha na escrita do arquivo.
 */
MtzStatus mtz_imprimir(const Matriz *m, FILE *arquivo);


/**
 * @brief Carrega uma matriz a partir de um arquivo.
 * @param caminho Caminho do arquivo que contém a matriz.
 * @param saida Recebe o endereço da matriz carregada.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `caminho` ou `saida` for nulo.
 * @retval MTZ_ERRO_MEMORIA se houver falha na alocação de memória.
 * @retval MTZ_ERRO_ARQUIVO se houver falha ao abrir ou ler o arquivo.
 * @retval MTZ_ERRO_FORMATO se o conteúdo do arquivo estiver em formato inválido.
 */
MtzStatus mtz_carregar(const char *caminho, Matriz **saida);


/**
 * @brief Salva uma matriz em um arquivo.
 * @param m Matriz a ser salva.
 * @param caminho Caminho do arquivo onde a matriz será salva.
 * @return MTZ_OK em caso de sucesso.
 * @retval MTZ_ERRO_NULO se `m` ou `caminho` for nulo.
 * @retval MTZ_ERRO_ARQUIVO se houver falha ao abrir ou escrever no arquivo.
 */
MtzStatus mtz_salvar(const Matriz *m, const char *caminho);

#endif