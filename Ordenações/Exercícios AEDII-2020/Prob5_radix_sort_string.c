#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* a = 97 (portanto subtrair 96 pra obter a opção e fazer um if pra tratar o space 32)
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Problema 5 – Ordenação Linear aplicada a strings
*/

typedef struct{
    char nome[15];
    int tam;
}Pessoa;

void countingSort (Pessoa *vet,int tam, int k){
	int i,aux;
	int soma=0;
	Pessoa *vetB;
    vetB = (Pessoa *)malloc(tam*sizeof(Pessoa));
	int C[27];
	
    //inicializa vetor C com 0 em todas as posições
	for(i=0;i<27;i++){
		C[i]=0;
	}

    //percorre a primeira letra de cada nome contabilizando 1 na letra correspondente no vetor C
	for (i=0;i<tam;i++){
        // Confere se o nome i já foi totalmente percorrido, se sim, considera o restante dos caracteres faltantes como space (posição 0)
        if (vet[i].tam < k + 1){
            C[0]++;
        }
        else{
            // converte o caracter para inteiro de acordo com a tabela ASCII
            aux = (int) vet[i].nome[k];
            //se for uma letra maíuscula a mesma é convertida para minúscula
            if (aux >= 65 && aux <= 90)  {
                aux = aux + 32;
                vet[i].nome[k] = aux;
            }
            //define a posição certa para aquele caracter no vetor C
            aux = aux - 96;
            // contabiliza 1 na posição correspondente daquele algarismo
            C[aux]++;
        }
	}

    // percorre o vetor C fazendo a soma acumulada dos seus elementos
	for(i=0;i<26;i++){
		// caso seja a primeira posição a variavel soma irá receber o primeiro valor
        if(i==0){
            soma = C[i];
            printf("%d ",soma);
        }
		else{	// Nas demais posições a variavel soma será a soma acumulada de todas as posições anteriores
			soma += C[i];
			C[i] = soma; // a soma acumulada é armazenada na posição atual do vetor
            printf("%d ",C[i]);
		}
	}
    soma += C[i];
	C[i] = soma; // a soma acumulada é armazenada na posição atual do vetor
    printf("%d\n",C[i]);

	for(i=tam-1;i>=0;i--){	// percorre, começando no final, o vetor passando cada valor para a posição correta, de forma  que o vetor B fique ordenado do menor valor da casa decimal passada para a função (exp) para o maior
		aux = (int) vet[i].nome[k];
        aux = aux - 96;
        if(aux < 1 || aux > 26) aux = 0;
		vetB[C[aux]-1] = vet[i];	// usando o vetor C os valores são colocados no vetor B já na posição correta
		C[aux]--;                                             
	}

    // Copia os valores do vetor auxiliar B para o vetor principal
    for(i=0;i<tam;i++){	
		vet[i] = vetB[i];
    }
}

void radixSort (Pessoa *vet, int maior, int tam){
	int i;

	for(i=maior-1;i>= 0;i--){	
		countingSort(vet, tam, i);
	}
}

int main(){
	int i, p, m,tam, maior;
	Pessoa *vet;
	
	//Leitura do valor correspondente a quantidade de itens de entrada
	scanf("%d",&tam);
	vet = (Pessoa *)malloc(tam*sizeof(Pessoa));
	
	//Leitura dos itens que serão ordenados
	for(i=0;i<tam;i++){
		scanf("%s",vet[i].nome);
        vet[i].tam = strlen(vet[i].nome);
        if (i == 0) maior = vet[i].tam;
        if(vet[i].tam > maior) maior = vet[i].tam;
	}

    scanf("%d",&p);
    p--;
    scanf("%d",&m);
    m = p + m;

	radixSort(vet, maior, tam);

    for(i=p;i<m;i++){
		if(i>=tam) break;
        printf("%s\n",vet[i].nome);
	}

	return 0;
}
