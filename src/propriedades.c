#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Preciso atualizar dps para usar as funções dos outro modulos

MtzStatus mtz_traco(const Matriz *m, double *saida){
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;
    double soma =0;
    for(int i =0; i < m->linhas; i++){
        soma += m->dados[i * m-> colunas + i];
    }
    if(soma == 0)
        return MTZ_ERRO_NULO;
    *saida = soma;
    return MTZ_OK;
}

MtzStatus mtz_determinante(const Matriz *m, double *saida){
    if(!mtz_e_quadrada(m))
        return MTZ_ERRO_NAO_QUADRADA;
    
    Matriz copia = copiar(m);
    int sinal = 1;
    for(int k =0; k < copia->colunas; k++){
        //1: acha maior linha
        int maior_linha = k;
        for(int i = k+1; i < copia->linhas; i++){
            if(copia->dados[i * copia->colunas + k] > copia->dados[maior_linha * copia->colunas + k])
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
    for(int i =0; i < m->linhas; i++){
        produto *= m->dados[i * m-> colunas + i];
    }
    produto *= sinal;
    *saida = produto;
    return 0;
}

int mtz_e_quadrada(const Matriz *m){
    if(m->linhas == m->colunas){
        return 1;
    }
    return 0;
}

int mtz_e_simetrica(const Matriz *m, double eps){
    Matriz transposta;
    transposta.colunas = m->colunas;
    transposta.linhas = m->linhas;
    transposta.dados = malloc(transposta->colunas * transposta->linhas * sizeof *transposta.dados);
    if(mtz_sao_iguais(m, transposta, eps))
        return 1;
    else
        return 0;
}

int mtz_sao_iguais(const Matriz *a, const Matriz *b, double eps){
    if(a->linhas != b->linhas || a->colunas != b->colunas)
        return 0;
    for(int i=0; i < a->linhas; i++){
        for(int j = 0; j < a->colunas; j++){
            if(fabs(a->dados[i * a->colunas + j] - b->dados[i * b->colunas + j]) > eps){
                return 0;
            }
        }
    }
    return 1;
}