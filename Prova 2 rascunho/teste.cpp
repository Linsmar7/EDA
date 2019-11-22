        if (h1->next) { //Se EXISTIR elementos na lista 1:
            caux = h1->next; //Celula auxiliar = primeira celula da lista 1
            for (int i = 0; i < qntdLista1; i++) { //Loop para tirar as duplicatas na 2° lista
                if (caux->element == aux) {
                    enableaux = 0; //Se essa variavel for igual a 0, significa que esse número existe na lista 1.
                    break;
                }
                else enableaux = 1;
                caux = caux->next;
            }
            if (enableaux == 1) { //Se for igual a 1, não tem duplicata, pode inserir na lista 2.
            //Vendo se tem duplicatas na própria lista 
                if (h2->next) {
                    caux = h2->next;
                    for (int i = 0; i < qntdLista2; i++) {
                        if (aux == caux->element) break;
                        else enablein = 1;
                        if (caux->next) caux = caux->next;
                    }
                    if (enablein == 1) {
                        insert(aux, h2);
                        qntdLista2++;
                    }
                }
                else {
                    insert(aux, h2);
                    qntdLista2++;
                }
                free(caracVetor);
            }
        }
        else { //Se NÃO EXISTIR elementos na lista 1:
            if (h2->next) {
                caux = h2->next;
                for (int i = 0; i < qntdLista2; i++) {
                    if (aux == caux->element) break;
                    else enablein = 1;
                    if (caux->next) caux = caux->next;
                }
                if (enablein == 1) {
                    insert(aux, h2);
                    qntdLista2++;
                }
            }
            else {
                insert(aux, h2);
                qntdLista2++;
            }
            free(caracVetor);
        }