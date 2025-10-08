#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
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
    if((*li) == NULL) //lista vazia: insere in�cio
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
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
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

    if(no->ant == NULL)//remover o primeiro e �nico
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
1) Fa�a uma fun��o que remova um aluno dada a sua respectiva matricula.
Sua fun��o deve reajustar os ponteiros ant e prox assim que remover o
elemento, n�o esque�a de verificar se a elemento que ser� removido
est� em uma c�lula que � a primeira ou a �ltima ou alguma c�lula do
meio da lista, para cada posi��o o ajuste dos ponteiros � diferente.
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
2) Fa�a uma fun��o que insira um novo elemento na lista de forma
ordenada. Utilize a fun��o insere_lista_ordenada da lista encadeada
como base para criar essa fun��o.
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
3) Fa�a um fun��o que conte quantos alunos tem uma nota qualquer n1
igual, com o seguinte prot�tipo int conta_lista_nota(Lista* li, int n1). A
fun��o deve utilizar apenas o ponteiro li passado como par�metro, n�o
pode ser criado nenhum outro ponteiro auxiliar. Ao final al�m de informar
a quantidade alunos com a mesma nota, o ponteiro li deve estar
apontado para a primeira c�lula �cabe�a� da lista.
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
4) Refa�a as fun��es de inserir e remover no in�cio e fim para que a lista
comporte-se de forma circular. No fim, fa�a uma fun��o que para
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
5) Fa�a uma estrutura do tipo Fila utilizando o conceito de lista duplamente
ou simplesmente encadeada, voc� pode escolher qual ir� utilizar. �
preciso criar as fun��es Enfileirar e Desenfileirar. Essas fun��es devem
utilizar o conceito de n� descritor (nodesc), que � uma estrutura que
controla onde est� a c�lula inicial da lista e a c�lula final, a inser��o e
remo��o na fila deve utilizar apenas os n�s que est�o na estrutura do n�
descritor. Abaixo segue as duas estruturas que ser�o usadas, a fun��o
que inicializa o n� descritor e o cabe�alho das fun��es.
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
