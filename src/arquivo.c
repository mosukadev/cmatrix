#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libmatriz/arquivo.h"
#include "matriz_interno.h"

MtzStatus mtz_de_vetor(size_t linhas, size_t colunas, const double *dados, Matriz **saida) {
    
    if (saida == NULL || dados == NULL) {
        return MTZ_ERRO_NULO;
    }

    if (linhas == 0 || colunas == 0) {
        MTZ_ERRO_DIMENSAO;
    }

    Matriz *m = malloc(sizeof(Matriz));

    if (m == NULL) {
        return MTZ_ERRO_MEMORIA;
    }

    m->linhas = linhas;
    m->colunas = colunas;
    m->dados = malloc(linhas * colunas * sizeof(double));

    if (m->dados == NULL) {
        return MTZ_ERRO_MEMORIA;
    }

    for (size_t i = 0; i < linhas*colunas; i++) {
        m->dados[i] = dados[i];
    }
    
    *saida = NULL;
    *saida = m;

    return MTZ_OK;
}

MtzStatus mtz_imprimir(const Matriz *m, FILE *arquivo) {

    if (m == NULL || arquivo == NULL) {
        return MTZ_ERRO_NULO;
    }

    size_t tamanho = snprintf(NULL, 0, "%zu %zu", m->linhas, m->colunas) + 2; // +2 because of \n
    
    char *str = malloc(tamanho*sizeof(char));

    if (str == NULL) {
        free(str);
        return MTZ_ERRO_MEMORIA;
    }

    snprintf(str, tamanho, "%zu %zu\n", m->linhas, m->colunas);

    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas-1; j++) {

            size_t tam_adicionado = snprintf(NULL, 0, "%f ", m->dados[i*m->colunas + j]);
            
            char *temp = realloc(str, (tamanho + tam_adicionado)*sizeof(char));

            if (temp == NULL) {
                free(temp);
                free(str);
                return MTZ_ERRO_MEMORIA;
            }

            str = temp;

            snprintf(str + tamanho - 1, tam_adicionado + 1, "%f ", m->dados[i*m->colunas + j]); // -1 because of \0
            
            tamanho += tam_adicionado;
        }
        size_t tam_adicionado = snprintf(NULL, 0, "%f", m->dados[(i+1)*m->colunas-1]) + 1; // +2 because of \n
        
        char *temp = realloc(str, (tamanho + tam_adicionado)*sizeof(char));
        
        if (temp == NULL) {
            free(temp);
            free(str);
            return MTZ_ERRO_MEMORIA;
        }

        str = temp;

        snprintf(str + tamanho - 1, tam_adicionado + 1, "%f\n", m->dados[(i+1)*m->colunas-1]); // -1 because of \0

        tamanho += tam_adicionado;
        
    }

    fprintf(arquivo, "%s", str);

    free(str);

    return MTZ_OK;
}

MtzStatus mtz_carregar(const char *caminho, Matriz **saida) {

    if (caminho == NULL || saida == NULL) {
        return MTZ_ERRO_NULO;
    }

    FILE *arquivo;

    arquivo = fopen(caminho, "r");
    

    if (arquivo == NULL) {
        return MTZ_ERRO_ARQUIVO;
    }

    size_t linhas, colunas;

    if (fscanf(arquivo, "%zu %zu", &linhas, &colunas) != 2) {
        fclose(arquivo);
        return MTZ_ERRO_FORMATO;
    }

    if (linhas == 0 || colunas == 0) {
        fclose(arquivo);
        return MTZ_ERRO_DIMENSAO;
    }

    Matriz *m = malloc(sizeof(Matriz));

    if (m == NULL) {
        fclose(arquivo);
        return MTZ_ERRO_MEMORIA;
    }

    m->linhas = linhas;
    m->colunas = colunas;
    m->dados = malloc(linhas * colunas * sizeof(double));

    if (m->dados == NULL) {
        fclose(arquivo);
        free(m);
        return MTZ_ERRO_MEMORIA;
    }

    double tmp;

    for (int i = 0; i < linhas * colunas; i++) {
        
        if (fscanf(arquivo, "%lf", &tmp) != 1) {
            fclose(arquivo);
            free(m->dados);
            free(m);
            return MTZ_ERRO_FORMATO;
        }

        m->dados[i] = tmp;
    }

    fclose(arquivo);

    *saida = NULL;
    *saida = m;

    return MTZ_OK;

}

MtzStatus mtz_salvar(const Matriz *m, const char *caminho) {

    if (m == NULL || caminho == NULL) {
        return MTZ_ERRO_NULO;
    }
    
    FILE *arquivo;

    arquivo = fopen(caminho, "w");
    
    if (arquivo == NULL) {
        return MTZ_ERRO_ARQUIVO;
    }

    MtzStatus resultado = mtz_imprimir(m, arquivo);

    fclose(arquivo);
    
    return resultado;
}
