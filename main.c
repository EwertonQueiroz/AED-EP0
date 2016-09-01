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

int vetor_pista[50];
int aux[25];
int z = 0; // A variavel global z controla o tamanho do vetor.

/**
Esta função realiza a leitura do arquivo que contém as altitudes da pista.
Atentar para o fato de que não há verificação de validade do arquivo, ou seja,
se o arquivo não for localizado o programa funcionará de maneira inesperada.
*/
void ler_arquivo (char url[]) {
    FILE *arquivo;

    arquivo = fopen (url, "r");

    fscanf (arquivo, "%d", &vetor_pista[z]);

    while (vetor_pista[z] != 0) {
        z++;
        fscanf (arquivo, "%d", &vetor_pista[z]);
    }

    fclose (arquivo);
}

// Esta função percorre o vetor da esquerda para a direita e o ordena de maneira crescente.
void ordenar_selecao (int v[], int inicio, int tamanho) {
    int i, j, x, menor;

    for (i = inicio; i < tamanho - 1; ++i) {
        menor = i;

        for (j = i + 1; j < tamanho; ++j) {
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
Esta função é exclusivamente para testes. Ela serve para visualizar como está o vetor vetor_pista.*/
void imprimir_vetor_teste (int v[], int tamanho) {
    int a;
    for (a = 0; a < tamanho; a++) {
        printf ("[%d] = %d \t", a, v[a]);
    }
}
//*/

// Esta função realiza a impressão da pista corrigida.
void imprimir_vetor (int v[], int inicio, int tamanho) {
    int a;

    printf("%d ", inicio);

    for (a = inicio; a <= tamanho; a++) {
        printf ("%d ", v[a]);
    }

    printf ("\n\n");
}

int checar_avalanche (int v[], int inicio, int tamanho, int a[]) {
    int i;

    for (i = inicio; i < inicio + tamanho; i++) {
        a[i] = v[i];
    }

    ordenar_selecao (a, inicio, tamanho);

    for (i = inicio; i < inicio + tamanho; i++) {
        if (a[i] != v[i]) {
            return i;
        }
    }

    return -1;
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
    int inicio_avalanche = checar_avalanche(v, linha_inicio, linha_tamanho, aux);

    if (inicio_avalanche != -1) {
        if (inicio_avalanche == 0) {
            inicio_avalanche = 1;
            ordenar_selecao (v, inicio_avalanche, linha_tamanho + 1);
            imprimir_vetor (v, inicio_avalanche, linha_tamanho);
        }
        else {
            ordenar_selecao (v, inicio_avalanche, linha_tamanho + 1);
            imprimir_vetor (v, inicio_avalanche, linha_tamanho);
        }
    }
    else {
        printf("%d\n\n", inicio_avalanche);
    }

    while (v[linha_fim + 1] != 0) {
        linha_tamanho = v[linha_fim + 1];
        linha_inicio = linha_fim + 2;
        linha_fim += linha_tamanho + 1;
        inicio_avalanche = checar_avalanche(v, linha_inicio, linha_fim, aux);

        if (inicio_avalanche != -1) {
            ordenar_selecao (v, inicio_avalanche, linha_fim + 1);
            imprimir_vetor (v, inicio_avalanche, linha_fim);
        }
        else {
            printf("%d\n\n", inicio_avalanche);
        }
    }
}

/**
É necessário que o caminho do arquivo ou apenas o nome,
caso o arquivo esteja no mesmo diretório do executável,
seja informado no parâmetro da função ler_arquivo().
*/
int main() {
    ler_arquivo ("pista");

//    imprimir_vetor_teste(vetor_pista, z);

//    printf("\n\n%d\n\n", checar_avalanche(vetor_pista, 7, 8, aux));
//
//    imprimir_vetor_teste(&aux, z);

    reparar_pista (vetor_pista);
    //imprimir_vetor_teste(vetor_pista, z);
    return 0;
}
