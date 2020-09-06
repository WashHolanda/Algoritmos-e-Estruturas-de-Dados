#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 04 - Ordenação interna - RadixSort
*/

void countingSort (int *vet,int tam, int exp){
	int i,aux;
	int soma=0;
	int vetB[tam];
	int contador[10];
	
	for(i=0;i<10;i++){	//inicializa vetor contador(vetor C) com 0
		contador[i]=0;
	}
	for (i=0;i<tam;i++){	//conta quantos valores de cada algarismo em determinada casa decimal o vetor possui
        aux=(vet[i]/exp)%10;	// de acordo com o expoente passado como parâmetro é armazenado em aux o algarismo correspondente daquela casa decimal
		contador[aux]++;	// contabiliza 1 na posição correspondente daquele algarismo
	}
	for(i=0;i<10;i++){	// percorre o vetor contador (vetor C) somando seus elementos
		if(i==0){	// a primeira posição não altera. Porém a variavel soma deve receber o valor dessa primeira posição
			soma=contador[i];
		}
		else{	// Nas demais posições a variavel soma será a soma acumulada de todas as posições anteriores
			soma+=contador[i];
			contador[i]=soma;	// a soma acumulada é armazenada na posição atual do laço
		}
	}
	for(i=tam-1;i>=0;i--){	// percorre, começando no final, o vetor passando cada valor para a posição correta, de forma o vetor B fique ordenado do menor valor da casa decimal passada para a função (exp) para o maior
		aux=(vet[i]/exp)%10;
		vetB[contador[aux]-1]=vet[i];	// usando o vetor contador (vetor C) os valores são colocados no vetor B já na posição correta
		contador[aux]--;	// Decrementa 1 na posição do algarismo no qual o valor já foi colocado na posição correta                                                              
	}
	for(i=0;i<tam-1;i++){	// Copia os valores do vetor auxiliar B para o vetor principal, além de imprimir esses valores
		vet[i]=vetB[i];
		printf("%d ",vet[i]);
	}
	vet[i]=vetB[i];
	printf("%d\n",vet[i]);
}

void radixSort (int *vet, int tam){
	int i,exp;
	int maior=vet[0];
	
	for(i=0;i<tam-1;i++){	// Busca no vetor qual é o seu maior valor
		if(vet[i]>maior){
			maior=vet[i];
		}
	}
	for(exp=1;maior/exp>0;exp*=10){	// Chama a função de ordenação para cada casa decimal até chegar na maior casa decimal do maior valor encontrado anteriormente
		countingSort(vet,tam,exp);
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
	radixSort(vet,N);
	
	return 0;
}
