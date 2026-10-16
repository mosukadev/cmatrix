#include <stdio.h>
#include <libmatriz/libmatriz.h>

int main() {
    Matriz *a = NULL;          /* 3x3, lida do arquivo            */
    Matriz *b = NULL;          /* 3x3, criada a partir de um vetor */
    Matriz *c = NULL;          /* 2x3, usada nos casos de erro     */
    Matriz *soma = NULL;
    Matriz *diferenca = NULL;
    Matriz *produto = NULL;
    Matriz *transposta = NULL;
    Matriz *dobro = NULL;
    Matriz *invalida = NULL;

    /* Zerados para nao imprimir lixo caso a funcao falhe e nao
       escreva no parametro de saida. */
    double traco = 0.0;
    double determinante = 0.0;
    MtzStatus status;

    /* Conteudo das matrizes, em ordem por linhas. */
    const double valores_b[] = { 1.0, 0.0, 2.0, 0.0, 1.0, 0.0, 3.0, 0.0, 1.0 };

    const double valores_c[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    
   /* 1 - modulo arquivo: le a matriz A do disco */
    printf("\nLendo a matriz A de app/exemplo.txt\n");
    status = mtz_carregar("app/exemplo.txt", &a);
    if (status != MTZ_OK) {
        printf("    Falhou: %s\n", mtz_mensagem_erro(status));
        return 1;
    }
    printf("    Lida com sucesso: %zu linhas e %zu colunas\n",mtz_linhas(a), mtz_colunas(a));
    mtz_imprimir(a, stdout);
     
   /* 2 - modulo arquivo: cria a matriz B a partir de um vetor */
    printf("\nCriando a matriz B (3x3) a partir de um vetor\n");
    status = mtz_de_vetor(3, 3, valores_b, &b);
    if (status != MTZ_OK) {
        printf("    Falhou: %s\n", mtz_mensagem_erro(status));
        mtz_destruir(a);
        return 1;
    }
    printf("Criada: %zu linhas e %zu colunas\n",
    mtz_linhas(b), mtz_colunas(b));
    mtz_imprimir(b, stdout);

    /* 3 - modulo operacoes: soma */
    printf("\nSomando A + B\n");
    status = mtz_somar(a, b, &soma);
    printf("    %s\n", mtz_mensagem_erro(status));
    mtz_imprimir(soma, stdout);

    /* 4 - modulo operacoes: subtracao */
    printf("\nSubtraindo A - B\n");
    status = mtz_subtrair(a, b, &diferenca);
    printf("    %s\n", mtz_mensagem_erro(status));
    mtz_imprimir(diferenca, stdout);

    /* 5 - modulo operacoes: multiplicacao */
    printf("\nMultiplicando A x B\n");
    status = mtz_multiplicar(a, b, &produto);
    printf("      %s, resultado %zux%zu\n", mtz_mensagem_erro(status),mtz_linhas(produto), mtz_colunas(produto));
    mtz_imprimir(produto, stdout);

    /* 6 - modulo operacoes: transposicao */
    printf("\nTranspondo A: as linhas viram colunas\n");
    status = mtz_transpor(a, &transposta);
    printf("    %s, de %zux%zu para %zux%zu\n", mtz_mensagem_erro(status), mtz_linhas(a), mtz_colunas(a), mtz_linhas(transposta), mtz_colunas(transposta));
    mtz_imprimir(transposta, stdout);

    /* 7 - modulo operacoes: multiplicacao por escalar */
    printf("\nMultiplicando A por 2\n");
    status = mtz_escalar(a, 2.0, &dobro);
    printf("    %s\n", mtz_mensagem_erro(status));
    mtz_imprimir(dobro, stdout);

    /* 8 - modulo propriedades */
    printf("\nConsultando as propriedades de A\n");
    printf("    A e quadrada?  %s\n", mtz_e_quadrada(a) ? "sim" : "nao");
    printf("    A e simetrica? %s\n", mtz_e_simetrica(a, 1e-9) ? "sim" : "nao");
    printf("    A e igual a B? %s\n", mtz_sao_iguais(a, b, 1e-9) ? "sim" : "nao");

    status = mtz_traco(a, &traco);
    printf("    Traco de A: %.2f (%s)\n", traco, mtz_mensagem_erro(status));

    status = mtz_determinante(a, &determinante);
    printf("    Determinante de A: %.2f (%s)\n", determinante, mtz_mensagem_erro(status));

    /* 9 - cria uma matriz 2x3 para demonstrar os casos de erro */
    printf("\nCriando a matriz C (2x3) para os casos de erro\n");
    status = mtz_de_vetor(2, 3, valores_c, &c);
    printf("    %s\n", mtz_mensagem_erro(status));
    mtz_imprimir(c, stdout);

    /* 10 - erro: traco exige matriz quadrada */
    printf("\nTentando calcular o traco de C, que e %zux%zu\n",mtz_linhas(c), mtz_colunas(c));
    status = mtz_traco(c, &traco);
    printf("     A biblioteca recusou: %s\n", mtz_mensagem_erro(status));

    /* 11 - erro: soma exige dimensoes iguais */
    printf("\nTentando somar A (%zux%zu) com C (%zux%zu)\n", mtz_linhas(a), mtz_colunas(a), mtz_linhas(c), mtz_colunas(c));
    status = mtz_somar(a, c, &invalida);
    printf("     A biblioteca recusou: %s\n", mtz_mensagem_erro(status));
    
    /* 12 - modulo arquivo: grava o resultado no disco */
    printf("\nGravando o produto A x B em saida.txt\n");
    status = mtz_salvar(produto, "saida.txt");
    printf("     %s\n", mtz_mensagem_erro(status));

    /* 13 - modulo matriz: libera toda a memoria */
    printf("\nLiberando a memoria de todas as matrizes\n\n");
    mtz_destruir(a); mtz_destruir(b); mtz_destruir(c); mtz_destruir(soma); mtz_destruir(diferenca); mtz_destruir(produto); mtz_destruir(transposta); mtz_destruir(dobro); mtz_destruir(invalida);
    printf("    É isso. Acabou.\n");

    return 0;
}
