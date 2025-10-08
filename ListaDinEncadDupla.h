//Arquivo ListaDinEncadDupla.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;

typedef struct fila {
    int info;
    struct fila *prox;
    struct fila *ant;
} Fila;

typedef struct nodesc {
    Fila *ini;
    Fila *fim;
} noDesc;

Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);

//ex1
int remove_lista_mat(Lista* li, int mat);

//ex2
int insere_lista_ordenada(Lista* li, struct aluno al);

//ex3
int conta_lista_nota(Lista* li, float n1);

//ex4
int insere_lista_inicio_circular(Lista* li, struct aluno al);
int insere_lista_final_circular(Lista* li, struct aluno al);
int remove_lista_inicio_circular(Lista* li);
int remove_lista_final_circular(Lista* li);
void percorre_lista_circular(Lista* li);
void libera_lista_circular(Lista* li);

//ex5
int inicializa_noDesc(noDesc **no);
int enfileirar(noDesc *n, int elem);
int desenfileirar(noDesc *n, int *elem);
