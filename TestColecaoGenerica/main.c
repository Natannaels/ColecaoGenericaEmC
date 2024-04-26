#include <stdio.h>
#include <string.h>
#include "gColection.c"

typedef struct _aluno_{
    int num;
    char nome[10];
}Aluno;


//Cria a colecao 
void criarColecao(int n) {
    gColection *col;
    col = gcolCreate(n);
    if(col != NULL) {
        printf("Colecao Criada Com Sucesso!");
    }
}

//Lista os elementos da Colecao
void gcolList(gColection *c) {  
    Aluno *a = (Aluno *) gcolGetFirst(c);
    while(a != NULL) {        
        printf(" - %d - \n", a->num);
        a = (Aluno *)gcolGetNext(c);
    }
    
}

int cmpNum(void *a, void *b) {
    Aluno *pa; int *pb;
    pa = (Aluno *) a; 
    pb = (int *) b;
    printf("pa->num: %d\n", pa->num);
    printf("*pb: %d\n", *pb);
    if(pa->num == *pb) {
        printf("TRUE\n");
        return TRUE;
        
    }else {
        printf("FALSE\n");
        return FALSE;
        
    }
}

int main() {

    // Criar uma coleção para alunos
    gColection *colecao = gcolCreate(10);

    int numAluno;
    char nomeAluno[50];

    printf("Nome e Numero: ");
    scanf("%s %d",nomeAluno, &numAluno);

    // Criar alunos para adicionar ao cofo
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    aluno->num = numAluno;
    strcpy(aluno->nome, nomeAluno);
    gcolInsert(colecao, aluno);

    printf("Nome e Numero: ");
    scanf("%s %d",nomeAluno, &numAluno);

    aluno = (Aluno *)malloc(sizeof(Aluno));
    aluno->num = numAluno;
    strcpy(aluno->nome, nomeAluno);
    gcolInsert(colecao, aluno);

    // Realizar busca pelo número
    int numBuscar = 10;
    Aluno *alunoEncontrado;

    //Bucar
    alunoEncontrado = (Aluno *)gcolQuery(colecao, &numBuscar, cmpNum);
    if (alunoEncontrado != NULL) {
        printf("Estava na Colecao: %s %d\n", alunoEncontrado->nome, alunoEncontrado->num);
    } else {
        printf("Não encontrado!\n");
    }

    //Remover
    alunoEncontrado = (Aluno *)gcolRemove(colecao, &numBuscar, cmpNum);
    if (alunoEncontrado != NULL) {
        printf("Eliminado: %s %d\n", alunoEncontrado->nome, alunoEncontrado->num);
    } else {
        printf("Não encontrado!\n");
    }

    return 0;
}

