#ifndef TESTE_H
#define TESTE_H

#include <stdio.h>
#include <math.h>

extern int g_total_testes;
extern int g_testes_passaram;
extern int g_testes_falharam;


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