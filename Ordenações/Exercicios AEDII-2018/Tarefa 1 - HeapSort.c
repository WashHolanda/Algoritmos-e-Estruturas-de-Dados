#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 01 - Ordenação Interna - HeapSort
*/

//3 4 9 2 5 1 8

int* refaz(int *arvBin,int tam, int i, int controle){
	int aux,raiz_sub;
	
	if((2*i)+1>=tam){
		if((2*i)+1==tam && controle==1){
			if(arvBin[i]<arvBin[(2*i)+1]){
				aux=arvBin[(2*i)+1];
				arvBin[(2*i)+1]=arvBin[i];
				arvBin[i]=aux;	
			}
		}
		return;
	}
	
	if(arvBin[i]<arvBin[(2*i)+1] || arvBin[i]<arvBin[(2*i)+2]){
		if(arvBin[(2*i)+1]>arvBin[(2*i)+2]){
			aux=arvBin[(2*i)+1];
			arvBin[(2*i)+1]=arvBin[i];
			arvBin[i]=aux;
			raiz_sub=(2*i)+1;
		}
		else{
			aux=arvBin[(2*i)+2];
			arvBin[(2*i)+2]=arvBin[i];
			arvBin[i]=aux;
			raiz_sub=(2*i)+2;
		}
	}
	else{
		return;
	}
	if((2*i)+1<tam){
		refaz(arvBin,tam,raiz_sub,controle);
	}
	return;
}

int* constroi(int *arvBin,int tam){
	int i;
	for(i=tam-1;i>=0;i--){	
		refaz(arvBin,tam,i,0);	//Passa o valor da raíz para a função refaz, sendo esse valor decrementado fazendo com que todas as sub-arvores sejam refeitas
	}
}

int* ordena(int *arvBin,int tam){
	int i,j,aux;
	for(i=tam-1;i>0;i--){
		aux=arvBin[0];
		arvBin[0]=arvBin[i];	//Troca primeiro valor com o último
		arvBin[i]=aux;
		refaz(arvBin,i-1,0,1);	//Após a troca refaz o heap
		for(j=0;j<tam-1;j++){
			printf("%d ",arvBin[j]);
		}
		printf("%d\n",arvBin[j]);
	}
}

int main(){
	int i,N;
	int *arvBin;
	
	//Leitura do valor correspondente a quantidade de números de entrada
	scanf("%d",&N);
	arvBin = (int *)malloc(N*sizeof(int));
	
	//Leitura dos números que serão ordenados
	for(i=0;i<N;i++){
		scanf("%d",&arvBin[i]);
	}
	constroi(arvBin,N); // Chamada da função que irá refazer o heap
	
	//Impressão do Heap pronto
	for(i=0;i<N-1;i++){
		printf("%d ",arvBin[i]);
	}
	printf("%d\n",arvBin[i]);
	
	ordena(arvBin,N);
	

	free(arvBin);
	return 0;
}
