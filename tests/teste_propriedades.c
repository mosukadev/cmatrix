// A é [[1,2],[3,4]], B é [[5,6],[7,8]], C é [[1,2,3],[4,5,6]] e D é [[7,8],[9,10],[11,12]].
// Matrizes usadas: E é [[1,2,3],[4,5,6],[7,8,10]], com determinante menos 3. F é [[3,8],[4,6]], com determinante menos 14. G é [[1,2],[2,4]], com determinante 0. H é [[0,1],[1,0]], com determinante menos 1, e obriga a troca de linhas. S é [[1,2],[2,1]], que é simétrica.



// mtz_traco: traço de A. Esperado: 5.
// mtz_traco: matriz 2x3. Esperado: MTZ_ERRO_NAO_QUADRADA.
// mtz_traco: matriz 1x1 com valor 9. Esperado: 9. Caso limite.
// mtz_determinante: matriz F. Esperado: menos 14.
// mtz_determinante: matriz E. Esperado: menos 3.
// mtz_determinante: identidade 3x3. Esperado: 1.
// mtz_determinante: matriz G, que é singular. Esperado: 0.
// mtz_determinante: matriz H, que tem zero no primeiro pivô. Esperado: menos 1. É o caso do teste que vai falhar de propósito.
// mtz_determinante: matriz 1x1 com valor 5. Esperado: 5. Caso limite.
// mtz_determinante: matriz 2x3. Esperado: MTZ_ERRO_NAO_QUADRADA.
// mtz_determinante: conferir a matriz depois do cálculo. Esperado: não foi alterada.
// mtz_e_quadrada: matriz 3x3. Esperado: verdadeiro.
// mtz_e_quadrada: matriz 2x3. Esperado: falso.
// mtz_e_quadrada: NULL. Esperado: falso.
// mtz_e_simetrica: matriz S. Esperado: verdadeiro.
// mtz_e_simetrica: matriz A. Esperado: falso.
// mtz_e_simetrica: matriz 2x3. Esperado: falso, porque não é quadrada.
// mtz_sao_iguais: duas cópias iguais. Esperado: verdadeiro.
// mtz_sao_iguais: tamanhos diferentes. Esperado: falso.
// mtz_sao_iguais: diferença de 0,0000000001 com tolerância de 0,000001. Esperado: verdadeiro.
// mtz_sao_iguais: uma das matrizes é NULL. Esperado: falso.


#include <stdio.h>

#include <libmatriz/arquivo.h>
#include <libmatriz/matriz.h>
#include <libmatriz/propriedades.h>

#include "../src/matriz_interno.h"
#include "teste.h"

static double dados_a[] = {1, 2, 3, 4};
static double dados_b[] = {5, 6, 7, 8};
static double dados_c[] = {1, 2, 3, 4, 5, 6};
static double dados_d[] = {7, 8, 9, 10, 11, 12};
static double dados_e[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
static double dados_f[] = {3, 8, 4, 6};
static double dados_g[] = {1, 2, 2, 4};
static double dados_h[] = {0, 1, 1, 0};
static double dados_s[] = {1, 2, 2, 1};
static Matriz *A, *B, *C, *D, *E, *F, *G, *H, *S, *I, *temp;

static void teste_mtz_traco(void){
    static const double dados_unico[] = {9};
    Matriz *I;
    MtzStatus status;

    double saida = 0.0;
    double esperado = 5.0;

    mtz_de_vetor(2, 2, dados_a, &A);
    status = mtz_traco(A, &saida);
    VERIFICA_IGUAL(saida, esperado, "traco_de_A");

    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_traco(C, &saida);
    VERIFICA_IGUAL(status, MTZ_ERRO_NAO_QUADRADA, "traco_de_2x3");

    mtz_de_vetor(1, 1, dados_unico, &I);
    status = mtz_traco(I, &saida);
    esperado = 9.0;
    VERIFICA_IGUAL(saida, esperado, "traco_de_1x1");

    mtz_destruir(A);
    mtz_destruir(C);
    mtz_destruir(I);
}

static void teste_mtz_determinante(void){
    static double dados_identidade[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    static double dados_unico[] = {5};
    Matriz *identidade, *un_elemento;
    MtzStatus status;

    double saida = 0.0;
    double esperado = -14.0;

    mtz_de_vetor(2, 2, dados_f, &F);
    status = mtz_determinante(F, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_F');

    esperado = -3.0;
    mtz_de_vetor(3, 3, dados_e, &E);
    status = mtz_determinante(E, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_E');

    esperado = 1.0;
    mtz_de_vetor(3, 3, dados_identidade, &identidade);
    status = mtz_determinante(identidade, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_identidade');

    esperado = 0.0;
    mtz_de_vetor(2, 2, dados_g, &G);
    status = mtz_determinante(G, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_G');

    esperado = -1.0;
    mtz_de_vetor(2, 2, dados_h, &H);
    status = mtz_determinante(H, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_H');

    esperado = 5.0;
    mtz_de_vetor(1, 1, dados_unico, &un_elemento);
    status = mtz_determinante(un_elemento, &saida);
    VERIFICA_IGUAL(saida, esperado, 'determinante_unico_elemento');

    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_determinante(C, &saida);
    VERIFICA_IGUAL(status, MTZ_ERRO_NAO_QUADRADA, 'determinante_2x3');

    double eps =  1e-9;
    bool igualdade = mtz_sao_iguais(C, mtz_de_vetor(2, 3, dados_c, &temp), eps);
    VERIFICA_IGUAL(igualdade, true, 'matriz_alteracao');

    mtz_destruir(F);
    mtz_destruir(E);
    mtz_destruir(G);
    mtz_destruir(H);
    mtz_destruir(C);
    mtz_destruir(temp);
    mtz_destruir(identidade);
    mtz_destruir(un_elemento);
}

static void teste_mtz_e_quadrada(void){
    bool status;

    mtz_de_vetor(3, 3, dados_e, &E);
    status = mtz_e_quadrada(E);
    VERIFICA_IGUAL(status, true, 'quadrada_3x3');

    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_e_quadrada(C);
    VERIFICA_IGUAL(status, false, 'quadrada_2x2');

    status = mtz_e_quadrada(NULL);
    VERIFICA_IGUAL(status, false, 'quadrada_NULL');

    mtz_destruir(E);
    mtz_destruir(C);
}

static void teste_mtz_e_simetrica(void){
    bool status;
    double eps =  1e-9;

    mtz_de_vetor(2,2, dados_s, &S);
    status = mtz_e_simetrica(S,eps);
    VERIFICA_IGUAL(status, true, 'simetrica_S');

    mtz_de_vetor(2, 2, dados_a, &A);
    status = mtz_e_simetrica(A, eps);
    VERIFICA_IGUAL(status, false, 'simetrica_A');

    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_e_simetrica(C, eps);
    VERIFICA_IGUAL(status, false, 'simetrica_2x3');

    mtz_destruir(S);    
    mtz_destruir(A);
    mtz_destruir(C);
}

static void teste_mtz_sao_iguais(void){
    bool status;
    double eps =  1e-9;

    mtz_de_vetor(2,2, dados_s, &S);
    status = mtz_sao_iguais(S,S, eps);
    VERIFICA_IGUAL(status, true, 'igual_mesma');

    mtz_de_vetor(2, 3, dados_c, &C);
    status = mtz_sao_iguais(S,C, eps);
    VERIFICA_IGUAL(status, false, 'igual_tamanhos_diferentes');


    eps =  1e-6;
    mtz_copiar(C, &temp);
    const double diferenca = 1e-10;
    for (size_t i = 0; i < mtz_linhas(temp); i++){
        for (size_t j = 0; j < mtz_colunas(temp); j++){
            double valor;
            mtz_obter(temp, i, j, &valor);
            mtz_definir(temp, i, j, valor - diferenca);
        }
    }
    status = mtz_sao_iguais(C, temp, eps);
    VERIFICA_IGUAL(status, true, 'igual_diferenca_dentro_tolerancia');

    mtz_destruir(S);
    mtz_destruir(C);
    mtz_destruir(temp);
}