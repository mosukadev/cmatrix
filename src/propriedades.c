#include <stdio.h>
#include <stdlib.h>

//Preciso atualizar dps para usar as funções dos outro modulos

MtzStatus mtz_traco(const Matriz *m, double *saida){
    int soma =0;
    for(int i =0; i < m->linhas; i++){
        soma += m->dados[i * m-> colunas + i];
    }

    return soma;
}

MtzStatus mtz_determinante(const Matriz *m, double *saida){
    Matriz copia = copiar(m)
    for(int k =0; k < copia->colunas; k++){
        //1: acha maior linha
        int maior_linha = 0;
        for(int i; i < copia->linhas; i++){

        }
        //2: fazer escalonamento até ficar triangular
        //3: multiplicar diagonal principal


    }

}

int mtz_e_quadrada(const Matriz *m){
    if(m->linhas == m-> coluna){
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
        for(int j = 0; j < a->colunas){
            if(a->dados[i * a-> colunas + j] != a->dados[i * a-> colunas + j]){
                return 0;
            }
        }
    }
    return 1;
}