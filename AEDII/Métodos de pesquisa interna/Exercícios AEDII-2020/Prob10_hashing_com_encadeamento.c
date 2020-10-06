#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 10 – Pesquisa Interna – Hashing com Encadeamento
*/

typedef struct TipoItem{
    int key;
    struct TipoItem *prox;
}TipoItem;

typedef struct TipoHash{
    TipoItem **inicio;
}TipoHash;

// Inicializa o Hash
void inicializaHash(TipoHash *tab, int tam){
    int i;
    
    tab->inicio = malloc(tam*sizeof(TipoItem*));
    
    for(i=0;i<tam;i++){
        tab->inicio[i];
    }
}

// Imprime os itens de uma posição do Hash.
void imprimePos(TipoItem *tab){
    int i;

    if(tab != NULL){
        printf("%d ",tab->key);
        imprimePos(tab->prox);
    }
}

// Pesquisa se um dado está na tabela.
int pesquisa(TipoItem *tab, int num){
    while (tab != NULL){
        if(tab->key == num)
            return 1;
        tab = tab->prox;
    }
    return 0;
}

// Insere um novo valor na tabela.
TipoItem* insercao(TipoItem* tab, int num){
    TipoItem *novo;

    if(tab != NULL){
        if(tab->prox != NULL)
            insercao(tab->prox, num);
        else{
            novo = (TipoItem*) malloc(sizeof(TipoItem));
            tab->prox = novo;
            tab->prox->key = num;
            tab->prox->prox = NULL;
        }
    }
    else{
        novo = (TipoItem*) malloc(sizeof(TipoItem));
        novo->key = num;
        novo->prox = NULL;
        return novo;
    }
    return tab;
}

// Remove um valor informado da tabela.
TipoItem* remocao(TipoItem* tab, int num){
    TipoItem *aux;

    aux = tab;
    if(tab->key == num){
        tab = tab->prox;
        free(aux);
    }
    else{
        while (aux->prox->key != num){
            aux = aux->prox;
        }
        aux->prox = aux->prox->prox;  
    }
    return tab;
}

int main(){
    int tam,qtd,num,i,j,pos;
    TipoHash tab;

    scanf("%d",&tam);
    inicializaHash(&tab, tam);

    // Inserção
    scanf("%d",&qtd);

    for(i=0;i<qtd;i++){
        scanf("%d",&num);
        pos = num % tam;
        tab.inicio[pos] = insercao(tab.inicio[pos], num);    
    }

    // Pesquisa
    scanf("%d",&num);
    pos = num % tam;
    if (pesquisa(tab.inicio[pos], num))
        tab.inicio[pos] = remocao(tab.inicio[pos], num);
    else{
        pos = num % tam;
        tab.inicio[pos] = insercao(tab.inicio[pos], num);
    }

    for(i=0;i<tam;i++){
        printf("[%d] ",i);
        imprimePos(tab.inicio[i]);
        printf("\n");
    }

    return 0;
}