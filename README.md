# Estruturas de Dados - Lista de Exercícios com Listas Duplamente Encadeadas

**Aluno:** Guilherme de Sousa Brito  
**RA:** 2576627

Este repositório contém a resolução da **Lista 6 de Exercícios** da disciplina de **Algoritmos e Estruturas de Dados III**, ministrada na **UTFPR - Campus Santa Helena**.

Todos os exercícios foram implementados utilizando o projeto **ProjListaDinEncadDupla** disponibilizado pelo professor, com foco em **listas duplamente encadeadas** e **listas duplamente encadeadas circulares**.

---

## 📘 Enunciados dos Exercícios

### 1. Remoção por Matrícula

Implemente uma função que remova um aluno da lista a partir de sua **matrícula**.  
A função deve reajustar corretamente os ponteiros `ant` e `prox`, considerando se o nó a ser removido está no **início**, **meio** ou **fim** da lista.

---

### 2. Inserção Ordenada

Crie uma função que insira um novo elemento na lista de forma **ordenada**, utilizando como base a função `insere_lista_ordenada` da lista encadeada simples.

---

### 3. Contagem por Nota

Implemente a função `int conta_lista_nota(Lista* li, int n1)` que conta quantos alunos possuem a nota `n1`.  
⚠️ A função deve utilizar **apenas o ponteiro `li`** passado como parâmetro e, ao final, o ponteiro deve estar novamente apontando para a **cabeça da lista**.

---

### 4. Inserção e Remoção em Lista Circular

Refaça as funções de **inserção** e **remoção** no início e fim da lista para que ela se comporte de forma **circular**.  
Implemente também uma função que percorra toda a lista utilizando essa estrutura circular.

---

### 5. Fila com Nó Descritor

Implemente uma estrutura de **Fila** utilizando lista **duplamente encadeada** ou **simplesmente encadeada**.  
Utilize a estrutura de **nó descritor** para controlar os ponteiros de início e fim da fila.

```c
struct fila {
    int info;
    struct fila *prox;
    struct fila *ant;
};

struct nodesc {
    struct fila *ini;
    struct fila *fim;
};
