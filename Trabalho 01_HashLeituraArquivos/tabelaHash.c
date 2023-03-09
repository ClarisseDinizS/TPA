#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "hash.h"

// CLARISSE DINIZ SILVA
// TRABALHO 01 - TABELA HASH COM LEITURA DE ARQUIVOS

// ----------------- FUNCOES -----------------

// Função para calcular o tamanho da hash
int definirTamanhoHash(int tamanho){
	// divisão por 2 (Aluno e Matrícula) e 1,5 é o ideal numero primo
	tamanho = (tamanho/2) * 1.5; 
	return tamanho;
}

// Funcao para ler a qtde de linhas do arquivo e retornar o calculo do tamanho da hash
int inicializarTamanhoHash(FILE *arq){
	
	char c;
	int tam = 0;
	
	// Condicao para leitura do arquivo
	if ((arq = fopen("Lista_Aluno_Matricula.txt", "r")) == NULL)
        printf("O arquivo não existe!\n"); // Msg a ser mostrada na tela, caso o arquivo não seja encontrado
    else
        while ((c = fgetc(arq)) != EOF) // Enquanto não encontrar o EOF(Final do arquivo)
            if (c == '\n') // procura a quebra de linha
                tam++; // soma o tamanho
    fclose(arq);
    tam++;

    tam = definirTamanhoHash(tam); // funcao para calcular o tamanho da hash
	return tam;
	
}

// Inicializacao da tabela hash
void iniciaHash(TDados **hash, int tamanho){
    int i;
    // Repeticao para colocar NULL em todas as posicoes da hash inicialmente
    for (i = 0; i < tamanho; i++){ 
    	hash[i] = NULL;
	}      
}

//funcao para calcular o módulo
int calcularMod(long long numero, int tamanho)
{
    int mod;
    // ele pega a chave e divide pelo tamanho para saber em qual posicao será armazenado o dado
    mod = numero % tamanho;
    return mod;
}

//Busca na lista a matricula e retorna 1 se encontrar e 0 se não encontrar
int buscaElementoLista(TDados **hash, long long numero, int tamanho){
	
	// calcula o módulo para encontrar a posicao do elemento
    int posicao = calcularMod(numero, tamanho); 
    TDados *lista = hash[posicao]; // coloca a posicao achada no módulo na hash

    while (lista != NULL){
        if (numero == lista->matricula)
            return 1; // retorna 1 se encontrar o dado
        lista = lista->prox;
    }
    return 0;
}

void inserirElementoLista(TDados **hash, long long numero, string *nome, int tamanho){
    int posicao = calcularMod(numero, tamanho); // calcula o módulo para encontrar a posicao do elemento
    TDados **lista = &hash[posicao]; // passa a posicao achada no módulo na hash

    if (*lista == NULL){ // lista vazia
        
		*lista = (TDados *)malloc(sizeof(TDados)); // alocacao dinamica
        if (*lista == NULL){
            printf("\nErro na alocacao da memoria!"); // Mensagem de erro caso a alocacao nao seja feita
            exit(1);
        }
        
        (*lista)->matricula = numero; // recebe o numero da matricula
        strcpy((*lista)->nomeAluno, (*nome)); // copia o valor da 2 string (nome) para a variavel do nome
        (*lista)->prox = NULL;
		
		// Confirma a insercao na hash e mostra a quantidade de posicoes
        printf("\n\tInserido hash[%d]", posicao); 
    }
    else{ // Lista possui elementos 
	 	
		 // tratamento de colisao
        printf("\n\tColisao  hash[%d]", posicao); // mostra a posicao em que houve colisao

        TDados *armazena = hash[posicao]; // guarda a posicao do inicio do ponteiro

        while ((*lista)->prox != NULL)
            // Verifica fim da lista caso contenha mais de 2 numeros
            *lista = (*lista)->prox;

        (*lista)->prox = (TDados *)malloc(sizeof(TDados)); // alocacao dinamica
        
		if ((*lista)->prox == NULL) // erro de alocacao
        {
            printf("\nErro na alocacao da memoria!");
            exit(1);
        }

        *lista = (*lista)->prox;
        (*lista)->matricula = numero; // pega o valor da matricula e adiciona na variavel
        strcpy((*lista)->nomeAluno, (*nome)); // copia a segunda string (nome) para a variavel
        (*lista)->prox = NULL; // seta a proxima prosicao como NULL 

        hash[posicao] = armazena; // retornando ponteiro para a posicao do inicio
    }
}

//Insere na tabelas os dados do arquivo (alunos e matriculas)
void inserirElementoNaHash(TDados **hash, int tam, FILE *arq){
    string nome;
    long long numero = 0;
    int i;
    int vetorMatricula[13]; // vetor definido com a quantidade de numeros na matricula
    char *c;
	
	// leitura do arquivo e verificacao se encontrou o arquivo
    if ((arq = fopen("Lista_Aluno_Matricula.txt", "r")) == NULL)  // "r" para abrir o arquivo para leitura desde o inicio dele
        printf("Arquivo nao encontrado!");
    
	else { // achou o arquivo
        while (!feof(arq)){ // enquanto não acha o fim o arquivo
            fgets(nome, sizeof(nome), arq); // pega a string do arquivo
            fscanf(arq, "%lld\n", &numero);
			
			// calcula o modulo para encontrar a posicao do elemento
            int posicao = calcularMod(numero, tam); 

            if (hash[posicao] != NULL){ // if para tentar encontrar a matricula dada
                if (buscaElementoLista(hash, numero, tam)){ // busca na hash e retorna a mensagem abaixo se encontrar
                    printf("O item %d ja foi cadastrado", numero);
                    return;
                }
            }
            inserirElementoLista(hash, numero, &nome, tam); // insere o elemento na lista
        }
    }
    fclose(arq); // fechamento do arquivo
}

// Funçao para inserir o elemento apenas
void inserirElemento(TDados **hash, long long numero, string *nome, int tamanho)
{
    int posicao = calcularMod(numero, tamanho); // pegar a posicao para inserir o elemento
	
	// Bloco para encontrar o elemento e verificar se ele já foi cadastrado ou nao
    if (hash[posicao] != NULL) {
        if (buscaElementoLista(hash, numero, tamanho)){ 
            printf("O item %d ja foi cadastrado", numero);
            return;
        }
    }
    inserirElementoLista(hash, numero, nome, tamanho); // usa a funcao para inserir o elemento na tabela hash
} 

// Funcao criada para simplificar o menu na hora de colocar uma nova matricula
void inserirMatriculaNova(TDados **hash, int tam){
    
	long long numero;
    string nome;

    printf("\tInsira a matricula: ");
    scanf("%lld", &numero);

    getchar();
    printf("\tInsira o nome: ");
    fgets(nome, sizeof(nome), stdin);

    inserirElemento(hash, numero, &nome, tam);
}

//Funcao para facilitar o menu -- Apenas a pergunta para poder pesquisar alguma matricula
long long matriculaPergunta(){ // tipo long long apenas para retornar a matricula
    long long numero;

    printf("\tInforme a matricula:: ");
    scanf("%lld", &numero);

    return numero;
} 

// funcao par buscar a matricula na tabela e exibir ela para o usuario
void buscaDados(TDados **hash, int tam){
    long long numero = matriculaPergunta(); // recebe o numero da matricula
    int posicao = calcularMod(numero, tam); // pegar a posicao da chave passada
    int exibe = 0;
    TDados *lista = hash[posicao];

    while (lista != NULL){ // enquanto a lista tiver elementos
        if (numero == lista->matricula) { // se chave for igual a matricula adicionada na lista
            printf("\n\tHash[%d] -> Matricula: %lld \n\t\tNome: %s", posicao, lista->matricula, lista->nomeAluno);
            exibe = 1;
        }
        lista = lista->prox; // busca no proximo elemento
    }

    if (!exibe){ // se a variavel exibir continuar como 0, a matricula nao foi encontrada
    	printf("\n Matricula nao encontrada!");
	}
        
}
// funcao para excluir elementos da lista pela chave (matricula)
void excluirDados(TDados **hash, int tam){
    
	long long numero = matriculaPergunta(); // recebe o valor da matricula desejada
    int posicao = calcularMod(numero, tam); // pega a posicao 
	
	// procura a chave desejada dentro da tabela
    if (!buscaElementoLista(hash, numero, tam)){ // 
        printf("\nMatricula nao encontrada!\n");
        return;
    }
	
    TDados **lista = &hash[posicao];
    TDados *anterior = *lista;
    TDados *proximo = (*lista)->prox;
    TDados *guarda = hash[posicao]; // guarda posicao do ponteiro

    while (*lista != NULL){ // percorre a lista enquanto ela não achar o fim dela
        
		if ((*lista)->matricula == numero){ // Se encontrou o item
            
			if (*lista == anterior){ // Encontrou a matricula no INICIO
                
				if ((*lista)->prox == NULL){ // Se a lista s? tem 1 elemento
                    free(*lista);
                    hash[posicao] = NULL;
                }
                else {
                    (*lista)->prox = proximo->prox;
                    (*lista)->matricula = proximo->matricula;
                    strcpy((*lista)->nomeAluno, proximo->nomeAluno);
                    hash[posicao] = guarda;
                }
            }
            
			else{ //  A matricula NAO ESTA no inicio da lista
                anterior->prox = proximo;
                free(*lista);
                hash[posicao] = guarda;
            }
            printf("\n\tMatricula removida com sucesso!\n");
            return;
        } 
        
		anterior = *lista;
        *lista = (*lista)->prox;
        proximo = (*lista)->prox;
    } // fim do while da lista

    hash[posicao] = guarda; // pega o ponteiro para posicao inicial
    // libera os espacos da memoria
	free(anterior);
    free(proximo);
    free(guarda);
}

// funcao para percorrer a lista e mostrar antes do menu se inseriu ou não os elementos do arquivo
void percorreElementosLista(TDados **hash, int posicao){
    TDados *lista = hash[posicao];
	
	// enquanto tiver elemento, ele mostra o nome e matricula
    while (lista != NULL){
        printf(" Matricula: %lld\n\t\tNome: %s \t\t->", lista->matricula, lista->nomeAluno);
        lista = lista->prox;
    }
    // se não, printa NUL
    printf(" NULL");
}

// mostra a tabela hash com a quantidade de posicoes e se possui ou nao valores em cada um delas
void exibirDados(TDados **hash, int tam){ 
    int i;
	
	printf(" ----- TABELA HASH ELEMENTOS -----");
    printf("\n");
    for (i = 0; i < tam; i++){
        printf("\n\tHash[%d] ->", i);
        percorreElementosLista(hash, i); // usa a funcao de percorrer para mostrar se possui ou nao dados em cada posicao da lista
    }
}

//Salva os dados alterados e adicionados novamento dentro do arquivo txt
void salvarDadosArq(TDados **hash, int tam){
    int i;
    FILE *arq;
    TDados *lista;

    arq = fopen("Lista_Aluno_Matricula.txt", "w"); // abertura do arquivo

    for (i = 0; i < tam; i++){
        lista = hash[i];
        while (lista != NULL){
        	// fprintf escreve no arquivo txt os novos dados inseridos ou alterados
            fprintf(arq, "%s", lista->nomeAluno);
            fprintf(arq, "%lld\n", lista->matricula);
            lista = lista->prox;
        }
    }
    fclose(arq); // fecha o arquivo

    printf("\nBase de Dados salva com sucesso!\n");
}

// Menu de opcoes
void menuOpcoes(TDados **hash, int num, int tamanho){
    switch (num)
    {
    case 0:
        break;
    case 1:
        inserirMatriculaNova(hash, tamanho);
        break;
    case 2:
        buscaDados(hash, tamanho);
        break;
    case 3:
        excluirDados(hash, tamanho);
        break;
    case 4:
        exibirDados(hash, tamanho);
        break;
    case 5:
        salvarDadosArq(hash, tamanho);
        break;
    default:
        printf("\t\nOPCAO INVALIDA!");
        break;
    }
}

// Menu para exibir as opcoes para o usuario
void menuPrincipal(TDados **hash, int tam){
    int opcao;
    do
    {
        printf("\n\n----------	MENU DE OPCOES --------------\n\n");
        printf("\t1 - Inserir Aluno\n");
        printf("\t2 - Buscar Aluno\n");
        printf("\t3 - Remover Aluno\n");
        printf("\t4 - Imprimir dados da tabela\n");
        printf("\t5 - Salvar dados\n");
        printf("\t0 - Sair\n");

        printf("Informe sua opcao: ");
        scanf("%d", &opcao);
		
		// funcao de opcoes com cada funcao acima
        menuOpcoes(hash, opcao, tam);

    } while (opcao != 0);
}

// MAIN simplificada por causa das funcoes de perguntas e afins
void main() {
    int tamanho;
    FILE *arquivo;
	
	// Inicializacao do tamanho da hash pelo arquivo lido
    tamanho = inicializarTamanhoHash(arquivo);
    TDados *hash[tamanho];
	
	//inicializa a lista
    iniciaHash(hash, tamanho);
	
	// insere os valores na tabela hash
    inserirElementoNaHash(hash, tamanho, arquivo);
	
	// menu de opcoes com as funcoes de INSERIR, BUSCAR, REMOVER, IMPPRIMIR E SALVAR
    menuPrincipal(hash, tamanho);
}






