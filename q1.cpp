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
    int aux = -1, enableaux = 0; //Variavel enableaux serve pra tirar as duplicatas na 2° lista
    int qntdLista1 = 0, qntdLista2 = 0; //Essas variaveis servem pra contar quantos elementos tem na lista,
    char col;                           //podia ser feito também dentro da própria struct da lista.
    celula *caux = newCell(); // Celula auxiliar
    celula *h1 = newCell(); //1º Lista
    celula *h2 = newCell(); //2º Lista

    //Abrindo o arquivo de entrada  
    in = fopen(argv[1], "r");
    if (in == NULL) cout << "O arquivo não pode ser aberto" << endl;

    //Passando o que tem dentro do arquivo para a 1ª lista
    for (qntdLista1 = 0; col != ']'; qntdLista1++) {
        fscanf (in, "%d", &aux);
        fscanf (in, "%c", &col); //Essa variável serve pra procurar o caracter ']'
        if (aux != -1) {
            insert(aux, h1);
        }
        else if (col == ']') break;
    }
    fscanf (in, "%d", &aux);
    fscanf (in, "%c", &col);
    aux = -1;
    //Passando o que tem dentro do arquivo para a 2ª lista RETIRANDO AS DUPLICATAS
    for (qntdLista2 = 0; col != ']' ; qntdLista2++) {
        fscanf (in, "%d", &aux);
        fscanf (in, "%c", &col);
        if (h1->next) {
            if (aux != -1) {
                caux = h1->next;
                for (int i = 0; i < qntdLista1-1; i++) { //Loop para tirar as duplicatas na 2° lista
                    if (caux->element == aux) {
                        enableaux = 0; //Se essa variavel for igual a 0, significa que o número na lista é igual a outro número na lista 1.
                        qntdLista2--;  //Como é igual, não vai ser inserido na 2° lista, portanto, diminuir o tamanho dela.
                        break;
                    }
                    else enableaux = 1;
                    caux = caux->next;
                }
                if (enableaux == 1) { //Se for igual a 1, não tem duplicata, pode inserir na lista 2.
                    insert(aux, h2);
                    enableaux = 0;
                }
            }
            else if (col == ']') break;
        }
        else {
            if (aux != -1) insert(aux, h2);
            else if (col == ']') break;
        }
    }
    std::fclose(in); //Fechando o arquivo

    //Abrindo arquivo de saida
    out = fopen(argv[2], "w");
    if (!(out = fopen(argv[2], "w"))) cout << "O arquivo não pode ser aberto" << endl;

    //Passando a 1º lista inteira pra saida
    std::fprintf(out, "[");
    if (h1->next) {
        caux = h1->next;
        for (int i = 0; i < qntdLista1-1; i++) {
            std::fprintf(out, "%d", caux->element);
            if (i < qntdLista1-2) std::fprintf(out, " ");
            caux = caux->next;
        }
    }
    //Passando a 2º lista, sem duplicatas pra saida
    if (h2->next && h1->next) {
        caux = h2->next;
        std::fprintf(out, " ");
        for (int i = 0; i < qntdLista2; i++) {
            std::fprintf(out, "%d", caux->element);
            if (i < qntdLista2-1) std::fprintf(out, " ");
            caux = caux->next;
        }
    }
    else if (!h1->next) {
        caux = h2->next;
        for (int i = 0; i < qntdLista2; i++) {
            std::fprintf(out, "%d", caux->element);
            if (i < qntdLista2-1) std::fprintf(out, " ");
            caux = caux->next;
        }
    }
    std::fprintf(out, "]");
    return 0;
}