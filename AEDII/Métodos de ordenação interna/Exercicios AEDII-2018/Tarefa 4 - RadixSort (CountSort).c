#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Noturno
Tarefa 04 - Ordena��o interna - RadixSort
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
        aux=(vet[i]/exp)%10;	// de acordo com o expoente passado como par�metro � armazenado em aux o algarismo correspondente daquela casa decimal
		contador[aux]++;	// contabiliza 1 na posi��o correspondente daquele algarismo
	}
	for(i=0;i<10;i++){	// percorre o vetor contador (vetor C) somando seus elementos
		if(i==0){	// a primeira posi��o n�o altera. Por�m a variavel soma deve receber o valor dessa primeira posi��o
			soma=contador[i];
		}
		else{	// Nas demais posi��es a variavel soma ser� a soma acumulada de todas as posi��es anteriores
			soma+=contador[i];
			contador[i]=soma;	// a soma acumulada � armazenada na posi��o atual do la�o
		}
	}
	for(i=tam-1;i>=0;i--){	// percorre, come�ando no final, o vetor passando cada valor para a posi��o correta, de forma o vetor B fique ordenado do menor valor da casa decimal passada para a fun��o (exp) para o maior
		aux=(vet[i]/exp)%10;
		vetB[contador[aux]-1]=vet[i];	// usando o vetor contador (vetor C) os valores s�o colocados no vetor B j� na posi��o correta
		contador[aux]--;	// Decrementa 1 na posi��o do algarismo no qual o valor j� foi colocado na posi��o correta                                                              
	}
	for(i=0;i<tam-1;i++){	// Copia os valores do vetor auxiliar B para o vetor principal, al�m de imprimir esses valores
		vet[i]=vetB[i];
		printf("%d ",vet[i]);
	}
	vet[i]=vetB[i];
	printf("%d\n",vet[i]);
}

void radixSort (int *vet, int tam){
	int i,exp;
	int maior=vet[0];
	
	for(i=0;i<tam-1;i++){	// Busca no vetor qual � o seu maior valor
		if(vet[i]>maior){
			maior=vet[i];
		}
	}
	for(exp=1;maior/exp>0;exp*=10){	// Chama a fun��o de ordena��o para cada casa decimal at� chegar na maior casa decimal do maior valor encontrado anteriormente
		countingSort(vet,tam,exp);
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
	radixSort(vet,N);
	
	return 0;
}
