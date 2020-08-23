#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 04 - Ordenação Interna - HeapSort
*/

void maxheapfy(int *arv, int i, int tam){
	int aux, max;
	int left = (2*i)+1;
	int right = (2*i)+2;

	//printf("%d %d %d\n",arv[i], arv[left],arv[right]);

	if ((left<=tam) && (arv[left] > arv[i])){
		 max = left;
	}
	else{
		max = i;
	}
	if ((right<=tam) && (arv[right] > arv[max])){
		max = right;
	}
	if (max != i){
		aux = arv[i];
		arv[i] = arv[max];
		arv[max]=aux;
		maxheapfy(arv, max, tam);
	}
}

void buildMaxHeap (int *arv, int tam){
	int i;
	for(i=tam/2;i>=0;i--){	
		maxheapfy(arv, i, tam);
	}
}

int heapExtractMax (int *arv, int tam){
	int max;

	if (tam < 0) printf("erro!\n");
	
	max = arv[0];
	arv[0] = arv[tam];
	maxheapfy(arv, 0, tam);

	return max;
}

void heapSort(int *arv, int tam){
	int i, n;
	int *vet;
	
	buildMaxHeap(arv, tam-1);

	//Impressão do Heap pronto
	for(i=0;i<tam-1;i++){
		printf("%d ",arv[i]);
	}
	printf("%d\n",arv[i]);

	vet = (int *)malloc(tam*sizeof(int)); //vetor saída
	n = tam - 1;

	while (n>=0){
		vet[n] = heapExtractMax(arv,n);
		n--;
	}

	//Impressão do vetor totalmente ordenado
	for(i=0;i<tam-1;i++){
		printf("%d ",vet[i]);
	}
	printf("%d\n",vet[i]);
	
	free(vet);
}

int main(){
	int i,tam;
	int *arv;
	
	//Leitura do valor correspondente a quantidade de números de entrada
	scanf("%d",&tam);
	arv = (int *)malloc(tam*sizeof(int));
	
	//Leitura dos números que serão ordenados
	for(i=0;i<tam;i++){
		scanf("%d",&arv[i]);
	}

	heapSort(arv, tam);
	
	free(arv);
	return 0;
}
