/* avl.h
 * Definição do TAD para representar uma árvore AVL e protótipo
 * de suas operações.
 *
 * Ciro C. Trindade
 * 06/out/2021
 */

#ifndef __CABECALHO_H
#define __CABECALHO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// Definição da estrutura de dados
typedef struct {
    char palavra[31];
    char sinonimo[31];
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/*
 * Imprime a árvore AVL t através de um percurso em ordem.
 */
void print_tree(avl_tree t);


/*
 * Verifica se a palavra x já ocorreu na árvore AVL t; 
 * caso afirmativo, seu contador é incrementado; caso contrário, 
 * x é inserida em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, char * x, char * y, bool * h);


/* 
 * Faz uma rotação para a direita na árvore AVL t. 
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);

/*
 * Se a palavra x está contida na árvore AVL t, x é
 * removida de t, h sinaliza uma diminuição da altura
 * de t e a função devolve verdadeiro; caso contrário,
 * nada é feito e a função devolve falso.
 */
bool delete(avl_tree * t, char * x, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore esquerda e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore direita e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se 
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);

void findSin(avl_tree, char *, char *);

/* Devolve a profundidade da árvore AVL apontada por t. */
int avl_profundidade(avl_tree t);

void searchSin(avl_tree t, char *);

void close(avl_tree);

void saveInArq(avl_tree, FILE*);

#endif
