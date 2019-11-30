#include <iostream>
using namespace std;

#define MAX(a, b) (a > b)?a:b

float rotacoes = 0; //Variavel global para armazenar a quantidade de rotações
float soma = 1; //Variavel global para fazer o somatorio de pBST e pAVL, começa com 1 pra contar com a raiz

struct node {
    int element, height;
    struct node *left = NULL, *right = NULL;
};
typedef struct node node_t;


//Função pra criação de nó
node_t *newNode (int e){
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p) {
        p->element = e;
        p->right = p->left = NULL;
        p->height = 0;
    }
    return p;
}
/*-----------------------*/

//Função de saber a altura de um nó
int avl_height(node_t *x) {
    if (x) return x->height;
    return -1;
}
/*-----------------------*/


/* FUNÇÕES DE ÁRVORE DE BUSCA */
//Função pra altura de árvore de busca
node_t *height_BST (node_t *r) {
    int lh = avl_height(r->left);
    int rh = avl_height(r->right);
    r->height = 1 + (MAX(lh, rh));
    return r;
}
/*-----------------------*/


//Função de inserir em árvore de busca
node_t *insert (int e, node_t *r) {
    if (r) {
        if (e > r->element) r->right = insert(e, r->right);
        else if (e < r->element) r->left = insert(e, r->left);
        else return r;
    }
    else {
        node_t *p = newNode(e);
        return p;
    }
    return height_BST(r);
}
/*-----------------------*/


/*-----------------------*/

/* FUNÇÕES DE ÁRVORE AVL */

//Função pra rotacionar para esquerda
node_t *avl_rLeft(node_t *x) {
    node_t *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = 1 + (MAX(avl_height(x->left), avl_height(x->right)));
    y->height = 1 + (MAX(avl_height(y->left), avl_height(y->right)));
    rotacoes++;

    return y;
}
/*-----------------------*/

//Função pra rotacionar para direita
node_t *avl_rRight(node_t *x) {
    node_t *y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = 1 + (MAX(avl_height(x->left), avl_height(x->right)));
    y->height = 1 + (MAX(avl_height(y->left), avl_height(y->right)));
    rotacoes++;

    return y;
}
/*-----------------------*/


//Função para rebalanceamento
node_t *rebalance (node_t *r) {
    int lh = avl_height(r->left);
    int rh = avl_height(r->right);
    int th = lh - rh;
    r->height = 1 + (MAX(lh, rh));

    if (th == 2) {
        if (r->left) 
        if (avl_height(r->left->right) > avl_height(r->left->left))r->left = avl_rLeft(r->left);
        r = avl_rRight(r);
    }
    else if (th == -2) {
        if (r->right) 
        if (avl_height(r->right->left) > avl_height(r->right->right))r->right = avl_rRight(r->right);
        r = avl_rLeft(r);
    }
    return r;
}
/*-----------------------*/


//Função para inserir em árvore AVL
node_t *avl_insert (int e, node_t *r) {
    if (r == NULL) {
        r = newNode(e);
        return r;
    }
    else if (r->element > e) r->left = avl_insert(e, r->left);
    else if (r->element < e) r->right = avl_insert(e, r->right);
    return rebalance(r);
}
/*-----------------------*/


//Função h(i), essa função percorre toda a árvore, vendo a distancia de cada nó com a raiz
void h_i(node_t *r, node_t *absolute){
    if (r == NULL) return;
    if (absolute == NULL) return;
    node_t *y;
    node_t *x;
    if (r->left) {
        y = r->left;
        soma += 1 + avl_height(absolute) - avl_height(y);
        h_i(y, absolute);
    }
    if (r->right) {
        x = r->right;
        soma += 1 + avl_height(absolute) - avl_height(x);
        h_i(x, absolute);
    }
    if (r->right == NULL && r->left == NULL) return;
}
/*-----------------------*/


/* MAIN */
int main (int argc, char *argv[]) {
    //IF caso o usuário não coloque a quantidade correta de argumentos
    if (argc != 3){
        cout << "ERRO! Falta de argumentos: digite " << argv[0] << ".exe <arq-entrada> <arq-saida>" << endl;
        cout << "Exemplo: " << argv[0] << ".exe in.txt out.txt" << endl;
        return 1;
    }

    //Declaração
    FILE *in, *out;
    int aux;
    float elementosinseridos;
    float media;
    float pAVL = 1;
    float pBST = 1;
    node_t *avl; //Arvore AVL
    node_t *ab; //Arvore de Busca

    //Abertura do arquivo para a árvore AVL
    in = fopen(argv[1], "r");
    if (!(in = fopen(argv[1], "r"))) cout << "O arquivo de entrada para a árvore AVL não pode ser aberto" << endl;
    out = fopen(argv[2], "w"); //Abertura do arquivo de saída
    if (!(out = fopen(argv[2], "w"))) cout << "O arquivo de saída não pode ser aberto" << endl;
    fprintf(out, "%s\r\n", " /*-----ÁRVORE AVL-----*/ ");
    while (fscanf(in, "%d", &aux) == 1) {
        avl = avl_insert(aux, avl);
        elementosinseridos++;
        soma = 1;
        h_i(avl, avl);
        media = rotacoes/elementosinseridos;
        pAVL = soma/elementosinseridos;
        fprintf(out, "%s", "Elementos inseridos: ");
        fprintf(out, "%.0f", elementosinseridos);
        fprintf(out, "%s", " -> Quantidade de rotações feitas: ");
        fprintf(out, "%.0f", rotacoes);
        fprintf(out, "%s", " -> Média de rotações: ");
        fprintf(out, "%.2f", media);
        fprintf(out, "%s", " -> pAVL: ");
        fprintf(out, "%.2f\r\n", pAVL);
    }
    fclose(in);

    
    fprintf(out, "%s\r\n", " ");
    fprintf(out, "%s\r\n", " /*-----ÁRVORE BST-----*/ ");
    elementosinseridos = 0;

    in = fopen(argv[1], "r");
    if (!(in = fopen(argv[1], "r"))) cout << "O arquivo de entrada para a árvore BST não pode ser aberto" << endl;
    while (fscanf(in, "%d", &aux) == 1) {
        ab = insert(aux, ab);
        elementosinseridos++;
        soma = 1;
        h_i(ab, ab);
        pBST = soma/elementosinseridos;
        fprintf(out, "%s", "Elementos inseridos: ");
        fprintf(out, "%.0f", elementosinseridos);
        fprintf(out, "%s", " -> pBST: ");
        fprintf(out, "%.2f\r\n", pBST);
    }
    fclose(in);
    fclose(out);

return 0;
}