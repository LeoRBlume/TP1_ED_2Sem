#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "dicionario.h"

#define MAX_LEN 63

int main() {
    setlocale(LC_ALL, ". UTF8") ;

    avl_tree t = NULL; // Ponteiro para a raiz da árvore
    FILE * arq; // Arquivo lógico
    char str1[31];
    char str2[31];
    char linha[MAX_LEN];
    char palavra[31];
    char * resp;
    int op = 0;
    bool h;

    if ((arq = fopen("arq.txt", "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo arq.txt\n");
        return 1;
    }

    fscanf(arq, "%[^' '|\t] %[^' '|\t|\n]", str1, str2);
    avl_search(&t, str1, str2, &h);

    while (fgets(linha, MAX_LEN, arq) != NULL) { 
        fscanf(arq, "%[^' '|\t] %[^' '|\t|\n]", str1, str2);
        avl_search(&t, str1, str2, &h);
    }

    fclose(arq);
    
    do{
        printf("\n-------Menu de Operações do dicionario-------\n\n");
        printf("[1] Procurar pelo sinônimo de uma palavra\n");
        printf("[2] Substituir o sinonimo de uma palavra por outro\n");
        printf("[3] Excluir uma palavra (e seu sinônimo)\n");
        printf("[0] Sair\n");
        printf("\nOpção: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("Informe o sinonimo: ");
                scanf(" %30[^\n]", palavra);
                printf("Palavras com sinonimos: ");
                searchSin(t, palavra);
            break;

            case 2:
                printf("Informe a palavra que deseja substituir o sinonimo: ");
                scanf(" %30[^\n]", str1);

                printf("Informe o novo sinonimo da palavra: ");
                scanf(" %30[^\n]", str2);

                printf("%s %s", str1, str2);

                findSin(t, str1, str2);
            break;

            case 3:

                printf("Informe uma palavra para excluir: ");
                scanf(" %30[^\n]", str1);
                if(delete(&t, str1, &h)) printf("Deletado com sucesso");
                else printf("Não deletado");
            break;
        }   
    }
    while (op != 0);
    close(t);
    return 0;
}
