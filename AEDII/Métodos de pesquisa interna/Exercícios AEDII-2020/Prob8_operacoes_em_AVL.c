#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 08 – Pesquisa Interna – Operações em Árvores AVL
*/

typedef struct TipoNo{
    int key;
    struct TipoNo *esq,*dir;
}TipoNo;

typedef struct TipoNo* ArvBin;

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

// Imprime árvore com parênteses aninhados.
void Imprime(TipoNo *arv){
	if (arv != NULL) {
		printf("(C%d", arv->key);
		Imprime(arv->esq);
		Imprime(arv->dir);
		printf(")");
	}
	else
		printf("()");
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

// Calcula o Fator de Balanceamento de um nó.
int calculaFB(TipoNo *arv){
    int fb;

    fb = alturaArv(arv->esq) - alturaArv(arv->dir);

    return fb;
}

// Busca o sucessor do nó que será removido.
TipoNo* sucessor(TipoNo *arv,TipoNo *paisuc,TipoNo *suc){
    TipoNo *aux;
    
    if (suc->esq == NULL){
        suc->esq = arv->esq;
        if (arv->dir != suc){
            aux = suc->dir;
            suc->dir = arv->dir;
            paisuc->esq = aux;
        }
        arv = suc;
        return arv;
    }
    else
        return sucessor(arv, suc, suc->esq);
}

// Executa a rotação LL na árvore.
TipoNo* rotacaoLL(TipoNo *pa){
    TipoNo *pb;

    pb = pa->esq;
    pa->esq = pb->dir;
    pb->dir = pa;
    pa = pb;
    return pa;
}

// Executa a rotação RR na árvore.
TipoNo* rotacaoRR(TipoNo *pa){
    TipoNo *pb;

    pb = pa->dir;
    pa->dir = pb->esq;
    pb->esq = pa;
    pa = pb;
    return pa;
}

// Executa a rotação LR na árvore.
TipoNo* rotacaoLR(TipoNo *pa){
    TipoNo *pb, *pc;

    pb = pa->esq;
    pc = pb->dir;
    pb->dir = pc->esq;
    pc->esq = pb;
    pa->esq = pc->dir;
    pc->dir = pa;
    pa = pc;
    return pa;
}

// Executa a rotação RL na árvore.
TipoNo* rotacaoRL(TipoNo *pa){
    TipoNo *pb, *pc;

    pb = pa->dir;
    pc = pb->esq;
    pb->esq = pc->dir;
    pc->dir = pb;
    pa->dir = pc->esq;
    pc->esq = pa;
    pa = pc;
    return pa;
}

// Verifica qual rotação precisa ser feita.
TipoNo* rotaciona(TipoNo *arv){
    if (calculaFB(arv) > 1){ //rotação LL
        if (calculaFB(arv->esq) > 0){
            arv = rotacaoLL(arv);
            return arv;;
        }
        if (calculaFB(arv->esq) < 0){ //rotação LR
            arv = rotacaoLR(arv);
            return arv;
        }
    }
    else if(calculaFB(arv) < -1){ // rotação RR
        if (calculaFB(arv->dir) < 0){
            arv = rotacaoRR(arv);
            return arv;
        }
        if (calculaFB(arv->dir) > 0){ //rotação RL
            arv = rotacaoRL(arv);
            return arv;
        }
    }
    else if(calculaFB(arv) < 1 && calculaFB(arv) > -1){
        return arv; 
    }
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
    else if (k == (*arv)->key)
        return;
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
    else
        return sucessor(arv, arv, arv->dir);
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

// Rebalanceia a árvore.
void rebalanceia(ArvBin *arv){
    if(*arv == NULL)
        return;
    rebalanceia(&((*arv)->esq));
    rebalanceia(&((*arv)->dir));
    if(calculaFB(*arv) > 1 || calculaFB(*arv) < -1)
        *arv = rotaciona(*arv);
}

int main(){
    int i, valor, alt, tam;
	ArvBin *arv;

    arv = inicializaArv();
    scanf("%d",&tam); // quantidade de dados a serem inseridos

    // Inserção
    for(i=0;i<tam;i++){
        scanf("%d",&valor);
        insereNo(arv,valor);
        rebalanceia(arv);
    }

    //Pesquisa
    scanf("%d",&valor);
    if(busca(arv, valor) == 0){
        insereNo(arv, valor);
        rebalanceia(arv);
    }
    else
        rebalanceia(arv);
    Imprime(*arv);
    printf("\n");

    return 0;
}