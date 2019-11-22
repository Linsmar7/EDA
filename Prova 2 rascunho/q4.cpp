#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    //IF caso o usuário não coloque a quantidade correta de argumentos
    if (argc != 3){
        cout << "ERRO! Falta de argumentos: digite " << argv[0] << ".exe <arq-entrada> <arq-saida>" << endl;
        cout << "Exemplo: " << argv[0] << ".exe in.txt out.txt" << endl;
        return 1;
    }
    //Declaração
    FILE *in;
    FILE *out;
    int n, m; //Tamanho da matriz
    int aux;

    //Abrindo arquivo de entrada
    in = fopen(argv[1], "r");

    //Pegando N e M do arquivo
    fscanf(in, "%d", &aux);
    n = aux;
    fscanf(in, "%d", &aux);
    m = aux;
    //Declarando a matriz
    int **matriz = (int **)malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++) matriz[i] = (int *)malloc(m * sizeof(int));
    //Colocando os elementos dentro da matriz
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(in, "%d", &aux);
            matriz[i][j] = aux;
        }
    }
    fclose(in); //Fechando o arquivo


return 0;
}