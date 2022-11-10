//verefica se um valor esta presente em um vetor e retona 1 se sim ou 0 se nao (inteiros)

int inINT (int valor,int *vetor,int tamVetor){
    int booleano = 0;
    for (int i = 0; i < tamVetor; ++i) {
        if ( vetor[i] == valor){
            booleano = 1;
            break;
        }
    }
    return booleano;
}

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

//

















// printa uma lista
void print_vetor_s(int *vetor,int tam){
    for (int i = 0; i <tam ; ++i) {
        printf("%d ",*(vetor+i));
    }
    printf("\n");
}
void print_vetor_S(char *vetor,int tam){
    for (int i = 0; i <tam ; ++i) {
        printf("%c ",*(vetor+i));
    }
    printf("\n");
}


