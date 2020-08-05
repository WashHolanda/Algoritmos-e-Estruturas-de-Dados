#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 01 AED2 - 2020 - Mesclar vetores ordenados
*/

void mescla (int *vet1, int tam1, int *vet2, int tam2){
	int *vet,tam,i;
	int aux1=0;
	int aux2=0;
	tam = tam1+tam2;
	vet = (int*) malloc((tam)*sizeof(int));
	
	//Preenchimento do vetor temporário (vetor totalmente ordenado)
	for(i=0;i<tam;i++){
		if(aux1<tam1 && aux2<tam2){
			if(vet1[aux1]<vet2[aux2]){
				vet[i]=vet1[aux1];
				aux1++;
			}
			else{
				vet[i]=vet2[aux2];
				aux2++;
			}
		}
		else{	
			if(aux2>=tam2){
				vet[i]=vet1[aux1];
				aux1++;
			}
			else{
				vet[i]=vet2[aux2];
				aux2++;
			}
		}
	}
	imprime(vet,tam);
	free(vet);
}

void imprime(int *vet,int n){
	int i;
	for(i=0;i<n-1;i++){
		printf("%d ",vet[i]);
	}
	printf("%d\n",vet[i]);
}


int main(){
	int i,n1,n2;
	int *vet1,*vet2;
	
	scanf("%d",&n1);
	vet1 = (int *)malloc(n1*sizeof(int));
	
	for(i=0;i<n1;i++){
		scanf("%d",&vet1[i]);
	}
	
	scanf("%d",&n2);
	vet2 = (int *)malloc(n2*sizeof(int));
	
	for(i=0;i<n2;i++){
		scanf("%d",&vet2[i]);
	}
	
	mescla(vet1,n1,vet2,n2);
	return 0;
}
