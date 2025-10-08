#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
int main()
{
    struct aluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
        {4,"Ricardo",7.5,8.7,6.8},
        {1,"Bianca",9.7,6.7,8.4},
        {3,"Ana",5.7,6.1,7.4}
    };
    Lista* li = cria_lista();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));

    int i;
    for(i=0; i < 4; i++)
        insere_lista_inicio(li,a[i]);

    //ex1
    printf("=== Exercicio 1: Remover aluno pela matricula ===\n\n");

    imprime_lista(li);
    printf("\nRemovendo aluno com matricula 2...\n\n");
    remove_lista_mat(li, 2);
    printf("\nLista apos remocao:\n");
    imprime_lista(li);

    //ex2
    printf("\n\n=== Exercicio 2: Inserir elemento de forma ordenada ===\n\n");

    Lista *li_ordenada = cria_lista();
    for(i = 0; i < 4; i++)
        insere_lista_ordenada(li_ordenada, a[i]);

    printf("Lista ordenada por matricula:\n");
    imprime_lista(li_ordenada);

    //ex3
    printf("=== Exercicio 3: Contar alunos com mesma nota ===\n\n");
    printf("Numero de notas encontradas: %d\n\n", conta_lista_nota(li_ordenada, 9.5));

    //ex4
    printf("=== Exercicio 4: Lista Circular ===\n\n");

    Lista *li_circular = cria_lista();
    for(int i = 0; i < 4; i++)
        insere_lista_inicio_circular(li_circular, a[i]);

    printf("Lista circular apos insercao no inicio:\n");
    percorre_lista_circular(li_circular);

    remove_lista_inicio_circular(li_circular);
    printf("\nLista circular apos remover o primeiro elemento:\n");
    percorre_lista_circular(li_circular);

    remove_lista_final_circular(li_circular);
    printf("\nLista circular apos remover o ultimo elemento:\n");
    percorre_lista_circular(li_circular);

    //ex5
    printf("\n=== Exercicio 5: Fila com no descritor ===\n\n");

    noDesc *fila;
    if (!inicializa_noDesc(&fila))
    {
        printf("Erro ao inicializar a fila!\n");
        return 1;
    }


    printf("Enfileirando elementos: 10, 20, 30, 40\n");
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);
    enfileirar(fila, 40);

    printf("Desenfileirando elementos:\n");
    int valor;
    while(desenfileirar(fila, &valor))
    {
        printf("Elemento removido: %d\n", valor);
    }

    free(fila);
    libera_lista_circular(li_circular);
    libera_lista(li_ordenada);
    libera_lista(li);
    system("pause");
    return 0;
}

