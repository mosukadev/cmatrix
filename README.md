# libcmatrix

Biblioteca em C para trabalhar com matrizes de `double`: criação, cópia, acesso
a elementos, soma, subtração, multiplicação, transposição, traço, determinante,
comparação e leitura/gravação em arquivo de texto.

Projeto do **Trabalho Prático 2** (Técnicas de Programação, Ciência da
Computação, IME-USP). A biblioteca tem **22 funções públicas** distribuídas em
**5 módulos**, é gerada em versão **estática** (`.a`) e **dinâmica** (`.so`) e
acompanha uma aplicação cliente, testes automatizados e integração contínua.

## Sumário

1. [Pré-requisitos](#pré-requisitos)
2. [Estrutura do projeto](#estrutura-do-projeto)
3. [Compilação](#compilação)
4. [Alvos do Makefile](#alvos-do-makefile)
5. [Execução](#execução)
6. [Testes](#testes)
7. [Instalação](#instalação)
8. [Usando a biblioteca em outro programa](#usando-a-biblioteca-em-outro-programa)
9. [Módulos e funções públicas](#módulos-e-funções-públicas)
10. [Tratamento de erros](#tratamento-de-erros)
11. [Formato do arquivo de matriz](#formato-do-arquivo-de-matriz)
12. [Convenções do código](#convenções-do-código)
13. [Fluxo de trabalho com Git](#fluxo-de-trabalho-com-git)
14. [Reproduzindo a partir de um clone limpo](#reproduzindo-a-partir-de-um-clone-limpo)
15. [Integrantes](#integrantes)

## Pré-requisitos

| Ferramenta | Uso | Obrigatória |
|---|---|---|
| Linux (ou WSL) | ambiente de execução | sim |
| `gcc` | compilação | sim |
| `make` | automação do build | sim |
| `git` | controle de versão | sim |
| `valgrind` | alvo `make valgrind` | não |
| `tree` | mostrar a estrutura na demonstração | não |

No Debian/Ubuntu:

```bash
sudo apt install build-essential git valgrind tree
```

## Estrutura do projeto

```
projeto_c/
├── include/                  # Interface pública (é o que o cliente enxerga)
│   ├── libcmatrix.h           # Cabeçalho único: reúne os cinco módulos
│   └── libcmatrix/
│       ├── erro.h            # Códigos de erro e mensagens
│       ├── matriz.h          # Criação, cópia, destruição e acesso
│       ├── operacoes.h       # Soma, subtração, multiplicação, escalar, transposta
│       ├── propriedades.h    # Traço, determinante e verificações
│       └── arquivo.h         # Vetor, impressão, leitura e gravação
├── src/                      # Implementação (nunca instalada)
│   ├── matriz_interno.h      # Definição privada de struct Matriz (tipo opaco)
│   ├── erro.c
│   ├── matriz.c
│   ├── operacoes.c
│   ├── propriedades.c
│   └── arquivo.c
├── app/                      # Aplicação cliente
│   ├── principal.c           # Programa de demonstração
│   └── exemplo.txt           # Matriz lida pelo programa
├── tests/                    # Testes automatizados
│   ├── teste.h               # Macros VERIFICA, VERIFICA_IGUAL, VERIFICA_PROXIMO
│   ├── teste.c               # Executor: roda todos os testes e imprime o resumo
│   ├── teste_<modulo>.c/.h   # Um par de arquivos por módulo
│   └── dados/                # Arquivos de matriz válidos e inválidos
├── scripts/demo.sh           # Roteiro da demonstração
├── .github/workflows/ci.yml  # Integração contínua (GitHub Actions)
├── Makefile
└── README.md
```

A compilação cria, fora do controle de versão (veja `.gitignore`):

| Pasta | Conteúdo |
|---|---|
| `build/est/` | objetos da biblioteca estática e arquivos de dependência `.d` |
| `build/din/` | objetos compilados com `-fPIC` para a biblioteca dinâmica |
| `build/test_runner` | executável dos testes |
| `lib/` | `libcmatrix.a` e `libcmatrix.so` |
| `bin/` | `app_estatico` e `app_dinamico` |

### Interface pública e tipo opaco

O cabeçalho público declara apenas `typedef struct Matriz Matriz;`. A definição
da `struct` fica em `src/matriz_interno.h`, que só os arquivos da biblioteca
incluem e que **não é instalado**. Assim, quem usa a biblioteca não consegue
acessar `linhas`, `colunas` ou `dados` diretamente e precisa usar as funções
`mtz_linhas`, `mtz_obter` etc. Se a forma de armazenar a matriz mudar, a
aplicação cliente continua igual e só precisa ser recompilada.

## Compilação

```bash
make
```

Gera as duas bibliotecas e os dois executáveis do cliente:

```
src/*.c ── gcc -c ────────▶ build/est/*.o ── ar rcs ──────▶ lib/libcmatrix.a
src/*.c ── gcc -c -fPIC ──▶ build/din/*.o ── gcc -shared ─▶ lib/libcmatrix.so

app/principal.c + lib/libcmatrix.a  ─▶ bin/app_estatico
app/principal.c + -Llib -lcmatrix  ─▶ bin/app_dinamico
```

O executável dinâmico é ligado pelo nome da biblioteca (`-lcmatrix`), e o
Makefile define um `rpath` relativo ao executável (`$ORIGIN/../lib`) para
localizar `lib/libcmatrix.so` mesmo quando o diretório de trabalho muda.

Flags usadas (variável `CFLAGS` do Makefile):

| Flag | Finalidade |
|---|---|
| `-Wall -Wextra -Wpedantic` | ativa os avisos do compilador (o projeto compila sem nenhum) |
| `-g` | inclui informação de depuração (GDB e valgrind) |
| `-Iinclude` | permite `#include <libcmatrix.h>` |
| `-Iinclude/libcmatrix` | permite que os arquivos de `src/` e `tests/` incluam os cabeçalhos dos módulos pelo nome (por exemplo `"erro.h"`) |

Além delas: `-MMD -MP` (`DFLAGS`) geram os arquivos de dependência dos objetos
da biblioteca e dos executáveis do cliente; `-fPIC` é usada só nos objetos da
biblioteca dinâmica; `-Itests` é usada só na compilação dos testes. A
aplicação cliente e quem usa a biblioteca instalada devem incluir apenas
`<libcmatrix.h>`.

### Compilação incremental

Cada objeto da biblioteca (`build/est/*.o` e `build/din/*.o`) gera um arquivo
de dependência `.d` (opções `-MMD -MP`), assim como os executáveis do cliente
(`bin/app_estatico.d` e `bin/app_dinamico.d`). Todos são incluídos pelo
Makefile, que recompila somente o que depende do arquivo alterado:

```bash
make                       # segunda execução: "Nothing to be done"
touch src/propriedades.c
make                       # recompila só propriedades.c e religa as bibliotecas e os apps
```

Os módulos `operacoes`, `propriedades` e `arquivo` não dependem uns dos outros;
mexer em um deles não recompila os demais.

Os testes **não** usam arquivos `.d`: o alvo `build/test_runner` compila
`tests/teste.c` e todos os `tests/teste_*.c` em um único comando, e suas
dependências estão listadas à mão no Makefile (os fontes e cabeçalhos dos
testes e `lib/libcmatrix.a`). Se qualquer um deles mudar, o executável de testes
é refeito por inteiro.

## Alvos do Makefile

| Alvo | O que faz |
|---|---|
| `make` / `make all` | Compila `lib/libcmatrix.a`, `lib/libcmatrix.so`, `bin/app_estatico` e `bin/app_dinamico`. |
| `make clean` | Remove `build/`, `lib/` e `bin/`. |
| `make run` | Compila se necessário e executa a aplicação (versão dinâmica). |
| `make run-static` | Executa a aplicação ligada à biblioteca estática. |
| `make run-dynamic` | Executa a aplicação ligada à biblioteca dinâmica. |
| `make test` | Compila e executa todos os testes. Termina com erro se algum falhar. |
| `make valgrind` | Executa os testes sob o valgrind (`--leak-check=full`) para detectar vazamentos. |
| `make install` | Instala as bibliotecas e os cabeçalhos públicos em `$(PREFIX)`. |
| `make uninstall` | Remove as duas bibliotecas e todos os cabeçalhos instalados em `$(PREFIX)`. |

## Execução

```bash
make run            # versão dinâmica
make run-static     # versão estática
make run-dynamic    # versão dinâmica
```

O programa `app/principal.c` usa as cinco partes da biblioteca: lê a matriz A de
`app/exemplo.txt`, cria a matriz B a partir de um vetor, mostra as duas, calcula
soma, subtração, produto, transposta e múltiplo escalar, consulta traço,
determinante, se é quadrada e se é simétrica, provoca erros de propósito (traço
de matriz 2×3 e soma de tamanhos diferentes), grava o produto em `saida.txt` e
libera toda a memória.

> **Execute a aplicação de exemplo a partir da raiz do projeto.** Ela lê
> `app/exemplo.txt` por caminho relativo. A biblioteca dinâmica é localizada
> pelo `rpath` relativo à localização do executável, não ao diretório de
> trabalho. Use `make run-*` ou execute `./bin/app_dinamico` estando na raiz.

Para comprovar que cada versão usa a biblioteca esperada:

```bash
ldd bin/app_estatico    # não lista libcmatrix
ldd bin/app_dinamico    # lista libcmatrix.so
```

## Testes

```bash
make test
```

Os testes ficam em `tests/`, um arquivo por módulo, e todos são compilados em um
único executável (`build/test_runner`) ligado à biblioteca estática. Cada teste
é uma função pequena que cria o que precisa e libera no final. Eles cobrem
casos normais, valores limite e entradas inválidas.

Saída esperada:

Testes bem sucedidos:
```
[OK] mtz_criar_3x4
[OK] determinante_H
```

Testes com falha:
```
[FALHA] nome_do_teste (tests/teste_x.c:52): esperado -1.000000, obtido 1.000000
```

Resultado final:
```
Total: 81, Passaram: 81, Falharam: 0
```

- `[OK]` e `[FALHA]` indicam o resultado de cada verificação; em caso de falha,
  o arquivo e a linha aparecem na mensagem.
- Números reais são comparados com tolerância (`VERIFICA_PROXIMO`), nunca com `==`.
- O programa termina com código diferente de zero se qualquer teste falhar, e
  por isso o `make test` também falha (útil para a integração contínua).
- Os arquivos de `tests/dados/` (`m2x2.txt`, `m3x3.txt`, `vazio.txt`,
  `faltando.txt`, `letras.txt`, `dim_zero.txt`) alimentam os testes de leitura.

Teste de vazamento de memória:

```bash
make valgrind
```

> Um dos testes de arquivo verifica a falha de gravação em uma pasta sem
> permissão. Isso não funciona quando os testes rodam como **root**
> (por exemplo, em alguns contêineres), pois o root ignora a permissão.

## Instalação

Para instalar **sem privilégios de administrador**, escolha um prefixo no seu
diretório pessoal:

```bash
make install PREFIX=$HOME/.local
```

O prefixo padrão é `$(HOME)/.local`. Para instalar no sistema:

```bash
sudo make install PREFIX=/usr/local
```

O que é instalado:

```
$(PREFIX)/lib/libcmatrix.a
$(PREFIX)/lib/libcmatrix.so
$(PREFIX)/include/libcmatrix.h
$(PREFIX)/include/libcmatrix/{erro,matriz,operacoes,propriedades,arquivo}.h
```

O arquivo `src/matriz_interno.h` **não** é instalado, pois é interno.

```bash
ls $HOME/.local/lib $HOME/.local/include/libcmatrix   # conferir
make uninstall PREFIX=$HOME/.local                   # desfazer
```

O `make uninstall` remove as duas bibliotecas, o cabeçalho principal
`$(PREFIX)/include/libcmatrix.h` e a pasta `$(PREFIX)/include/libcmatrix/`.

## Usando a biblioteca em outro programa

Depois de instalada (aqui com `PREFIX=$HOME/.local`), um programa externo só
precisa incluir o cabeçalho único:

```c
#include <stdio.h>
#include <libcmatrix.h>

int main(void) {
    const double v[] = {1, 2, 3, 4};
    Matriz *a = NULL, *t = NULL;
    double det = 0.0;

    if (mtz_de_vetor(2, 2, v, &a) != MTZ_OK) return 1;
    mtz_determinante(a, &det);
    printf("det = %.1f\n", det);       /* det = -2.0 */
    mtz_transpor(a, &t);
    mtz_imprimir(t, stdout);
    mtz_destruir(a);
    mtz_destruir(t);
    return 0;
}
```

**Ligação estática** (a biblioteca é copiada para dentro do executável):

```bash
gcc exemplo.c -I$HOME/.local/include $HOME/.local/lib/libcmatrix.a -lm -o exemplo_est
```

Passa-se o caminho completo do `.a`. Com `-lcmatrix`, o ligador escolheria o
`.so`, porque as duas versões ficam no mesmo diretório.

**Ligação dinâmica** (a biblioteca é carregada na hora de executar):

```bash
gcc exemplo.c -I$HOME/.local/include -L$HOME/.local/lib -lcmatrix -lm \
    -Wl,-rpath,$HOME/.local/lib -o exemplo_din
```

O `-Wl,-rpath` grava no executável onde procurar a `.so`. Sem ele, é preciso
`LD_LIBRARY_PATH=$HOME/.local/lib ./exemplo_din`, caso contrário o programa
não inicia ("cannot open shared object file").

### Estática × dinâmica

| Aspecto | Estática (`.a`) | Dinâmica (`.so`) |
|---|---|---|
| Tamanho do executável | maior (código copiado) | menor |
| Dependência em execução | nenhuma | precisa encontrar a `.so` |
| Atualização da biblioteca | exige recompilar o programa | basta trocar a `.so` |
| Compilação da biblioteca | `gcc -c` normal | `gcc -c -fPIC` e `gcc -shared` |

## Módulos e funções públicas

Todas as funções públicas começam com `mtz_` e estão documentadas nos
cabeçalhos (finalidade, parâmetros, retorno e condições de erro).

| Módulo | Responsabilidade | Funções |
|---|---|---|
| `erro` | códigos de status e mensagens | `mtz_mensagem_erro` |
| `matriz` | ciclo de vida e acesso | `mtz_criar`, `mtz_destruir`, `mtz_copiar`, `mtz_obter`, `mtz_definir`, `mtz_linhas`, `mtz_colunas` |
| `operacoes` | aritmética de matrizes | `mtz_somar`, `mtz_subtrair`, `mtz_multiplicar`, `mtz_escalar`, `mtz_transpor` |
| `propriedades` | cálculos e verificações | `mtz_traco`, `mtz_determinante`, `mtz_e_quadrada`, `mtz_e_simetrica`, `mtz_sao_iguais` |
| `arquivo` | entrada e saída | `mtz_de_vetor`, `mtz_imprimir`, `mtz_carregar`, `mtz_salvar` |

Dependências: `erro` não depende de ninguém; `matriz` depende de `erro`;
`operacoes`, `propriedades` e `arquivo` dependem de `matriz` e `erro`.

O determinante usa eliminação de Gauss com pivoteamento parcial, calculada
sobre uma **cópia** (a matriz original não é alterada), e inverte o sinal a
cada troca de linhas.

## Tratamento de erros

Funções que podem falhar devolvem `MtzStatus`. O resultado é entregue por um
parâmetro de saída chamado `saida`. As funções de verificação
(`mtz_e_quadrada`, `mtz_e_simetrica`, `mtz_sao_iguais`) devolvem `bool` e
retornam `false` para ponteiro nulo. `mtz_linhas` e `mtz_colunas` devolvem 0
para ponteiro nulo.

| Código | Quando ocorre |
|---|---|
| `MTZ_OK` | sucesso |
| `MTZ_ERRO_NULO` | algum parâmetro obrigatório é nulo |
| `MTZ_ERRO_DIMENSAO` | dimensão zero ou dimensões incompatíveis |
| `MTZ_ERRO_INDICE` | linha ou coluna fora da matriz |
| `MTZ_ERRO_MEMORIA` | falha de alocação |
| `MTZ_ERRO_NAO_QUADRADA` | traço ou determinante de matriz não quadrada |
| `MTZ_ERRO_ARQUIVO` | arquivo inexistente ou sem permissão |
| `MTZ_ERRO_FORMATO` | cabeçalho inválido ou valores faltando/não numéricos |

`mtz_mensagem_erro(status)` traduz o código em texto. A biblioteca nunca
encerra o programa nem imprime mensagens de erro; quem decide o que fazer é o
chamador.

```c
Matriz *m = NULL;
MtzStatus s = mtz_carregar("matriz.txt", &m);
if (s != MTZ_OK) {
    fprintf(stderr, "Erro: %s\n", mtz_mensagem_erro(s));
    return 1;
}
```

## Formato do arquivo de matriz

A primeira linha tem o número de linhas e de colunas. Depois vem uma linha do
arquivo para cada linha da matriz:

```
2 3
1.0 2.0 3.0
4.0 5.0 6.0
```

Regras de validação na leitura (`mtz_carregar`):

- cabeçalho ausente ou ilegível: `MTZ_ERRO_FORMATO`;
- dimensão zero (por exemplo `0 0`): `MTZ_ERRO_DIMENSAO`;
- menos valores que `linhas × colunas`, ou valor que não é número:
  `MTZ_ERRO_FORMATO`;
- arquivo inexistente ou sem permissão: `MTZ_ERRO_ARQUIVO`.

`mtz_imprimir` e `mtz_salvar` escrevem os valores com seis casas decimais.

## Convenções do código

- Nomes e comentários em português; funções públicas com prefixo `mtz_`, tipos
  com `Mtz` e constantes com `MTZ_`.
- Todo cabeçalho tem proteção contra inclusão dupla e todo `.c`.
- Funções internas são `static`; parâmetros não modificados são `const`;
  tamanhos e índices usam `size_t`.
- Sem variáveis globais na biblioteca, sem `printf` ou `exit` (exceto
  `mtz_imprimir`).
- Toda alocação é verificada e todo caminho de erro libera o que já foi alocado.
- Números de ponto flutuante são comparados com tolerância, nunca com `==`.

## Fluxo de trabalho com Git

- A branch `main` sempre compila; ninguém faz commit direto nela.
- Cada integrante trabalha na própria branch (`feature/nucleo`,
  `feature/operacoes`, `feature/propriedades`, `feature/arquivo`) e abre Pull
  Request quando o `make test` passa. Todo PR é revisado por um colega.
- Integração contínua (`.github/workflows/ci.yml`): a cada push e Pull Request
  o GitHub Actions executa `make all`, `make install` e `make test`.
- Mensagens de commit no formato `tipo(parte): o que foi feito`, por exemplo
  `feat(operacoes): implementa mtz_multiplicar` ou
  `fix(propriedades): corrige sinal na troca de linhas`.
- A versão entregue está marcada com a tag `v1.0`.

## Reproduzindo a partir de um clone limpo

```bash
git clone https://github.com/mosukadev/projeto_c.git
cd projeto_c
git checkout v1.0
make
make test
make run
make install PREFIX=$HOME/.local
```

Para rodar a demonstração completa (itens da apresentação), use
`scripts/demo.sh`.

## Integrantes

| Integrante | Responsabilidade |
|---|---|
| Lucas | erro e núcleo (`erro`, `matriz`) |
| Cristhian | operações e programa de exemplo (`operacoes`, `app/`) |
| Eduardo | propriedades e compilação (`propriedades`, Makefile, CI) |
| Leonardo | arquivos, testes e documentação (`arquivo`, `tests/`, README) |
