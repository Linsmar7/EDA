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
    int aux , enableaux = 0, enablein = 0; //Variavel enableaux serve pra tirar as duplicatas na 2° lista e enablein serve pra duplicatas na mesma lista.
    int qntdLista1 = 0, qntdLista2 = 0; //Essas variaveis servem pra contar quantos elementos tem na lista,
                                        //podia ser feito também dentro da própria struct da lista.
    char *caracVetor;
    char caracter;
    celula *caux = newCell(); // Celula auxiliar
    celula *h1 = newCell(); //1º Lista
    celula *h2 = newCell(); //2º Lista

    //Abrindo o arquivo de entrada  
    in = fopen(argv[1], "r");
    if (in == NULL) cout << "O arquivo não pode ser aberto" << endl;
    //Passando o que tem dentro do arquivo para a 1ª lista
    fscanf (in, "%c", &caracter); //Lendo o caracter '['
    for (; caracter != ']';) { //O loop funciona enquanto caracter for diferente de ]
        fscanf(in, "%c", &caracter);
        if (caracter == ']') break; //Se achar o caracter ] logo de cara, acaba o loop.
        else if (caracter == ' ') continue; //Se achar espaço, o código abaixo é ignorado e volta pro inicio do loop.
        else {  //Se não:
            caracVetor = (char *) malloc(sizeof(char)*2147483647); //Alocação de memória pro vetor, não precisa
                                                                   //ser maior que 2147483647, pelo limite de INT
            for (int o = 0; caracter != ' '; o++) { //Loop pra pegar char por char e transformar num número só
                caracVetor[o] = caracter; //Joga o caracter dentro do vetor de caracteres
                fscanf (in, "%c", &caracter); //Ve quem é o proximo no arquivo
                if (caracter == ' ' || caracter == ']') { //Se for espaço ou ], acaba
                    aux = atoi(caracVetor); //Transforma o vetor de caracteres em inteiro e joga em aux
                    break;
                }
            }
            if (h1->next) {
                caux = h1->next;
                for (int i = 0; i < qntdLista1; i++) {
                    if (aux == caux->element) {
                        enablein = 0;
                        break;
                    }
                    else enablein = 1;
                    if (caux->next) caux = caux->next;
                }
                if (enablein == 1) {
                    insert(aux, h1);
                    qntdLista1++;
                    enablein = 0;
                }
            }
            else {
                insert(aux, h1);
                qntdLista1++;
                enablein = 0;
            }
            free(caracVetor);
        }
    }

    fscanf (in, "%c", &caracter); //Lendo o espaço entre as 2 listas, como só tem 1 espaço, só precisa de 1, se tivesse
                                  //um número aleatório de espaços, poderia ser feito 1 loop com condição.
    fscanf (in, "%c", &caracter); //Lendo o caracter '[' da 2° lista
    //Passando o que tem dentro do arquivo para a 2ª lista RETIRANDO AS DUPLICATAS
    for (; caracter != ']' ;) {
        fscanf (in, "%c", &caracter);
        if (caracter == ']') break; //Se achar ] logo de cara, significa que a lista está vazia, então o loop acaba
        else if (caracter == ' ') continue; //Se achar espaço, volta pro inicio do loop
        else {
            caracVetor = (char *) malloc(sizeof(char)*2147483647); //Alocação de memória
            for (int o = 0; caracter != ' '; o++) { //Mesmo loop pra passar os números do arquivo pra inteiros no código
                caracVetor[o] = caracter; 
                fscanf (in, "%c", &caracter);
                if (caracter == ' ' || caracter == ']') {
                    aux = atoi(caracVetor);
                    break;
                }
            }
            free(caracVetor);
        }
        if (qntdLista1 > 0) { //Se EXISTIR algo dentro da lista 1, temos que jogar fora os números repetidos
            caux = h1->next;
            for (int i = 0; i < qntdLista1; i++) {
                if (caux->element == aux) {
                    enableaux = 0;
                    break;
                }
                else enableaux = 1;
                if (caux->next) caux = caux->next;
            }
            if (enableaux == 1) { //Se o número passar e não for repetido com a lista 1, temos que verificar se ele é repetido com algum número dentro da PRÓPRIA lista.
                if (qntdLista2 > 0) {
                    caux = h2->next;
                    for (int i = 0; i < qntdLista2; i++) {
                        if(caux->element == aux) {
                            enablein = 0;
                            break;
                        }
                        else enablein = 1;
                        if (caux->next) caux = caux->next;
                    }
                }
                else {
                    insert(aux, h2);
                    qntdLista2++;
                    enablein = 0;
                    enableaux = 0;
                }
                if (enablein == 1) {
                    insert(aux, h2);
                    qntdLista2++;
                    enablein = 0;
                    enableaux = 0;
                }
            }
        }
        else { //Se não tiver ngm na lista 1, só devemos nos preocupar com repetições dentro da própria lista.
            if (qntdLista2 > 0) {
                caux = h2->next;
                for (int i = 0; i < qntdLista2; i++) {
                    if(caux->element == aux) {
                        enablein = 0;
                        break;
                    }
                    else enablein = 1;
                    if (caux->next) caux = caux->next;
                }
            }
            else {
                insert(aux, h2);
                qntdLista2++;
                enablein = 0;
                enableaux = 0;
            }
            if (enablein == 1) {
                insert(aux, h2);
                qntdLista2++;
                enablein = 0;
                enableaux = 0;
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