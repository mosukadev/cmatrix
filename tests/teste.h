#ifndef TESTE_H
#define TESTE_H

#include <stdio.h>
#include <math.h>

extern int g_total_testes;
extern int g_testes_passaram;
extern int g_testes_falharam;

// Inicialisa as variaveis globais
// Nao tem parametros
// Nao retorna valores
void TESTE_INICIAR(void) {
    g_total_testes = 0;
    g_testes_passaram = 0;
    g_testes_falharam = 0;
}

// Imprime no console retultado dos testes
// Nao tem parametros
// Retorna 0 caso g_testes_falharam for 0, e 1 caso contrario
int TESTE_RELATORIO(void){

    printf("Total: %d, Passaram: %d, Falharam: %d\n", g_total_testes, g_testes_passaram, g_testes_falharam);

    return g_testes_falharam == 0 ? 0 : 1;
}


#define VERIFICA(condicao, nome_teste) do { \
    g_total_testes++; \
    if (condicao) { \
        g_testes_passaram++; \
        printf("[OK] %s\n", nome_teste); \
    } \
    else { \
        g_testes_falharam++; \
        printf("[FALHA] %s (%s:%d)\n", nome_teste, __FILE__, __LINE__); \
    } \
} while (0)


#define VERIFICA_PROXIMO(obtido, esperado, tolerancia, nome_teste) do { \
    g_total_testes++; \
    if (fabs(esperado - obtido) <= tolerancia) { \
        g_testes_passaram++; \
        printf("[OK] %s\n", nome_teste); \
    } \
    else { \
        g_testes_falharam++; \
        printf("[FALHA] %s (%s:%d): esperado %f, obtido %f\n", nome_teste, __FILE__, __LINE__, esperado, obtido); \
    } \
} while (0)


#define VERIFICA_IGUAL(obtido, esperado, nome_teste) do { \
    g_total_testes++; \
    if (obtido == esperado) { \
        g_testes_passaram++; \
        printf("[OK] %s\n", nome_teste); \
    } \
    else { \
        g_testes_falharam++; \
        printf("[FALHA] %s (%s:%d): esperado %d, obtido %d\n", nome_teste, __FILE__, __LINE__, esperado, obtido); \
    } \
} while (0)

#endif