#include <stdio.h>
#include "teste.h"

int g_total_testes = 0;
int g_testes_passaram = 0;
int g_testes_falharam = 0;

int main() {

    g_total_testes = 0;
    g_testes_passaram = 0;
    g_testes_falharam = 0;

    printf("Total: %d, Passaram: %d, Falharam: %d\n", g_total_testes, g_testes_passaram, g_testes_falharam);

    return g_testes_falharam == 0 ? 0 : 1;
}