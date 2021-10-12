#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "dicionario.h"

int main() {
    setlocale(LC_ALL, ". UTF8") ;

    avl_tree t = NULL;
    char palavra[31];
    char filename[61];
    char str1[31];
    char str2[31];
    int op = 0;
    bool h;

    printf("Digite o nome do arquivo que possue as palavras com a extensão (.txt): ");
    scanf(" %60[^\n]", filename);

    avl_init(&t, filename);
    
    do{
        printf("\n============ Menu de Operações do dicionario =========\n");
        printf("[1] Exibir todas palavras e sinônimos\n");
        printf("[2] Procurar pelo sinônimo de uma palavra\n");
        printf("[3] Substituir o sinonimo de uma palavra por outro\n");
        printf("[4] Excluir uma palavra (e seu sinônimo)\n");
        printf("[0] Sair e salvar\n");
        printf("\nOpção: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("\n======================================================\n");
                printf("Palavra                        Sinônimo\n");
                printf("======================================================\n");
                avl_print(t);
                printf("======================================================\n");
                break;

            case 2:
                printf("\n> Informe o sinonimo: ");
                scanf(" %30[^\n]", palavra);
                printf("Palavras com sinonimos: ");
                avl_search_sin(t, palavra);
                printf("\n");
            break;

            case 3:
                printf("\n> Informe a palavra que deseja substituir o sinonimo: ");
                scanf(" %30[^\n]", str1);

                printf("> Informe o novo sinonimo da palavra: ");
                scanf(" %30[^\n]", str2);

                avl_find_sin(t, str1, str2);
                printf("\n");
            break;

            case 4:
                printf("\n> Informe uma palavra para excluir: ");
                scanf(" %30[^\n]", str1);

                if(avl_delete(&t, str1, &h))
                    printf("Deletado com sucesso");
                else
                    printf("Não deletado");
                printf("\n");
            break;
        }   
    }
    while (op != 0);

    avl_save(t, filename);
    return 0;
}
