#include <libmatriz/erro.h>

const char *mtz_mensagem_erro(MtzStatus status) {
    switch (status) {
        case MTZ_ERRO_NULO:
            return "Ponteiro nulo recebido.";
            break;
        case MTZ_ERRO_DIMENSAO:
            return "Dimensões incompatíveis ou nulas.";
            break;
        case MTZ_ERRO_INDICE:
            return "Posição fora da matriz.";
            break;
        case MTZ_ERRO_MEMORIA:
            return "Falha na alocação.";
            break;
        case MTZ_ERRO_NAO_QUADRADA:
            return "Operação exige matriz quadrada.";
            break;
        case MTZ_ERRO_ARQUIVO:
            return "Falha ao abrir ou gerar arquivo.";
            break;
        case MTZ_ERRO_FORMATO:
            return "Conteúdo de arquivo inválido.";
            break;
        default:
            return "Erro desconhecido";
            break;
    }
    
}