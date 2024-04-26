#ifndef _GCOLECTION_C_
#define _GCOLECTION_C_

#include <stdlib.h>
#include "gColection.h"

gColection * gcolCreate(int n) {
    gColection * c;
    if(n > 0) {
        c = (gColection *) malloc(sizeof(gColection));
        if(c != NULL) {
            c->itens = (void **) malloc(sizeof(void*) * n);
            if(c->itens != NULL) {
                c->maxItens = n;
                c->numItens = 0;
                c->current = 0;
                return c;
            }
            free(c);
        }      
    }
    return NULL;
}

int gcolDestroy(gColection * c) {
    if(c != NULL) {
        if(c->numItens == 0) {
            free(c->itens);
            free(c);
            return TRUE;
        }
    }
    return FALSE;
}

int gcolInsert(gColection *c, void *item) {
    if(c->numItens < c->maxItens) {
        c->itens[c->numItens] = item;
        c->numItens++;
        return TRUE;
    }
    return FALSE;
}

void * gcolQuery(gColection *c, void *key, int(*cmp)(void *, void *)) {
    int i; int stat; void *data;
    if(c != NULL) {
        if(c->numItens > 0) {
            i = 0;
            stat = cmp(c->itens[i], key);
            printf(" stat %d: %d\n", i, stat);
            while(i < c->numItens && stat != TRUE) {
                i++;
                stat = cmp(c->itens[i], key);
                printf(" stat %d: %d\n", i, stat);
            }
            if(stat == TRUE) {
                data = c->itens[i];
                printf("Encontrado\n");
                return data;
                
            }
        }
    }
    printf("Nada\n");
    return NULL;
}

void * gcolRemove(gColection *c, void *key, int (*cmp)(void *, void *)) {
    int i, j; void *data; int stat;
    if(c != NULL) {
        if(c->numItens > 0) {
            i = 0;
            stat = cmp(c->itens[i], key);

            while(i < c->numItens && stat != TRUE) {
                i++;
                stat = cmp(c->itens[i], key);
            }
            if(stat == TRUE) {
                data = c->itens[i];
                for(j = i; j < c->numItens; j++) {
                    c->itens[j] = c->itens[j + 1];
                }
                c->numItens--;
                return data;
            }
        }
    }
    return NULL;
}

void * gcolGetFirst(gColection *c) {
    if(c != NULL) {
        if(c->numItens > 0) {
            c->current = 0;
            return c->itens[c->current];
        }
    }
    return NULL;
}

void * gcolGetNext(gColection *c) {
    if(c != NULL) {
        c->current++;
        if(c->current < c->numItens) {
            return c->itens[c->current];
        }
    }
    return NULL;
}


/*
int gcolEmpties(gColection *c) {
    if (c != NULL) {
        if(c->numItens > 0) {
            for (int i = 0; i < c->numItens; i++) {
                free(c->itens[i]);
            }
            c->numItens = 0;
            return TRUE;
        }      
    }
    return FALSE;
}
*/
int gcolEmpties(gColection *c) {
    if (c != NULL) {
        if(c->numItens > 0) {
            c->numItens = 0;
            return TRUE;
        }      
    }
    return FALSE;
}

#endif