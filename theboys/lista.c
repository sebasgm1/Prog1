/*

  Neste arquivo estão implementadas a funções descritas no lista.h.
  Cada função tem sua descrição de funcionamente e comentários
  nas linhas que é interessante comentar, que não foram consideradas triviais.

*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "entidades.h"
#include <stdbool.h>

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
struct lista_t *lista_cria () {
  struct lista_t *lista = malloc (sizeof(struct lista_t));

  if (lista == NULL)
    return NULL;
  
  lista->prim = NULL;
  lista->ult = NULL;
  lista->tamanho = 0;
  lista->n_vivos = 0;

  return lista;
}


// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi (struct lista_t *lst) {
  if (lst == NULL)
    return NULL;

  struct item_t *aux;
  while (lst->prim != NULL) {
    aux = lst->prim;
    lst->prim = lst->prim->prox;
    free (aux);
  }
  free (lst);
  lst = NULL;

  return lst;
}


// Insere o item na lista na posição indicada;
// se a posição for além do fim da lista ou for -1, insere no fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int cria_heroi (struct lista_t *lst, int pos, int xp, int paci, int vel, struct cjto_t *habilidades) {  
  if (lst == NULL)
    return -1;
  
  struct item_t *novo = malloc (sizeof(struct item_t));
  if (novo == NULL)
    return -1;

  lst->n_vivos ++;

  novo->ant = NULL;
  novo->prox = NULL;
  novo->vivo = true;
  novo->id = pos;
  novo->xp = xp;
  novo->paciencia = paci;
  novo->vel = vel;
  novo->hab = habilidades;

  
  if (pos>lst->tamanho-1 || pos<0) {
    if (lst->tamanho == 0) {
      lst->prim = novo;
      lst->ult = novo;

      lst->tamanho ++;          // tive que fazer o incremento aqui dentro pois o lst->tamanho é usado no IF
      return lst->tamanho;
    }
    novo->ant = lst->ult;
    lst->ult->prox = novo;  
    lst->ult = novo;

    lst->tamanho ++;
    return lst->tamanho;
  }

  struct item_t *aux = lst->prim;
  for (int i=0; i<pos; i++) {
    aux = aux->prox;
  }
  novo->ant = aux->ant;
  novo->prox = aux;

  if (aux->ant != NULL)
    aux->ant->prox = novo;    // o anterior ao aux vai armazenar em seu ponteiro prox o endereço do novo
  else
    lst->prim = novo;

  aux->ant = novo;            // o aux aponta pro novo, que tomou sua posição
  lst->tamanho++;
  return lst->tamanho;
}


// Retira o item da lista da posição indicada.
// se a posição for além do fim da lista ou for -1, retira do fim.
// Retorno: qual heroi morreu ou -1 em erro.
int mata_heroi (struct lista_t *lst, int *item, int pos) {
  if (lst == NULL || lst->tamanho<1)
    return -1;
  
  struct item_t *aux;
  lst->n_vivos --;        // se passou do teste, já morreu, pode decementar

  // caso em que pos passa o tamanho da lista ou pos<0
  if ((pos>lst->tamanho-1 || pos<0) && lst->tamanho>1) {
    lst->ult->vivo = false;

    return lst->ult->id;
  }

  // caso em que a lista tem apenas um item
  if ((lst->tamanho == 1) && (pos <= 0 || pos>lst->tamanho-1)) {
    *item = lst->prim->id;
    lst->prim->vivo = false;

    lst->n_vivos --;
    return item;
  }

   // caso em que posi é 0 e (lst->elementos) > 1
  if (pos == 0){
    *item = lst->prim->id;
    lst->prim->vivo = false;

    lst->n_vivos --;
    return item;
  }

  // caso em que eu quero retirar o último elemento e (lst->elementos) > 1
  if (pos == lst->tamanho-1) {
    *item = lst->ult->id;
    lst->ult->vivo = false;

    lst->n_vivos --;
    return lst->tamanho;
  }

  // daqui pra frente são os casos em que 0 < pos < (lst->tamanho)-1
  aux = lst->prim;
  for (int i=0; i<pos; i++) {
    aux = aux->prox;
  }
  *item = aux->id;
  aux->vivo = false;

  lst->n_vivos --;
  return aux->id;
}


// Informa se o heroi está vivo ou morto na posição indicada, sem retirá-lo.
// se a posição for -1, consulta do fim.
// Retorno: número de herois vivos ou -1 em erro.
// se a posição for além do fim retora erro, -1
int lista_consulta (struct lista_t *lst, bool *vivo, int pos) {
  // if (lst == NULL || lst->tamanho<1)
  if (lst == NULL || lst->tamanho<1 || pos>lst->tamanho-1)
    return -1;
  
  // if (pos<0 || pos>lst->tamanho-1) {
  if (pos<0) {
    *vivo = lst->ult->vivo;
    return lst->n_vivos;
  }

  struct item_t *aux = lst->prim;
  for (int i=0; i<pos; i++) {
    aux = aux->prox;
  }

  *vivo = aux->vivo;
  return lst->n_vivos;
}


// Informa a posição da 1ª ocorrência do id indicado na lista.
// Retorno: posição do id ou -1 se não encontrar ou erro.
int lista_procura (struct lista_t *lst, int id) {
  if (lst == NULL || lst->tamanho<1)
    return -1;
  
  struct item_t *aux = lst->prim;
  int i = 0;  

  // enquanto nao achar o id e I nao for maior que o tamanho da fila, vai iterando
  while (aux != NULL && i<=lst->tamanho-1) {
    if (aux->id == id) {
      return i;
    }
    aux = aux->prox;
    i++;              // ficar de olho nessa linha, n sei se é ++i ou i++
  }
  return -1;
}


// Informa o tamanho da lista (o número de itens presentes nela).
// Retorno: número de itens na lista ou -1 em erro.
int lista_tamanho (struct lista_t *lst) {
  if (lst == NULL || lst->tamanho<0)
    return -1;
  return lst->tamanho;
}


// Imprime o conteúdo da lista do inicio ao fim no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois, sem newline.
void lista_imprime (struct lista_t *lst) {
  if (lst == NULL || lst->tamanho<1) {
    return;
  }  
  printf ("%d", lst->prim->id);

  struct item_t *aux = lst->prim;
  for (int i=1; i<lst->tamanho; i++) {      // começa do 1 por que a primeira posição já foi printada
    aux = aux->prox;
    printf (" %d", aux->id);
  }
  return;
}