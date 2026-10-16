#include <stdio.h>
#include "teste.h"

int main() {
    printf("Total: %d, Passaram: %d, Falharam: %d\n", g_total_testes, g_testes_passaram, g_testes_falharam);

    return g_testes_falharam == 0 ? 0 : 1;
}