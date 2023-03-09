#include <stdio.h>
#include <stdlib.h>


// CLARISSE DINIZ SILVA
// TRABALHO 01 - TABELA HASH COM LEITURA DE ARQUIVOS

typedef char string[300];

typedef struct dados{
	
	long long matricula; // inteiro de 64bits para armazenar a matricula;
	string nomeAluno;
	struct dados *prox;
	
}TDados;

// Funcoes da HASH e calculo de tamanho e módulo
int definirTamanhoHash(int tamanho);
int inicializarTamanhoHash(FILE *arq);
int calcularMod(long long numero, int tamanho);
void iniciaHash(TDados **hash, int tamanho);

// Funcoes INSERIR, BUSCAR, EXCLUIR e outras uteis para facilitar o menu

int buscaElementoLista(TDados **hash, long long numero, int tamanho);

void inserirElementoLista(TDados **hash, long long numero, string *nome, int tamanho);
void inserirElementoNaHash(TDados **hash, int tam, FILE *arquivo);
void inserirElemento(TDados **hash, long long numero, string *nome, int tamanho);
void inserirMatriculaNova(TDados **hash, int tam);
void buscaDados(TDados **hash, int tam);
void excluirDados(TDados **hash, int tam);
void percorreElementosLista(TDados **hash, int posicao);
void exibirDados(TDados **hash, int tam);
void salvarDadosArq(TDados **hash, int tam);
void menuOpcoes(TDados **hash, int num, int tam);
void menuPrincipal(TDados **hash, int tam);

long long matriculaPergunta();




