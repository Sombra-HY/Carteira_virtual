/*
 * Este arquivo é direcionado para criacao de funcoes que auxiliam na criacao do projeto.
 * Funcoes relacionadas na modoficacao de arquivo, como criar, ler, atualizar e deletar
 * (CRUD)
*/


void binario(){

    char var[20];

    char c[10]="aa123";
    FILE *arq = fopen("teste.txt","bw");
    fwrite(c,6,sizeof(char),arq);
    fclose(arq);

    arq = fopen("teste.txt","r");
    fread(var, sizeof(var),10,arq);
    printf("%s",var);
    fclose(arq);


}

