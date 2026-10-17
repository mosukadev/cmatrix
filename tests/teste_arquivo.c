#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <libmatriz.h>
#include "teste.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>
// #include "../include/libmatriz.h"
// #include "../src/matriz_interno.h"
// #include "../include/libmatriz/matriz.h"
// #include "teste.h"

void mtz_de_vetor_ok() {

    size_t linhas = 2, colunas = 3;

    double vetor[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    Matriz *m;

    MtzStatus retorno = mtz_de_vetor(linhas, colunas, vetor, &m);

    VERIFICA_IGUAL(retorno, MTZ_OK, "mtz_de_vetor_ok");

    if (retorno != MTZ_OK) {
        return;
    }

    double dado = 0;
    for (size_t i = 0; i < linhas*colunas; i ++) {
        mtz_obter(m, i / colunas, i % colunas, &dado);//dado = m->dados[i];
        VERIFICA_PROXIMO(dado, vetor[i], 1e-9, "mtz_de_vetor_ok");
    }
    
    mtz_destruir(m);
}

void mtz_de_vetor_zero_linhas() {

    size_t linhas = 0, colunas = 4;

    double vetor[] = {1, 2, 3, 4};

    Matriz *m;

    MtzStatus retorno = mtz_de_vetor(linhas, colunas, vetor, &m);

    VERIFICA_IGUAL(retorno, MTZ_OK, "mtz_de_vetor_zero_linhas");

    if (retorno != MTZ_OK) {
        return;
    }

    double dado = 0;
    for (size_t i = 0; i < linhas*colunas; i ++) {
        mtz_obter(m, i / colunas, i % colunas, &dado);//dado = m->dados[i];
        VERIFICA_PROXIMO(dado, vetor[i], 1e-9, "mtz_de_vetor_zero_linhas");
    }
    
    mtz_destruir(m);
}

void mtz_imprimir_temp() {

    size_t linhas_teste = 2, colunas_teste = 2;

    double vetor[] = {1, 2, 3, 4};

    Matriz *m;

    MtzStatus retorno = mtz_de_vetor(linhas_teste, colunas_teste, vetor, &m);

    VERIFICA_IGUAL(retorno, MTZ_OK, "mtz_imprimir_temp");

    if (retorno != MTZ_OK) {
        return;
    }

    FILE *arquivo = tmpfile();

    mtz_imprimir(m, arquivo);

    size_t linhas, colunas;
    
    size_t ver = fscanf(arquivo, "%zu %zu", &linhas, &colunas);

    VERIFICA_IGUAL(ver, 2, "mtz_imprimir_temp");

    if (ver != 2) {
        fclose(arquivo);
        return;
    }

    double tmp;

    for (size_t i = 0; i < linhas * colunas; i++) {
        
        VERIFICA(fscanf(arquivo, "%lf", &tmp) != 1 || tmp != vetor[i], "mtz_imprimir_temp");
        if (fscanf(arquivo, "%lf", &tmp) != 1 || tmp != vetor[i]) {
            fclose(arquivo);
            free(m);
            return;
        }

    }

    fclose(arquivo);
}