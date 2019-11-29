#include <iostream>
using namespace std;

#define MAX(a, b) (a > b)?a:b

float rotacoes = 0;

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


/* FUNÇÕES DE ÁRVORE DE BUSCA */
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
    return r;
}
/*-----------------------*/

/* FUNÇÕES DE ÁRVORE AVL */
//Função de saber a altura de um nó
int avl_height(node_t *x) {
    if (x) return x->height;
    return -1;
}
/*-----------------------*/

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


/* MAIN */
int main (int argc, char *argv[]) {
    //IF caso o usuário não coloque a quantidade correta de argumentos
    if (argc != 2){
        cout << "ERRO! Falta de argumentos: digite " << argv[0] << ".exe <arq-entrada>" << endl;
        cout << "Exemplo: " << argv[0] << ".exe in.txt" << endl;
        return 1;
    }

    //Declaração
    FILE *in;
    int aux;
    float elementosinseridos;
    float media;
    node_t *avl; //Arvore AVL
    node_t *ab; //Arvore de Busca

    //Abertura do arquivo
    in = fopen(argv[1], "r");
    while (fscanf(in, "%d", &aux) == 1) {
        avl = avl_insert(aux, avl);
        ab = insert(aux, ab);
        elementosinseridos++;
        media = rotacoes/elementosinseridos;
        cout << elementosinseridos << " -> " << media << endl;
    }
    fclose(in);
return 0;
}