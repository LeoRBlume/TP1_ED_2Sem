/* avl.c
 * Implementação das operações realizadas sobre o TAD que  
 * representa uma árvore AVL.
 *
 * Ciro C. Trindade
 * 06/out/2021
 */
 
#include "cabecalho.h"

void print_tree(avl_tree t) {
    if (t != NULL) {
        print_tree(t->esq);
        printf("%s %s\n", t->dado.palavra, t->dado.sinonimo);
        print_tree(t->dir);
    }
}

void avl_search(avl_tree * t, char * x, char * y, bool * h) {
    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        *h = true;
        strcpy((*t)->dado.palavra,x);
        strcpy((*t)->dado.sinonimo,y);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcasecmp(x,(*t)->dado.palavra) < 0) { // Inserir a esquerda
        avl_search(&(*t)->esq, x, y, h);
        if (*h) { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        *h = false;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else if (strcasecmp(x,(*t)->dado.palavra) > 0) { // Inserir a direita
        avl_search(&(*t)->dir, x, y, h);
        if (*h) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                         *h = false;
                         break;
                case 0 : (*t)->bal = 1;
                         break;
                case 1: // Rebalanceamento
                    if ((*t)->dir->bal == 1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }
                    else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                    } // fim do else
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else // a chave já está na árvore
       strcpy((*t)->dado.sinonimo,y);
} // fim de avl_search

// Rotação para a esquerda

void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

// Rotação para a direita
void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


bool delete(avl_tree * t, char * x, bool * h) {
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(x,(*t)->dado.palavra) == 0) { // a chave está neste nó
        p = *t;
        if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) { // nó com uma única subárvore esquerda
            *t = p->esq;
            *h = true;
        }
        else {
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.palavra) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
}

void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotação simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotaçãoo dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}

void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}


avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}

int avl_profundidade(avl_tree t)
{
    if (t == NULL) {
        return 0;
    }
    int e = avl_profundidade(t->esq);
    int d = avl_profundidade(t->dir);
    return 1 + (e > d ? e : d);
}

void findSin(avl_tree t, char * palavra, char * sinonimoNovo){

    if(t == NULL) return;

    if(strcmp(palavra, t->dado.palavra) == 0) strcpy(t->dado.sinonimo, sinonimoNovo);

    else if(strcasecmp(t->dado.palavra, palavra) > 0)findSin(t->esq, palavra, sinonimoNovo);

    else findSin(t->dir, palavra, sinonimoNovo);
        
}

void searchSin(avl_tree t, char * sinonimo) {
    if (t != NULL) {
        searchSin(t->esq, sinonimo);
        if(strcmp(t->dado.sinonimo, sinonimo) == 0) printf("%s | ", t->dado.palavra);
        searchSin(t->dir, sinonimo);
    }
}


void close(avl_tree t){

    FILE * arq; // Arquivo lógico
    
    if ((arq = fopen("arq2.txt", "w")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo arq.txt\n");
        return;
    }

    saveInArq(t, arq);

    fclose(arq);

}

void saveInArq(avl_tree t, FILE * arq) {
    if (t != NULL) {
        saveInArq(t->esq, arq);
            fprintf(arq, "%s %s\n", t->dado.palavra, t->dado.sinonimo);
        saveInArq(t->dir, arq);
    }
}