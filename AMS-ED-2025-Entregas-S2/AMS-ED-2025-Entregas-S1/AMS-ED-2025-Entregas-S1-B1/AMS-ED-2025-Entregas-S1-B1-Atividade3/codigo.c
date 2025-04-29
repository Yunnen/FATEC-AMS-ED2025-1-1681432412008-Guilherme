/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-Atividade 3                      */
/*             Objetivo: Usar ListaLigada para modificar,excluir,incluir            */
/*                                                                                  */
/*                                  Autor: Guilherme Gallo Migliorini               */
/*                                                                   Data:24/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pedido {
    int numPedido;
    char cliente[50];
    char descricao[100];
    int quantidade;
    int status;
    struct Pedido *prox;
};

const char *status[] = {
    "Pendente",   // 0
    "Em preparo", // 1
    "Pronto",     // 2
    "Entregue"    // 3
};

//Número dos Pedidos Totais
int numPedidoGlobal = 0;  


struct Pedido* visualizar(struct Pedido **pedidos) {
    
    //Verifica Antes de A lista de Pedidos não está vazia
    if (*pedidos == NULL) {
        printf("\nDetectamos que a Lista está vazia!\n");
        return NULL;
    }

    int numeroPedido;
    struct Pedido *cPedidos = *pedidos;
    
    
    //Pede o número do Pedido e Verifica se o Usuario Colocou um numero valido
    printf("Insira o Número do Pedido:\n");
    do {
        if (scanf("%d", &numeroPedido) != 1) {
            printf("Entrada inválida! Digite um número válido.\n");
            while (getchar() != '\n'); // Limpa buffer
        } else if (numeroPedido < 1) {
            printf("Número inválido! Deve ser pelo menos 1.\n");
        }
    } while (numeroPedido < 1);

    //Percorre a lista procurando o Pedido e dps devolve um ponteiro dele
    while (cPedidos != NULL) {
        if (cPedidos->numPedido == numeroPedido) {
            return cPedidos; // Retorna o pedido encontrado
        }
        cPedidos = cPedidos->prox;
    }
    
    //Retorno caso o pedido não seja encotrado
    printf("\n[ERRO] Não encontramos nenhum pedido com esse número!\n");
    return NULL;
}



void alterarStatus(struct Pedido **pedidos) {
    
    //Verifica se a Lista não está vazia
    if (*pedidos == NULL) {
        printf("\nA lista de pedidos está vazia!\n");
        return;
    }
    
    //Cria variavies uma de Anterior e uma do Pedido
    struct Pedido *anterior = NULL;
    
    //Chama a funçao já pronta pois ela já retorna o pedido
    struct Pedido *pedido = visualizar(pedidos);

    //Verifica se o pedido existe
    if (pedido == NULL) {
        printf("Operação cancelada! Pedido não encontrado.\n");
        return;
    }
    
    //Usa o array de Status para mostrar as opções de status
    printf("\nEscolha o novo status do pedido:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d - %s\n", i, status[i]);
    }
    
    
    //Filtro contra erros de digitação do Usuario
    int novoStatus;
    do {
        printf("Digite o número correspondente ao novo status: ");
        if (scanf("%d", &novoStatus) != 1 || novoStatus < 0 || novoStatus > 3) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa buffer
        } else {
            break;
        }
    } while (1);

    pedido->status = novoStatus;
    printf("Status do pedido atualizado para: %s\n", status[novoStatus]);

    // Se o pedido foi concluído (Entregue), removê-lo da lista
    if (novoStatus == 3) {
        struct Pedido *atual = *pedidos;

        // Se o pedido a ser removido é o primeiro da lista
        if (atual == pedido) {
            *pedidos = atual->prox;
        } else {
            // Percorre a lista para encontrar o pedido anterior
            while (atual != NULL && atual != pedido) {
                anterior = atual;
                atual = atual->prox;
            }
            if (anterior != NULL) {
                anterior->prox = pedido->prox;
            }
        }
        
        //Depois de Retirar o Pedido ele libera a memoria do Pedido
        free(pedido);
        printf("O pedido foi entregue e removido da lista!\n");
    }
}

void cadastro(struct Pedido **pedidos) {
    struct Pedido *novoPedido = (struct Pedido*)malloc(sizeof(struct Pedido));
    
    //Verifica se existe espaço para alocação de memoria
    if (novoPedido == NULL) {
        printf("[DEBUG] Erro ao alocar memória!\n");
        return;
    }
    
    //Aumenta o Numero do pedido
    numPedidoGlobal++;
    novoPedido->numPedido = numPedidoGlobal;
    novoPedido->status = 0; // Pedido começa como "Pendente"


    //Coletando Informações e aplicando filtros contra erros se necessario!
    getchar(); // Limpa buffer
    printf("\nNome do Cliente:\n");
    fgets(novoPedido->cliente, 50, stdin);
    novoPedido->cliente[strcspn(novoPedido->cliente, "\n")] = 0;

    printf("\nDescrição do Prato:\n");
    fgets(novoPedido->descricao, 100, stdin);
    novoPedido->descricao[strcspn(novoPedido->descricao, "\n")] = 0;

    do {
        printf("\nQuantos Pratos?:\n");
        if (scanf("%d", &novoPedido->quantidade) != 1) {
            printf("Entrada inválida! Digite um número válido.\n");
            while (getchar() != '\n'); // Limpa buffer
        }
    } while (novoPedido->quantidade < 1);

    novoPedido->prox = *pedidos;
    *pedidos = novoPedido;
    
    
    //Retorno do Status de Sistema
    printf("\nPedido cadastrado com sucesso!\n");
}

int main() {
    
    //Inicializa a Lista Pedido vazia
    struct Pedido *pedidos = NULL;
    
    printf("Olá, seja bem-vindo(a) ao nosso Sistema de Gerenciamento de Pedidos (っ◔◡◔)っ ❤\n");

    int con = 1;
    
    while (con != 0) {
        printf("\nO que você deseja fazer?\n");
        printf("1 - Cadastrar um pedido novo\n");
        printf("2 - Visualizar um Pedido\n");
        printf("3 - Modificar o Status de um Pedido\n");
        printf("0 - Encerrar o Programa\n\n");
        scanf("%d", &con);
    
        switch (con) {
            case 1:
                printf("Você selecionou: 1 - Cadastrar um pedido novo!\n");
                cadastro(&pedidos);
                break;
            case 2:
                printf("Você selecionou: 2 - Visualizar um Pedido!\n");
                struct Pedido *cPedidos = visualizar(&pedidos);
                
                if (cPedidos) { // Verifica se o pedido foi encontrado
                    printf("\n===== Pedido Encontrado =====\n");
                    printf("Número do Pedido: %d\n", cPedidos->numPedido);
                    printf("Cliente: %s\n", cPedidos->cliente);
                    printf("Descrição: %s\n", cPedidos->descricao);
                    printf("Quantidade: %d\n", cPedidos->quantidade);
                    printf("Status: %s\n", status[cPedidos->status]);
                    printf("=============================\n");
                }
                break;
            case 3:
                printf("Você selecionou: 3 - Modificar o Status de um Pedido!\n");
                alterarStatus(&pedidos);
                break;
            case 0:
                printf("Encerrando o Programa!\n");
                break;
            default:
                printf("Opção inválida! Escolha uma opção entre 0 e 3.\n");
                break;
        }
    }
    free(con);
    free(pedidos);
    return 0;
}
