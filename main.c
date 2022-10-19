#include <stdio.h>
#include "string.h"
#include "funcoes.c"
#include "CRUD.c"

int Saldo(){
    printf("saldo");
    return 1;
}
int Extrato(){
    printf("Estrato");
    return 1;
}
int Transferencia(){
    printf("Transferencia");
    return 1;
}

int Menu(){

    // O menu mostrara apenas as opcao principais do programa

    char delimitador[]={'1','2','3','9'};
    char escolha;

    printf("\nSeja Bem vindo!\n\nEscolha uma das opcoes abaixo: \n\n""[1] - SALDO   \n""[2]-  EXTRATO \n""[3] - TRANFERENCIA  \n""[9] - ENCERRAR OPERACAO \n");
    scanf("%c",&escolha);

    // O while trata possiveis palavras erradas digitadas pleo usuario que nao estao presentes no delimitador[]={'1','2','3','9'}
    // fazendo o digitar novamente. obs (FLUSH = limpa os dados nao usados, resolve o erro do scanf nao sendo lido)

    while ( 0 == (inCHAR(escolha,delimitador,4))){
        printf("Valor Incongruente!\nDigite novamente:");
        fflush(stdin);
        scanf(" %c",&escolha);
    }

    int v = (inCHAR(escolha,delimitador,4))?(escolha - '0'):0;

    return v;
}

int main(){
    //
    printf("%d", Menu());

    return 1;
}


