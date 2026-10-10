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

// mtz_carregar

void mtz_salvar(size_t linhas, size_t colunas, double **entrada, char *caminho){

    FILE *fptr;

    fptr = fopen(caminho, "w");


    size_t size = snprintf(NULL, 0, "%zu %zu", linhas, colunas) + 2; // +2 because of \n
    char *str = malloc(size*sizeof(char));
    snprintf(str, size, "%zu %zu\n", linhas, colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas-1; j++) {

            size_t added_size = snprintf(NULL, 0, "%f ", entrada[i][j]);
            
            char *temp = realloc(str, (size + added_size)*sizeof(char));
            str = temp;

            snprintf(str + size - 1, added_size + 1, "%f ", entrada[i][j]); // -1 because of \0
            
            size += added_size;
        }
        size_t added_size = snprintf(NULL, 0, "%f", entrada[i][colunas-1]) + 1; // +2 because of \n
        
        char *temp = realloc(str, (size + added_size)*sizeof(char));
        str = temp;

        snprintf(str + size - 1, added_size + 1, "%f\n", entrada[i][colunas-1]); // -1 because of \0

        size += added_size;
        
    }
    printf("%s",str);

    fprintf(fptr, "%s", str);

    fclose(fptr); 

    free(str);
}

int main() {

    size_t linhas = 3, colunas = 3;
    double *vec = malloc(linhas * colunas * sizeof(double));



    for (int i = 0; i < linhas*colunas; i++) {
        vec[i] = (double) i + 1;
    }

    double **mat = malloc(linhas * sizeof(double *));
    
    for (int i = 0; i < linhas; i++) {
        mat[i] = malloc(colunas * sizeof(double));
    }

    mtz_de_vetor(linhas, colunas, vec, mat);

    mtz_salvar(linhas, colunas, mat, "testelol");

    free(vec);
    free(mat);
}