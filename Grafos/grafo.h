#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char string[100];

typedef struct adjacencia {
    int vertice; // vertice de destino 
    int distancia; // distancia associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; // O próximo elemento da lista de adjacencias
}ADJACENCIA;

typedef struct vertice {
    /* Dados armazenados vão aqui */
    ADJACENCIA *cab; //possui apenas a cabeça da lista de adjacencia
    string nome;// nome do vertice
}VERTICE;

typedef struct grafo { //lembrando que cada grafo possui:
    int vertices; // numero de vertice total do grafo
    int arestas; // numero de arestas totais do grafo
    VERTICE *adj; // Arranjo de vertices da estrutura
}GRAFO;

GRAFO * inicializaGrado(GRAFO *gr);
GRAFO *criaGrafo (int vertices);
ADJACENCIA *criaAdj(int v, int distancia);
int criaAresta(GRAFO *grafo, char* nome, int verticeInicial, int verticeFinal, int distancia);
void imprime(GRAFO *grafo);