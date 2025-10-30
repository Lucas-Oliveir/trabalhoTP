#include<stdio.h>
#include "corzinha.h"
#include <windows.h>
#include <stdlib.h>
#include "loja.h"



loja loj;

int main()
{
    system("chcp 65001 >nul");
    system("cls");
    int n=1;
    loj.quant=0;
    loj.vetsize=0;
    while(n!=0)
    {
        system("CLS");
        printf(GREEN"+=====================================================================+\n");
        printf("|"RED "  S U P E R M E R C A D O     G I R O"GREEN"                                |\n");
        printf("+=====================================================================+\n"RESET);
        printf(BLUE"==== Menu Principal ====\n\n"RESET);
        printf(YELLOW"Digite o número da ação desejada:\n"RESET);
        printf(RED"1. Cadastrar produto\n");
        printf("2. Editar produto\n");
        printf("3. Excluir produto\n");
        printf("4. Listar todos os produtos\n");
        printf("5. Listar produtos disponíveis\n");
        printf("6. Consultar produto\n");
        print(RED"\n\nNúmero da ação desejada: "RESET);
        scanf("%d",&n);
        escolha(n,&loj);
    }

    printf(CLEAR);
    print(GREEN"\n=====================================\n"
        "Obrigado por usar nosso programa!\n" 
        "Até a próxima execução :)\n"
        "=====================================\n"RESET);

    system("pause");
    return 0;

}