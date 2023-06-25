#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

GRAFO * inicializaGrado(GRAFO *gr){

	gr = criaGrafo(20);
    
    //ORADEA ATE ...
    criaAresta(gr, "ORADEA", 0, 1, 71);//ZERIND
    criaAresta(gr, "ORADEA", 0, 8, 151);//SIBIU

    //ZERIND ATE ...
    criaAresta(gr, "ZERIND", 1, 0, 71);//ORADEA
	criaAresta(gr, "ZERIND", 1, 2, 75);//ARAD

    //ARAD ATE ...
	criaAresta(gr, "ARAD", 2, 1, 75);//ZERIND
	criaAresta(gr, "ARAD", 2, 3, 118);//TIMISOARA
    criaAresta(gr, "ARAD", 2, 8, 140);//SIBIU
	
    //TIMISOARA ATE ...
    criaAresta(gr, "TIMISOARA", 3, 2, 118);//ARAD
    criaAresta(gr, "TIMISOARA", 3, 4, 111);//LUGOJ
	
    //LUGOJ ATE ...
    criaAresta(gr, "LUGOJ", 4, 3, 111);//TIMISOARA
    criaAresta(gr, "LUGOJ", 4, 5, 70);//MEHADIA
	
    //MEHADIA ATE ...
    criaAresta(gr, "MEHADIA", 5, 4, 70);//LUGOJ
    criaAresta(gr, "MEHADIA", 5, 6, 75);//DROBETA
    
    //DROBETA ATE ...
    criaAresta(gr, "DROBETA", 6, 5, 75);//MEHADIA
    criaAresta(gr, "DROBETA", 6, 7, 120);//CRAIOVA
    
    //CRAIOVA ATE ...
    criaAresta(gr, "CRAIOVA", 7, 6, 120);//DROBETA
    criaAresta(gr, "CRAIOVA", 7, 9, 146);//RIMNICU VILCEA
	criaAresta(gr, "CRAIOVA", 7, 10, 138);//RIMNICU VILCEA
    
    //SIBIU ATE ...
    criaAresta(gr, "SIBIU", 8, 0, 151);//ORADEA
    criaAresta(gr, "SIBIU", 8, 2, 140);//ARAD
    criaAresta(gr, "SIBIU", 8, 9, 80);//RIMNICU VILCEA
    criaAresta(gr, "SIBIU", 8, 11, 99);//FAGARAS
    
    //RIMNICU VILCEA ATE ...
    criaAresta(gr, "RIMNICU VILCEA", 9, 7, 146);//CRAIOVA
    criaAresta(gr, "RIMNICU VILCEA", 9, 8, 80);//SIBIU
	criaAresta(gr, "RIMNICU VILCEA", 9, 10, 97);//PITESTI

	//PITESTI ATE ...
    criaAresta(gr, "PITESTI", 10, 7, 146);//CRAIOVA
    criaAresta(gr, "PITESTI", 10, 9, 97);//RIMNICU VILCEA
	criaAresta(gr, "PITESTI", 10, 12, 101);//BUCHAREST

	//FAGARAS ATE ...
    criaAresta(gr, "FAGARAS", 11, 8, 99);//SIBIU
    criaAresta(gr, "FAGARAS", 11, 12, 211);//BUCHAREST

	//BUCHAREST ATE ...
    criaAresta(gr, "BUCHAREST", 12, 10, 101);//PITESTI
    criaAresta(gr, "BUCHAREST", 12, 11, 211);//FAGARAS
	criaAresta(gr, "BUCHAREST", 12, 13, 90);//GIUGIU
	criaAresta(gr, "BUCHAREST", 12, 14, 85);//URZICENI

	//GIUGIU ATE ...
    criaAresta(gr, "GIUGIU", 13, 12, 90);//BUCHAREST

	//URZICENI ATE ...
    criaAresta(gr, "URZICENI", 14, 12, 85);//BUCHAREST
    criaAresta(gr, "URZICENI", 14, 15, 98);//HIRSOVA
	criaAresta(gr, "URZICENI", 14, 17, 142);//VASLUI

	//HIRSOVA ATE ...
    criaAresta(gr, "HIRSOVA", 15, 14, 98);//URZICENI
    criaAresta(gr, "HIRSOVA", 15, 16, 86);//EFORIE

	//EFORIE ATE ...
    criaAresta(gr, "EFORIE", 16, 15, 86);//HIRSOVA

	//VASLUI ATE ...
    criaAresta(gr, "VASLUI", 17, 14, 142);//URZICENI
    criaAresta(gr, "VASLUI", 17, 18, 93);//IASI

	//IASI ATE ...
    criaAresta(gr, "IASI", 18, 17, 92);//VASLUI
    criaAresta(gr, "IASI", 18, 19, 87);//NEAMT

	//NEAMT ATE ...
    criaAresta(gr, "NEAMT", 19, 18, 87);//IASI

	return gr;
}

// Funcao para criar um GRAFO
GRAFO *criaGrafo (int vertices) {
	int i;
	
	GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO)); //aloca espaco para estrtura grafo
	grafo->vertices = vertices; //atualizo o numero de vertice
	grafo->arestas = 0;  //atualizo o numero de vertice
	grafo->adj = (VERTICE *)malloc(vertices*sizeof(VERTICE)); //ler abaixo
	
	//Dentro da estrturua tem so o arranjo para o ponteiro de vertice, nao o arranjo em si 	
	// entao aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<vertices; i++){ 
		grafo->adj[i].cab=NULL; //coloco NULL em todas arestas
	}
	return(grafo);
}

//Funcao para adicionar arestas no GRAFO
ADJACENCIA *criaAdj(int v, int distancia){ 
	
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA)); //aloca espaco para um no
	temp->vertice =v; //vertice alvo da adjacencia
	temp->distancia = distancia; //distancia da aresta
	temp->prox = NULL; 
	
	return(temp); //retorno endereco da adjacencia
}

int criaAresta(GRAFO *grafo, char* nome, int verticeInicial, int verticeFinal, int distancia){ //vai de verticeInicial a verticeFinal
	if(!grafo) return (0);  //validacoes se o grafo existe 
	if((verticeFinal<0)||(verticeFinal >= grafo->vertices))return(0); //validacoes se os valores nao sao neg
	if((verticeInicial<0)||(verticeFinal >= grafo->vertices))return(0); //ou maiores que o numero de vertice do grafo
	
	ADJACENCIA *novo = criaAdj(verticeFinal, distancia); //crio adjacencia com o vertice final e o distancia
	//coloco a adjacencia na lista do vertice inicial
	novo->prox = grafo->adj[verticeInicial].cab; //o campo prox da adjacencia vai receber a cabeca da lista
	grafo->adj[verticeInicial].cab=novo; // e a cabeca da lista passa a ser o novo elemento
    strcpy(grafo->adj[verticeInicial].nome, nome);
	grafo->arestas++; // atualizo o numero de aresta no grafo
	return (1);
}

void imprime(GRAFO *grafo){
	//validacoes se o grafo existe 
	
	printf("Cidades: %d\tCaminho: %d\n\n",grafo->vertices,grafo->arestas); //imprime numero de vertice e arestas
	int i;
	
	for(i=0; i<grafo->vertices; i++){
		printf("Origem: %s\n", grafo->adj[i].nome);
		ADJACENCIA *ad = grafo->adj[i].cab; //chamo a cabeca da lista de adjacencia desta aresta
			
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("\tDestino: %s\n\tDistancia: %d\n\n", grafo->adj[ad->vertice].nome, ad->distancia); //imprimo a adjacencia e seu distancia
				ad=ad->prox; //passo para proxima adjacencia
			}
		printf("\n");	
	}
}

void main(){
	GRAFO *gr;

    gr = inicializaGrado(gr);
	imprime(gr);
}
