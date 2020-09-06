#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 03 - Quicksort é estável?
*/

typedef struct{
    char nome[15];
    int idade;
}Pessoa;

//Função que faz o algoritmo de partição usando mediana de 3 valores
int particiona (Pessoa *vet,int inicio,int fim){
    Pessoa aux;
	int i = inicio-1;
	int j = inicio;
    int medianaIndice = 0;
    int meio = (inicio+fim)/2;
    int a = vet[inicio].idade;  
    int b = vet[meio].idade;
    int c = vet[fim].idade; 

    //Encontra a mediana para usa-lá como pivo
    if(a < b){
        if(b < c) medianaIndice = meio; //a < b  && b <  c
        else{ 
            if(a < c) medianaIndice = fim; //a < c  && c <= b
            else medianaIndice = inicio; //c <= a && a <  b
        }
    }
    else{
        if(c < b) medianaIndice = meio; //c < b && b <= a
        else{
            if(c < a) medianaIndice = fim; //b <= c && c < a
            else medianaIndice = inicio; //b <= a && a <= c
        }
    }

    //coloca o elemento da mediana no fim
    aux = vet[medianaIndice];
    vet[medianaIndice] = vet[fim];
    vet[fim] = aux;

	while(j<fim){
		if(vet[j].idade <= vet[fim].idade){
            i++;
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;
			j++;
		}
		else j++;
	}

	aux = vet[i+1];
    vet[i+1] = vet[j];
	vet[j] = aux;
    return i+1;	
}
//Função QuickSort principal
void quickSort (Pessoa *vet, int inicio, int fim){
	int pivo;
	
	if(inicio<fim){
		pivo = particiona(vet, inicio, fim);
		quickSort(vet,inicio,pivo-1);
        quickSort(vet,pivo+1,fim);
	}
}

/* Verifica se a ordenacao foi estavel */
void estavel(Pessoa *aux, Pessoa  *vet, int tam){
    int i,j,flag;

    for(i=0;i<tam-1;i++){
        if(vet[i].idade == vet[i+1].idade){
            for(j=0;j<tam;j++){
                if(!strcmp(aux[j].nome,vet[i].nome) || !strcmp(aux[j].nome,vet[i+1].nome) ){
                    if(!strcmp(aux[j].nome,vet[i].nome)) j = tam;
                    else{
                        printf("no\n");
                        return;
                    }
                }
            }
        }
    }
    printf("yes\n");
}

int main(){
	int i, p, m,tam;
	Pessoa *vet, *aux;
	
	scanf("%d",&tam);
	vet = (Pessoa *)malloc(tam*sizeof(Pessoa));
    aux = (Pessoa *)malloc(tam*sizeof(Pessoa));
	
	for(i=0;i<tam;i++){
        scanf("%s",vet[i].nome);
		scanf("%d",&vet[i].idade);
	}

    scanf("%d",&p);
    p--;
    scanf("%d",&m);
    m = p + m;
    for(i=0;i<tam;i++){ // duplica o vetor de entrada
        strcpy(aux[i].nome,vet[i].nome);
        aux[i].idade = vet[i].idade;
    }

	quickSort(vet,0,tam-1);
    estavel(aux,vet,tam);

    for(i=p;i<m;i++){
		if(i>=tam) break;
        printf("%s %d\n",vet[i].nome, vet[i].idade);
	}
    
	free(vet);
    free(aux);
	return 0;
}
