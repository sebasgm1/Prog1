// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria () {
  struct fprio_t *f = malloc (sizeof (struct fprio_t));
  if (f == NULL)
    return NULL;
  
  f->prim = NULL;
  f->num = 0;
  return f;
}


// Remove todos os nodos da fila e a libera.
// ATENÇÃO: a memória de cada item deve ser liberada por quem a alocou.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f) {
  if (f == NULL)
    return NULL;
  
  struct fpnodo_t *atual = f->prim;
  struct fpnodo_t *ante;

  // for (int i=0; i<f->num-1; i++) {        // -1 pois começamos do 0 e sempre pegamos o próximo
  //   free (atual->item);
  //   ante = atual;
  //   atual = atual->prox;
  //   free (ante);
  // }

  while (atual != NULL) {
    if (atual->item != NULL)
      free (atual->item);
    ante = atual;
    atual = atual->prox;
    free (ante);
  }

  free (f);
  f = NULL;
  return f;
}


// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {
  if (f == NULL || item == NULL )
    return -1;

  struct fpnodo_t *nodo = malloc (sizeof (struct fpnodo_t));
  if (nodo == NULL)
    return -1;

  nodo->item = item;
  nodo->tipo = tipo;
  nodo->prio = prio;
  nodo->prox = NULL;

  // caso a lista esteja vazia
  if (f->prim == NULL) {
    f->prim = nodo;
    f->num ++;
    return f->num;
  }

  struct fpnodo_t *atual = f->prim;

  // verifica se nao tem nenhum ponteiro igual ao que será inserido
  for (int i=0; i<f->num; i++) {
    if (item == atual->item) {
      free(nodo);
      return -1;
    }      
    atual = atual->prox;
  }

  // começa da segunda posição pois a primeira já foi testada
  atual = f->prim;
  struct fpnodo_t *ante = NULL;

  // verifica em que posição ele deve estar e insere ele
  while (atual != NULL && prio >= atual->prio) {
    ante = atual;
    atual = atual->prox;        // se chegar no final da lista, atual vai ser NULL
  }

  // atual vai ser NULL quando chegar no fim da fila
  if (atual == NULL) {
    ante->prox = nodo;
    f->num ++;
    return f->num;
  }

  // caso tenha um nodo na primeira posiçao e eu quero adicinoar na primeira posição
  if (ante == NULL) {
    nodo->prox = atual;
    f->prim = nodo;
    f->num ++;
    return f->num;
  }

  ante->prox = nodo;
  nodo->prox = atual;

  f->num ++;
  return f->num;

}


// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {
  if (f == NULL || tipo == NULL || prio == NULL || f->num == 0)
    return NULL;
  
  void *item = f->prim->item;
  struct fpnodo_t *primeiro = f->prim;

  *tipo = f->prim->tipo;
  *prio = f->prim->prio;
  f->prim = f->prim->prox;
  
  free (primeiro);

  f->num --;
  
  return item;
}


// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f) {
  if (f == NULL)
    return -1;

  if (f->num < 0) {       // nao é necessárioa, mas vai que
    printf ("fprio_tamanho: tamanho de fila negativo\n");
    return -1;
  } 

  return f->num;
}


// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f) {
  if (f->prim == NULL)
    return;

  printf ("(%d %d)", f->prim->tipo, f->prim->prio);
  struct fpnodo_t *atual = f->prim;

  // for (int i = 1; i<f->num; i++) {
  //   atual = atual->prox;
  //   printf (" (%d %d)", atual->tipo, atual->prio);
  // }

  while (atual->prox != NULL) {
    atual = atual->prox;
    printf (" (%d %d)", atual->tipo, atual->prio);
  }
  return;
}