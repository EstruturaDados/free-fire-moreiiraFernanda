#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ---------------------------------------------------------------------
// Definição da struct Item
// ---------------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------------------------------------------------------------
// Função auxiliar para limpar o buffer de entrada (stdin)
// ---------------------------------------------------------------------
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------------------------------------------------------------------
// Protótipos das funções obrigatórias
// ---------------------------------------------------------------------
void inserirItem(Item itens[], int *numItens);
void removerItem(Item itens[], int *numItens);
void listarItens(Item itens[], int numItens);
int  buscarItem(Item itens[], int numItens, const char *nomeBusca);

// ---------------------------------------------------------------------
// Função principal
// ---------------------------------------------------------------------
int main() {
    Item itens[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n================= MOCHILA DO JOGADOR =================\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
        case 1:
            inserirItem(itens, &numItens);
            listarItens(itens, numItens);
            break;
        case 2:
            removerItem(itens, &numItens);
            listarItens(itens, numItens);
            break;
        case 3: {
            char nomeBusca[30];
            printf("Digite o nome do item a ser buscado: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int indice = buscarItem(itens, numItens, nomeBusca);
            if (indice != -1) {
                printf("\nItem encontrado:\n");
                printf("Nome: %s\n", itens[indice].nome);
                printf("Tipo: %s\n", itens[indice].tipo);
                printf("Quantidade: %d\n", itens[indice].quantidade);
            } else {
                printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
            }
            listarItens(itens, numItens);
            break;
        }
        case 4:
            listarItens(itens, numItens);
            break;
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ---------------------------------------------------------------------
// inserirItem
// ---------------------------------------------------------------------
void inserirItem(Item itens[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel cadastrar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n=== Cadastro de novo item ===\n");
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("Quantidade invalida. Operacao cancelada.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    itens[*numItens] = novoItem;
    (*numItens)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// ---------------------------------------------------------------------
// removerItem
// ---------------------------------------------------------------------
void removerItem(Item itens[], int *numItens) {
    if (*numItens == 0) {
        printf("\nNao ha itens na mochila para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int indice = buscarItem(itens, *numItens, nomeRemover);
    if (indice == -1) {
        printf("\nItem '%s' nao encontrado. Nenhuma remocao realizada.\n", nomeRemover);
        return;
    }

    for (int i = indice; i < *numItens - 1; i++) {
        itens[i] = itens[i + 1];
    }
    (*numItens)--;

    printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
}

// ---------------------------------------------------------------------
// listarItens
// ---------------------------------------------------------------------
void listarItens(Item itens[], int numItens) {
    printf("\n================= ITENS NA MOCHILA =================\n");

    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < numItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome      : %s\n", itens[i].nome);
        printf("  Tipo      : %s\n", itens[i].tipo);
        printf("  Quantidade: %d\n", itens[i].quantidade);
    }
}

// ---------------------------------------------------------------------
// buscarItem
// ---------------------------------------------------------------------
int buscarItem(Item itens[], int numItens, const char *nomeBusca) {
    for (int i = 0; i < numItens; i++) {
        if (strcmp(itens[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}
