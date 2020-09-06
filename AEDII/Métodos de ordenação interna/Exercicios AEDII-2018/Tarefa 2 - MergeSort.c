#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 02 - Ordenação interna - MergSort
*/

void intercala (int *vet, int inicio, int meio, int fim){
	int *temp, metade1, metade2,i,j,k;
	int tam = (fim-inicio)+1;	//calcula o tamanho do vetor
	metade1=inicio;	//guarda a posição que começa a primeira metade do vetor
	metade2=meio+1;	//guarda a posição que começa a segunda metade do vetor
	temp = (int*) malloc((tam)*sizeof(int));	//declara um vetor temporário
	
	//Preenchimento do vetor temporário (vetor totalmente ordenado)
	for(i=0;i<tam;i++){
		if(metade1<=meio && metade2<=fim){	//Confere se alguma das metades já passou todos os itens para o vetor temporário
			if(vet[metade1]<vet[metade2]){	//Caso ambas as metades possuam itens ele vai comparar as duas
				temp[i]=vet[metade1];	//Caso o valor da metade 1 seja menor, ele é colocado no vetor temporário na posição i
				metade1++;	//Passa para o próximo valor da metade 1
			}
			else{
				temp[i]=vet[metade2];	//Caso o valor da metade 2 seja menor, ele é colocado no vetor temporário na posição i
				metade2++;	//Passa para o próximo valor da metade 2
			}
		}
		else{	
			if(metade2>fim){ //caso a metade2 tenha passado todos os seus valores para o vetor temporário, o restante do vetor é preenchido com os valores da metade 1
				temp[i]=vet[metade1];
				metade1++;
			}
			else{//caso a metade1 tenha passado todos os seus valores para o vetor temporário, o restante do vetor é preenchido com os valores da metade 2
				temp[i]=vet[metade2];
				metade2++;
			}
		}
	}
	//copia o vetor temporário (já ordenado) pro vetor original
	k=inicio;
	for(j=0;j<tam;j++){
		vet[k]=temp[j];
		k++;	
	}
	free(temp);
}

void imprime(int *vet,int N){
	int i;
	for(i=0;i<N-1;i++){
		printf("%d ",vet[i]);
	}
	printf("%d\n",vet[i]);
}

void mergSort (int *vet, int inicio, int fim, int tam){
	int meio,i;
	
	if(inicio!=fim){	//confere se o vetor possui um unico elemento
		meio = (inicio+fim)/2;  //calculo do meio do vetor
		mergSort(vet,inicio,meio, tam);	//chamada de uma nova função de mergeSort passando a primeira metade do vetor como parâmetro
		mergSort(vet,meio+1,fim, tam);	//chamada de uma nova função de mergeSort passando a segunda metade do vetor como parâmetro
		intercala(vet,inicio,meio,fim);	//chamada da função que irá intercalar as duas metades do vetor que foram ordenadas
		imprime(vet,tam);
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
	mergSort(vet,0,N-1,N);
	
	return 0;
}
