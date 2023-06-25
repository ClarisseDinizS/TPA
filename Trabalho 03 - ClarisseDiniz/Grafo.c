// ----------------- CLARISSE DINIZ SILVA -----------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

//=====================\ FUNCOES /===========================//

void inicializa(TRegistro *d){
    int l, c;

    strcpy(d->vertices[0], "ORADEA");
    strcpy(d->vertices[1], "ZERIND");
    strcpy(d->vertices[2], "ARAD");
    strcpy(d->vertices[3], "TIMISOARA");
    strcpy(d->vertices[4], "LUGOJ");
    strcpy(d->vertices[5], "MEHADIA");
    strcpy(d->vertices[6], "DROBETA");
    strcpy(d->vertices[7], "CRAIOVA");
    strcpy(d->vertices[8], "SIBIU");
    strcpy(d->vertices[9], "RIMNICU VILCEA");
    strcpy(d->vertices[10], "PITESTI");
    strcpy(d->vertices[11], "FAGARAS");
    strcpy(d->vertices[12], "BUCHAREST");
    strcpy(d->vertices[13], "GIUGIU");
    strcpy(d->vertices[14], "URZICENI");
    strcpy(d->vertices[15], "HIRSOVA");
    strcpy(d->vertices[16], "EFORIE");
    strcpy(d->vertices[17], "VASLUI");
    strcpy(d->vertices[18], "IASI");
    strcpy(d->vertices[19], "NEAMT");

    // Definicao da Matriz de Adjacencias
    for (l = 0; l < TAMANHO; l++)
    {
        d->estimativas[l] = -1;
        d->precendentes[l] = -1;
        d->finalizado[l] = 0;

        for (c = 0; c < TAMANHO; c++)
        {
            d->caminhos[l][c] = 0;
        } 
    }     

    // de ORADEA a ...
    d->caminhos[0][1] = 71;
    d->caminhos[0][8] = 151;

    // de ZERIND a ...
    d->caminhos[1][0] = 71;
    d->caminhos[1][2] = 75;

    // de ARAD a ...
    d->caminhos[2][1] = 75;
    d->caminhos[2][3] = 118;
    d->caminhos[2][8] = 140;

    // de TIMISOARA a ...
    d->caminhos[3][2] = 118;
    d->caminhos[3][4] = 111;

    // de LUGOJ a ...
    d->caminhos[4][3] = 111;
    d->caminhos[4][5] = 70;

    // de MEHADIA a ...
    d->caminhos[5][4] = 70;
    d->caminhos[5][6] = 75;

    // de DROBETA a ...
    d->caminhos[6][5] = 75;
    d->caminhos[6][7] = 120;

    // de CRAIOVA a ...
    d->caminhos[7][6] = 120;
    d->caminhos[7][9] = 146;
    d->caminhos[7][10] = 138;

    // de SIBIU a ...
    d->caminhos[8][0] = 151;
    d->caminhos[8][2] = 140;
    d->caminhos[8][9] = 80;
    d->caminhos[8][11] = 99;

    // de RIMNICU VILCEA a ...
    d->caminhos[9][7] = 146;
    d->caminhos[9][8] = 80;
    d->caminhos[9][10] = 97;

    // de PITESTI a ...
    d->caminhos[10][7] = 138;
    d->caminhos[10][9] = 97;
    d->caminhos[10][12] = 101;

    // de FAGARAS a ...
    d->caminhos[11][8] = 99;
    d->caminhos[11][12] = 211;

    // de BUCHAREST a ...
    d->caminhos[12][10] = 101;
    d->caminhos[12][11] = 211;
    d->caminhos[12][13] = 90;
    d->caminhos[12][14] = 85;

    // de GIUGIU a ...
    d->caminhos[13][12] = 90;

    // de URZICENI a ...
    d->caminhos[14][12] = 85;
    d->caminhos[14][15] = 98;
    d->caminhos[14][17] = 142;

    // de HIRSOVA a ...
    d->caminhos[15][14] = 98;
    d->caminhos[15][16] = 86;

    // de EFORIE a ...
    d->caminhos[16][15] = 86;

    // de VASLUI a ...
    d->caminhos[17][14] = 142;
    d->caminhos[17][18] = 92;

    // de IASI a ...
    d->caminhos[18][17] = 92;
    d->caminhos[18][19] = 87;

    // de NEAMT a ...
    d->caminhos[19][18] = 87;
}

// funcao que faz a busca do melhor caminho para seguir
void busca(int origem, int destino, TRegistro *d){
    int ultimo = origem, col, menor, menorVert;

    printf("\n\n\n\tBUSCA do MELHOR CAMINHO\n");
    printf("\t=======================\n\n");
    printf("\tORIGEM: %s\n\n", d->vertices[origem]);
    printf("\tDESTINO: %s\n\n", d->vertices[destino]);

    d->precendentes[origem] = -1;
    d->estimativas[origem] = 0;
    d->finalizado[origem] = 1;

	// enquanto nao encontra o ultimo local, vai visitando todas as cidades encontrando o melhor caminha
    while (ultimo != destino){
        printf("\n\tVisitando: %s (%d km)", d->vertices[ultimo], d->estimativas[ultimo]);

        for (col = 0; col < TAMANHO; col++){

            if (d->finalizado[col] == 0){

                if (d->caminhos[ultimo][col] > 0){
                    if (origem == d->precendentes[col]){
                        d->estimativas[col] = d->caminhos[ultimo][col];
                    }
                    else{
                        d->estimativas[col] = d->caminhos[ultimo][col] + d->estimativas[ultimo];
                    }
                    d->precendentes[col] = ultimo;
                } 
            }     
        }         
		
		// utiliza a funcao para encontra a menor estimativa
        menorVert = encontreMenorEstimativa(d);

        ultimo = menorVert;
        d->finalizado[ultimo] = 1;
	
	// ao finalizar, exibe todas as cidades em que foram passada.
        exibe(d);
    } 

    geraCaminho(d, origem, destino);
}

// funcao que exibe todas as cidades que foram passadas e seus precedentes
void exibe(TRegistro *d){
    int pos;

    printf("\n\n");
    printf("+==============| INICIO |===========================================================+\n");

    for (pos = 0; pos < TAMANHO; pos++){
        printf("INDICE: (%d) NOME: %s\t", pos, d->vertices[pos]);
        printf("ESTIMATIVA: %d\tPRECENDENTE: %d", d->estimativas[pos], d->precendentes[pos]);
        printf("\tFINALIZADO: %d\n", d->finalizado[pos]);
        printf("\n-----------------------------------------------------------------------------------\n");
    } // for

    printf("+==============| FIM |===========================================================+\n\n");
}

// funcao para encontrar a menor estimativa do caminha
int encontreMenorEstimativa(TRegistro *d){
    int menorVert = -1, menor, col, flag = 0;

    for (col = 0; col < TAMANHO; col++){
        if (d->finalizado[col] == 0){

            if (d->estimativas[col] > -1){

                if ((flag == 0) || (d->estimativas[col] < menor)){
                    menor = d->estimativas[col];
                    menorVert = col;
                    flag = 1;
                } 
            }     
        }         
    }             
    return menorVert;
}

// funcao de gera o caminho, junto com o peso e as cidades que foram passadas
void geraCaminho(TRegistro *d, int origem, int destino){
    int atual, l;

    printf("\n\n\n\t\t>>> RESULTADO FINAL <<<\n\n");
    printf("\t\t  (CAMINHO ENCONTRADO)\n\n");

    atual = destino;
    do{
        printf("\t%s", d->vertices[atual]);
        if (atual == destino){
            printf("   (%d)\n", d->estimativas[atual]);
        }
        else{
            printf("\n");
        }
        atual = d->precendentes[atual];
    } while (atual > -1);

    printf("\n\n\n");

    for (l = 0; l < TAMANHO; l++){
        d->estimativas[l] = -1;
        d->precendentes[l] = -1;
        d->finalizado[l] = 0;
    }
}

// menu para permitir que o usuario faca outra busca ou sair do programa
void menu(TRegistro *d){
    int origem, destino;

    do{
        printf("Informe o codigo de origem: ");
        scanf("%d", &origem);
    } while (origem > TAMANHO || origem < 0);

    do{
        printf("Informe o codigo de destino: ");
        scanf("%d", &destino);
    } while (destino > TAMANHO || destino < 0);

    opcoes(d, origem, destino);
}

// Menu de opcoes do programa
void opcoes(TRegistro *d, int origem, int destino){
    
	int opcao;
    busca(origem, destino, d);

    do{
        printf("0 - Sair");
        printf("\n1 - Continuar");
        printf("\n\tEscolha a opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        system("CLS");
    } while (opcao != 0 && opcao != 1);

    switch (opcao){
    case 1:
        menu(d);
        break;

    default:
        break;
    }
}

int main(){
	
    TRegistro dados;
    inicializa(&dados);
    menu(&dados);
}
