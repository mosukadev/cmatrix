#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libmatriz/matriz.h>
#include <libmatriz/propriedades.h>
#include "matriz_interno.h"
#include <libmatriz/arquivo.h>
#include <stdbool.h>


MtzStatus mtz_traco(const Matriz *m, double *saida){
    if(m == NULL || saida == NULL)
        return MTZ_ERRO_NULO;
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;
    double soma =0;
    for(size_t i = 0; i < m->linhas; i++){
        soma += m->dados[i * m-> colunas + i];
    }
    *saida = soma;
    return MTZ_OK;
}

MtzStatus mtz_determinante(const Matriz *m, double *saida){
    if(m == NULL || saida == NULL)
        return MTZ_ERRO_NULO;
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;

    Matriz *copia;
    MtzStatus status = mtz_copiar(m, &copia);
    if(status != MTZ_OK)
        return status;

    int sinal = 1;
    double produto = 1.0;

    for(size_t k = 0; k < copia->colunas; k++){
        size_t maior_linha = k;
        for(size_t i = k + 1; i < copia->linhas; i++){
            if(fabs(copia->dados[i * copia->colunas + k]) > fabs(copia->dados[maior_linha * copia->colunas + k]))
                maior_linha = i;
        }

        if(copia->dados[maior_linha * copia->colunas + k] == 0.0){
            produto = 0.0;
            break;
        }

        if(maior_linha != k){
            for(size_t j = 0; j < copia->colunas; j++){
                double temp = copia->dados[k * copia->colunas + j];
                copia->dados[k * copia->colunas + j] = copia->dados[maior_linha * copia->colunas + j];
                copia->dados[maior_linha * copia->colunas + j] = temp;
            }
            sinal *= -1;
        }

        for(size_t i = k + 1; i < copia->linhas; i++){
            double mult = copia->dados[i * copia->colunas + k] /
                          copia->dados[k * copia->colunas + k]*(-1);
            for(size_t j = k; j < copia->colunas; j++){
                copia->dados[i * copia->colunas + j] += copia->dados[k * copia->colunas + j] * mult;
            }
        }

        produto *= copia->dados[k * copia->colunas + k];
    }
    produto *= sinal;
    *saida = produto;
    mtz_destruir(copia);
    return MTZ_OK;
}

bool mtz_e_quadrada(const Matriz *m){
    if(m == NULL)
        return false;

    if(m->linhas == m->colunas){
        return true;
    }
    return false;
}

bool mtz_e_simetrica(const Matriz *m, double eps){
    if(m == NULL)
        return false;
        
    if(!mtz_e_quadrada(m))
        return false;

    Matriz *transposta;
    if(mtz_criar(m->linhas, m->colunas, &transposta) != MTZ_OK)
        return false;

    for(size_t i = 0; i < m->linhas; i++){
        for(size_t j = 0; j < m->colunas; j++){
            double valor = m->dados[i * m->colunas + j];
            if(mtz_definir(transposta, j, i, valor) != MTZ_OK){
                mtz_destruir(transposta);
                return false;
            }
        }
    }

    bool simetrica = mtz_sao_iguais(m, transposta, eps);
    mtz_destruir(transposta);
    return simetrica;
}

bool mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps){
    if(a == NULL || b == NULL)
        return false;
    if(a->linhas != b->linhas || a->colunas != b->colunas)
        return false;
    for(size_t i = 0; i < a->linhas; i++){
        for(size_t j = 0; j < a->colunas; j++){
            if(fabs(a->dados[i * a->colunas + j] - b->dados[i * b->colunas + j]) > eps){
                return false;
            }
        }
    }
    return true;
}