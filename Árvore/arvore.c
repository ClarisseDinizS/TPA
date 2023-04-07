// CLARISSE DINIZ SILVA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// Inicializacao da arvore
TNo *inicializaArvore(TNo **nodo){
    
	// Inicia o nodo como nulo
	(*nodo) = NULL;
}

// Criacao do no na arvore
TNo *criaNo(int valor){
    
	// aplica NULL em todos os valores e dados para insercao de novos dados
	TNo *novo = (TNo *)malloc(sizeof(TNo));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    
    // retorna o novo no
    return novo;
}

// Insercao do no dentro da arvore
TNo *insere(TNo **nodo, int valorNovo){
	
	// verifica se o no esta vazio para poder inserir
    if ((*nodo) == NULL){
        (*nodo) = criaNo(valorNovo);
    }
    
    //  verifica se o no da esquerda esta nulo para poder inserir
    else if (valorNovo < (*nodo)->valor){
        (*nodo)->esq = insere(&(*nodo)->esq, valorNovo);
    }
    
	// verifica o outro lado se esta vazio para inserir o valor
    else{
        (*nodo)->dir = insere(&(*nodo)->dir, valorNovo);
    } 
    
    return (*nodo);
}

// Funcao para inserir um numero novo dentro da arvore
void inserir(TNo **nodo){
    
	int numero;

    printf("\tInsira o numero: ");
    scanf("%d", &numero);

    insere(nodo, numero);
}

// Funcao para remover algum no na arvore
TNo *remover(TNo *nodo, int valorNovo){
    
	if (nodo == NULL){
        // interrompe a busca pelo valor, pois não existe
        return NULL;
    }
    
	else if (nodo->valor > valorNovo){
        // vai descendo pela esquerda
        nodo->esq = remover(nodo->esq, valorNovo);
    }
    
	else if (nodo->valor < valorNovo){
        // vai descendo pela direita
        nodo->dir = remover(nodo->dir, valorNovo);
    }
    
	else{
        // Encontrou no a ser removido da arvore
        if (nodo->dir == NULL && nodo->esq == NULL){
            // No a ser removido nao tem FILHOS.
            free(nodo);
            nodo = NULL;
        }
        
		else if (nodo->esq == NULL){
            // No a ser removido tem apenas FILHO DA  DIREITA na arvore
            TNo *temporario = nodo;
            nodo = nodo->dir;
            free(temporario);
        }
        
		else if (nodo->dir == NULL){
            // No a ser removido tem apenas FILHO DA ESQUERDA na arvore
            TNo *temporario = nodo;
            nodo = nodo->esq;
            free(temporario);
        }
        
		else{
            // No tem dois FILHOS.
            TNo *prov = nodo->esq;
            while (prov->dir != NULL)
            {
                prov = prov->dir;
            } 
            // Fazendo a troca dos dados entre os nos
            nodo->valor = prov->valor;
            prov->valor = valorNovo;

            nodo->esq = remover(nodo->esq, valorNovo);
        }
    }
    return nodo;
}

// Funcao para remover um valor da arvore
void removerValor(TNo *nodo){
    int numero;
	
		
    printf("\tInsira o numero: ");
    scanf("%d", &numero);

    remover(nodo, numero);
}

// Imprime em ordem
void imprimir_em_ordem(TNo *nodo){
    
	if (nodo != NULL){
        imprimir_em_ordem(nodo->esq);
        printf("\n\t(%d).", nodo->valor);
        imprimir_em_ordem(nodo->dir);
    } 
}

// Imprime em pre ordem
void imprimir_pre_ordem(TNo *nodo){
    
	if (nodo != NULL){
        printf("\n\t(%d).", nodo->valor);
        imprimir_pre_ordem(nodo->esq);
        imprimir_pre_ordem(nodo->dir);
    } 
}

// Imprime em pos ordem
void imprimir_pos_ordem(TNo *nodo){
    
	if (nodo != NULL){
        imprimir_pos_ordem(nodo->esq);
        imprimir_pos_ordem(nodo->dir);
        printf("\n\t(%d).", nodo->valor);
    } 
}

// Busca valor na arvore
void buscaValor(TNo *nodo, int procurado){
    
    //  Valor Nulo
	if (nodo == NULL){
        printf("\n\n\tÃrvore VAZIA ... ImpossÃ­vel iniciar busca de %d.\n\n", procurado);
    }
    
    // Faz a busca e vai visitando as ramificacoes
	else{
        printf("\n\n\tIniciando BUSCA pelo valor %d", procurado);
        printf("\n\n\tVisitando a RAIZ (%d).\n", nodo->valor);
        busca(nodo, procurado);
    }

}

// Busca no na arvore
void busca(TNo *nodo, int procurado){
    
    // No Nulo
	if (nodo == NULL){
        printf("\n<<VALOR INEXISTENTE NA ARVORE>>\n\n\n");
    }
    
    // No encontrado
    else if (nodo->valor == procurado){
        printf("\n<<ENCONTRADO>>\n\n\n");
    }
    
    // Procura pelas ramificaoes e desce pela esquerda
    else if (nodo->valor > procurado){
        printf("\nPROCURADO: %d\tVISITADO: %d", procurado, nodo->valor);
        printf("\n\n... Descendo pela Sub-Arvore ESQUERDA.");
        busca(nodo->esq, procurado);
    }
    // Procura pelas ramificaoes e desce pela direita
	else{
        printf("\nPROCURADO: %d\tVISITADO: %d", procurado, nodo->valor);
        printf("\n\n... Descendo pela Sub-Arvore DIREITA.");
        busca(nodo->dir, procurado);
    }
}

// Busca valor
void buscar(TNo *nodo){
    int numero;

    printf("\tInsira o numero: ");
    scanf("%d", &numero);
	buscaValor(nodo, numero);
}

// Menu com todas as opcoes do sistema (Inserir, buscar, remover e imprimir na ordem desejada)
void menu(TNo **nodo){
    int op;
    
    // Menu de opcoes para o usuario e cada case utiliza a devida funcao
	do{
        printf("\t0. Sair\n");
        printf("\t1. Inserir na arvore\n");
        printf("\t2. Buscar na arvore\n");
        printf("\t3. Remover da arvore\n");
        printf("\t4. Imprimir em pre ordem\n");
        printf("\t5. Imprimir em ordem\n");
        printf("\t6. Imprimir em pos ordem\n");

        printf("Escolha a opcao: ");
        scanf("%d", &op);

		switch (op){
		    case 0:
		        break;
		    case 1:
		        inserir(nodo);
		        break;
		    case 2:
		        buscar(*nodo);
		        break;
		    case 3:
		        removerValor(*nodo);
		        break;
		    case 4:
		        imprimir_pre_ordem(*nodo);
		        break;
		    case 5:
		        imprimir_em_ordem(*nodo);
		        break;
		    case 6:
		        imprimir_pos_ordem(*nodo);
		        break;
		    default:
		        printf("\t\n Opcao invalida! Tente outra opcao.");
		        break;
		    }

    } while (op != 0);
    
    printf("Fim do programa.....");
}

// Main para a chamada das funcoes e funcionament do programa
void main(){
    
	TNo *raiz;
    inicializaArvore(&raiz);
	menu(&raiz);
}
