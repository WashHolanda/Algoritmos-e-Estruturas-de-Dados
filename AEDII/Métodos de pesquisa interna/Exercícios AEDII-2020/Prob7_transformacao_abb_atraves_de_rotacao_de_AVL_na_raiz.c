#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Problema 07 - Transformação de ABB através de rotação de ́ArvoreAVL na raiz
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

// Carrega dados de uma árvore digitada na entrada.
TipoNo* carrega(){
	char c;
	TipoNo *no;

	scanf("%c", &c);
	if (c == '(') {
		scanf("%c", &c);
		if (c == 'C') {
			no = (TipoNo*) malloc(sizeof(TipoNo));
			scanf("%d", &no->key);
			no->esq = carrega();
			no->dir = carrega();
			scanf("%c", &c);
		}
		else if (c == ')')
			no = NULL;
	}
	return no;
}

int calculaFB(TipoNo *arv){
    int fb;

    fb = alturaArv(arv->esq) - alturaArv(arv->dir);

    return fb;
}

TipoNo* rotacaoLL(TipoNo *pa){
    TipoNo *pb;

    pb = pa->esq;
    pa->esq = pb->dir;
    pb->dir = pa;
    pa = pb;
    return pa;
}

TipoNo* rotacaoRR(TipoNo *pa){
    TipoNo *pb;

    pb = pa->dir;
    pa->dir = pb->esq;
    pb->esq = pa;
    pa = pb;
    return pa;
}

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

TipoNo* rotaciona(TipoNo *arv){
    if (calculaFB(arv) > 1){ //rotação LL
        if (calculaFB(arv->esq) > 0){
            arv = rotacaoLL(arv);
            printf("\nLL\n");
            return arv;;
        }
        if (calculaFB(arv->esq) < 0){
            arv = rotacaoLR(arv);
            printf("\nLR\n");
            return arv;
        }
    }
    else if(calculaFB(arv) < -1){ // rotação RR
        if (calculaFB(arv->dir) < 0){
            arv = rotacaoRR(arv);
            printf("\nRR\n");
            return arv;
        }
        if (calculaFB(arv->dir) > 0){
            arv = rotacaoRL(arv);
            printf("\nRL\n");
            return arv;
        }
    } 
}

int main(){
    int i, valor, alt;
	ArvBin *arv;

    arv = inicializaArv();

    *arv = carrega(); // le arvore binaria inicial com parenteses aninhados
    alt = alturaArv(*arv); // Calcula a altura da árvore de entrada

    printf("%d\n",alt-1);
    Imprime(*arv);
    *arv = rotaciona(*arv); // faz a rotação na raiz da arvore
    alt = alturaArv(*arv);
    printf("%d\n",alt-1);
    Imprime(*arv);
    printf("\n");

    return 0;
}