#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// Inicializar Arvore
TNo *inicializaArvore(TNo **nodo){
    (*nodo) = NULL;
}

// Funcao que retorna o maior valor entre dois long longeiros (Utilizado pelas rotacoes)
int maior(int a, int b){
    return (a > b) ? a : b;
}

// Cria no na Arvore
TNo *criaNo(int valor){
    TNo *novo = (TNo *)malloc(sizeof(TNo));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

// Funcao que verifica e imprime na tela a altura da Arvore ou do no
int altura(TNo **nodo){
	
    if ((*nodo) == NULL)  // Se raiz for nulo
        return -1;          // retorna 0
    return (*nodo)->altura; // Senao usa funcao recursiva
}

// Funcao que retorna o fator de balanceamento do no
int balanceamento(TNo **nodo){
	
    if ((*nodo) == NULL)
        return 0;
    
	return altura(&(*nodo)->esq) - altura(&(*nodo)->dir);
}

// Funcao para a rotacaoo da sub-arvore (para a direita)
TNo *rotDir(TNo **nodo){
    
	TNo *auxiliarEsquerda = (*nodo)->esq;
    TNo *auxiliarDireita = auxiliarEsquerda->dir;

    // Realizando rotacaoo para a direita
    auxiliarEsquerda->dir = (*nodo);
    (*nodo)->esq = auxiliarDireita;

    // Atualizando alturas
    (*nodo)->altura = maior(altura(&(*nodo)->esq), altura(&(*nodo)->dir)) + 1;
    auxiliarEsquerda->altura = maior(altura(&(auxiliarEsquerda)->esq), altura(&(auxiliarEsquerda)->dir)) + 1;

    // Retornando a nova raiz (Raiz atualizada)
    return auxiliarEsquerda;
}

// Funcao para a rotacaoo da sub-arvore (para a esquerda)
TNo *rotEsq(TNo **nodo){
    
	TNo *auxiliarDireita = (*nodo)->dir;
    TNo *auxiliarEsquerda = auxiliarDireita->esq;

    // Realizando rotacao para esquerda
    auxiliarDireita->esq = (*nodo);
    (*nodo)->dir = auxiliarEsquerda;

    // Atualizando alturas
    (*nodo)->altura = maior(altura(&(*nodo)->esq), altura(&(*nodo)->dir)) + 1;
    auxiliarDireita->altura = maior(altura(&(auxiliarDireita)->esq), altura(&(auxiliarDireita)->dir)) + 1;

    // Retornando a nova raiz (Raiz atualizada)
    return auxiliarDireita;
}

// Insere no dentro da arvore
TNo *insere(TNo **nodo, int valor){
	// Verifica se o no esta nulo
    if ((*nodo) == NULL){
        (*nodo) = criaNo(valor); // Se estiver, cria o no
    }
	else if (valor < (*nodo)->valor){
        (*nodo)->esq = insere(&(*nodo)->esq, valor); // insere do lado esquerdo
    }
    
    else if (valor > (*nodo)->valor){
        (*nodo)->dir = insere(&(*nodo)->dir, valor); // insere do lado direito
    }
    
	else{
        printf("\n\tValor %d jÃ¡ existe\n", (*nodo)->valor); // Se o no ja estiver presente na arvvore
        return (*nodo);
    } 

    //Passo 2 - Atualiza a altura do novo no (em relacao ao anterior) 
    (*nodo)->altura = maior(altura(&(*nodo)->esq), altura(&(*nodo)->dir)) + 1;

    // Passo 3 - Declarada uma variavel inteira que tem por objetivo obter o fator de balanceamento 
	//do no em relacao ao anterior para saber se a arvore ficou desbalanceada
    
	int fb = balanceamento(&(*nodo)); // Verifica o fator de balanceamento

    // Se o novo no desbalanceou a arvore, sera necessario obter o balanceamento por meio de uma das 4 formas (dependendo do caso)

    // Rotacao simples para a esquerda
    if (fb > 1 && valor < (*nodo)->esq->valor){ // Se o fator de balanceamento da Raiz for maior que 1 e o Id informado for menor que o Id que esta na Raiz -> Esquerda
        (*nodo) = rotDir(&(*nodo)); 
	}               // Retorna a Raiz, depois de aplicada a Rotacao  para Direita(Funcao)

    // Rotacao simples para direita
    if (fb < -1 && valor > (*nodo)->dir->valor){
    	(*nodo) = rotEsq(&(*nodo));
	}
        
    // Rotacao dupla para a esquerda
    if (fb > 1 && valor > (*nodo)->esq->valor){
        (*nodo)->esq = rotEsq(&(*nodo)->esq);
        (*nodo) = rotDir(&(*nodo));
    }

    // Rotacao dupla para direita
    if (fb < -1 && valor < (*nodo)->dir->valor){
        (*nodo)->dir = rotDir(&(*nodo)->dir);
        (*nodo) = rotEsq(&(*nodo));
    } 

    // Passo 4 - Retorna a nova Raiz(atualizada) 
    return (*nodo);
}

// Insere novo numero dentro da arvore
void inserir(TNo **nodo){
    
	int valor;

    printf("\tInsira a valor: ");
    scanf("%d", &valor);
	insere(nodo, valor);
	
}

// Remove no da arvore
TNo *remover(TNo **nodo, int valor){
	
    if ((*nodo) == NULL){
        return NULL; // interrompe
    }
    
	else if ((*nodo)->valor > valor){
        // desce pela esquerda
        (*nodo)->esq = remover(&(*nodo)->esq, valor);
    }
    
	else if ((*nodo)->valor < valor){
        // desce pela direita
        (*nodo)->dir = remover(&(*nodo)->dir, valor);
    }
    
	else{
        // Encontrou No que vai ser retirado da arvore
        if ((*nodo)->dir == NULL && (*nodo)->esq == NULL){
            // no a ser removido NAO POSSUI FILHOS.
            free((*nodo));
            (*nodo) = NULL;
        }
        
		else if ((*nodo)->esq == NULL){
            // No a ser removido tem apenas FILHO a DIREITA.
            TNo *temporario = (*nodo);
            (*nodo) = (*nodo)->dir;
            free(temporario);
        }
        
		else if ((*nodo)->dir == NULL){
            // No a ser removido tem apenas FILHO a ESQUERDA.
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
            (*nodo)->valor = prov->valor;
            prov->valor = valor;

            (*nodo)->esq = remover(&(*nodo)->esq, valor);
        }
    }

    if ((*nodo) == NULL) // Se a arvore for nula
        return (*nodo);  // Retorna ela mesma

    // Passo 2 - Atualiza a altura do novo no
    (*nodo)->altura = maior(altura(&(*nodo)->esq), altura(&(*nodo)->dir)) + 1;

    // Passo 3 - Declarada uma variavel inteira que tem por objetivo obter o fator de balanceamento deste no 
	// em relacao ao anterior para saber se a arvore ficou desbalanceada
    int fb = balanceamento(&(*nodo));

    // Se o novo no causou desbalanceamento da arvore, sera necessario obter o balanceamento por meio de uma das 4 formas 

    // Rotacao simples para a esquerda
    if (fb > 1 && balanceamento(&(*nodo)->esq) >= 0)
        return rotDir(&(*nodo));

    // Rotacao dupla para  esquerda
    if (fb > 1 && balanceamento(&(*nodo)->esq) < 0){
        (*nodo)->esq = rotEsq(&(*nodo)->esq);
        return rotDir(&(*nodo));
    }

    // Rotacao simples para  direita
    if (fb < -1 && balanceamento(&(*nodo)->dir) <= 0)
        return rotEsq(&(*nodo));

    // Rotacao dupla para  direita
    if (fb < -1 && balanceamento(&(*nodo)->dir) > 0){
        (*nodo)->dir = rotDir(&(*nodo)->dir);
        return rotEsq(&(*nodo));
    }

    return (*nodo);
}

// Remove valor da arvore
void removerValor(TNo **nodo){
	
    int numero;

    printf("\tInsira o numero: ");
    scanf("%d", &numero);

    remover(nodo, numero);
}

// Imprime em ordem
void caminhamento_em_ordem(TNo *nodo){
	
    if (nodo != NULL)
    {
        caminhamento_em_ordem(nodo->esq);
        printf("\n\tAltura: %d -> %d", nodo->altura, nodo->valor);
        caminhamento_em_ordem(nodo->dir);
    } 
}

// Imprime em pre ordem
void caminhamento_pre_ordem(TNo *nodo){
    
	if (nodo != NULL){
        printf("\n\tAltura: %d -> %d", nodo->altura, nodo->valor);
        caminhamento_pre_ordem(nodo->esq);
        caminhamento_pre_ordem(nodo->dir);
    } 
}

// Imprime em pos ordem
void caminhamento_pos_ordem(TNo *nodo){
	
    if (nodo != NULL){
        caminhamento_pos_ordem(nodo->esq);
        caminhamento_pos_ordem(nodo->dir);
        printf("\n\tAltura: %d -> %d", nodo->altura, nodo->valor);
    } 
}

// Busca no na arvore
void buscarNo(TNo **nodo, int procurado){
	
	// VAZIO
    if ((*nodo) == NULL){
        printf("\n<<VALOR INEXISTENTE NA ARVORE>>\n\n\n");
    }
    // ENCONTRADO
    else if ((*nodo)->valor == procurado){
        printf("\n<<ENCONTRADO>>\n\n\n");
    }
    // NAO ENCONTRADO, VISITA PELA ESQUERDA
    else if ((*nodo)->valor > procurado){
        printf("\nPROCURADO: %d\tVISITADO: %d", procurado, (*nodo)->valor);
        printf("\n\n... Descendo pela Sub-Arvore ESQUERDA.");
        buscarNo(&(*nodo)->esq, procurado);
    }
    // NAO ENCONTRADO, VISITA PELA DIREITA
    else{
        printf("\nPROCURADO: %d\tVISITADO: %d", procurado, (*nodo)->valor);
        printf("\n\n... Descendo pela Sub-Arvore DIREITA.");
        buscarNo(&(*nodo)->dir, procurado);
    }
}

// Busca valor dentro da Arvore
void buscaValor(TNo **nodo, int procurado){
	
    if ((*nodo) == NULL){
        printf("\n\n\tÃrvore VAZIA ... ImpossÃ­vel iniciar busca de %d.\n\n", procurado);
    }
    else{
        printf("\n\n\tIniciando BUSCA pelo valor %d", procurado);
        printf("\n\n\tVisitando a RAIZ (%d).\n", (*nodo)->valor);
        buscarNo(nodo, procurado);
    }
}

// Busca valor 
void buscar(TNo **nodo){
	
    int numero;

    printf("\tInsira o numero: ");
    scanf("%d", &numero);

    buscaValor(nodo, numero);
}

// Menu printado na tela (Inserir, Remover, Buscar e Imprimir nas ordens)
void menu(TNo **nodo){
    int op;
    do
    {
        printf("\n\n----------	|| MENU ||	--------------\n\n");
        printf("\t0. Sair\n");
        printf("\t1. INSERIR na arvore\n");
        printf("\t2. BUSCAR na arvore\n");
        printf("\t3. REMOVER da arvore\n");
        printf("\t4. IMPRIMIR em pre ordem\n");
        printf("\t5. IMPRIMIR em ordem\n");
        printf("\t6. IMPRIMIR em pos ordem\n");

        printf("Escolha a opcao: ");
        scanf("%d", &op);
        
        switch (op){
		    case 0:
		        break;
		    case 1:
		        inserir(nodo);
		        break;
		    case 2:
		        buscar(nodo);
		        break;
		    case 3:
		        removerValor(nodo);
		        break;
		    case 4:
		        caminhamento_pre_ordem(*nodo);
		        break;
		    case 5:
		        caminhamento_em_ordem(*nodo);
		        break;
		    case 6:
		        caminhamento_pos_ordem(*nodo);
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
    menu(&raiz);
}
