/**
Universidade Federal Rural de Pernambuco
Discente: Ewerton Queiroz
Disciplina: Algoritmos e Estruturas de Dados
Data: 28/08/2016
Atividade: EP0
OBS: O programa não cumpre o requisito de realizar operações apenas no trecho
     afetado pela avalanche, consequentemente, a saída do mesmo não informa
     onde se iniciou a avalanche, informa apenas a pista completamente corrigida.
*/

#include <stdio.h>
#include <stdlib.h>

int aux[50];
int z = 0; // A variavel global z controla o tamanho do vetor.

/**
Esta função realiza a leitura do arquivo que contém as altitudes da pista.
Atentar para o fato de que não há verificação de validade do arquivo, ou seja,
se o arquivo não for localizado o programa funcionará de maneira inesperada.
*/
void ler_arquivo (char url[]) {
    FILE *arquivo;

    arquivo = fopen (url, "r");

    fscanf (arquivo, "%d", &aux[z]);

    while (aux[z] != 0) {
        z++;
        fscanf (arquivo, "%d", &aux[z]);
    }

    fclose (arquivo);
}

// Esta função percorre o vetor da esquerda para a direita e o ordena de maneira crescente.
void ordenar_selecao (int v[], int inicio, int fim) {
    int i, j, x, menor;

    for (i = inicio; i < fim - 1; ++i) {
        menor = i;

        for (j = i + 1; j < fim; ++j) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        x = v[i];
        v[i] = v[menor];
        v[menor] = x;
    }
}

/**
Esta função é exclusivamente para testes. Ela serve para visualizar como está o vetor aux.
void imprimir_vetor_teste (int v[], int tamanho) {
    int a;
    for (a = 0; a < tamanho; a++) {
        printf ("[%d] = %d \t", a, v[a]);
    }
}
*/

// Esta função realiza a impressão da pista corrigida.
void imprimir_vetor (int v[], int inicio, int tamanho) {
    int a;

    printf("%d ", inicio);

    for (a = inicio; a <= tamanho; a++) {
        printf ("%d ", v[a]);
    }

    printf ("\n\n");
}

int checar_avalanche(int v[], int inicio, int tamanho) {
    int a = 0;
    int final = inicio + 1;
    while (v[inicio] < v[final]) {
        a++;
        final++;
    }

    return a;
}

/**
Esta função realiza os reparos na pista da seguinte forma:
    A partir do vetor recebido nos parâmetros, consegue-se obter o tamanho da pista,
a primeira e a última altitude.
Após isso, é utilizado o algoritmo de ordenação por seleção para ordenar as altitudes
da pista. Para a pista ser ordenada corretamente, ou seja, ordenar sem considerar o
valor que indica o tamanho da mesma, é utilizada a variável "linha_inicio".
*/
void reparar_pista (int v[]) {
    int linha_tamanho = v[0];
    int linha_inicio = 1;
    int linha_fim = linha_tamanho;
    int inicio_avalanche = checar_avalanche(v, linha_inicio, linha_tamanho);

    //ordenar_selecao (v, linha_inicio, linha_tamanho + 1);
    ordenar_selecao (v, inicio_avalanche, linha_tamanho + 1);
    imprimir_vetor (v, inicio_avalanche, linha_tamanho);

    while (v[linha_fim + 1] != 0) {
        linha_tamanho = v[linha_fim + 1];
        linha_inicio = linha_fim + 2;
        linha_fim += linha_tamanho + 1;

        inicio_avalanche = checar_avalanche(v, linha_inicio, linha_tamanho);
        ordenar_selecao (v, inicio_avalanche, linha_fim + 1);
        imprimir_vetor (v, inicio_avalanche, linha_fim);
    }
}

/**
É necessário que o caminho do arquivo ou apenas o nome,
caso o arquivo esteja no mesmo diretório do executável,
seja informado no parâmetro da função ler_arquivo().
*/
int main() {
    ler_arquivo ("pista");

    reparar_pista (aux);

    return 0;
}
