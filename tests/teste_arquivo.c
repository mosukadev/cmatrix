#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

#include <libcmatrix.h>
#include "teste.h"

void mtz_de_vetor_2x3() {
    size_t linhas = 2, colunas = 3;
    double vetor[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matriz *m;

    MtzStatus retorno = mtz_de_vetor(linhas, colunas, vetor, &m);

    bool correto = retorno == MTZ_OK;
    for (size_t i = 0; correto && i < linhas * colunas; i++) {
        double dado = 0.0;
        correto = mtz_obter(m, i / colunas, i % colunas, &dado) == MTZ_OK && fabs(dado - vetor[i]) <= 1e-9;
    }

    mtz_destruir(m);
    VERIFICA(correto, "mtz_de_vetor_ok");
}

void mtz_de_vetor_zero_linhas() {
    size_t linhas = 1, colunas = 4;
    double vetor[] = {1, 2, 3, 4};
    Matriz *m;

    MtzStatus retorno = mtz_de_vetor(linhas, colunas, vetor, &m);

    bool correto = retorno == MTZ_OK;
    for (size_t i = 0; correto && i < linhas * colunas; i++) {
        double dado = 0.0;
        correto = mtz_obter(m, i / colunas, i % colunas, &dado) == MTZ_OK && fabs(dado - vetor[i]) <= 1e-9;
    }

    mtz_destruir(m);
    VERIFICA(correto, "mtz_de_vetor_zero_linhas");
}

void mtz_imprimir_temp() {
    size_t linhas_teste = 2, colunas_teste = 2;
    double vetor[] = {1, 2, 3, 4};
    Matriz *m;
    FILE *arquivo;

    bool correto = mtz_de_vetor(linhas_teste, colunas_teste, vetor, &m) == MTZ_OK;

    if (correto) {
        arquivo = tmpfile();
        correto = arquivo != NULL && mtz_imprimir(m, arquivo) == MTZ_OK && fseek(arquivo, 0, SEEK_SET) == 0;
    }

    size_t linhas = 0, colunas = 0;
    if (correto) {
        correto = fscanf(arquivo, "%zu %zu", &linhas, &colunas) == 2 ;
    }
    for (size_t i = 0; correto && i < linhas * colunas; i++) {
        double tmp = 0.0;
        correto = fscanf(arquivo, "%lf", &tmp) == 1 && tmp == vetor[i];
    }

    fclose(arquivo);
    mtz_destruir(m);
    VERIFICA(correto, "mtz_imprimir_temp");
}

void teste_imprimir_nula(void) {
    FILE *arquivo = tmpfile();
    if (arquivo == NULL) {
        VERIFICA(false, "teste_imprimir_nula");
        return;
    }

    MtzStatus retorno = mtz_imprimir(NULL, arquivo);
    fclose(arquivo);

    VERIFICA_IGUAL(retorno, MTZ_ERRO_NULO, "teste_imprimir_nula");
}

void teste_carregar_m2x2() {
    const double valores_esperados[] = {6.0, 7.0, 7.0, 6.0};
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/m2x2.txt", &m);
    bool correto = retorno == MTZ_OK;

    for (size_t i = 0; correto && i < 4; i++) {
        double valor = 0.0;
        correto = mtz_obter(m, i / 2, i % 2, &valor) == MTZ_OK && fabs(valor - valores_esperados[i]) <= 1e-9;
    }

    mtz_destruir(m);
    VERIFICA(correto, "teste_carregar_m2x2");
} 

void teste_carregar_inexistente() {
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/inexistente.txt", &m);

    VERIFICA(retorno == MTZ_ERRO_ARQUIVO, "teste_carregar_inexistente");
}

void teste_carregar_vazio() {
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/vazio.txt", &m);

    VERIFICA(retorno == MTZ_ERRO_FORMATO,"teste_carregar_vazio");
}

void teste_carregar_faltando() {
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/faltando.txt", &m);

    VERIFICA(retorno == MTZ_ERRO_FORMATO, "teste_carregar_faltando");
}  

void teste_carregar_letras(void) {
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/letras.txt", &m);

    VERIFICA(retorno == MTZ_ERRO_FORMATO, "teste_carregar_letras");
}  

void teste_carregar_dim_zero() {
    Matriz *m;
    MtzStatus retorno = mtz_carregar("tests/dados/dim_zero.txt", &m);

    VERIFICA(retorno == MTZ_ERRO_DIMENSAO, "teste_carregar_dim_zero");
}  

void teste_salvar_e_carregar_de_volta() {
    const double identidade[] = {1.0, 0.0, 0.0, 1.0};
    const char *caminho = "tests/dados/identidade_2x2.txt";
    Matriz *original;
    Matriz *carregada;

    bool correto = mtz_de_vetor(2, 2, identidade, &original) == MTZ_OK;

    if (correto) {
        correto = mtz_salvar(original, caminho) == MTZ_OK;
    }

    if (correto) {
        correto = mtz_carregar(caminho, &carregada) == MTZ_OK;
    }

    if (correto) {
        correto = mtz_sao_iguais(original, carregada, 1e-9);
    }

    mtz_destruir(original);
    mtz_destruir(carregada);
    remove(caminho);
    VERIFICA(correto, "teste_salvar_e_carregar_de_volta");
}

void teste_salvar_pasta_sem_permissao() {
    const double identidade[] = {1.0, 0.0, 0.0, 1.0};
    char pasta[] = "tests/dados/sem_permissao_XXXXXX";
    char caminho[sizeof pasta + sizeof "/matriz.txt"];
    Matriz *m;
    bool pasta_criada = mkdtemp(pasta) != NULL;
    bool correto = pasta_criada;

    if (pasta_criada) {
        snprintf(caminho, sizeof caminho, "%s/matriz.txt", pasta);
    }
    
    if (correto) {
        correto = mtz_de_vetor(2, 2, identidade, &m) == MTZ_OK;
    }

    if (correto) {
        correto = chmod(pasta, 0500) == 0;
    }
    
    if (correto) {
        correto = mtz_salvar(m, caminho) == MTZ_ERRO_ARQUIVO;
    }

    mtz_destruir(m);
    if (pasta_criada) {
        remove(caminho);
        rmdir(pasta);
    }
    
    VERIFICA(correto, "teste_salvar_pasta_sem_permissao");
}

void teste_salvar_nula() {
    Matriz *m = NULL;
    bool correto = mtz_salvar(m, "tests/dados/salvar_nulo.txt") == MTZ_ERRO_NULO;

    mtz_destruir(m);
    VERIFICA(correto, "teste_salvar_nula");
}