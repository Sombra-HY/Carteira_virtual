#include <stdio.h>
#include "string.h"
#include <time.h>
#include <Windows.h>

// formato dos dados no arquivo em binario
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

// funcao que verifica se uma valor esta dentro de uma vetor, similar ao "in" do python,
// retornando verdadeiro ou falso se o valor tiver na lista, 1 ou 0.
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
        // retrona o valor do saldo atual
    }
}
// adicionar_ rea coloca ou tira dinheiro do arquivo, ele recebe
// o parametro inteiro, se for negativo ele vai tirar se for positivo ele vai
// adicionar saldo na conta

void adicionar_rea(int valor){
    //formato dos dados
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

    // pegando valores de horario atual
    struct tm *p;
    time_t seconds;
    time(&seconds);
    p = localtime(&seconds);
    struct dados dados;

    // Aqui vai adiconar dinheiro
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

        //escrevendo na ultima linha em binario
        FILE *arq = fopen("arquivo.txt", "ab");
        fwrite(&dados, sizeof(dados), 1, arq);
        fclose(arq);
    }
    // arqui vai tira dinheiro
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

        //escrevendo na ultima linha em binario
        FILE *arq = fopen("arquivo.txt", "ab");
        fwrite(&dados, sizeof(dados), 1, arq);
        fclose(arq);
    }
}


// imprime_arq printa os valores do arquivo conforme algun tipo de filtro
// passado pelo main.c os parametros Qmes é a quantidade de mes anteriores a ser imprimido
// completo é um parametro que define a orden em outros parametros, no caso se ele for 1 (ativado)
// ele ignorara os valores como Qmes e imprimira todos componentes do arquivo.
// tipocategoria é um parametro que faz ser imprimido apenas valores digitados
// pelo usuario, no caso se for diferente de "1" ele imprimira todos valores
// que tenha no arquivo com categoria == tipocategoria
// caso seja "1" ele imprimira tudo...

void imprime_arq(int Qmes, int completo, char *tipocategoria){
    printf("%s",tipocategoria);
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

    if(completo){
        while(fread(&valor, 1, sizeof(valor), arq)){

            // SEM FILTRO
            printf("\n_____________%d/%d/%d_____________\n"
                       "%c %.2lf\n"
                       "categoria : %s\n"
                       "descricao: %s\n[disponivel: R$ %.2lf]\n",valor.dia,valor.mes,valor.ano ,(valor.desconto>0?'+':' '),valor.desconto,valor.categoria,valor.descricao,valor.saldo);
            Sleep(1000);
        }
    }

    // verificacao do categoria == "1", faz imprimir tudo, mas apenas com o filtro de mes ativado
    else{
        if(tipocategoria[0]=='1'){
            //FILTRO MES
            while(fread(&valor, 1, sizeof(valor), arq)){
                if ((valor.mes + (valor.ano)*12) >= (dados.mes + (dados.ano * 12))-Qmes){
                    printf("\n_____________%d/%d/%d_____________\n"
                           "%c %.2lf\n"
                           "categoria : %s\n"
                           "descricao: %s\n[disponivel: R$ %.2lf]\n",valor.dia,valor.mes,valor.ano ,(valor.desconto>0?'+':' '),valor.desconto,valor.categoria,valor.descricao,valor.saldo);
                    Sleep(1000);
                }

            }
        }

        // esse print o filtro de meses e de categoria estao ativados
        // o extrato tera dois filtros
        else{
            while(fread(&valor, 1, sizeof(valor), arq)){
                int vefstr = strcmp(valor.categoria,tipocategoria);
                // FILTRO MES E CATEGORIA
                if (((valor.mes + (valor.ano)*12) >= (dados.mes + (dados.ano * 12))-Qmes) && (vefstr==0)){
                    printf("\n_____________%d/%d/%d_____________\n"
                           "%c %.2lf\n"
                           "categoria : %s\n"
                           "descricao: %s\n[disponivel: R$ %.2lf]\n",valor.dia,valor.mes,valor.ano ,(valor.desconto>0?'+':' '),valor.desconto,valor.categoria,valor.descricao,valor.saldo);
                    Sleep(1000);
                }

            }
        }
    }

    fclose(arq);
    int i = 0;

    //pequeno timer durante o processo
    printf("\nCarregando");
    while (i++ < 3) {
        Sleep(1000); // Sleep 1 segundo
        printf(".");
    }
    printf("\n");
}

// A tranferecia sera solicitado pelo usuario os valores do favorecido, ou seja
// de quem recebera o dinheiro assim como o "pix", apos isso ele removera o dinheiro
// e salvara no arquivo o dinheiro retirado, e salvara na categoria TRANFERENCIA por padrao
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
    // TIPO DE CATEGORIA PADRAO == TRANSFERENCIA

    strupr(dados.categoria);
    fflush(stdin);

    struct dados conta;

    struct conta{
        char nome[30];
        char pix[30];
    };
    struct conta valor;

    // entradas que serao descritas na secao descriacao do arquivo
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

    // Escrita
    FILE *arq = fopen("arquivo.txt", "ab");
    fwrite(&dados, sizeof(dados), 1, arq);
    fclose(arq);
    return 1;
}