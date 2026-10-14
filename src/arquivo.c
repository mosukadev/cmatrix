#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mtz_de_vetor(size_t linhas, size_t colunas, double *entrada, double **saida) {
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            saida[i][j] = entrada[i*colunas+j];
        }
    }
}

// mtz_imprimir

void mtz_carregar(char *caminho, double ***saida, size_t tam_saida[2]){

    FILE *file;

    file = fopen(caminho, "r");
    
    size_t linhas, colunas;

    fscanf(file, "%zu %zu", &linhas, &colunas);

    tam_saida[0] = linhas;
    tam_saida[1] = colunas;

    (*saida) = malloc(linhas * sizeof(double *));
    double tmp;

    for (int i = 0; i < linhas; i++) {
        (*saida)[i] = malloc(colunas * sizeof(double));

        for (int j = 0; j < colunas; j++) {
            fscanf(file, "%lf", &tmp);
            (*saida)[i][j] = tmp;
        }
    }

    fclose(file);
}

void mtz_salvar(size_t linhas, size_t colunas, double **entrada, char *caminho){

    FILE *file;

    file = fopen(caminho, "w");


    size_t tamanho = snprintf(NULL, 0, "%zu %zu", linhas, colunas) + 2; // +2 because of \n
    char *str = malloc(tamanho*sizeof(char));
    snprintf(str, tamanho, "%zu %zu\n", linhas, colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas-1; j++) {

            size_t tam_adicionado = snprintf(NULL, 0, "%f ", entrada[i][j]);
            
            char *temp = realloc(str, (tamanho + tam_adicionado)*sizeof(char));
            str = temp;

            snprintf(str + tamanho - 1, tam_adicionado + 1, "%f ", entrada[i][j]); // -1 because of \0
            
            tamanho += tam_adicionado;
        }
        size_t tam_adicionado = snprintf(NULL, 0, "%f", entrada[i][colunas-1]) + 1; // +2 because of \n
        
        char *temp = realloc(str, (tamanho + tam_adicionado)*sizeof(char));
        str = temp;

        snprintf(str + tamanho - 1, tam_adicionado + 1, "%f\n", entrada[i][colunas-1]); // -1 because of \0

        tamanho += tam_adicionado;
        
    }
    printf("%s",str);

    fprintf(file, "%s", str);

    fclose(file); 

    free(str);
}

int main() {

    // size_t linhas = 3, colunas = 3;
    // double *vec = malloc(linhas * colunas * sizeof(double));



    // for (int i = 0; i < linhas*colunas; i++) {
    //     vec[i] = (double) i + 1;
    // }

    // double **mat = malloc(linhas * sizeof(double *));
    
    // for (int i = 0; i < linhas; i++) {
    //     mat[i] = malloc(colunas * sizeof(double));
    // }

    // mtz_de_vetor(linhas, colunas, vec, mat);

    //mtz_salvar(linhas, colunas, mat, "testelol");

    //free(vec);
    //free(mat);

    double **mat;
    
    size_t tam_mat[2];
    
    mtz_carregar("testelol", &mat, tam_mat);

    size_t linhas = tam_mat[0];
    size_t colunas = tam_mat[1];

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%lf ", mat[i][j]);
        }
        printf("\n");
    }

    free(mat);
}