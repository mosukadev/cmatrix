#include <stdio.h>
#include <stddef.h>
#include "teste.h"
#include "teste_erro.h"
#include "teste_matriz.h"
#include "teste_operacoes.h"
#include "teste_propriedades.h"
#include "teste_arquivo.h"

int g_total_testes = 0;
int g_testes_passaram = 0;
int g_testes_falharam = 0;

typedef void (*FuncaoTeste)(void);

static const FuncaoTeste testes[] = {
    mtz_de_vetor_ok,
    //mtz_de_vetor_nulo,
    mtz_de_vetor_zero_linhas,
    // mtz_mensagem_erro_ok,
    // mtz_mensagens_erros_diferentes,
    // mtz_codigo_erro_invalido,
    // mtz_criar_3x4,
    // mtz_verificar_3x4_zeros,
    // mtz_criar_1x1,
    // mtz_criar_0_linhas,
    // mtz_criar_0_colunas,
    // mtz_criar_saida_nula,
    // mtz_destruir_nulo,
    // mtz_criar_e_destruir_100,
    // mtz_copiar_2x2,
    // mtz_copiar_e_mudar_valor,
    // mtz_copiar_origem_nula,
    // mtz_obter_1_1,
    // mtz_obter_ultima_posicao,
    // mtz_obter_linha_pelo_numero_de_linhas,
    // mtz_obter_matriz_nula,
    // mtz_definir_7_em_0_1,
    // mtz_definir_coluna_inexistente,
    // mtz_linhas_colunas_2x5,
    // mtz_linhas_colunas_matriz_nula,
    // teste_somar_A_mais_B,
    // teste_somar_dimensoes_diferentes,
    // teste_somar_matriz_nula,
    // teste_subtrair_A_menos_B,
    // teste_subtrair_de_si_mesma,
    // teste_subtrair_dimensoes_diferentes,
    // teste_multiplicar_C_por_D,
    // teste_multiplicar_pela_identidade,
    // teste_multiplicar_dimensoes_incompativeis,
    // teste_multiplicar_dimensao_do_resultado,
    // teste_escalar_por_dois,
    // teste_escalar_por_zero,
    // teste_escalar_por_menos_um,
    // teste_escalar_matriz_nula,
    // teste_transpor_2x3,
    // teste_transpor_duas_vezes,
    // teste_transpor_1x4,
    // teste_soma_com_zero,
    // teste_subtracao_resulta_zero,
    // teste_soma_comutativa,
    // teste_identidade_multiplicativa,
    // teste_transposta_da_transposta,
    // teste_determinante_da_transposta,
    // teste_transposta_do_produto,
    // teste_escalar_por_um,
    // teste_traco_de_A,
    // teste_traco_de_2x3,
    // teste_traco_de_1x1,
    // teste_determinante_F,
    // teste_determinante_E,
    // teste_determinante_identidade,
    // teste_determinante_G,
    // teste_determinante_H,
    // teste_determinante_unico_elemento,
    // teste_determinante_2x3,
    // teste_determinante_nao_altera_matriz,
    // teste_quadrada_3x3,
    // teste_quadrada_2x3,
    // teste_quadrada_NULL,
    // teste_simetrica_S,
    // teste_simetrica_A,
    // teste_simetrica_2x3,
    // teste_igual_mesma,
    // teste_igual_tamanhos_diferentes,
    // teste_igual_diferenca_dentro_tolerancia,
    // teste_igual_uma_nula
};

int main() {

    for (size_t i = 0; i < sizeof testes / sizeof testes[0]; i++) {
        testes[i]();
    }

    printf("Total: %d, Passaram: %d, Falharam: %d\n", g_total_testes, g_testes_passaram, g_testes_falharam);

    return g_testes_falharam == 0 ? 0 : 1;
}