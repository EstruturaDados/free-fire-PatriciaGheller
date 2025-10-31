#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Inserir item
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= 10) {
        printf("\n Mochila cheia! Remova um item para adicionar outro.\n");
        return;
    }

    Item novo;
    getchar();
    printf("\n-> Adicionar Novo Item\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*contador] = novo;
    (*contador)++;

    printf("\n Item '%s' adicionado com sucesso!\n", novo.nome);
}

// Remover item
void removerItem(Item mochila[], int *contador) {
    char nome[30];
    getchar();
    printf("\n-> Remover Item\n");
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*contador)--;
            printf("\n Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    printf("\n Item '%s' não encontrado na mochila.\n", nome);
}

// Listar itens
void listarItens(Item mochila[], int contador) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", contador);
    printf("| %-12s | %-10s | %-9s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("| %-12s | %-10s | %-9d |\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("---------------------------------------------\n");
}

// Ordenar mochila por nome
void ordenarMochila(Item mochila[], int contador) {
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                Item temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
}

// Busca sequencial
int buscarSequencial(Item mochila[], int contador, char nome[], int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < contador; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Busca binária
int buscarBinaria(Item mochila[], int contador, char nome[], int *comparacoes) {
    int inicio = 0, fim = contador - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

// Buscar item por nome
void buscarItem(Item mochila[], int contador) {
    char nome[30];
    int comparacoesSeq, comparacoesBin;
    getchar();
    printf("\n-> Buscar Item\n");
    printf("Nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int posSeq = buscarSequencial(mochila, contador, nome, &comparacoesSeq);
    ordenarMochila(mochila, contador);
    int posBin = buscarBinaria(mochila, contador, nome, &comparacoesBin);

    if (posSeq != -1) {
        printf("\n🔍 Item encontrado:\n");
        printf("Nome: %s\n", mochila[posSeq].nome);
        printf("Tipo: %s\n", mochila[posSeq].tipo);
        printf("Quantidade: %d\n", mochila[posSeq].quantidade);
    } else {
        printf("\n Item '%s' não encontrado na mochila.\n", nome);
    }

    printf("\n Comparações realizadas:\n");
    printf("Sequencial: %d\n", comparacoesSeq);
    printf("Binária (após ordenação): %d\n", comparacoesBin);
}

// Função principal
int main() {
    Item mochila[10];
    int contador = 0;
    int opcao;

    do {
        printf("\nMOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
        printf("Itens na Mochila: %d/10\n", contador);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("5. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &contador); break;
            case 2: removerItem(mochila, &contador); break;
            case 3: listarItens(mochila, contador); break;
            case 4: buscarItem(mochila, contador); break;
            case 5: printf("\n Saindo do sistema. Boa sorte na ilha!\n"); break;
            default: printf("\n Opção inválida. Tente novamente.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); getchar(); // pausa para leitura
        system("clear"); // use "cls" no Windows

    } while (opcao != 5);

    return 0;
}
