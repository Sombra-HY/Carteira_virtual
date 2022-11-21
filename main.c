#include <stdio.h>
#include "string.h"
#include "funcoes.h"





//int Extrato(){
//
//    int x;
//    char cat[30];
//
//    printf("----------------Extrato------------------\n\nEscolha uma das opcoes abaixo:\n\n");
//    printf("[1] - Escolher Categoria - (1 mes)\n[2] - Completo - (12 mes)\n:");
//    scanf("%d",&x);
//    if(x==1){
//        printf("escolha uma categoria: ");
//        scanf("%s",&cat);
//
//        //funcao que chama que entrega o extrato
//        printf("-------------%s---------------\n",cat);
//    }
//    else if(x==2){
//
//    }
//
//    return 1;
//}



void Saldo(int *x){
    //altera o valor de x se for 1 para 0 e 0 para 1 (INTERRUPTOR DESLIGA E LIGA)
    *(x) = (*x==1)? 0:1;
}

int teste(){
    //valores padroes de formato da carteira, inicialmente ela estara escondida

    char escolha ='0';
    int x = 0;

    //principal

    while(escolha!='9'){
        double saldo = procura_saldo();
        char mostra[4][20];
        sprintf(mostra[1],"%.2lf",saldo);
        strcpy(mostra[0],"****");
        strcpy(mostra[2],"MOSTRAR SALDO");
        strcpy(mostra[3],"ESCONDER SALDO");

        char delimitador[]={'1','2','3','4','5','9'};

        //este print vai ser alterado ao chamar a funcao SALDO, atraves da variavel x que sera alterada, resultando em um print diferente
        //obs (FLUSH = limpa os dados nao usados, resolve o erro do scanf nao sendo lido)

        printf("-----------------------------------\nOla!   Carteira: %s\n\n"
               "Escolha uma das opcoes abaixo: "
               "\n\n""[1] - %s   "
                     "\n""[2] - EXTRATO"
                         "\n""[3] - TRANFERENCIA"
                             "\n[4] - ADICIONAR GASTO"
                             "\n[5] - ADICIONAR RECEITA"
                             "\n""[9] - ENCERRAR OPERACAO \n\n:",mostra[0+x],mostra[2+x]);

        fflush(stdin);
        scanf("%c",&escolha);

        // O while trata possiveis palavras erradas digitadas pelo usuario que nao estao presentes no delimitador[]={'1','2','3','9'}
        // fazendo o digitar novamente. obs (FLUSH = limpa os dados nao usados, resolve o erro do scanf nao sendo lido)

        while ( 0 == (inCHAR(escolha,delimitador,6))){
            printf("Valor Incongruente!\nDigite novamente:");
            fflush(stdin);
            scanf(" %c",&escolha);
        }

        // se for 9 encerra a a operacao
        int v = (escolha - '0');
        if (v == 9){
            printf("\nOperacao Finalizada!\n");
            return 1;}

        if (v == 1) {
            Saldo(&x);
        }
        if (v==2){
            imprime_arq();
        }
        if (v==3){
            Transferencia();
        }
        if (v==4){
            adicionar_rea(-1);
        }
        if (v==5){
            adicionar_rea(1);
        }
    }

}

int main(){
    teste();
}



