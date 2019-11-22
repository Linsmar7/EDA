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
    int lista1[5];
    int lista2[5];
    int aux = 0;
    char col;
    //Abrindo o arquivo de entrada  
    in = fopen(argv[1], "r");
    if (in == NULL) cout << "O arquivo não foi aberto" << endl;
    else cout << "O arquivo foi aberto" << endl;
    //Passando o que tem dentro do arquivo pro 1º vetor
    for (int i = 0; i < 5; i++) {
        fscanf (in, "%d", &aux);
        fscanf (in, "%c", &col);
        if (col != '[') {
            lista1[i] = aux;
        }
        else if (col == '[') i = -1;
        else if (col == ']') break;
    }
    //Passando o que tem dentro do arquivo pro 2º vetor
    for (int i = 0; i < 5; i++) {
        fscanf (in, "%d", &aux);
        fscanf (in, "%c", &col);
        if (col != '[') {
            lista2[i] = aux;
        }
        else if (col == '[') i = -1;
        else if (col == ']') break;
    }
    fclose(in);
    for (int i = 0; i < 5; i++) {
        cout << "Lista1: " << lista1[i] << " " << " Lista2: " << lista2[i] << " ";
    }
    cout << endl;
    //Abrindo arquivo de saida
    out = fopen(argv[2], "w");
    if (!(out = fopen(argv[2], "w"))) cout << "O arquivo não foi aberto" << endl;
    else cout << "O arquivo foi aberto" << endl;
    //Escrevendo no arquivo
    fprintf(out, "[");
    for (int i = 0; i < 5; i++) {
        fprintf(out, "%d", lista1[i]);
        if (i < 4) fprintf(out, " ");
    }
    fprintf(out, "]");
    fprintf(out, " ");
    fprintf(out, "[");
    for (int i = 0; i < 5; i++) {
        fprintf(out, "%d", lista2[i]);
        if (i < 4) fprintf(out, " ");
    }
    fprintf(out, "]");
    fclose(out);

return 0;
}
