#include <stdio.h>
#include <libmatriz/arquivo.h>
#include <libmatriz/matriz.h>
#include <libmatriz/operacoes.h>
#include <libmatriz/propriedades.h>
#include "../src/matriz_interno.h"
#include "teste.h"
#include "teste_operacoes.h"

static double dados_a[] = {1, 2, 3, 4};
static double dados_b[] = {5, 6, 7, 8};
static double dados_c[] = {1, 2, 3, 4, 5, 6};
static double dados_d[] = {7, 8, 9, 10, 11, 12};
static double dados_i[] = {1, 0, 0, 1};
static double dados_zero[] = {0, 0, 0, 0};
static Matriz *A, *B, *C, *D, *I, *Z, *R, *T, *esperada, *temp;

static double esperado, saida;
static MtzStatus status;
static bool veracidade;
static double eps =  1e-9;

/* mtz_somar */
void teste_somar_A_mais_B(void){
    static double dados_esperado[] = {6, 8, 10, 12};
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_b, &B);
    mtz_de_vetor(2, 2, dados_esperado, &esperada);
    status = mtz_somar(A, B, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "somar_A_mais_B");
    mtz_destruir(A); mtz_destruir(B); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_somar_dimensoes_diferentes(void){
    R = NULL;
    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_de_vetor(3, 2, dados_d, &D);
    status = mtz_somar(C, D, &R);
    VERIFICA_IGUAL(status, MTZ_ERRO_DIMENSAO, "somar_dimensoes_diferentes");
    mtz_destruir(C); mtz_destruir(D); mtz_destruir(R);
}

void teste_somar_matriz_nula(void){
    R = NULL;
    mtz_de_vetor(2, 2, dados_b, &B);
    status = mtz_somar(NULL, B, &R);
    VERIFICA_IGUAL(status, MTZ_ERRO_NULO, "somar_matriz_nula");
    mtz_destruir(B); mtz_destruir(R);
}

/* mtz_subtrair */
void teste_subtrair_A_menos_B(void){
    static double dados_esperado[] = {-4, -4, -4, -4};
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_b, &B);
    mtz_de_vetor(2, 2, dados_esperado, &esperada);
    status = mtz_subtrair(A, B, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "subtrair_A_menos_B");
    mtz_destruir(A); mtz_destruir(B); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_subtrair_de_si_mesma(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_a, &temp);
    mtz_de_vetor(2, 2, dados_zero, &Z);
    status = mtz_subtrair(A, temp, &R);
    veracidade = mtz_sao_iguais(R, Z, eps);
    VERIFICA_IGUAL(veracidade, true, "subtrair_de_si_mesma");
    mtz_destruir(A); mtz_destruir(temp); mtz_destruir(Z); mtz_destruir(R);
}

void teste_subtrair_dimensoes_diferentes(void){
    R = NULL;
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_subtrair(A, C, &R);
    VERIFICA_IGUAL(status, MTZ_ERRO_DIMENSAO, "subtrair_dimensoes_diferentes");
    mtz_destruir(A); mtz_destruir(C); mtz_destruir(R);
}

/* mtz_multiplicar */
void teste_multiplicar_C_por_D(void){
    static double dados_esperado[] = {58, 64, 139, 154};
    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_de_vetor(3, 2, dados_d, &D);
    mtz_de_vetor(2, 2, dados_esperado, &esperada);
    status = mtz_multiplicar(C, D, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "multiplicar_C_por_D");
    mtz_destruir(C); mtz_destruir(D); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_multiplicar_pela_identidade(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_i, &I);
    status = mtz_multiplicar(A, I, &R);
    veracidade = mtz_sao_iguais(R, A, eps);
    VERIFICA_IGUAL(veracidade, true, "multiplicar_pela_identidade");
    mtz_destruir(A); mtz_destruir(I); mtz_destruir(R);
}

void teste_multiplicar_dimensoes_incompativeis(void){
    R = NULL;
    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_de_vetor(2, 3, dados_c, &temp);
    status = mtz_multiplicar(C, temp, &R);
    VERIFICA_IGUAL(status, MTZ_ERRO_DIMENSAO, "multiplicar_dimensoes_incompativeis");
    mtz_destruir(C); mtz_destruir(temp); mtz_destruir(R);
}

void teste_multiplicar_dimensao_do_resultado(void){
    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_de_vetor(3, 2, dados_d, &D);
    status = mtz_multiplicar(C, D, &R);
    veracidade = (mtz_linhas(R) == 2 && mtz_colunas(R) == 2);
    VERIFICA_IGUAL(veracidade, true, "multiplicar_dimensao_do_resultado");
    mtz_destruir(C); mtz_destruir(D); mtz_destruir(R);
}

/* mtz_escalar */
void teste_escalar_por_dois(void){
    static double dados_esperado[] = {2, 4, 6, 8};
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_esperado, &esperada);
    status = mtz_escalar(A, 2.0, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "escalar_por_dois");
    mtz_destruir(A); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_escalar_por_zero(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_zero, &Z);
    status = mtz_escalar(A, 0.0, &R);
    veracidade = mtz_sao_iguais(R, Z, eps);
    VERIFICA_IGUAL(veracidade, true, "escalar_por_zero");
    mtz_destruir(A); mtz_destruir(Z); mtz_destruir(R);
}

void teste_escalar_por_menos_um(void){
    static double dados_esperado[] = {-1, -2, -3, -4};
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_esperado, &esperada);
    status = mtz_escalar(A, -1.0, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "escalar_por_menos_um");
    mtz_destruir(A); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_escalar_matriz_nula(void){
    R = NULL;
    status = mtz_escalar(NULL, 2.0, &R);
    VERIFICA_IGUAL(status, MTZ_ERRO_NULO, "escalar_matriz_nula");
    mtz_destruir(R);
}

/* mtz_transpor */
void teste_transpor_2x3(void){
    static double dados_esperado[] = {1, 4, 2, 5, 3, 6};
    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_de_vetor(3, 2, dados_esperado, &esperada);
    status = mtz_transpor(C, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "transpor_2x3");
    mtz_destruir(C); mtz_destruir(esperada); mtz_destruir(R);
}

void teste_transpor_duas_vezes(void){
    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_transpor(C, &T);
    status = mtz_transpor(T, &R);
    veracidade = mtz_sao_iguais(R, C, eps);
    VERIFICA_IGUAL(veracidade, true, "transpor_duas_vezes");
    mtz_destruir(C); mtz_destruir(T); mtz_destruir(R);
}

void teste_transpor_1x4(void){
    static double dados_linha[] = {1, 2, 3, 4};
    mtz_de_vetor(1, 4, dados_linha, &temp);
    mtz_de_vetor(4, 1, dados_linha, &esperada);
    status = mtz_transpor(temp, &R);
    veracidade = mtz_sao_iguais(R, esperada, eps);
    VERIFICA_IGUAL(veracidade, true, "transpor_1x4");
    mtz_destruir(temp); mtz_destruir(esperada); mtz_destruir(R);
}

/* propriedades da matematica */
void teste_soma_com_zero(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_zero, &Z);
    status = mtz_somar(A, Z, &R);
    veracidade = mtz_sao_iguais(R, A, eps);
    VERIFICA_IGUAL(veracidade, true, "soma_com_zero");
    mtz_destruir(A); mtz_destruir(Z); mtz_destruir(R);
}

void teste_subtracao_resulta_zero(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_a, &temp);
    mtz_de_vetor(2, 2, dados_zero, &Z);
    status = mtz_subtrair(A, temp, &R);
    veracidade = mtz_sao_iguais(R, Z, eps);
    VERIFICA_IGUAL(veracidade, true, "subtracao_resulta_zero");
    mtz_destruir(A); mtz_destruir(temp); mtz_destruir(Z); mtz_destruir(R);
}

void teste_soma_comutativa(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_b, &B);
    status = mtz_somar(A, B, &R);
    status = mtz_somar(B, A, &T);
    veracidade = mtz_sao_iguais(R, T, eps);
    VERIFICA_IGUAL(veracidade, true, "soma_comutativa");
    mtz_destruir(A); mtz_destruir(B); mtz_destruir(R); mtz_destruir(T);
}

void teste_identidade_multiplicativa(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_i, &I);
    status = mtz_multiplicar(A, I, &R);
    veracidade = mtz_sao_iguais(R, A, eps);
    VERIFICA_IGUAL(veracidade, true, "identidade_multiplicativa");
    mtz_destruir(A); mtz_destruir(I); mtz_destruir(R);
}

void teste_transposta_da_transposta(void){
    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_transpor(C, &T);
    status = mtz_transpor(T, &R);
    veracidade = mtz_sao_iguais(R, C, eps);
    VERIFICA_IGUAL(veracidade, true, "transposta_da_transposta");
    mtz_destruir(C); mtz_destruir(T); mtz_destruir(R);
}

void teste_determinante_da_transposta(void){
    esperado = 0.0;
    saida = 0.0;
    mtz_de_vetor(2, 2, dados_a, &A);
    status = mtz_transpor(A, &T);
    status = mtz_determinante(A, &esperado);
    status = mtz_determinante(T, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_da_transposta");
    mtz_destruir(A); mtz_destruir(T);
}

void teste_transposta_do_produto(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    mtz_de_vetor(2, 2, dados_b, &B);
    status = mtz_multiplicar(A, B, &temp);
    status = mtz_transpor(temp, &T);
    status = mtz_transpor(A, &I);
    status = mtz_transpor(B, &Z);
    status = mtz_multiplicar(Z, I, &R);
    veracidade = mtz_sao_iguais(T, R, eps);
    VERIFICA_IGUAL(veracidade, true, "transposta_do_produto");
    mtz_destruir(A); mtz_destruir(B); mtz_destruir(temp);
    mtz_destruir(T); mtz_destruir(I); mtz_destruir(Z); mtz_destruir(R);
}

void teste_escalar_por_um(void){
    mtz_de_vetor(2, 2, dados_a, &A);
    status = mtz_escalar(A, 1.0, &R);
    veracidade = mtz_sao_iguais(R, A, eps);
    VERIFICA_IGUAL(veracidade, true, "escalar_por_um");
    mtz_destruir(A); mtz_destruir(R);
}

