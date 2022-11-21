#include <stdio.h>
#include "string.h"
#include <time.h>
#include <Windows.h>

// funcao que verifica se uma valor esta dentro de uma vetor, similar ao "in" do python, retornando verdadeiro ou falso se o valor tiver na lista, 1 ou 0.
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

int inCHAR (char valor,char *vetor,int tamVetor){
    int booleano = 0;
    for (int i = 0; i < tamVetor; ++i) {
        if ( vetor[i] == valor){
            booleano = 1;
            break;
        }
    }
    return booleano;
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

void adicionar_rea(int valor){
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

    struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);
    struct dados dados;

    if (valor==1){

        printf("\n%s","Digite um valor para adicionar: ");

        scanf("%lf", &dados.desconto);
        fflush(stdin);

        dados.saldo = procura_saldo()+dados.desconto;

        printf("Digite uma categoria: \n");
        scanf("%s", &dados.categoria);
        strupr(dados.categoria);
        fflush(stdin);

        printf("Digite uma descricao (Opcional): \n");
        scanf("%[^\n]s", &dados.descricao);
        fflush(stdin);

        // data atual
        dados.dia = p->tm_mday;
        dados.mes = p->tm_mon + 1;
        dados.ano = p->tm_year + 1900;
        dados.hora = p->tm_hour;
        dados.minuto = p->tm_min;
        dados.segundo = p->tm_sec;

        FILE *arq = fopen("arquivo.txt", "ab");
        fwrite(&dados, sizeof(dados), 1, arq);
        fclose(arq);
    }
    else{

        printf("\n%s","Digite o valor do gasto: ");

        scanf("%lf", &dados.desconto);
        dados.desconto *=-1;
        fflush(stdin);

        dados.saldo = procura_saldo() + dados.desconto;

        printf("Digite a categoria: \n");
        scanf("%s", &dados.categoria);
        strupr(dados.categoria);
        fflush(stdin);

        printf("Digite a descricao (Opcional): \n");
        scanf("%[^\n]s", &dados.descricao);
        fflush(stdin);

        // data atual
        dados.dia = p->tm_mday;
        dados.mes = p->tm_mon + 1;
        dados.ano = p->tm_year + 1900;
        dados.hora = p->tm_hour;
        dados.minuto = p->tm_min;
        dados.segundo = p->tm_sec;

        FILE *arq = fopen("arquivo.txt", "ab");
        fwrite(&dados, sizeof(dados), 1, arq);
        fclose(arq);
    }
}

void imprime_arq(int Qmes){
    struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);
    struct dados dados;

    // data atual
    dados.dia = p->tm_mday;
    dados.mes = p->tm_mon + 1;
    dados.ano = p->tm_year + 1900;
    dados.hora = p->tm_hour;
    dados.minuto = p->tm_min;
    dados.segundo = p->tm_sec;

    struct dados valor;

    FILE *arq = fopen("arquivo.txt", "rb");

    // So pode imprimir valores em que o  arquivo (mes + (ano * 12)) >= atual (mes + (ano * 12) - Qmes)
    // neste caso os dias nao sao contabilizados

    while(fread(&valor, 1, sizeof(valor), arq)){
        if ((valor.mes + (valor.ano)*12) >= (dados.mes + (dados.ano * 12))-Qmes){
            printf("\n_____________%d/%d/%d_____________\n"
                   "%c %.2lf\n"
                   "categoria : %s\n"
                   "descricao: %s\n[disponivel: R$ %.2lf]\n",valor.dia,valor.mes,valor.ano ,(valor.desconto>0?'+':' '),valor.desconto,valor.categoria,valor.descricao,valor.saldo);
            Sleep(1000);
        }

    }
    fclose(arq);
    int i = 0;
    while (i++ < 3) {
        Sleep(1000); // Sleep 1 segundo
        printf(". ");
    }
    printf("\n");
}

int Transferencia(){
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

    struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);

    struct dados dados;

    printf("%s","\nDigite a quantia a ser transferiada: ");
    scanf("%lf", &dados.desconto);
    dados.desconto *=-1;
    fflush(stdin);

    dados.saldo = procura_saldo() + dados.desconto;

    strcpy(dados.categoria, "TRANSFERENCIA");
    strupr(dados.categoria);
    fflush(stdin);

    struct dados conta;

    struct conta{
        char nome[30];
        char pix[30];
    };
    struct conta valor;

    printf("Digite o nome do favorecido: ");
    scanf("%[^\n]s", &valor.nome);
    fflush(stdin);

    printf("Digite o PIX: ");
    scanf("%s", &valor.pix);
    fflush(stdin);
    sprintf(dados.descricao, "nome do favorecido: %s\nPIX: %s",valor.nome,valor.pix);

    // data atual
    dados.dia = p->tm_mday;
    dados.mes = p->tm_mon + 1;
    dados.ano = p->tm_year + 1900;
    dados.hora = p->tm_hour;
    dados.minuto = p->tm_min;
    dados.segundo = p->tm_sec;

    FILE *arq = fopen("arquivo.txt", "ab");
    fwrite(&dados, sizeof(dados), 1, arq);
    fclose(arq);
    return 1;
}