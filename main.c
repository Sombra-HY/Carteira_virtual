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

    int escolha = 0;

    printf("\nSeja Bem vindo!\n\nEscolha uma das opcoes abaixo: \n\n"
           "[1] - SALDO   \n"
           "[2]-  EXTRATO \n"
           "[3] - TRANFERENCIA  \n"
           "[9] - ENCERRAR OPERACAO \n");
    scanf("%d",&escolha);

    return escolha;
}

int main(){

    typedef int (*function)();
    function f[]={Menu,Saldo, Extrato, Transferencia};
    int vetor[]={1,2,3,9};


    int escolha = Menu();
    escolha = (in(escolha,vetor,4))? escolha:0;

    if (escolha==9)
        printf("Operacao finalizada!");
    else
        f[escolha]();

    return 1;
}


