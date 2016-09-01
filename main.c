/**
Universidade Federal Rural de Pernambuco
Discente: Ewerton Queiroz
Disciplina: Algoritmos e Estruturas de Dados
Data: 28/08/2016
Atividade: EP0
OBS: A saída do programa não apresenta o início da avalanche de 0 à N, sendo N o tamanho do vetor.
    Ele apresenta o índice do vetor_pista onde se iniciou a avalanche.
    A função checar_avalanche está com problemas e eu não sei como corrigí-los, se o senhor puder
    me dar um feedback sobre o que tem de errado com ela, eu ficaria muito agradecido.

    Ocorre o seguinte:
        Há momento que o vetor aux não é ordenado dentro dela, consequentemente, no momento que
        ocorre as comparações com o trecho do vetor_pista, não são encontradas diferenças e é
        devolvido -1 incorretamente. Eu tenho um exemplo de arquivo ao qual utilizei para testes.
        Caso queira conferir está no seguinte link:
                https://github.com/EwertonQueiroz/AED-EP0/blob/master/pista2
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
Esta função é exclusivamente para testes. Ela serve para visualizar como está o vetor vetor_pista.    *
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

    printf ("%d ", inicio);

    for (a = inicio; a <= tamanho; a++) {
        printf ("%d ", v[a]);
    }

    printf ("\n\n");
}

/**
Esta função copia a pista para o vetor aux, ordena o vetor aux e depois compara
com os elementos do vetor_pista, caso encontre alguma diferença, ou seja, caso
ocorreu uma avalanche na pista, é devolvida a posição onde a avalanche ocorreu.
*/
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
valor que indica o tamanho da mesma, para isso é utilizada a variável "linha_inicio".
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
    ler_arquivo ("pista2");

    reparar_pista (vetor_pista);

    return 0;
}
