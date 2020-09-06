#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 02 - Ordena��o interna - MergSort
*/

void intercala (int *vet, int inicio, int meio, int fim){
	int *temp, metade1, metade2,i,j,k;
	int tam = (fim-inicio)+1;	//calcula o tamanho do vetor
	metade1=inicio;	//guarda a posi��o que come�a a primeira metade do vetor
	metade2=meio+1;	//guarda a posi��o que come�a a segunda metade do vetor
	temp = (int*) malloc((tam)*sizeof(int));	//declara um vetor tempor�rio
	
	//Preenchimento do vetor tempor�rio (vetor totalmente ordenado)
	for(i=0;i<tam;i++){
		if(metade1<=meio && metade2<=fim){	//Confere se alguma das metades j� passou todos os itens para o vetor tempor�rio
			if(vet[metade1]<vet[metade2]){	//Caso ambas as metades possuam itens ele vai comparar as duas
				temp[i]=vet[metade1];	//Caso o valor da metade 1 seja menor, ele � colocado no vetor tempor�rio na posi��o i
				metade1++;	//Passa para o pr�ximo valor da metade 1
			}
			else{
				temp[i]=vet[metade2];	//Caso o valor da metade 2 seja menor, ele � colocado no vetor tempor�rio na posi��o i
				metade2++;	//Passa para o pr�ximo valor da metade 2
			}
		}
		else{	
			if(metade2>fim){ //caso a metade2 tenha passado todos os seus valores para o vetor tempor�rio, o restante do vetor � preenchido com os valores da metade 1
				temp[i]=vet[metade1];
				metade1++;
			}
			else{//caso a metade1 tenha passado todos os seus valores para o vetor tempor�rio, o restante do vetor � preenchido com os valores da metade 2
				temp[i]=vet[metade2];
				metade2++;
			}
		}
	}
	//copia o vetor tempor�rio (j� ordenado) pro vetor original
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
		mergSort(vet,inicio,meio, tam);	//chamada de uma nova fun��o de mergeSort passando a primeira metade do vetor como par�metro
		mergSort(vet,meio+1,fim, tam);	//chamada de uma nova fun��o de mergeSort passando a segunda metade do vetor como par�metro
		intercala(vet,inicio,meio,fim);	//chamada da fun��o que ir� intercalar as duas metades do vetor que foram ordenadas
		imprime(vet,tam);
	}
}

int main(){
	int i,N;
	int *vet;
	
	//Leitura do valor correspondente a quantidade de n�meros de entrada
	scanf("%d",&N);
	vet = (int *)malloc(N*sizeof(int));
	
	//Leitura dos n�meros que ser�o ordenados
	for(i=0;i<N;i++){
		scanf("%d",&vet[i]);
	}
	mergSort(vet,0,N-1,N);
	
	return 0;
}
