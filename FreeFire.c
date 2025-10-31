#include <stdio.h>      // Entrada e saída padrão
#include <stdlib.h>     // Funções utilitárias como atoi()
#include <string.h>     // Manipulação de strings
#include <time.h>       // Medição de tempo de execução

#define MAX_COMPONENTES 10  // Limite máximo de componentes na mochila

// Estrutura que representa um componente
typedef struct {
    char nome[30];         // Nome do componente
    char tipo[20];         // Tipo do componente
    int quantidade;        // Quantidade disponível
    int prioridade;        // Prioridade de montagem (1 a 10)
} Componente;

// Exibe os componentes em formato de tabela
void mostrarComponentes(Componente lista[], int total) {
    printf("\nINVENTARIO ATUAL (%d/%d)\n", total, MAX_COMPONENTES);
    printf("| %-13s | %-12s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("|---------------|--------------|------------|------------|\n");
    for (int i = 0; i < total; i++) {
        printf("| %-13s | %-12s | %-10d | %-10d |\n",
               lista[i].nome, lista[i].tipo, lista[i].quantidade, lista[i].prioridade);
    }
    printf("|---------------|--------------|------------|------------|\n");
}

// Ordena os componentes por nome (ordem alfabética)
int bubbleSortNome(Componente lista[], int total) {
    int comparacoes = 0;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Componente temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Ordena os componentes por tipo
int insertionSortTipo(Componente lista[], int total) {
    int comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
            comparacoes++;
        }
        lista[j + 1] = chave;
        comparacoes++;
    }
    return comparacoes;
}

// Ordena os componentes por prioridade
int selectionSortPrioridade(Componente lista[], int total) {
    int comparacoes = 0;
    for (int i = 0; i < total - 1; i++) {
        int min = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
    return comparacoes;
}

// Busca binária por nome (requer lista ordenada por nome)
int buscaBinariaPorNome(Componente lista[], int total, char chave[], int *comparacoes) {
    int inicio = 0, fim = total - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(lista[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Função principal
int main() {
    Componente mochila[MAX_COMPONENTES];
    int total = 0;
    int ordenadoPorNome = 0;
    int opcao;
    char entrada[10]; // Usada para capturar quantidade e prioridade

    do {
        // Menu principal
        printf("\nPLANO DE FUGA - CÓDIGO DA ILHA (NÍVEL MESTRE)\n");
        printf("Itens na Mochila: %d/%d\n", total, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("\n1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Buscar Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                // Adiciona um novo componente
                if (total >= MAX_COMPONENTES) {
                    printf(" Mochila cheia! Remova um componente para adicionar outro.\n");
                    break;
                }

                printf("\n-> Adicionar Componente\n");
                printf("Nome: ");
                fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                printf("Quantidade: ");
                fgets(entrada, sizeof(entrada), stdin);
                mochila[total].quantidade = atoi(entrada);

                printf("Prioridade (1 a 10): ");
                fgets(entrada, sizeof(entrada), stdin);
                mochila[total].prioridade = atoi(entrada);

                total++;
                ordenadoPorNome = 0;
                printf(" Componente adicionado com sucesso!\n");
                break;

            case 2: {
                // Remove um componente pelo nome
                char nome[30];
                printf("\n-> Descartar Componente\n");
                printf("Nome do componente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nome) == 0) {
                        for (int j = i; j < total - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        total--;
                        encontrado = 1;
                        printf(" Componente '%s' descartado.\n", nome);
                        break;
                    }
                }
                if (!encontrado)
                    printf(" Componente não encontrado.\n");
                break;
            }

            case 3:
                // Exibe os componentes
                mostrarComponentes(mochila, total);
                break;

            case 4: {
                // Ordena os componentes
                int criterio;
                printf("\n--- Estrategia de Organizacao ---\n");
                printf("Como deseja ordenar os componentes?\n");
                printf("1. Por Nome (Ordem Alfabética)\n");
                printf("2. Por Tipo\n");
                printf("3. Por Prioridade de Montagem\n");
                printf("0. Cancelar\n");
                printf("Escolha o criterio: ");
                scanf("%d", &criterio);
                getchar();

                clock_t inicio, fim;
                int comparacoes = 0;

                switch (criterio) {
                    case 1:
                        inicio = clock();
                        comparacoes = bubbleSortNome(mochila, total);
                        fim = clock();
                        ordenadoPorNome = 1;
                        break;
                    case 2:
                        inicio = clock();
                        comparacoes = insertionSortTipo(mochila, total);
                        fim = clock();
                        ordenadoPorNome = 0;
                        break;
                    case 3:
                        inicio = clock();
                        comparacoes = selectionSortPrioridade(mochila, total);
                        fim = clock();
                        ordenadoPorNome = 0;
                        break;
                    case 0:
                        printf("Ordenação cancelada.\n");
                        continue;
                    default:
                        printf(" Criterio inválido.\n");
                        continue;
                }

                double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                printf("\nMochila organizada com sucesso.\n");
                printf("Análise de Desempenho: Foram necessárias %d comparacoes.\n", comparacoes);
                printf("Tempo de execução: %.6f segundos.\n", tempo);
                mostrarComponentes(mochila, total);
                break;
            }

            case 5: {
                // Busca binária por nome
                if (!ordenadoPorNome) {
                    printf("\n ALERTA: A busca binária requer que a mochila esteja ordenada por NOME.\nUse a opção 4 para ordenar a mochila primeiro.\n");
                    break;
                }

                char chave[30];
                int comparacoes;
                printf("\n-> Buscar Componente por Nome\n");
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                int pos = buscaBinariaPorNome(mochila, total, chave, &comparacoes);
                if (pos != -1) {
                    printf("\n Componente-chave encontrado!\n");
                    printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo,
                           mochila[pos].quantidade, mochila[pos].prioridade);
                } else {
                    printf("\n Componente-chave '%s' não encontrado.\n", chave);
                }
                printf("Comparações realizadas: %d\n", comparacoes);
                break;
            }

            case 0:
                // Encerra o programa
                printf("\n TORRE DE FUGA ATIVADA! Você escapou da ilha com sucesso!\n");
                break;

            default:
                // Trata opções inválidas
                printf("\n Opção inválida. Tente novamente.\n");
        }

        // Pausa antes de limpar a tela
        printf("\nPressione Enter para continuar...");
        getchar(); // espera o Enter
        system("clear"); // use "cls" no Windows

    } while (opcao != 0); // repete até o usuário escolher sair

    return 0; // encerra o programa
}
