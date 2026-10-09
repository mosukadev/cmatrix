#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libmatriz/matriz.h>
#include <libmatriz/matriz_interno.h>
#include <libmatriz/arquivo.h>
#include <stdbool.h>

//Arrumar validações

MtzStatus mtz_traco(const Matriz *m, double *saida){
    if(m == NULL)
        return MTZ_ERRO_NULO;
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;
    double soma =0;
    for(int i =0; i < m->linhas; i++){
        soma += m->dados[i * m-> colunas + i];
    }
    *saida = soma;
    return MTZ_OK;
}

MtzStatus mtz_determinante(const Matriz *m, double *saida){
    if(m == NULL)
        return MTZ_ERRO_NULO;
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;
    
    Matriz copia = mtz_copiar(m);
    int sinal = 1;
    for(int k =0; k < copia->colunas; k++){
        //1: acha maior linha
        int maior_linha = k;
        for(int i = k+1; i < copia->linhas; i++){
            if(fabs(copia->dados[i * copia->colunas + k]) > fabs(copia->dados[maior_linha * copia->colunas + k]))
                maior_linha = i;
        }
        //2: fazer escalonamento até ficar triangular
        //2.1: trocar linhas
        if(maior_linha != k){
            for(int j =0; j < copia->colunas; j++){
                double temp = copia->dados[k * copia->colunas + j];
                copia->dados[k * copia->colunas + j] = copia->dados[maior_linha * copia->colunas + j];
                copia->dados[maior_linha * copia->colunas + j] = temp;
            }
            sinal *= -1;        
        }
        //2.2: multiplicar linhas demais para zeras o k-ésimo elemento
        // Fórmula: j-ésimo elemento/j-esimo elemento da maior linha * (-1)
        for(int i = k+1; i < copia->linhas; i++){
            double mult = (copia->dados[i * copia->colunas + k]/ copia->dados[k * copia->colunas + k])*(-1);
            for(int j =k; j < copia->colunas; j++){
                copia->dados[i * copia->colunas + j] += copia->dados[k * copia->colunas + j] * mult;
            }
        }
    }
    //3: multiplicar diagonal principal
    double produto = 1;
    for(int i =0; i < copia->linhas; i++){
        produto *= copia->dados[i * copia-> colunas + i];
    }
    produto *= sinal;
    *saida = produto;
    mtz_destruir(copia);
    return 0;
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
            double valor;
            mtz_definir(transposta, j, i, valor);
        }
    }

    bool simetrica = mtz_sao_iguais(m, transposta, eps);
    mtz_destruir(transposta);
    return simetrica;
}

bool mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps){
    if(m == NULL)
        return false;
    if(a->linhas != b->linhas || a->colunas != b->colunas)
        return false;
    for(int i=0; i < a->linhas; i++){
        for(int j = 0; j < a->colunas; j++){
            if(fabs(a->dados[i * a->colunas + j] - b->dados[i * b->colunas + j]) > eps){
                return false;
            }
        }
    }
    return true;
}