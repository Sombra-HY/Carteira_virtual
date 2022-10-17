#include <stdio.h>
#include "funcoes.c"
#include "CRUD.c"

int main(){
// abre o arquivo para leitura
    FILE *f = fopen("arquivo.txt","r");
    char c[400]; // para armazenar o que for lido

    fscanf(f,"%s", &c); // le a primeira linha
    printf("%s\n", c); // exibe a linha
    print_vetor_S(c,400);
    fscanf(f,"%s", &c); // le a próxima linha
    printf("%s\n", c); // exibe o que foi lido
    fscanf(f,"%s", &c); // le a primeira linha
    printf("%s\n", c); // exibe a linha
    fscanf(f,"%s", &c); // le a próxima linha
    printf("%s\n", c); // exibe o que foi lido

    fclose(f); // fecha o arquivo
}