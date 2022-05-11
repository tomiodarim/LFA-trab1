#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main(void) {
  Automato *aut; char palavra[100];
	printf("Trabalho de Linguagens Formais e Automatos\nAmin Ismail, Gustavo Ayala e Lucas Tomio Darim\n\n");
	aut = lerAutomato();
	printf("Entre com a palavra a ser validada (ou -1 para sair):  ");
  scanf("%[^\n]%*c", palavra);
	while(palavra[0] != '-' || palavra[1] != '1'){
		aut->estadoAtual = 0;
		if(validaPalavra(aut, palavra)) printf("ACEITA\n\n");
		else printf("REJEITA\n\n");
		printf("Entre com a palavra a ser validada (ou -1 para sair): ");
		scanf("%[^\n]%*c", palavra);
	}
  liberaAut(aut);
  return 0;
}
