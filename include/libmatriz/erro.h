#ifndef ERRO_H
#define ERRO_H

/**
 * @file erro.h
 * @brief Códigos de status retornados pelas funções da biblioteca.
 */
typedef enum {
    MTZ_OK = 0,             /**< Operação realizada com sucesso. */
    MTZ_ERRO_NULO,          /**< Ponteiro nulo recebido. */
    MTZ_ERRO_DIMENSAO,      /**< Dimensão inválida ou incompatível. */
    MTZ_ERRO_INDICE,        /**< Índice fora dos limites da matriz. */
    MTZ_ERRO_MEMORIA,       /**< Falha na alocação de memória. */
    MTZ_ERRO_NAO_QUADRADA,  /**< Operação exige uma matriz quadrada. */
    MTZ_ERRO_ARQUIVO,       /**< Falha ao abrir, ler ou gravar arquivo. */
    MTZ_ERRO_FORMATO,       /**< Conteúdo do arquivo em formato inválido. */
    MTZ_ITERATOR            /**< Marca o final do enum para iterar sobre ele */
} MtzStatus;

/**
 * @brief Obtém uma mensagem descritiva para um código de status.
 * @param status Código de status do qual será obtida a mensagem.
 * @return Uma string constante contendo a mensagem correspondente ao status.
 */
const char *mtz_mensagem_erro(MtzStatus status);

#endif