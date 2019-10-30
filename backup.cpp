#include <iostream>
using namespace std;
struct cell {
    int element;
    struct cell *next;
};
typedef struct cell celula;
//Função de criação de uma célula da lista
celula *newCell (){
    celula *p = (celula *)malloc(sizeof(celula));
    if (p) {
        p->element = -1;
        p->next = NULL;
    }
    return p;
}
//Função de inserir células no final da lista
void insert (int e, celula *l) {
    celula *p = newCell();
    if (p) {
        p->element = e;
        while (l->next) l = l->next;
        l->next = p;
    }
}

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
    int aux , enableaux = 0; //Variavel enableaux serve pra tirar as duplicatas na 2° lista
    int qntdLista1 = 0, qntdLista2 = 0; //Essas variaveis servem pra contar quantos elementos tem na lista,
                                        //podia ser feito também dentro da própria struct da lista.
    char *caracVetor = (char *)NULL;
    char caracter;
    celula *caux = newCell(); // Celula auxiliar
    celula *h1 = newCell(); //1º Lista
    celula *h2 = newCell(); //2º Lista

    //Abrindo o arquivo de entrada  
    in = fopen(argv[1], "r");
    if (in == NULL) cout << "O arquivo não pode ser aberto" << endl;
    //Passando o que tem dentro do arquivo para a 1ª lista
    fscanf (in, "%c", &caracter); //Lendo o caracter '['
    for (; caracter != ']';) { //O for funciona enquanto caracter for diferente de ]
        fscanf(in, "%c", &caracter);
        if (caracter == ']') break; //Se achar o caracter ] logo de cara, acaba o loop.
        else {  //Se não:
            for (int o = 0; caracter != ' '; o++) { //Loop pra pegar números grandes
                caracVetor[o] = caracter; //Joga o caracter dentro do vetor de caracteres
                fscanf (in, "%c", &caracter); //Ve quem é o proximo no arquivo
                if (caracter == ' ' || caracter == ']') { //Se for espaço ou ], acaba
                    aux = atoi(caracVetor); //Transforma o vetor de caracteres em inteiro
                    break;
                }
            }
            insert(aux, h1); //Insere na lista 1
            qntdLista1++;
            free(caracVetor);
        }
    }

    fscanf (in, "%c", &caracter); //Lendo o espaço
    fscanf (in, "%c", &caracter); //Lendo o caracter '[' da 2° lista
    //Passando o que tem dentro do arquivo para a 2ª lista RETIRANDO AS DUPLICATAS
    for (; caracter != ']' ;) {
        fscanf (in, "%c", &caracter);
        if (h1->next) { //Se existir elementos na lista 1:
            if (caracter == ']') break;
            else {
                caux = h1->next;
                caracVetor = (char *) malloc(sizeof(char)*2147483647);
                for (int o = 0; caracter != ' '; o++) {
                    caracVetor[o] = caracter; 
                    fscanf (in, "%c", &caracter);
                    if (caracter == ' ' || caracter == ']') {
                        aux = atoi(caracVetor);
                        break;
                    }
                }
                free(caracVetor);
            }
            for (int i = 0; i < qntdLista1; i++) { //Loop para tirar as duplicatas na 2° lista
                if (caux->element == aux) {
                    enableaux = 0; //Se essa variavel for igual a 0, significa que o número na lista é igual a outro número na lista 1.
                    break;
                }
                else enableaux = 1;
                caux = caux->next;
            }
            if (enableaux == 1) { //Se for igual a 1, não tem duplicata, pode inserir na lista 2.
                insert(aux, h2);
                enableaux = 0;
                qntdLista2++;
            }
        }

        else { //Se não existir elementos na lista 1:
            if (caracter == ']') break;
            else {
                caracVetor = (char *) malloc(sizeof(char)*2147483647);
                for (int o = 0; caracter != ' '; o++) {
                    caracVetor[o] = caracter;
                    fscanf (in, "%c", &caracter);
                    if (caracter == ' ' || caracter == ']') {
                        aux = atoi(caracVetor);
                        break;
                    }
                }
                insert(aux, h2); //Insere na lista 2
                qntdLista2++;
                free(caracVetor);
            }
        }
    }
    fclose(in); //Fechando o arquivo

    //Abrindo arquivo de saida
    out = fopen(argv[2], "w");
    if (!(out = fopen(argv[2], "w"))) cout << "O arquivo não pode ser aberto" << endl;

    //Passando a 1º lista inteira pra saida
    fprintf(out, "[");
    if (h1->next) {
        caux = h1->next;
        for (int i = 0; i < qntdLista1; i++) {
            fprintf(out, "%d", caux->element);
            if (i < qntdLista1-1) fprintf(out, " ");
            caux = caux->next;
        }
    }
    //Passando a 2º lista, sem duplicatas pra saida
    if (h2->next && h1->next) {
        caux = h2->next;
        fprintf(out, " ");
        for (int i = 0; i < qntdLista2; i++) {
            fprintf(out, "%d", caux->element);
            if (i < qntdLista2-1) fprintf(out, " ");
            caux = caux->next;
        }
    }
    else if (!h1->next) {
        caux = h2->next;
        for (int i = 0; i < qntdLista2; i++) {
            fprintf(out, "%d", caux->element);
            if (i < qntdLista2-1) fprintf(out, " ");
            caux = caux->next;
        }
    }
    fprintf(out, "]");
    return 0;
}