#include "corzinha.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void print(const char* s) {
    if (*s == '\0') return;
    char* sexo = NULL;
    int len = 0;
    
    const char* i = s;
    while (*i != '\0') {
        // realoca espaço (+2 = caractere novo + terminador)
        char* tmp = realloc(sexo, len + 2);
        if (!tmp) {
            free(sexo);
            perror("realloc");
            return;
        }
        sexo = tmp;

        sexo[len++] = *i++;
        sexo[len] = '\0';

        printf("%c", sexo[len - 1]);
        fflush(stdout);
        Sleep(40);
    }
    free(sexo);
}

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} prod;

typedef struct {
    int quant;
    int vetsize;
    prod * produtos;
} loja;

void vetmanager(loja * loj)
{
    if(loj->vetsize==0)
    {
        loj->produtos=(prod*)calloc(10,sizeof(prod));
        loj->vetsize=10;
        loj->produtos[0].id=1e9;
        return;
    }

    if(loj->quant>=loj->vetsize)
    {
        loj->produtos=(prod*)realloc(loj->produtos,sizeof(prod)*(loj->vetsize+5));
        loj->vetsize+=5;
    }
}

int busca(loja * loj,int x)
{
    int l=0,r=loj->quant-1;

    while(l<r)
    {
        int mid=(r+l)/2;

        if(x<=loj->produtos[mid].id)
        {
            r=mid;
        }
        else l=mid+1;
    }

    if(loj->produtos[l].id==x) return l;
    return -1;
} 

void cadastrarProduto(loja* loj) {
    system("CLS");
    printf(GREEN"+=====================================================================+\n");
    printf("|"RED "  S U P E R M E R C A D O     G I R O"GREEN"                                |\n");
    printf("+=====================================================================+\n"RESET);
    printf(BLUE"==== Tela de Cadastro ====\n\n"RESET);

    inicio:

    loj->quant+=1;
    vetmanager(loj);
    prod aux;
    getchar();
    printf(RED"Digite o nome do Produto: " RESET);
    scanf("%[^\n]",aux.nome);
    printf(RED"Digite o ID do produto: "RESET);
    scanf("%d",&aux.id);
    printf(RED"Digite o preço do produto: R$ "RESET);
    scanf("%f",&aux.preco);
    printf(RED"Digite a quantidade do produto: "RESET);
    scanf("%d",&aux.quantidade);

    int j=loj->quant-1;

    while(j>=0 && loj->produtos[j].id>aux.id)
    {
        loj->produtos[j+1]=loj->produtos[j];
        j--;
    }

    loj->produtos[j+1]=aux;
    printf(GREEN"Produto Cadastrado Com Sucesso!\n"RESET);
    char opc;
    printf(YELLOW"Deseja cadastrar outro produto? (s/n): "RESET);
    scanf(" %c", &opc);
    if (opc == 's' || opc == 'S') goto inicio;

}


void listarProdutos(loja *loj, int e) {
    system("CLS");
    printf(GREEN"+=====================================================================+\n");
    printf("|"RED "  S U P E R M E R C A D O     G I R O"GREEN"                                |\n");
    printf("+=====================================================================+\n"RESET);
    printf(BLUE"==== Lista de Produtos ====\n\n"RESET);

    for(int i=0;i<loj->quant;i++)
    {
        if(e>loj->produtos[i].quantidade) continue;
        printf(YELLOW"Nome do Produto:"RESET" %s\n",loj->produtos[i].nome);
        printf(YELLOW"ID do produto:"RESET" %d\n",loj->produtos[i].id);
        printf(YELLOW"Preço do Produto:"RESET" %.2f\n",loj->produtos[i].preco);
        printf(YELLOW"Quantidade disponível do Produto:"RESET" %d\n\n",loj->produtos[i].quantidade);

        if(i!=loj->quant-1) printf(BLUE"+==============================================+\n\n"RESET);
    }

    printf(RED"Para voltar ao Menu Principal Pressione [ENTER]\n"RESET);
    system("PAUSE");

}

void consultarProduto(loja* loj)
{
    system("CLS");
    printf(GREEN"+=====================================================================+\n");
    printf("|"RED "  S U P E R M E R C A D O     G I R O"GREEN"                                |\n");
    printf("+=====================================================================+\n"RESET);
    printf(BLUE"==== Tela de Consulta ====\n\n"RESET);

    inicio:

    int id;
    printf("Digite o ID para a consulta: ");
    scanf("%d",&id);
    int busc=busca(loj,id);

    if(busc==-1)
    {
        printf(RED"\nNão existe nenhum produto com este ID cadastrado!!\n"RESET);
    }
    else
    {

        printf(YELLOW"Nome do Produto:"RESET" %s\n",loj->produtos[busc].nome);
        printf(YELLOW"ID do produto:"RESET" %d\n",loj->produtos[busc].id);
        printf(YELLOW"Preço do Produto:"RESET" %.2f\n",loj->produtos[busc].preco);
        printf(YELLOW"Quantida disponível do Produto:"RESET" %d\n\n",loj->produtos[busc].quantidade);
    }
    printf(BLUE"+==============================================+\n\n"RESET);
    char opc;
    printf(YELLOW"Deseja fazer outra consulta? (s/n): "RESET);
    scanf(" %c", &opc);
    if (opc == 's' || opc == 'S') goto inicio;

}

void excluirProduto(loja *loj) {
    system("CLS");
    printf(GREEN"+=====================================================================+\n");
    printf("|"RED "  S U P E R M E R C A D O     G I R O"GREEN"                                |\n");
    printf("+=====================================================================+\n"RESET);
    printf(BLUE"==== Tela de Remoção ====\n\n"RESET);

    inicio:
    int id;

    printf(RED"Digite o ID do produto a ser excluído: "RESET);
    scanf("%d",&id);

    int ind = busca(loj,id);

    if(ind == -1)
    {
        printf(RED"\nNão existe nenhum produto com este ID cadastrado!!\n"RESET);
        goto escolha;
    }
    loj->produtos[ind].id=INT_MAX;
    while(ind<loj->quant-1)
    {
        loj->produtos[ind]=loj->produtos[ind+1];
        ind++;
    }
    loj->quant--;

    printf(GREEN"Produto excluído com Sucesso!\n"RESET);

    escolha:
    char opc;
    printf(YELLOW"Deseja excluir outro produto? (s/n): "RESET);
    scanf(" %c", &opc);
    if (opc == 's' || opc == 'S') goto inicio;
}

void gotoxy(COORD pos)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void editarProduto(loja *loj) {
    int continuar = 1;

    while (continuar) {
        system("CLS");
        printf(GREEN "+=====================================================================+\n");
        printf("|" RED "  S U P E R M E R C A D O     G I R O" GREEN "                                |\n");
        printf("+=====================================================================+\n" RESET);
        printf(BLUE "==== Tela de Edição ====\n\n" RESET);

        int ID;
        printf(RED "Digite o ID do produto a ser editado: " RESET);
        scanf("%d", &ID);
        getchar(); // limpa o '\n' deixado pelo scanf

        int busc = busca(loj, ID);
        if (busc == -1) {
            printf(RED "\nNão existe nenhum produto com este ID cadastrado!!\n" RESET);
        } else {
            prod *p = &loj->produtos[busc];
            printf(RED "\nVocê está editando o produto de ID %d!\n\n" RESET, ID);

            char buffer[100];

            // Nome
            printf(YELLOW "Nome do Produto [%s]: " RESET, p->nome);
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0; // remove \n
                strcpy(p->nome, buffer);
            }

            // Preço
            printf(YELLOW "Preço do Produto [%.2f]: " RESET, p->preco);
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                p->preco = atof(buffer);
            }

            // Quantidade
            printf(YELLOW "Quantidade disponível do Produto [%d]: " RESET, p->quantidade);
            fgets(buffer, sizeof(buffer), stdin);
            if (buffer[0] != '\n') {
                p->quantidade = atoi(buffer);
            }

            printf(GREEN "\nProduto editado com sucesso!\n\n" RESET);
        }

        char opc;
        printf(YELLOW "Deseja editar outro produto? (s/n): " RESET);
        scanf(" %c", &opc);
        getchar(); // limpa o '\n'
        if (opc != 's' && opc != 'S') {
            continuar = 0;
        }
    }
}


void escolha(int x,loja* loj)
{
    switch(x)
    {
        case 1:
            cadastrarProduto(loj);
            break;
        case 2:
            editarProduto(loj);
            break;
        case 3:
            excluirProduto(loj);
            break;
        case 4:
            listarProdutos(loj,0);
            break;
        case 5:
            listarProdutos(loj,1);
            break;
        case 6:
            consultarProduto(loj);
            break;
        case 0:
            break;
        default:
            printf(RED"\nEscolha inválida!"RESET);
            Sleep(100);
            break;
    }

}
