/**
 * Bruno Luis - 5142934 - SI
 * Igor Amon - 1612804 - SI
 * Leonardo Blume - ??????? - SI
 * Gustavo Medeiros - ??????? - ??
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "dicionario.h"

#define MAX_LEN 63

void avl_init(avl_tree *t, char * filename)
{
    FILE * arq;
    char linha[MAX_LEN];
    char str1[31];
    char str2[31];
    bool h;

    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo arq.txt\n");
        return;
    }

    while (fscanf(arq, " %[^' '|\t] %[^' '|\t|\n]", str1, str2) != EOF) {
        avl_insert(t, str1, str2, &h);
    }

    fclose(arq);
}

void avl_print(avl_tree t)
{
    if (t != NULL) {
        avl_print(t->esq);
        printf("%-30s %-30.30s\n", t->dado.palavra, t->dado.sinonimo);
        avl_print(t->dir);
    }
}

void avl_insert(avl_tree * t, char * x, char * y, bool * h)
{
    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }

        *h = true;
        strcpy((*t)->dado.palavra, x);
        strcpy((*t)->dado.sinonimo, y);

        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }

    // Inserir a esquerda
    else if (strcasecmp(x,(*t)->dado.palavra) < 0) {
        avl_insert(&(*t)->esq, x, y, h);

        // O ramo esquerdo cresceu
        if (*h) {
            switch ((*t)->bal) {
                case 1:
                    (*t)->bal = 0;
                    *h = false;
                    break;

                case 0:
                    (*t)->bal = -1;
                    break;

                case -1: // Rebalanceamento
                    // Rotação simples p/ direita
                    if ((*t)->esq->bal == -1) {
                        avl_rotacao_dir(t);

                        // Ajusta o fator de balanceamento
                        (*t)->dir->bal = 0;
                    }

                    // Rotação dupla para direita
                    else {
                        avl_rotacao_esq(&(*t)->esq);
                        avl_rotacao_dir(t);

                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1)
                            (*t)->dir->bal = 1;
                        else
                            (*t)->dir->bal = 0;

                        if ((*t)->bal == 1)
                            (*t)->esq->bal = -1;
                        else
                            (*t)->esq->bal = 0;
                    }

                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    }

    // Inserir a direita
    else if (strcasecmp(x,(*t)->dado.palavra) > 0) {
        avl_insert(&(*t)->dir, x, y, h);
        
        // O ramo direito cresceu
        if (*h) {
            switch ((*t)->bal) {
                case -1:
                    (*t)->bal = 0;
                    *h = false;
                    break;

                case 0 :
                    (*t)->bal = 1;
                    break;

                // Rebalanceamento
                case 1:
                    // Rotação simples p/ esquerda
                    if ((*t)->dir->bal == 1) {
                        avl_rotacao_esq(t);

                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }

                    // Rotação dupla para esquerda
                    else {
                        avl_rotacao_dir(&(*t)->dir);
                        avl_rotacao_esq(t);

                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1)
                            (*t)->esq->bal = -1;
                        else
                            (*t)->esq->bal = 0;

                        if ((*t)->bal == -1)
                            (*t)->dir->bal = 1;
                        else
                            (*t)->dir->bal = 0;
                    }

                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    }
    // A palavra já está na árvore
    else {
        strcpy((*t)->dado.sinonimo,y);
    }
       
} // fim de avl_insert

void avl_rotacao_esq(avl_tree * t)
{
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

void avl_rotacao_dir(avl_tree * t)
{
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}

bool avl_delete(avl_tree * t, char * x, bool * h)
{
    avl_tree p;
    bool result;

    // A chave não se encontra na árvore
    if (*t == NULL)
        return false;
    // A chave está neste nó
    else if (strcasecmp(x,(*t)->dado.palavra) == 0) {
        p = *t;

        // Nó folha ou somente com subárvore direita
        if ((*t)->esq == NULL) {
            *t = p->dir;
            *h = true;
        }
        // Nó com uma única subárvore esquerda
        else if ((*t)->dir == NULL) {
            *t = p->esq;
            *h = true;
        }
        else {
            p = avl_get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) avl_balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.palavra) < 0) {
        result = avl_delete(&(*t)->esq, x, h);
        if (*h) avl_balance_esq(t, h);
        return result;
    }
    else {
        result = avl_delete(&(*t)->dir, x, h);
        if (*h) avl_balance_dir(t, h);
        return result;
    }
}

void avl_balance_esq(avl_tree * t, bool * h)
{
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1:
            (*t)->bal = 0;
            break;

        case 0:
            (*t)->bal = 1;
            *h = false;
            break;

        // Rebalanceamento
        case 1:
            p1 = (*t)->dir;
            b1 = p1->bal;

            // Rotação simples
            if (b1 >= 0) {
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
            
            // Rotação dupla
            else { 
                p2 = p1->esq;
                b2 = p2->bal;
                p1->esq = p2->dir;
                p2->dir = p1;
                p1->dir = p2->esq;
                p2->esq = *t;

                if (b2 == 1)
                    (*t)->bal = -1;
                else
                    (*t)->bal = 0;

                if (b2 == -1)
                    p1->bal = 1;
                else
                    p1->bal = 0;

                *t = p2;
                p2->bal = 0;
            }
    } // fim do switch
}

void avl_balance_dir(avl_tree * t, bool * h)
{
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1:
            (*t)->bal = 0;
            break;

        case 0:
            (*t)->bal = -1;
            *h = false;
            break;

        // Rebalanceamento
        case -1:
            p1 = (*t)->esq;
            b1 = p1->bal;

            // Rotação simples
            if (b1 <= 0) {
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
            
            // Rotaçãoo dupla
            else { 
                p2 = p1->dir;
                b2 = p2->bal;
                p1->dir = p2->esq;
                p2->esq = p1;
                p1->esq = p2->dir;
                p2->dir = *t;

                if(b2 == -1)
                    (*t)->bal = 1;
                else
                    (*t)->bal = 0;

                if(b2 == 1)
                    p1->bal = -1;
                else
                    p1->bal = 0;

                *t = p2;
                p2->bal = 0;
            }
    } // fim do switch
}

avl_tree avl_get_min(avl_tree * t, bool * h)
{
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = avl_get_min(&((*t)->esq),h);
        if (*h) avl_balance_esq(t, h);
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

void avl_find_sin(avl_tree t, char * x, char * y)
{
    if(t == NULL) return;

    if(strcmp(x, t->dado.palavra) == 0) strcpy(t->dado.sinonimo, y);

    else if(strcasecmp(t->dado.palavra, x) > 0) avl_find_sin(t->esq, x, y);

    else avl_find_sin(t->dir, x, y);
        
}

void avl_search_sin(avl_tree t, char * x)
{
    if (t != NULL) {
        avl_search_sin(t->esq, x);
        if(strcmp(t->dado.sinonimo, x) == 0) printf("%s ", t->dado.palavra);
        avl_search_sin(t->dir, x);
    }
}

void avl_save(avl_tree t, char * filename)
{
    FILE * arq;
    char op;

    do {
        printf("\n> Deseja salvar as alterações? (s/n) ");
        scanf(" %c", &op);
    } while (tolower(op) != 'n' && tolower(op) != 's');

    if (op == 's') {
        do { 
            printf("> Salvar as palavras e os sinônimos em %s? (s/n) ", filename);
            scanf(" %c", &op);
        } while (tolower(op) != 'n' && tolower(op) == 's');

        if (tolower(op) == 'n') {
            printf("> Novo nome do arquivo para salvar com a extensão (.txt): ");
            scanf(" %60[^\n]", filename);
        }
        
        if ((arq = fopen(filename, "w")) == NULL) {
            fprintf(stderr, "Erro na abertura do arquivo arq.txt\n");
            return;
        }

        avl_file_save(t, arq);
        fclose(arq);
    }
}

void avl_file_save(avl_tree t, FILE * arq)
{
    if (t != NULL) {
        avl_file_save(t->esq, arq);
            fprintf(arq, "%s %s\n", t->dado.palavra, t->dado.sinonimo);
        avl_file_save(t->dir, arq);
    }
}