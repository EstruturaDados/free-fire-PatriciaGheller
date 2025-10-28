#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item com nome, tipo e quantidade
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= 10) {
        printf(" Mochila cheia! Remova um item para adicionar outro.\n");
        return;
    }

    Item novo;
    getchar(); // Limpa o buffer antes de usar fgets

    printf("\n-> Adicionar Novo Item\n");

    // Captura nome com espaços
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n do final

    // Captura tipo com espaços
    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0'; // Remove o \n do final

    // Captura quantidade
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    // Adiciona item à mochila
    mochila[*contador] = novo;
    (*contador)++;

    printf("\n Item '%s' adicionado com sucesso!\n", novo.nome);
}

// Função para remover um item da mochila pelo nome
void removerItem(Item mochila[], int *contador) {
    char nome[30];
    getchar(); // Limpa o buffer antes de usar fgets

    printf("\n-> Remover Item\n");
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o \n

    // Busca e remove o item
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j + 1]; // Desloca os itens
            }
            (*contador)--;
            printf("\n🗑 Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    printf("\n Item '%s' não encontrado na mochila.\n", nome);
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int contador) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", contador);
    printf("| %-12s | %-10s | %-9s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("| %-12s | %-10s | %-9d |\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("---------------------------------------------\n");
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int contador) {
    char nome[30];
    getchar(); // Limpa o buffer antes de usar fgets

    printf("\n-> Buscar Item\n");
    printf("Nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o \n

    // Busca o item
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n Item encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("\n Item '%s' não encontrado.\n", nome);
}

// Função principal com menu interativo
int main() {
    Item mochila[10];     // Vetor que representa a mochila
    int contador = 0;     // Número atual de itens na mochila
    int opcao;            // Opção escolhida pelo jogador

    do {
        // Exibe o menu principal
        printf("\nMOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
        printf("Itens na Mochila: %d/10\n", contador);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a ação correspondente
        switch (opcao) {
            case 1: inserirItem(mochila, &contador); break;
            case 2: removerItem(mochila, &contador); break;
            case 3: listarItens(mochila, contador); break;
            case 4: buscarItem(mochila, contador); break;
            case 0: printf("\n Saindo do sistema. Boa sorte na ilha!\n"); break;
            default: printf("\n Opção inválida. Tente novamente.\n");
        }

        // Pausa para leitura e limpeza da tela
        printf("\nPressione Enter para continuar...");
        getchar(); getchar(); // Espera o Enter
        system("clear"); // Use "cls" se estiver no Windows

    } while (opcao != 0); // Continua até o jogador escolher sair

    return 0;
}