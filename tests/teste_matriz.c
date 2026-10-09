#include "teste.h"
#include <libmatriz.h>

#include <stdbool.h>

void mtz_criar_3x4() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    VERIFICA(status == MTZ_OK && M->linhas == 3 && m->colunas == 4, "mtz_criar_3x4");
}

void mtz_verificar_3x4_zeros() {
    Matriz *m;
    MtzStatus status = mtz_criar(3, 4, &m);

    bool nao_zero = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int valor;
            mtz_obter(m, 3, 4, &valor);

            if (valor != 0) {
                nao_zero = false;
                break;
            }
        }
    }

    VERIFICA(nao_zero, "mtz_verificar_3x4_zeros");
}
