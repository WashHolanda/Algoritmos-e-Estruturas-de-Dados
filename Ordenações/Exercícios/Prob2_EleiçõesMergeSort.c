#include<stdio.h>
#include<stdlib.h>

/*
Aluno: Washington Holanda de Oliveira
RA: 112268
Turma: Integral
Tarefa 02 AED2 - 2020 - Eleições Utilizando MergeSort
*/

typedef struct{
    int op1;
    int op2;
    int op3;
}Eleitores;

typedef struct{
    int id;
    int quant;
    float porc;
}Candidatos;

void mescla (Candidatos *vet, int inicio, int meio, int fim){
	int metade1, metade2,i,j,k;
	Candidatos *temp;
	int tam = (fim-inicio)+1;	//calcula o tamanho do vetor
	metade1=inicio;	//guarda a posição que começa a primeira metade do vetor
	metade2=meio+1;	//guarda a posição que começa a segunda metade do vetor
	temp = (Candidatos *)malloc(tam*sizeof(Candidatos));	//declara um vetor temporário

	//Preenchimento do vetor temporário (vetor totalmente ordenado)
	for(i=0;i<tam;i++){
		if(metade1<=meio && metade2<=fim){	//Confere se alguma das metades já passou todos os itens para o vetor temporário
			if(vet[metade1].quant<vet[metade2].quant){	//Caso ambas as metades possuam itens ele vai comparar as duas
				temp[i]=vet[metade1];	//Caso o valor da metade 1 seja menor, ele é colocado no vetor temporário na posição i
				metade1++;	//Passa para o próximo valor da metade 1
			}
			else if(vet[metade1].quant==vet[metade2].quant){
                if(vet[metade1].id>vet[metade2].id){
                    temp[i]=vet[metade1];	//Caso o valor da metade 1 seja menor, ele é colocado no vetor temporário na posição i
                    metade1++;	//Passa para o próximo valor da metade 1
                }
                else{
                    temp[i]=vet[metade2];	//Caso o valor da metade 2 seja menor, ele é colocado no vetor temporário na posição i
                    metade2++;	//Passa para o próximo valor da metade 2
                }
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

void mergeSort (Candidatos *vet, int inicio, int fim){
	int meio;

	if(inicio!=fim){	//confere se o vetor possui um unico elemento
		meio = (inicio+fim)/2;  //calculo do meio do vetor
		mergeSort(vet,inicio,meio);	//chamada de uma nova função de mergeSort passando a primeira metade do vetor como parâmetro
		mergeSort(vet,meio+1,fim);	//chamada de uma nova função de mergeSort passando a segunda metade do vetor como parâmetro
		mescla(vet,inicio,meio,fim);	//chamada da função que irá intercalar as duas metades do vetor que foram ordenadas
	}
}

int turno1(Eleitores *E, int tamE, Candidatos *C, int tamC){
    int i,voto;
    float validos=0.0;

    for(i=0;i<tamE;i++){
        if(E[i].op1>0 && E[i].op1<=tamC){ //confere se é um voto válido
            voto = E[i].op1;
            C[voto-1].quant = C[voto-1].quant + 1; //contabiliza o voto para o candidato escolhido
            validos++; //contabiliza um voto na quantidade total de votos válidos
        }
    }

    mergeSort(C,0,tamC-1); // Ordeno do menos votado pro mais votado
    if(validos==0){
        printf("0\n");
        return 0;
    }
    else{
        C[tamC-1].porc = (C[tamC-1].quant/validos)*100; //calculo a % do mais votado
        printf("%d %.2f\n",C[tamC-1].id,C[tamC-1].porc); //imprimo a % do mais votado do 1 Turno com duas casas decimais
        if(C[tamC-1].porc>=50.00){
            return 0;
        }
        else{
            return 1;
        }
    }
}

void turno2 (Candidatos vet[],Eleitores *E, int tamE,int tamC){
    int i,voto;
    float validos=0.0;

    for(i=0;i<tamE;i++){
        voto = E[i].op1;
        if(voto==vet[0].id){
            vet[0].quant++;
            validos++;
        }
        else if(voto==vet[1].id){
            vet[1].quant++;
            validos++;
        }
        else{
            voto = E[i].op2;
            if(voto==vet[0].id){
                vet[0].quant++;
                validos++;
            }
            else if(voto==vet[1].id){
                vet[1].quant++;
                validos++;
            }
            else{
                voto = E[i].op3;
                if(voto==vet[0].id){
                    vet[0].quant++;
                    validos++;
                }
                else if(voto==vet[1].id){
                    vet[1].quant++;
                    validos++;
                }
            }
        }
    }

    mergeSort(vet,0,1); // Ordeno do menos votado pro mais votado

    vet[1].porc = (vet[1].quant/validos)*100; //calculo a % do mais votado
    printf("%d %.2f\n",vet[1].id,vet[1].porc); //imprimo a % do mais votado do 2 Turno com duas casas decimais
}

int main(){
    int V,C,i;
    Eleitores *listaE;
    Candidatos *listaC,segTurn[2];

    scanf("%d",&V);
    scanf("%d",&C);

    listaE = (Eleitores *)malloc(V*sizeof(Eleitores));
    listaC = (Candidatos *)malloc(C*sizeof(Candidatos));

    for(i=0;i<V;i++){
        scanf("%d",&listaE[i].op1);
        scanf("%d",&listaE[i].op2);
        scanf("%d",&listaE[i].op3);
    }
    for(i=0;i<C;i++){
        listaC[i].id = i+1;
        listaC[i].quant = 0;
        listaC[i].porc = 0.00;
    }

    if(turno1(listaE,V,listaC,C)){
        segTurn[0].id= listaC[C-1].id;
        segTurn[1].id= listaC[C-2].id;
        segTurn[0].quant= 0;
        segTurn[1].quant= 0;
        segTurn[0].porc= 0;
        segTurn[1].porc= 0;

        turno2(segTurn,listaE,V,C);
    }
	return 0;
}
