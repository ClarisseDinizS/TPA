#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

// função para inicializar lista com os valores nulos
void inicializaLista(TLista *list){
	list->inicio = NULL;
	list->fim = NULL;
	list->total=0;
}

// Função para inserir os elementos na lista sempre no fim (Sem ordenar)
void inserirElemento(TLista *list, int num) {
	
	if(num == NULL) {
		printf("Não existe valor!");
		return;
	}
	
	TElemento *novo = (TElemento *) malloc(sizeof(TElemento));
	novo->valor = num;
	novo->prox = NULL;

	if(list->inicio == NULL) {
		list->inicio = novo;
		list->fim = novo;
		list->total = 1; } 
	else {
		list->fim->prox = novo;
		list->fim = novo;
		list->total++;}
		
	printf("Elemento adicionado na lista!");
}

/*// Teste para ordenar os valores 
(Compara valores maiores e menores para colocar na ordem correta)
		
		atual = lista->inicio;
		anterior = NULL;
		
		while(atual != NULL){
			if(atual->valor >= novo->valor){
				novo->prox = atual;
				if(anterior == NULL) 
					lista->inicio = novo;
				else 
					anterior->prox = novo;
					inserido = 1; 
					lista->total++;
				break; 
			}
		anterior = atual;
		atual = atual->prox;
		}
		if(!inserido){
			
			lista->fim->prox = novo; 
			lista->fim = novo;
		}
	
	}
}*/

// Mostrar a lista inteira
void exibir_lista(TLista *list){
	if(list->inicio == NULL){
		printf("\nNão existem elementos na lista. Está vazia!");
	}
	else{
		TElemento *atual = NULL;
		atual = list->inicio;
		
		while(atual != NULL){
			printf("\t%d\n", atual->valor);
			atual = atual->prox;
		}
	}
}

// Função para excluir elementos da lista
void excluirElemento(TLista *list, int argumento){
	TElemento *atualValor, *anterior;
	
	atualValor = list->inicio;
	anterior = NULL;

	
	while (atualValor != NULL){
		// Busca pelo elemento a ser excluído
		if (atualValor->valor == argumento){
			if (anterior == NULL){
				list->inicio = atualValor->prox;
			}	
			else{
				anterior->prox = atualValor->prox;
			}
			if (atualValor == list->fim){
				list->fim = NULL;
			}
			//Exclusão do elemento
			free(atualValor);
			break;
		} 
		anterior = atualValor;
		atualValor = atualValor->prox;
	} 
}

//Menu para informar as opções para o usuário
int menu(){
	
	int opcao;
	
	// Menu simples para informar as opções para o usuário
	do{
		printf("\n------- Bem Vindo ao Menu -------");
		printf("\n1 - Adicionar elemento na lista");
		printf("\n2 - Remover elemento da lista");
		printf("\n3 - Mostrar lista");
		printf("\n0 - Sair do programa");
		
		printf("\n\nInforme a opcao desejada:");
		
		scanf("%d", &opcao);
		
	}while((opcao < 0) || (opcao > 3));
	
	return opcao;
}

int main(int argc, const char * argv[]){
	TLista l;
	inicializaLista(&l);
	int opcao, num;
	
	// Loop para exibir o menu e as opções enquanto a escolha for diferente de 0
	do{
		opcao = menu();
			switch(opcao){
		
				case 1:
					printf("Digite o elemento que deseja inserir: ");
					scanf("%d", &num);
					inserirElemento(&l, num);
					break;
				
				case 2:
					printf("Digite o elemento que deseja remover: ");
					scanf("%d", &num);
					excluirElemento(&l,num);
					break;
					
				case 3:
					exibir_lista(&l);
					break;
					
				default:
					break;
		}	
	} while(opcao != 0);
	
	return 0;	

}





