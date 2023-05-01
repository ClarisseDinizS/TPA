#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// Inicializa a arvore
TNo *inicializaArvore(TNo **nodo){
    (*nodo) = NULL;
}
// Cria o no da arvore
TNo *criaNo(long long matricula, string *nome){
    TNo *novo = (TNo *)malloc(sizeof(TNo));
    novo->matricula = matricula;
    strcpy(novo->nome, (*nome));
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
// Insercao do no na Arvore
TNo *insere(TNo **nodo, long long matricula, string *nome){
    if ((*nodo) == NULL){
        (*nodo) = criaNo(matricula, nome);
    }
    
	else if (matricula < (*nodo)->matricula){
        (*nodo)->esq = insere(&(*nodo)->esq, matricula, nome);
    }
    
    else if (matricula > (*nodo)->matricula){
	
        (*nodo)->dir = insere(&(*nodo)->dir, matricula, nome);
    }
    
	else{
        printf("\n\tAluno %s com a matricula %lld ja existe\n", (*nodo)->nome, (*nodo)->matricula);
    } 
    return (*nodo);
}
// Insere na arvore todas as matriculas e nomes do arquivo
void inserirNaArvore(TNo **nodo){
    FILE *arquivo;
    string nome;
    long long matricula = 0;
    int i;

    if ((arquivo = fopen("Lista_Aluno_Matricula_Atual.txt", "r")) == NULL)// leitura do arquivo
        printf("Arquivo nao encontrado!");
    else
    {
        while (!feof(arquivo))
        {
            fgets(nome, sizeof(nome), arquivo);
            fscanf(arquivo, "%lld\n", &matricula);

            insere(nodo, matricula, &nome);
        }
    }
    fclose(arquivo);
}

// Insere um novo numero da arvore
void inserir(TNo **nodo){
    long long matricula;
    string nome;
	
	// solicita a nova matricula
    printf("\tInsira a matricula: ");
    scanf("%lld", &matricula);
	getchar();
	
	// pega o novo nome ligado a matricula
    printf("\tInsira o nome: ");
    fgets(nome, sizeof(nome), stdin);

    insere(nodo, matricula, &nome);
}

// Funcao para remover o no da arvore
TNo *remover(TNo **nodo, long long matricula){
    
	if ((*nodo) == NULL){
        // interrompe
        return NULL;
    }
    
	else if ((*nodo)->matricula > matricula){
        // desce pela esquerda
        (*nodo)->esq = remover(&(*nodo)->esq, matricula);
    }
    
	else if ((*nodo)->matricula < matricula){
        // desce pela direita
        (*nodo)->dir = remover(&(*nodo)->dir, matricula);
    }
    
	else{
        // Encontrou Nó a ser removido...
        if ((*nodo)->dir == NULL && (*nodo)->esq == NULL){
            // No a ser removido NÂO tem FILHOS.
            free(*nodo);
            (*nodo) = NULL;
        }
        
		else if ((*nodo)->esq == NULL){
            // No a ser removido tem apenas FILHO à DIREITA.
            TNo *temporario = (*nodo);
            (*nodo) = (*nodo)->dir;
            free(temporario);
        }
        
		else if ((*nodo)->dir == NULL){
            // No a ser removido tem apenas FILHO à ESQUERDA.
            TNo *temporario = (*nodo);
            (*nodo) = (*nodo)->esq;
            free(temporario);
        }
        
		else{
            // No tem dois FILHOS.
            TNo *prov = (*nodo)->esq;
            while (prov->dir != NULL){
                prov = prov->dir;
            } 
            // Trocando os dados entre os nodos ...
            (*nodo)->matricula = prov->matricula;
            prov->matricula = matricula;

            (*nodo)->esq = remover(&(*nodo)->esq, matricula);
        }
    }
    return (*nodo);
}
// Remove valor da arvore
void removerValor(TNo **nodo){
    long long numero;

    printf("\tInsira o numero: ");
    scanf("%lld", &numero);

    remover(nodo, numero);
}
// Imprime em ordem
void caminhamento_em_ordem(TNo *nodo){
    
	if (nodo != NULL){
        caminhamento_em_ordem(nodo->esq);
        printf("\n\tMatricula: %lld", nodo->matricula);
        printf("\n\tNome: %s", nodo->nome);
        caminhamento_em_ordem(nodo->dir);
    } 
}
// Imprime em pre ordem
void caminhamento_pre_ordem(TNo *nodo){
    
	if (nodo != NULL){
        printf("\n\tMatricula: %lld", nodo->matricula);
        printf("\n\tNome: %s", nodo->nome);
        caminhamento_pre_ordem(nodo->esq);
        caminhamento_pre_ordem(nodo->dir);
    } 
}
// Imprime em pos ordem
void caminhamento_pos_ordem(TNo *nodo){
    if (nodo != NULL)
    {
        caminhamento_pos_ordem(nodo->esq);
        caminhamento_pos_ordem(nodo->dir);
        printf("\n\tMatricula: %lld", nodo->matricula);
        printf("\n\tNome: %s", nodo->nome);
    } 
}
// Busca no na árvore
void buscarNo(TNo **nodo, long long procurado){
    
	// nao encontrou nenhum valor na arvore
	if ((*nodo) == NULL){
        printf("\n<<VALOR INEXISTENTE NA ARVORE>>\n\n\n");
    }
    
    //encontrou o valor nas primeiras posicoes
    else if ((*nodo)->matricula == procurado){
        printf("\n<<ENCONTRADO>>\n\n\n");
        printf("\n\tMatricula: %lld", (*nodo)->matricula);
        printf("\n\tNome: %s", (*nodo)->nome);
    }
    
	// vai descendo pelo lado esquerdo visitando os nos ate encontrar o valor
	else if ((*nodo)->matricula > procurado){
        printf("\nPROCURADO: %lld\tVISITADO: %lld", procurado, (*nodo)->matricula);
        printf("\n\n... Descendo pela Sub-Arvore ESQUERDA.");
        buscarNo(&(*nodo)->esq, procurado);
    }
    
	// vai descendo pelo lado direito visitando os nos ate encontrar o valor
    else{
        printf("\nPROCURADO: %lld\tVISITADO: %lld", procurado, (*nodo)->matricula);
        printf("\n\n... Descendo pela Sub-Arvore DIREITA.");
        buscarNo(&(*nodo)->dir, procurado);
    }
}

// Busca valor na arvore
void buscaValor(TNo **nodo, long long procurado){
    
	// arvore esta vazia, sem elementos
	if ((*nodo) == NULL){
        printf("\n\n\tArvore VAZIA ... Impossivel iniciar busca de %lld.\n\n", procurado);
    }
   	
	   // inicia a busca pela arvores e seus nos
	else{
        printf("\n\n\tIniciando BUSCA pelo valor %lld", procurado);
        printf("\n\n\tVisitando a RAIZ (%lld).\n", (*nodo)->matricula);
        buscarNo(nodo, procurado);
    }
}

// Busca valor
void buscar(TNo **nodo){
    long long numero;

    printf("\tInsira o numero: ");
    scanf("%lld", &numero);
	buscaValor(nodo, numero);
}

// Salva no arquivo os novos registros da arvore
void salvarRegistros(TNo **nodo, FILE *arquivo){
    
    //escreve os novos valores dentro da arvore
	fprintf(arquivo, "%lld\n%s", (*nodo)->matricula, (*nodo)->nome);
    
	//lado esquerdo
	if ((*nodo)->esq){
		salvarRegistros(&(*nodo)->esq, arquivo);
	}
     //lado direito   
    if ((*nodo)->dir){
    	salvarRegistros(&(*nodo)->dir, arquivo);
	}
        
}

// Salva no arquivo os novos registros da arvore
void salvar(TNo **nodo){
    int i;
    FILE *arquivo;
	arquivo = fopen("Lista_Aluno_Matricula_Atual.txt", "w"); // leitura do arquivo
	
	// salva as novas alteracoes dentro do arquivo
    salvarRegistros(nodo, arquivo);
	fclose(arquivo); // fecha o arquivo

    printf("\n\tArquivo salvo com sucesso!\n");
}

// Menu de opcoes: Inserir, buscar, remover, imprimir em pre, pos e em ordem
void menu(TNo **nodo){
    int op;
    do
    {
        printf("\n\n----------	|| MENU ||	--------------\n\n");
        printf("\t0. Sair\n");
        printf("\t1. INSERIR novo aluno\n");
        printf("\t2. REMOVER aluno\n");
        printf("\t3. BUSCAR aluno\n");
        printf("\t4. SALVAR base de dados\n");
        printf("\t5. IMPRIMIR em pre ordem\n");
        printf("\t6. IMPRIMIR em ordem\n");
        printf("\t7. IMPRIMIR em pos ordem\n");

        printf("Escolha a opcao: ");
        scanf("%d", &op);
        
        switch (op){
		    case 1:
		        inserir(nodo);
		        break;
		        
		    case 2:
		        removerValor(nodo);
		        break;
		        
		    case 3:
		        buscar(nodo);
		        break;
		        
		    case 4:
		        salvar(nodo);
		        break;
		        
		    case 5:
		        caminhamento_pre_ordem(*nodo);
		        break;
		        
		    case 6:
		        caminhamento_em_ordem(*nodo);
		        break;
		        
		    case 7:
		        caminhamento_pos_ordem(*nodo);
		        break;
		        
		    case 0:
		        break;
		        
		    default:
		        printf("\t\nNao existe essa opcao!");
		        break;
    	}
	} while (op != 0);
}

int main(){
    TNo *raiz;
    inicializaArvore(&raiz);
    inserirNaArvore(&raiz);
    menu(&raiz);
}
