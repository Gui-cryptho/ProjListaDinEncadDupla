#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Protótipos

//Definição do tipo lista
struct elemento
{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL)
    {
        Elem* no;
        while((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al)
{
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos)
    {
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else
    {
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al)
{
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat)
    {
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else
    {
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al)
{
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL) //lista vazia: insere início
    {
        no->ant = NULL;
        *li = no;
    }
    else
    {
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al)
{
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista não vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li)
{
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li)
{
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e único
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li)
{
    return 0;
}

int lista_vazia(Lista* li)
{
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li)
{
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL)
    {
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n",no->dados.n1,
               no->dados.n2,
               no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

/*
1) Faça uma função que remova um aluno dada a sua respectiva matricula.
Sua função deve reajustar os ponteiros ant e prox assim que remover o
elemento, não esqueça de verificar se a elemento que será removido
está em uma célula que é a primeira ou a última ou alguma célula do
meio da lista, para cada posição o ajuste dos ponteiros é diferente.
*/

int remove_lista_mat(Lista* li, int mat)
{
    if (li == NULL || *li == NULL)
        return 0;

    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;

    if (no == NULL)
        return 0;

    if (no->ant == NULL)
    {
        *li = no->prox;
        if (no->prox != NULL)
            no->prox->ant = NULL;
    }
    else if (no->prox == NULL)
    {
        no->ant->prox = NULL;
    }
    else
    {
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}

/*
2) Faça uma função que insira um novo elemento na lista de forma
ordenada. Utilize a função insere_lista_ordenada da lista encadeada
como base para criar essa função.
*/

int insere_lista_ordenada(Lista* li, struct aluno al)
{
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL)
    {
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else
    {
        Elem *atual = *li;
        Elem *anterior = NULL;
        while (atual != NULL && atual->dados.matricula < al.matricula)
        {
            anterior = atual;
            atual = atual->prox;
        }
        if (atual == *li)
        {
            no->ant = NULL;
            no->prox = *li;
            (*li)->ant = no;
            *li = no;
        }
        else
        {
            no->prox = anterior->prox;
            no->ant = anterior;
            anterior->prox = no;
            if (atual != NULL)
                atual->ant = no;
        }
        return 1;
    }
}

/*
3) Faça um função que conte quantos alunos tem uma nota qualquer n1
igual, com o seguinte protótipo int conta_lista_nota(Lista* li, int n1). A
função deve utilizar apenas o ponteiro li passado como parâmetro, não
pode ser criado nenhum outro ponteiro auxiliar. Ao final além de informar
a quantidade alunos com a mesma nota, o ponteiro li deve estar
apontado para a primeira célula “cabeça” da lista.
*/

int conta_lista_nota(Lista* li, float n1)
{
    if (li == NULL || *li == NULL)
        return 0;

    int cont = 0;
    while (*li != NULL)
    {
        if ((*li)->dados.n1 == n1)
            cont++;
        *li = (*li)->prox;
    }

    while (*li != NULL && (*li)->ant != NULL)
        *li = (*li)->ant;

    return cont;
}

/*
4) Refaça as funções de inserir e remover no início e fim para que a lista
comporte-se de forma circular. No fim, faça uma função que para
percorrer a lista inteira utilizando o comportamento circular da mesma.
*/

int insere_lista_inicio_circular(Lista* li, struct aluno al)
{
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;

    if ((*li) == NULL)
    {
        no->dados = al;
        no->prox = no;
        no->ant = no;
        *li = no;
    }
    else
    {
        Elem* ult = (*li)->ant;
        no->dados = al;
        no->prox = *li;
        no->ant = ult;
        ult->prox = no;
        (*li)->ant = no;
        *li = no;
    }
    return 1;
}

int insere_lista_final_circular(Lista* li, struct aluno al)
{
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;

    if ((*li) == NULL)
    {
        no->dados = al;
        no->prox = no;
        no->ant = no;
        *li = no;
    }
    else
    {
        Elem* ult = (*li)->ant;
        no->dados = al;
        no->prox = *li;
        no->ant = ult;
        ult->prox = no;
        (*li)->ant = no;
    }
    return 1;
}

int remove_lista_inicio_circular(Lista* li)
{
    if (li == NULL || *li == NULL) return 0;

    Elem* no = *li;
    if (no->prox == no)
    {
        free(no);
        *li = NULL;
        return 1;
    }
    Elem* ult = no->ant;
    *li = no->prox;
    (*li)->ant = ult;
    ult->prox = *li;
    free(no);
    return 1;
}

int remove_lista_final_circular(Lista* li)
{
    if (li == NULL || *li == NULL) return 0;

    Elem* ult = (*li)->ant;
    if (ult == *li)
    {
        free(ult);
        *li = NULL;
        return 1;
    }
    Elem* penult = ult->ant;
    penult->prox = *li;
    (*li)->ant = penult;
    free(ult);
    return 1;
}

void percorre_lista_circular(Lista* li)
{
    if (li == NULL || *li == NULL) return;

    Elem* no = *li;
    do
    {
        printf("Matricula: %d\n", no->dados.matricula);
        printf("Nome: %s\n", no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
    while (no != *li);
}
void libera_lista_circular(Lista* li)
{
    if (li == NULL || *li == NULL) return;

    Elem* no = *li;
    Elem* aux;

    do {
        aux = no->prox;
        free(no);
        no = aux;
    } while (no != *li);

    *li = NULL;
}


/*
5) Faça uma estrutura do tipo Fila utilizando o conceito de lista duplamente
ou simplesmente encadeada, você pode escolher qual irá utilizar. É
preciso criar as funções Enfileirar e Desenfileirar. Essas funções devem
utilizar o conceito de nó descritor (nodesc), que é uma estrutura que
controla onde está a célula inicial da lista e a célula final, a inserção e
remoção na fila deve utilizar apenas os nós que estão na estrutura do nó
descritor. Abaixo segue as duas estruturas que serão usadas, a função
que inicializa o nó descritor e o cabeçalho das funções.
*/

int inicializa_noDesc(noDesc **no) {
    *no = (noDesc*) malloc(sizeof(noDesc));
    if (!(*no))
        return 0;
    (*no)->ini = NULL;
    (*no)->fim = NULL;
    return 1;
}

int enfileirar(noDesc *n, int elem) {
    if (n == NULL)
        return 0;
    Fila *novo = (Fila*) malloc(sizeof(Fila));
    if (!novo)
        return 0;
    novo->info = elem;
    novo->prox = NULL;
    novo->ant = n->fim;

    if (n->fim != NULL)
        n->fim->prox = novo;
    n->fim = novo;

    if (n->ini == NULL)
        n->ini = novo;

    return 1;
}

int desenfileirar(noDesc *n, int *elem) {
    if (n == NULL || n->ini == NULL)
        return 0;

    Fila *remover = n->ini;
    *elem = remover->info;
    n->ini = remover->prox;

    if (n->ini != NULL)
        n->ini->ant = NULL;
    else
        n->fim = NULL;

    free(remover);
    return 1;
}
