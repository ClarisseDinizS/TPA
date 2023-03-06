// Inserir, Remover, Imprimir e Buscar
// CLARISSE DINIZ SILVA

#include "hash.h"

// cria e retorna um tipo Elemento
Elemento *criarElemento()
{
    Elemento *e = malloc(sizeof(Elemento));
    printf("Digite o valor: ");
    scanf("%d", &e->valor);
    return e;
}

// imprime um elemento
void imprimirElemento(Elemento *e)
{
    printf("\tValor: %d\n", e->valor);
}

// cria uma lista vazia e retorna seu endereï¿½o na memï¿½ria
Lista *criarLista()
{
    Lista *l = malloc(sizeof(Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}


void inserirInicio(Elemento *e, Lista *lista)
{
    No *no = malloc(sizeof(No));
    no->elemento = e;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

// Buscar elementos dentro da lista
No *buscarNo(int val, No *inicio)
{

    while (inicio != NULL)
    {
        if (inicio->elemento->valor == val)
            return inicio;
        else
            inicio = inicio->proximo;
    }
    return NULL;
}

void imprimirLista(No *inicio)
{
    while (inicio != NULL)
    {
        imprimirElemento(inicio->elemento);
        inicio = inicio->proximo;
    }
}


// inicializa a tabela com uma lista vazia em cada posição do vetor
void inicializar()
{
    int i;
    for (i = 0; i < M; i++)
        tabela[i] = criarLista();
}

// Função para calcular o mod
int funcaoEspalhamento(int valor)
{
    return valor % M;
}

// Criação do elemento e inserção na tabela
void inserTabela()
{
    Elemento *elem = criarElemento();
    int indice = funcaoEspalhamento(elem->valor);
    inserirInicio(elem, tabela[indice]);
}

// Função de buscar elementos na tabela
Elemento *buscarElementoTabela(int valor)
{
    int indice = funcaoEspalhamento(valor);
    No *no = buscarNo(valor, tabela[indice]->inicio);
    if (no)
        return no->elemento;
    else
        return NULL;
}

// Excluir elementos da lista
void removerElementoTabela(int valor)
{
    // Achar índice do número a ser removido
    int indice = funcaoEspalhamento(valor);

    Lista *lista = tabela[indice];
    No *no = lista->inicio;
    No *aux = NULL;
    Elemento *elemento = NULL;

    if (no != NULL)
    {
        elemento = no->elemento;

        if (elemento->valor == valor)
        {
            aux = no;
            no = no->proximo;
            lista->inicio = no;
            lista->tam--;
            printf("\nElemento removido: %d", aux->elemento->valor);
            free(aux);
        }
        else
        {
            aux = no->proximo;
            No *anterior = no;

            while ((aux != NULL) && (aux->elemento->valor != valor))
            {
                anterior = aux;
                aux = aux->proximo;
            }

            if (aux != NULL)
            {
                anterior->proximo = aux->proximo;
                lista->inicio = no;
                lista->tam--;
                printf("\nElemento removido: %d", aux->elemento->valor);
                free(aux);
            }
            else
            {
                printf("\nElemento nao encontrado\n");
            }
        }
    }
    else
    {
        printf("\nElemento nao encontrado\n");
    }
}

// Imprimir a tabela. Cada posição com todos os valores que estï¿½o nela;
void imprimirTabela()
{
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for (i = 0; i < M; i++)
    {
        printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimirLista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}

int main()
{
    int op, valor;
    Elemento *e;

    inicializar();

    do
    {
        printf("\n0 - Sair\n1 - Inserir\n2 - Buscar\n3 - Imprimir tabela\n4 - Excluir\n");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            printf("Fim...\n");
            break;
        case 1:
            inserTabela();
            break;
        case 2:
            printf("Qual o elemento a ser buscado? ");
            scanf("%d", &valor);
            e = buscarElementoTabela(valor);
            if (e)
                printf("Elemento encontrado: %d", e->valor);
            else
                printf("Elemento nao encontrado!\n");
            break;
        case 3:
            imprimirTabela();
            break;
        case 4:
            printf("Qual o elemento deseja excluir? ");
            scanf("%d", &valor);
            removerElementoTabela(valor);
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}
