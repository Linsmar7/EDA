#include <iostream>
using namespace std;

#define MAX(a, b) (a > b)?a:b

struct node {
    int element, height = 0;
    struct node *left = NULL, *right = NULL;
};
typedef struct node node_t;

node_t *newNode (){
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p) {
        p->element = -1;
        p->right = p->left = NULL;
        p->height = -1;
    }
    return p;
}

node_t *insert (int e, node_t *r) {
    if (r) {
        if (e > r->element) r->right = insert(e, r->right);
        else if (e < r->element) r->left = insert(e, r->left);
        else return r;
    }
    else {
        node_t *p = newNode();
        p->element = e;
        return p;
    }
    return r;
}

int avl_height(node_t *x) {
    if (x) return x->height;
    else return -1;
}

node_t *avl_rLeft(node_t *x) {
    node_t *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = MAX(avl_height(x->left), avl_height(x->right))+1;
    y->height = MAX(avl_height(y->left), avl_height(y->right))+1;

    return y;
}

node_t *avl_rRight(node_t *x) {
    node_t *y = x->left;
    x->right = y->left;
    y->left = x;
    x->height = MAX(avl_height(x->left), avl_height(x->right))+1;
    y->height = MAX(avl_height(y->left), avl_height(y->right))+1;

    return y;
}

node_t *rebalance (node_t *r) {
    int lh = avl_height(r->left);
    int rh = avl_height(r->right);
    int th = lh - rh;
    r->height = 1+max(lh, rh);
    if (th == 2) {
        if (r->left) {
            if (avl_height(r->left->right) > avl_height(r->left->left)) r->left = avl_rLeft(r->left);
        }
        r = avl_rRight(r);
    }
    else if (th == -2) {
        if (r->right && r->left) {
            if (avl_height(r->right->left) > avl_height(r->left->left)) r->right = avl_rRight(r->right);
        }
        r = avl_rLeft(r);
    }
    return r;
}

node_t *avl_insert (int e, node_t *r) {
    if (r == NULL) {
        r = newNode();
        r->element = e;
        return r;
    }
    else if (r->element > e) r->left = avl_insert(e, r->left);
    else if (r->element < e) r->right = avl_insert(e, r->right);
    return rebalance (r);
}

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
    node_t *ab = newNode();
    node_t *avl = newNode();

    //Abertura do arquivo
    in = fopen(argv[1], "r");
    while (fscanf(in, "%d", &aux) == 1) {
        cout << aux << endl;
        insert(aux, ab);
        avl_insert(aux, avl);
    }
    fclose(in);
    cout << avl->right->element << endl;
return 0;
}