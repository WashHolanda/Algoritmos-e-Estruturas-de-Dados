#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 03 - Ordenação interna - QuickSort
*/

int particiona (int *vet,int inicio,int fim){
	int aux;
	int i = inicio-1;
	int j = inicio;
	int pivo = fim;
	
	while(j<fim){
		if(vet[j]<=vet[pivo]){
			aux=vet[j];
			vet[j]=vet[i+1];
			vet[i+1]=aux;
			i++;
			j++;
		}
		else{
			j++;
		}
	}
	aux=vet[i+1];
	vet[i+1]=vet[j];
	vet[j]=aux;
	return i+1;	
}

void imprime(int *vet,int N){
	int i;
	for(i=0;i<N-1;i++){
		printf("%d ",vet[i]);
	}
	printf("%d\n",vet[i]);
}

void quickSort (int *vet, int inicio, int fim, int tam){
	int pivo;
	
	if(inicio<fim){
		pivo = particiona(vet, inicio, fim);
		imprime(vet,tam);
		quickSort(vet,inicio,pivo-1,tam);
		quickSort(vet,pivo+1,fim,tam);
	}
}

int main(){
	int i,N;
	int *vet;
	
	//Leitura do valor correspondente a quantidade de números de entrada
	scanf("%d",&N);
	vet = (int *)malloc(N*sizeof(int));
	
	//Leitura dos números que serão ordenados
	for(i=0;i<N;i++){
		scanf("%d",&vet[i]);
	}
	quickSort(vet,0,N-1,N);
	free(vet);
	return 0;
}
