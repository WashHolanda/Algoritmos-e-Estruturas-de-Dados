#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Problema 06 - Pesquisa Interna - ́Árvore Binária de Busca
*/
typedef struct TipoNo* ArvBin;

typedef struct TipoNo{
    int key;
    struct TipoNo *esq,*dir;
}TipoNo;

// Inicializa a árvore.
ArvBin* inicializaArv(){
    ArvBin *raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL) 
        *raiz = NULL;
    return raiz;
}

// Cria um novo nó na arvore.
TipoNo *criaNo(int k){
    TipoNo *novo = (TipoNo*) malloc(sizeof(TipoNo));
    novo->key = k;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void imprime(TipoNo *arv){
    if(arv==NULL)
        return;
    imprime(arv->esq);
    printf("%d\n",arv->key);
    imprime(arv->dir);
}

// Calcula a altura da ABB.
int alturaArv(TipoNo *arv){
    int alt_esq, alt_dir;

    if (arv == NULL) 
        return 0;
    alt_esq = alturaArv(arv->esq);
    alt_dir = alturaArv(arv->dir);
    if(alt_esq > alt_dir) 
        return (alt_esq + 1);
    else 
        return (alt_dir + 1);
}

//Calcula o tamanho da ABB.
int tamanhoArv(TipoNo *arv){
    int alt_esq, alt_dir;

    if (arv == NULL) 
        return 0;
    alt_esq = tamanhoArv(arv->esq);
    alt_dir = tamanhoArv(arv->dir);
    return (alt_esq + alt_dir + 1);
}

//Busca o sucessor do nó que será removido.
void sucessor(TipoNo *arv,TipoNo *suc){
    TipoNo *aux;

    if (suc->esq == NULL){
        arv->key = suc->key;
        aux = suc;
        suc = suc->dir;
        free(aux);
        arv->dir = suc;
    }
    else
        sucessor(arv, suc->esq);
}

// Insere um novo nó na ABB.
void insereNo(ArvBin *arv, int k){
    if (*arv == NULL){
        *arv = criaNo(k);
        return;
    }
    if(k < (*arv)->key){
        if((*arv)->esq != NULL)
            insereNo(&((*arv)->esq),k);
        else
            (*arv)->esq = criaNo(k);
    }
    else{
        if((*arv)->dir!=NULL)
            insereNo(&((*arv)->dir),k);
        else
            (*arv)->dir = criaNo(k);
    }
}

// Remove um nó da ABB.
TipoNo* removeNo(TipoNo *arv){
    TipoNo *aux;
    
    if(arv->dir == NULL && arv->esq == NULL){
           return NULL;
    }
    else if(arv->dir != NULL && arv->esq == NULL){
           return arv->dir;
    }
    else if(arv->dir == NULL && arv->esq != NULL){
           return arv->esq;
    }
    else{
        sucessor(arv, arv->dir);
        return arv;
    }
}

// Busca por um valor dentro da ABB.
int busca(ArvBin *arv, int k){
    if(*arv == NULL)
        return 0;
    if(k == (*arv)->key){
        *arv = removeNo(*arv);
        return 1;
    }
    if(k < (*arv)->key)
        return busca(&((*arv)->esq), k);
    else
        return busca(&((*arv)->dir), k);
}

int main(){
    int i, valor, tam1, alt1, tam2, alt2;
	ArvBin *arv;

    arv = inicializaArv();

    do{ // Inserção de elementos
        scanf("%d",&valor);
        if(valor >= 0)
            insereNo(arv,valor);
    }while (valor >= 0);

    tam1 = tamanhoArv(*arv);
    alt1 = alturaArv(*arv);

    //Pesquisa
    scanf("%d",&valor);
    if(busca(arv, valor) == 0){
        insereNo(arv, valor);
    }
    printf("nova arvore\n");
    imprime(*arv);
    tam2 = tamanhoArv(*arv);
    alt2 = alturaArv(*arv);

    printf("%d %d\n",tam1,alt1);
    printf("%d %d\n",tam2,alt2);

    return 0;
}