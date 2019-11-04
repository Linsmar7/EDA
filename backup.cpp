struct cell {
    int x, y;
    struct cell *next;
};
typedef struct cell celula;

typedef struct queue {
    celula *first, *last;
    unsigned int size; 
} fila;

celula *newCell (){
    celula *p = (celula *)malloc(sizeof(celula));
    if (p) {
        p->x = p->y = -1;
        p->next = NULL;
    }
    return p;
}

fila * newFila(){
    fila *q = (fila *)malloc(sizeof(fila));
    if (q) {
        q->size = 0;
        q->first = q->last = NULL;
    }
    return (q);
}

bool isempty(fila *q){
    return(q->size == 0);
}

void enqueue (int x, int y, fila *q){
    celula* c = newCell();
    if(c) {
        if(isempty(q)){
            q->last = q->first = c;
        }
        else {
            q->last->next = c;
            q->last = c;
        }
        c->x = x;
        c->y = y;
        q->size++;
    }
    else cout << "Problema na hora de enfileirar" << endl;
}

void dequeue (fila *q){
    if (isempty(q)) cout << "A fila está vazia, não é possível retirar elementos" << endl;
    else {
        celula *x = q->first;
        if (q->size == 1) q->first = q->last = NULL;
        else q->first = q->first->next;
        q->size--;
        free(x);
    }
}