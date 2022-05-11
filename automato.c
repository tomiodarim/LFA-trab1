#include <stdlib.h>
#include <stdio.h>
#include "automato.h"

FILE *f; //arquivo contendo a descricao do automato

//Define o alfabeto pertencente ao automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: O alfabeto do automato e definido
void definirAlfabeto(Automato* a){
	char c1, c2=','; int i;
  a->alfabeto = (char *) malloc(1000);
	fscanf(f, "alfabeto={");
	for(i = 0; c2 != '}'; i++){
		fscanf(f, "%c%c", &c1, &c2);
		a->alfabeto[i] = c1; 
	}
	a->alfabeto[i] = '\0';
  a->alfabeto = realloc(a->alfabeto ,i);
	fscanf(f, "\n");
}

//Define os estados pertencentes ao automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: Os estados do automato sao definidos
void definirEstados(Automato* a){
	char c=','; int i, n;
  a->estados = (int *) malloc (sizeof(int)*1000);
	fscanf(f, "estados={");
	for(i = 0; c != '}'; i++){
		fscanf(f, "q%d%c", &n, &c);
		a->estados[i] = n; 
	}
	a->nest = i;
  a->estados = (int *) realloc (a->estados, sizeof(int)*i);
	fscanf(f, "\n");
}

//Define quais estados do automato sao finais
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: Os estados finais do automato sao definidos
void definirFinais(Automato* a){
	char c=','; int i, n;
  a->finais = (int *) malloc (sizeof(int)*1000);
	fscanf(f, "finais={");
	for(i = 0; c != '}'; i++){
		fscanf(f, "q%d%c", &n, &c);
		a->finais[i] = n; 
	}
	a->nfin = i;
  a->finais = (int*) realloc (a->finais, sizeof(int)* i);
	fscanf(f, "\n");
}

//Define as transicoes possiveis do automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: As transicoes possiveis sao definidas
void definirTransicoes(Automato* a){
	int i, n1, n2, offset; char c;
  a->transicoes = (int *) malloc (sizeof(int) * 3 * 1000); //cria uma matriz 3x1000
	for(i = offset = 0; !feof(f); i++, offset += 3){         //o offset e usado para tratar o vetor do malloc como matriz
		fscanf(f, "(q%d,%c)= q%d%*c", &n1, &c, &n2);  
		a->transicoes[offset] = n1;   
		a->transicoes[offset + 1] = c;
		a->transicoes[offset + 2] = n2;
	}
	a->ntra = i;
  a->transicoes = (int *) realloc (a->transicoes, sizeof(int) * 3 * i); //a quantidade linhas e atualizada
}

//Abre um arquivo e le um automato a partir dele
//Pre-condicao: Um arquivo contendo a descricao do automato
//Pos-condicao: Retorna um ponteiro para um automato caso o arquivo exista, retorna NULL caso contrario
Automato* lerAutomato(){
	Automato *a; char nomeArquivo[100];

	printf("Entre com o arquivo do automato: ");
	scanf("%[^\n]%*c", nomeArquivo);

	f = fopen(nomeArquivo, "r");

	if(feof(f)){
		fclose(f);
		return NULL;
	}

	a = (Automato*) malloc(sizeof(Automato));
	definirAlfabeto(a);
	definirEstados(a);
	definirFinais(a);
	definirTransicoes(a);
	fclose(f);
	
	return a;
}

//Checa se um caractere pertence ao alfabeto do automato a
//Pre-condicao: Um automato existente e um caractere a ser avaliado
//Pos-condicao: Retorna 1 caso o caractere pertenca ao alfabeto, retorna 0 caso nao pertenca
int pertenceAlfabeto(Automato *aut, char letra){
	int i;
	for(i = 0; aut->alfabeto[i]; i++)
		if(letra == aut->alfabeto[i])
			return 1;
	return 0;
}

//Muda o estado do automato de acordo com o caractere e as transicoes possiveis do automato
//Pre-condicao: Um automato existente com transicoes definidas e um caractere de entrada
//Pos-condicao: Retorna 1 se for possivel fazer a transicao e atualiza o estado do automato de acordo, retorna 0 se nao houver transicao possivel
int mudaEstado(Automato *aut, int letra){
	int i, offset;
	for(i = offset =0; i < aut->ntra; i++, offset += 3){
		if(aut->estadoAtual == aut->transicoes[offset] && letra == aut->transicoes[offset + 1]){
			aut->estadoAtual = aut->transicoes[offset + 2];
			return 1;
		}
	}
	return 0;
}

//Checa se o estado atual do automato e final
//Pre-condicao: Um automato existente
//Pos-condicao: Retorna 1 se for final, retorna 0 se nao for
int isFinal(Automato *aut){
	int i;
	for(i = 0; i < aut->nfin; i++)
		if(aut->estadoAtual == aut->finais[i]) return 1;
	return 0;
}

//Checa se uma palavra e aceita pelo automato
//Pre-condicao: Um automato existente e uma string a ser verificada
//Pos-condicao: Retorna 1 se a palavra for valida, retorna 0 caso contrario
int validaPalavra(Automato *aut, char palavra[]){
	int i; char *aux = palavra;
	if(palavra[0] == '@'){
		printf("[q0]@\n");
		if(isFinal(aut))
			return 1;
		return 0;
	}
	for(i = 0; palavra[i]; i++){
		printf("[q%d]%s\n", aut->estadoAtual, aux++);
		if(!pertenceAlfabeto(aut, palavra[i])) return 0;
		if(!mudaEstado(aut, palavra[i])) return 0;
	}
	printf("[q%d]%s\n", aut->estadoAtual, aux++);
	if(isFinal(aut)) return 1;
	return 0;
}

//Libera a memoria alocada por um automato
//Pre-condicao:Um automato existente
//Pos-condicao:A memoria e liberada
void liberaAut(Automato *aut){
  free(aut->alfabeto);
	free(aut->estados);
  free(aut->finais);
	free(aut->transicoes);
  free(aut);
}