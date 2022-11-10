#include <stdio.h>
#include "string.h"
#include "funcoes.c"
#include "CRUD.c"
struct dados {
    double saldo;
    double desconto;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
    char categoria[30];
    char descricao[200];
};


int Extrato(){
    printf("Estrato");
    return 1;
}
int Transferencia(){
    printf("Transferencia");
    return 1;
}

double procura_saldo() {
    /* esta funcao procura o saldo no arquivo binario
      primeiro abro o arquivo, caso ele nao exista eu crio ele,
      apos isso leio o primeiro "struct" (quantidade de dados) no arquivo
    */
    FILE *arq = fopen("arquivo.txt", "ab");
    fclose(arq);

    struct dados valor;
    int var;
    double saldo;
    int cont=0;

    arq = fopen("arquivo.txt", "rb");
    var = fread(&valor, 1, sizeof(valor), arq);
    fclose(arq);

    /* o fread retorna 0 se nao tiver nada no arquivo, por isso
        verifico se o retorno for 0, retorno o saldo de R$ 0.00,
        caso contrario leio o struct e retono o ultimo saldo neste
    */
    if (var == 0) {
        return 0;
    } else {
        arq = fopen("arquivo.txt", "rb");
        while(!feof(arq)){
            cont++;
            fread(&valor,sizeof(valor),1,arq);
        }
        fclose(arq);

        return valor.saldo;
    }
}

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
    }

}

int main(){
    teste();
}



