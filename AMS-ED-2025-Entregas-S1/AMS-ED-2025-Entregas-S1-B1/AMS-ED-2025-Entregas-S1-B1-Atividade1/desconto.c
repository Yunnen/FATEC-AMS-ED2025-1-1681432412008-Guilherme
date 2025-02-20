/*------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados          */
/*                         Guilherme Gallo Migliorini                     */
/*            Objetivo: Aplicar descontos a produtos                      */
/*             Paradigama: - Utilizar Ponteiros para modificar valores    */
/*                                                                        */
/*                                                         Data:19/02/2025*/
/*------------------------------------------------------------------------*/ 
#include <stdio.h>

void aplicarDesconto(double *preco, int *desconto, double *novoPreco) {
    
    //Meu grande filtro contra erros do usuario! (͠≖ ͜ʖ͠≖)👌
    if(*preco <= 0){
        printf("Eita! Parece que você colocou o valor de R$ %.2f (╥﹏╥), um valor negativo...que tal tentar novamente?\n ", *preco);
        scanf("%lf", &*preco);
        aplicarDesconto(preco, desconto, novoPreco);
    }else if(*desconto < 0){
        printf("Eita! Parece que ouve um erro de digitação, você colocou %i%% de desconto??, um valor negativo...desse jeito o valor do produto iria aumentar apenas( ≖.≖), qua tal tentar novamente?\n", *desconto);
        scanf("%i", &*desconto);
        aplicarDesconto(preco, desconto, novoPreco);
    }else if(*desconto > 100){
        printf("Eita! Você inseriu %i%% de desconto, mais de 100%% ?(⊙.⊙)\n", *desconto);
        printf("Desse jeito teríamos que dar o produto de graça e ainda ficaríamos devendo dinheiro ao cliente!(ノ ͡• ⏥ ͡•)ノ\n");
        printf("Que tal tentar novamente?\n");
        scanf("%i", &*desconto); 
        aplicarDesconto(preco, desconto, novoPreco); 
    }else{
    double percentualDesconto = *desconto / 100.0; 
    *novoPreco = *preco - (*preco * percentualDesconto); 
    }
}

int main() {
    
    // Minhas Variaveis
    double preco = 0.0;
    double novoPreco = 0;
    int desconto = 0;

    //Meus Ponteiros
    double *ptrPreco = &preco;
    double *ptrNovoPreco = &novoPreco;
    int *ptrDesconto = &desconto;

    printf("Olá, seja bem-vindo(a) à nossa loja (っ◔◡◔)っ ❤\n");
    printf("Por favor, insira o valor do produto: R$ ");
    scanf("%lf", &preco);
    
    printf("Agora insira o valor de desconto (em %%): ");
    scanf("%i", &desconto);

    aplicarDesconto(ptrPreco, ptrDesconto, ptrNovoPreco);

    printf("\nMeus parabéns! Você realizou a compra de R$ %.2f, aplicando o desconto de %i%% você pagou apenas R$ %.2f. 🤑\n " , *ptrPreco, *ptrDesconto, *ptrNovoPreco);
    printf("\nNós agredecemos a preferencia! ≧◠‿◠≦✌ ");
    
}

