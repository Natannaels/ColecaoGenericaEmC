/*
*   main.c
*   
*   FUNCOES QUE APRESENTAO OS MENUS
*   E CHAMAM AS FUNCOES AUXILIARES.
*
*   Arquivo com a implementação das funções 
*   que exibem os menus da interface de texto
*   e auxiliam as chamadas das operações
*/
#include "gColection.h"// Protótipos das operacões de Coleção
#include<stdlib.h>
#include <stdio.h>
#include <string.h>

// Estrutura  de tipo escolhida
typedef struct _aluno_{
    int matr;
    char nome[30];
    float nota;
}Aluno;

// Função para criar uma coleção e verificar se foi criada com sucesso
gColection *criarColecao() {
    int n;
    printf("Insira o Tamanho Da Colecao: ");
    scanf("%d", &n);
    if(n > 0) {
        gColection *c = gcolCreate(n);
        if(c != NULL) {
            printf("\n**Colecao Criada Com Sucesso**\n");
            return c;
        }
    }
    printf("\n**O Tamanho Deve Ser Maior que 0**\n");
    return NULL;
}

// Função para imprimir informações do aluno
void imprimeInfo(Aluno *a) {
    if (a != NULL) {
        printf("\n");
        printf("NOME: %s\n", a->nome);
        printf("MATRICULA: %d\n", a->matr);
        printf("NOTA: %.2f\n", a->nota);
        printf("\n");
    } else {
        printf("\n**Nao encontrado**\n");
    }
}

// Função para listar os elementos da coleção
void gcolList(gColection *c) {  
    if(c != NULL) {
        Aluno *a = (Aluno *) gcolGetFirst(c);
        printf("\nLISTA DE ALUNOS:\n");
        while(a != NULL) {        
            imprimeInfo(a);
            a = (Aluno *)gcolGetNext(c);
        }
    }   
}

// Funções para comparar tipos (para busca ou remoção)
int cmpMatr(void *a, void *b) {
    Aluno *pa; int *pb;
    pa = (Aluno *) a; 
    pb = (int *) b;
    if(pa->matr == *pb) {
        return TRUE;     
    }else {
        return FALSE;
        
    }
}

int cmpNota(void *a, void *b) {
    Aluno *pa; float *pb;
    pa = (Aluno *) a; 
    pb = (float *) b;
    int x = (int)(pa->nota * 10);
    int y = (int)(*pb * 10);
    if(x == y) {
        return TRUE;     
    }else {
        return FALSE; 
    }
}

int cmpNome(void *a, void *b) {
    Aluno *pa; char *pb;
    pa = (Aluno *) a; 
    pb = (char *) b;
    if(strcmp(pa->nome, pb) == 0) {
        return TRUE;     
    }else {
        return FALSE;
        
    }
}

// Função para inserir alunos na coleção
void insereAlunos(gColection *c) {
    if(c != NULL) {
        if(gcolIsful(c) == FALSE) {
            int matr;
            char nome[30];
            float nota;  
            printf("Digite Nome: ");
            scanf("%s", nome);
            printf("Digite Matricula: ");
            scanf("%d", &matr);
            printf("Digite Nota: ");
            scanf("%f", &nota);
            
            Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
            aluno->matr = matr;
            aluno->nota = nota;
            strcpy(aluno->nome, nome);
            gcolInsert(c, aluno);
            printf("\n**Adicionado Com Sucesso**\n\n");
        }else {
            printf("\n**Ops! A Colecao esta Cheia**\n\n");
        }
    }
}

// Função para buscar por nome e imprimir informações do aluno
void buscarNome(gColection *c) {
    char nome[30];
    scanf("%s",nome);
    Aluno *a = (Aluno *)gcolQuery(c, nome, cmpNome);
    imprimeInfo(a);
}

// Função para buscar por matrícula e imprimir informações do aluno
void buscarMatr(gColection *c) {
    int matr;
    scanf("%d", &matr);
    Aluno *a;
    a = (Aluno *)gcolQuery(c, &matr, cmpMatr);
    imprimeInfo(a);
}

// Função para buscar por nota e imprimir informações do aluno
void buscarNota(gColection *c) {
    float nota;
    scanf("%f", &nota);
    Aluno *a;
    a = (Aluno *)gcolQuery(c, &nota, cmpNota);
    imprimeInfo(a);
}

// Função para escolher critério de busca (nome, matrícula ou nota)
void consultaAluno(gColection *colecao) {
    int opcao;
    if(colecao != NULL) {
        printf("\n---------------------\n");
        printf("Como Deseja Consultar:\n");
        printf("1 - NOME\n");
        printf("2 - MATRICULA\n");
        printf("3 - NOTA\n");
        printf("\n---------------------\n");
        printf("Escolha Uma Opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: 
                printf("Digite o NOME: ");
                buscarNome(colecao);
                break;
            case 2:
                printf("Digite MATRICULA: ");
                buscarMatr(colecao);
                break;
            case 3:
                printf("Digite NOTA: ");
                buscarNota(colecao);
                break;
            default:
                printf("Opcao Invalida!\n");
        }
    }
}

// Função para buscar e remover aluno (nome, matrícula ou nota)
void removerAluno(gColection *colecao) {
    int opcao;
    if(colecao != NULL) {
        Aluno *aluno;
        int matr;
        char nome[30];
        float nota;
        printf("\n---------------------\n");
        printf("Como Deseja Remover:\n");
        printf("1 - NOME\n");
        printf("2 - MATRICULA\n");
        printf("3 - NOTA\n");
        printf("\n---------------------\n");
        printf("Escolha Uma Opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:    
                printf("Digite o NOME: ");
                scanf("%s", nome);
                aluno = (Aluno *)gcolRemove(colecao, nome, cmpNome);
                if (aluno != NULL) {
                    printf("\nRemovendo: %s matr: %d nota: %.2f\n", aluno->nome, aluno->matr, aluno->nota);
                    printf("\n**Removido**\n");
                } else {
                    printf("\n**Nao Encontrado**\n");
                }
                break;
            case 2:     
                printf("Digite MATRICULA: ");
                scanf("%d", &matr);
                aluno = (Aluno *)gcolRemove(colecao, &matr, cmpMatr);
                if (aluno != NULL) {
                    printf("\nRemovendo: %s matr: %d nota: %.2f\n", aluno->nome, aluno->matr, aluno->nota);
                    printf("\n**Removido**\n");;
                } else {
                    printf("\n**Nao Encontrado**\n");
                }
                break;
            case 3:
                printf("Digite NOTA: ");
                scanf("%f", &nota);
                aluno = (Aluno *)gcolRemove(colecao, &nota, cmpNota);
                if (aluno != NULL) {
                     printf("\nRemovendo: %s matr: %d nota: %.2f\n", aluno->nome, aluno->matr, aluno->nota);
                    printf("\n**Removido**\n");
                } else {
                    printf("\n**Nao Encontrado**\n");
                }
                break;
            default:
                printf("Opcao Invalida!\n");
        }
    }
}

//Menu de manipulacao da colecao e chamada das funcoes
void manipulaCol(gColection *colecao) {
    int opcao;
    do {
        printf("\n------------------------------------\n");
        printf("1 - Inserir Aluno Na Colecao\n");
        printf("2 - Remover Aluno Da Colecao\n");
        printf("3 - Consultar Um Aluno Na Colecao\n");
        printf("4 - Listar Alunos da Colecao\n");
        printf("5 - Esvaziar Colecao\n");
        printf("6 - Destruir Colecao\n");
        printf("------------------------------------\n");
        printf("Escolha Uma Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            insereAlunos(colecao);
            break;
        case 2:
            removerAluno(colecao);
            break;
        case 3:
            consultaAluno(colecao);
            break;
        case 4:
            gcolList(colecao);
            break;
        case 5:
            gcolEmpty(colecao);
            printf("\n**Esvaziando Colecao...**\n");
            break;
        case 6:
            if(gcolDestroy(colecao)) {
                printf("\n**Colecao Destruida**\n");
                opcao = 0;
            }else {
                printf("\n**Esvazie A Colecao Antes**\n");
            }
            break;
        default:
            printf("Opcao Invalida!\n");
        }

    } while(opcao != 0);

}

int main() {
    printf("BEM VINDO AO REI DO COFO :)\n");
    gColection *colecao;
    int opcao;
    do {
        printf("\n---------------------\n");
        printf("1 - Criar Colecao\n");
        printf("0 - Sair\n");
        printf("---------------------\n");
        printf("Escolha Uma Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            colecao = criarColecao();
            if(colecao != NULL) {
                manipulaCol(colecao);
            }else {
                break;
            }  
            break;
        case 0:
            printf("Saindo...");
            break;
        
        default:
            printf("Opcao Invalida!\n");
        }

    } while(opcao != 0);
    return 0;
}