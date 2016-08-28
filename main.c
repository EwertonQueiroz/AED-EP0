/**
Universidade Federal Rural de Pernambuco
Discente: Ewerton Queiroz
Disciplina: Algoritmos e Estruturas de Dados

Atividade: EP0

OBS: O programa n�o cumpre o requisito de realizar opera��es apenas no trecho
     afetado pela avalanche, consequentemente, a sa�da do mesmo n�o informa
     onde se iniciou a avalanche, informa apenas a pista completamente corrigida.
*/

#include <stdio.h>
#include <stdlib.h>

int aux[50];
int z = 0; // A variavel global z controla o tamanho do vetor.

/**
Esta fun��o realiza a leitura do arquivo que cont�m as altitudes da pista.
Atentar para o fato de que n�o h� verifica��o de validade do arquivo, ou seja,
se o arquivo n�o for localizado o programa funcionar� de maneira inesperada.
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

// Esta fun��o percorre o vetor da esquerda para a direita e o ordena de maneira crescente.
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
Esta fun��o � exclusivamente para testes. Ela serve para visualizar como est� o vetor aux.

void imprimir_vetor_teste (int v[], int tamanho) {
    int a;
    for (a = 0; a < tamanho; a++) {
        printf ("[%d] = %d \t", a, v[a]);
    }
}
*/

// Esta fun��o realiza a impress�o da pista corrigida.
void imprimir_vetor (int v[], int inicio, int tamanho) {
    int a;
    for (a = inicio; a <= tamanho; a++) {
        printf ("%d ", v[a]);
    }
    printf ("\n\n");
}

/**
Esta fun��o realiza os reparos na pista da seguinte forma:
    A partir do vetor recebido nos par�metros, consegue-se obter o tamanho da pista,
a primeira e a �ltima altitude.
Ap�s isso, � utilizado o algoritmo de ordena��o por sele��o para ordenar as altitudes
da pista. Para a pista ser ordenada corretamente, ou seja, ordenar sem considerar o
valor que indica o tamanho da mesma, � utilizada a vari�vel "linha_inicio".
*/
void reparar_pista (int v[]) {
    int linha_tamanho = v[0];
    int linha_inicio = 1;
    int linha_fim = linha_tamanho;

    ordenar_selecao (v, linha_inicio, linha_tamanho + 1);
    imprimir_vetor (aux, linha_inicio, linha_tamanho);

    while (v[linha_fim + 1] != 0) {
        linha_tamanho = v[linha_fim + 1];
        linha_inicio = linha_fim + 2;
        linha_fim += linha_tamanho + 1;

        ordenar_selecao (v, linha_inicio, linha_fim + 1);
        imprimir_vetor (aux, linha_inicio, linha_fim);
    }
}

/**
� necess�rio que o caminho do arquivo ou apenas o nome,
caso o arquivo esteja no mesmo diret�rio do execut�vel,
seja informado no par�metro da fun��o ler_arquivo().
*/
int main() {
    ler_arquivo ("pista");

    reparar_pista (aux);

    return 0;
}
