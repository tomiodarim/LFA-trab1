#ifndef AUTOMATO_H
#define AUTOMATO_H

//
//Pre-condicao:
//Pos-condicao:

typedef struct Automato{
	int estadoAtual;   
	char *alfabeto;    //string contendo os caracteres pertencentes ao alfabeto
	int *estados;      //estados do automato
	int nest;          //numero total de estados
	int *finais;       //vetor que indica quais estados sao finais
	int nfin;          //numero total de estados finais
	int *transicoes;   //matriz contendo as transicoes possiveis do automato
	int ntra;          //numero total de transicoes do automato
} Automato;

//Define o alfabeto pertencente ao automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: O alfabeto do automato e definido
void definirAlfabeto(Automato* a);

//Define os estados pertencentes ao automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: Os estados do automato sao definidos
void definirEstados(Automato* a);

//Define quais estados do automato sao finais
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: Os estados finais do automato sao definidos
void definirFinais(Automato* a);

//Define as transicoes possiveis do automato
//Pre-condicao: Um automato existente e um arquivo aberto
//Pos-condicao: As transicoes possiveis sao definidas
void definirTransicoes(Automato* a);

//Abre um arquivo e le um automato a partir dele
//Pre-condicao: Um arquivo contendo a descricao do automato
//Pos-condicao: Retorna um ponteiro para um automato caso o arquivo exista, retorna NULL caso contrario
Automato* lerAutomato();

//Checa se um caractere pertence ao alfabeto do automato aut
//Pre-condicao: Um automato existente e um caractere a ser avaliado
//Pos-condicao: Retorna 1 caso o caractere pertenca ao alfabeto, retorna 0 caso nao pertenca
int pertenceAlfabeto(Automato *aut, char letra);

//Muda o estado do automato de acordo com o caractere e as transicoes possiveis do automato
//Pre-condicao: Um automato existente com transicoes definidas e um caractere de entrada
//Pos-condicao: Retorna 1 se for possivel fazer a transicao e atualiza o estado do automato de acordo, retorna 0 se nao houver transicao possivel
int mudaEstado(Automato *aut, int letra);

//Checa se o estado atual do automato e final
//Pre-condicao: Um automato existente
//Pos-condicao: Retorna 1 se for final, retorna 0 se nao for
int isFinal(Automato *aut);

//Checa se uma palavra e aceita pelo automato
//Pre-condicao: Um automato existente e uma string (fita) a ser verificada
//Pos-condicao: Retorna 1 se a palavra for valida, retorna 0 caso contrario
int validaPalavra(Automato *aut, char palavra[]);

//Libera a memoria alocada por um automato
//Pre-condicao:Um automato existente
//Pos-condicao:A memoria e liberada
void liberaAut(Automato *aut);

#endif
