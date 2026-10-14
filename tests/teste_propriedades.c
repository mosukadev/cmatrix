#include <stdio.h>

#include <libmatriz/arquivo.h>
#include <libmatriz/matriz.h>
#include <libmatriz/propriedades.h>

#include "../src/matriz_interno.h"
#include "teste.h"

static double dados_a[] = {1, 2, 3, 4};
static double dados_c[] = {1, 2, 3, 4, 5, 6};
static double dados_e[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
static double dados_f[] = {3, 8, 4, 6};
static double dados_g[] = {1, 2, 2, 4};
static double dados_h[] = {0, 1, 1, 0};
static double dados_s[] = {1, 2, 2, 1};
static Matriz *A, *C, *E, *F, *G, *H, *S, *temp;

double esperado, saida;
MtzStatus status;
bool veracidade;
double eps =  1e-9;

/* mtz_traco */
static void teste_traco_de_A(void){
    esperado = 5.0;
    saida = 0.0;

    mtz_de_vetor(2, 2, dados_a, &A);
    status = mtz_traco(A, &saida);
    VERIFICA_IGUAL(saida, esperado, "traco_de_A");

    mtz_destruir(A);
}

static void teste_traco_de_2x3(void){
    
    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_traco(C, &saida);
    VERIFICA_IGUAL(status, MTZ_ERRO_NAO_QUADRADA, "traco_de_2x3");

    mtz_destruir(C);
}

static void teste_traco_de_1x1(void){
    static const double dados_unico[] = {9};
    
    mtz_de_vetor(1, 1, dados_unico, &temp);
    status = mtz_traco(temp, &saida);
    esperado = 9.0;
    VERIFICA_IGUAL(saida, esperado, "traco_de_1x1");

    mtz_destruir(temp);
}

/* mtz_determinante */
static void teste_determinante_F(void){
    saida = 0.0;
    esperado = -14.0;

    mtz_de_vetor(2, 2, dados_f, &F);
    status = mtz_determinante(F, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_F");

    mtz_destruir(F);

}

static void teste_determinante_E(void){
    saida = 0.0;
    esperado = -3.0;

    mtz_de_vetor(3, 3, dados_e, &E);
    status = mtz_determinante(E, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_E");

    mtz_destruir(E);
}
static void teste_determinante_identidade(void){
    static double dados_identidade[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    saida = 0.0;
    esperado = 1.0;

    mtz_de_vetor(3, 3, dados_identidade, &temp);
    status = mtz_determinante(temp, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_identidade");

    mtz_destruir(temp);
}

static void teste_determinante_G(void){
    saida =0.0;
    esperado = 0.0;

    mtz_de_vetor(2, 2, dados_g, &G);
    status = mtz_determinante(G, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_G");

    mtz_destruir(G);
}

static void teste_determinante_H(void){
    saida = 0.0;
    esperado = -1.0;

    mtz_de_vetor(2, 2, dados_h, &H);
    status = mtz_determinante(H, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_H");

    mtz_destruir(H);
}

static void teste_determinante_unico_elemento(void){
    static double dados_unico[] = {5};
    saida = 0.0;
    esperado = 5.0;
    mtz_de_vetor(1, 1, dados_unico, &temp);
    status = mtz_determinante(temp, &saida);
    VERIFICA_IGUAL(saida, esperado, "determinante_unico_elemento");

    mtz_destruir(temp);
}

static void teste_determinante_2x3(void){
    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_determinante(C, &saida);
    VERIFICA_IGUAL(status, MTZ_ERRO_NAO_QUADRADA, "determinante_2x3");

    mtz_destruir(C);
}

static void teste_determinante_nao_altera_matriz(void){
    eps =  1e-9;
    mtz_de_vetor(2, 2, dados_h, &H);
    mtz_de_vetor(2, 3, dados_h, &temp);
    status = mtz_determinante(H, &saida);

    veracidade = mtz_sao_iguais(H, temp, eps);
    VERIFICA_IGUAL(veracidade, true, "matriz_alteracao");

    mtz_destruir(H);
    mtz_destruir(temp);
}

/* mtz_e_quadrada */
static void teste_quadrada_3x3(void){

    mtz_de_vetor(3, 3, dados_e, &E);
    veracidade = mtz_e_quadrada(E);
    VERIFICA_IGUAL(veracidade, true, "quadrada_3x3");

    mtz_destruir(E);
}

static void teste_quadrada_2x3(void){
    mtz_de_vetor(2, 3, dados_c, &C);
    veracidade = mtz_e_quadrada(C);
    VERIFICA_IGUAL(veracidade, false, "quadrada_2x3");

    mtz_destruir(C);
}

static void teste_quadrada_NULL(void){
    veracidade = mtz_e_quadrada(NULL);
    VERIFICA_IGUAL(veracidade, false, "quadrada_NULL");
}

/* mtz_e_simetrica */
static void teste_simetrica_S(void){
    eps =  1e-9;

    mtz_de_vetor(2,2, dados_s, &S);
    veracidade = mtz_e_simetrica(S,eps);
    VERIFICA_IGUAL(veracidade, true, "simetrica_S");

    mtz_destruir(S);
}

static void teste_simetrica_A(void){
    eps =  1e-9;

    mtz_de_vetor(2, 2, dados_a, &A);
    veracidade = mtz_e_simetrica(A, eps);
    VERIFICA_IGUAL(veracidade, false, "simetrica_A");

    mtz_destruir(A);
}
static void teste_simetrica_2x3(void){
    eps =  1e-9;

    mtz_de_vetor(2, 3, dados_c, &C);
    veracidade = mtz_e_simetrica(C, eps);
    VERIFICA_IGUAL(veracidade, false, "simetrica_2x3");

    mtz_destruir(C);
}

/* mtz_sao_iguais */
static void teste_igual_mesma(void){
    eps =  1e-9;

    mtz_de_vetor(2,2, dados_s, &S);
    veracidade = mtz_sao_iguais(S,S, eps);
    VERIFICA_IGUAL(veracidade, true, "igual_mesma");

    mtz_destruir(S);
}

static void teste_igual_tamanhos_diferentes(void){
    eps =  1e-9;

    mtz_de_vetor(2,2, dados_s, &S);
    mtz_de_vetor(2, 3, dados_c, &C);
    veracidade = mtz_sao_iguais(S,C, eps);
    VERIFICA_IGUAL(veracidade, false, "igual_tamanhos_diferentes");

    mtz_destruir(S);
    mtz_destruir(C);
}

static void teste_igual_diferenca_dentro_tolerancia(void){
    eps =  1e-6;

    mtz_de_vetor(2, 3, dados_c, &C);
    mtz_copiar(C, &temp);

    const double diferenca = 1e-10;
    for (size_t i = 0; i < mtz_linhas(temp); i++){
        for (size_t j = 0; j < mtz_colunas(temp); j++){
            double valor;
            mtz_obter(temp, i, j, &valor);
            mtz_definir(temp, i, j, valor - diferenca);
        }
    }
    veracidade = mtz_sao_iguais(C, temp, eps);
    VERIFICA_IGUAL(veracidade, true, "igual_diferenca_dentro_tolerancia");

    mtz_destruir(C);
    mtz_destruir(temp);
}

static void teste_igual_uma_nula(void){
    eps =  1e-9;

    mtz_de_vetor(2, 3, dados_c, &C);
    veracidade = mtz_sao_iguais(C, NULL, eps);
    VERIFICA_IGUAL(veracidade, false, "igual_uma_nula");

    mtz_destruir(C);
}