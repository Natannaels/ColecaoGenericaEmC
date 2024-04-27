/*
*   gColection.h
*
*   FUNCOES QUE REPRESENTAO 
*   AS OPERACOES DE UMA COLECAO.
*
*   Arquivo com as definições dos cabeçalhos  
*   das operações implementadas em gColection.c
*/
#ifndef _GCOLECTION_H_
#define _GCOLECTION_H_
#ifdef _GCOLECTION_C_
#define TRUE 1
#define FALSE 0  
    
    typedef struct _gcol_ gColection;
    gColection * gcolCreate(int maxItens);
    int gcolInsert(gColection *c, void *item);
    void * gcolRemove(gColection *c, void *key, int (*cmp)(void *, void *));
    void * gcolQuery(gColection *c, void *key, int (*cmp)(void *, void *));
    void * gcolGetFirst(gColection *c);
    void * gcolGetNext(gColection *c);
    int gcolDestroy(gColection * c);
    int gcolEmpty(gColection *c);
    int gcolIsful(gColection *c);
    
#else 
    #define TRUE 1
    #define FALSE 0 
    typedef struct _gcol_ gColection;
    extern gColection * gcolCreate(int maxItens);
    extern int gcolInsert(gColection *c, void *item);
    extern void * gcolRemove(gColection *c, void *key, int (*cmp)(void *, void *));
    extern void * gcolQuery(gColection *c, void *key, int (*cmp)(void *, void *));
    extern void * gcolGetFirst(gColection *c);
    extern void * gcolGetNext(gColection *c);
    extern int gcolDestroy(gColection * c);
    extern int gcolEmpty(gColection *c);
    extern int gcolIsful(gColection *c);
#endif
#endif