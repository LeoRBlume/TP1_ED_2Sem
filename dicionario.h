/**
 * Bruno Luis - 5142934 - SI
 * Igor Amon - 1612804 - SI
 * Leonardo Blume - ??????? - SI
 * Gustavo Medeiros - ??????? - ??
 */

#ifndef __DICIONARIO_H
#define __DICIONARIO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

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

/**
 * Inicia a árvore AVL com as palavras e os sinônimos do
 * arquivo especificado
 */
void avl_init(avl_tree * t, char * filename);

/**
 * Imprime a árvore AVL t através de um percurso em ordem.
 */
void avl_print(avl_tree t);

/**
 * Verifica se a palavra x já ocorreu na árvore AVL t; 
 * caso afirmativo, seu contador é incrementado; caso contrário, 
 * x é inserida em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, char * x, char * y, bool * h);

/**
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void avl_rotacao_esq(avl_tree * t);

/**
 * Faz uma rotação para a direita na árvore AVL t. 
 */
void avl_rotacao_dir(avl_tree * t);

/**
 * Se a palavra x está contida na árvore AVL t, x é
 * removida de t, h sinaliza uma diminuição da altura
 * de t e a função devolve verdadeiro; caso contrário,
 * nada é feito e a função devolve falso.
 */
bool avl_delete(avl_tree * t, char * x, bool * h);

/**
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore esquerda e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void avl_balance_esq(avl_tree * t, bool * h);

/**
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore direita e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void avl_balance_dir(avl_tree * t, bool * h);

/**
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se 
 * houve uma diminuição da altura de t.
 */
avl_tree avl_get_min(avl_tree * t, bool * h);

/**
 * Devolve a profundidade da árvore AVL apontada por t.
 */
int avl_profundidade(avl_tree t);

/** 
 * Verifica o sinônimo y da palavra x indicada na
 * árvore AVL t
 */
void avl_find_sin(avl_tree t, char * x, char * y);

/**
 * Procura a palavra na árvore AVL t pelo sinônimo x
*/
void avl_search_sin(avl_tree t, char * x);

/**
 * Inicia o processo de salvar a árvore AVL t
 * no arquivo indicado pelo filename, ou por outro
 * que o usuário digitar
 */
void avl_save(avl_tree t, char * filename);

/**
 * Percorre a árvore AVL t para salvar os dados no arquvio
 * de nome indicado pelo filename
 */
void avl_file_save(avl_tree t, FILE* arq);

#endif
