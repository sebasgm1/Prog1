/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define max 100

void troca (struct racional *a, struct racional *b) {
  struct racional temp = *a;
  *a = *b;
  *b = temp;
}

void bubblesort (struct racional v[], int n) {
  int trocou = 1;
  while (trocou) {
    trocou = 0;
    for (int i = 0; i<n-1; i++) {
      if (compara_r (v[i], v[i+1]) == 1) {
        troca (&v[i], &v[i+1]);
        trocou = 1;
      }
    }
  }
}

/* programa principal */
int main ()
{
  struct racional v[max];
  struct racional r3;
  int n;
  struct racional *p = v; /* inicializa o ponteiro na primeira posiçao do vetor v */

  scanf ("%d", &n); /* le o número de posiçoes que vao ser usadas */

  if (n>100 || n<1) {
    printf ("Entrada inválida, digide um número entre 1 e 100\n");
    scanf ("%d", &n);
  }

  //preencha o vetor com n números racionais lidos da entrada
  //(leia o numerador e o denominador de cada racional)
  for (int i=0; i<n; i++) { 
    scanf ("%ld", &(p+i)->num);
    scanf ("%ld", &(p+i)->den);
  }

  printf ("VETOR = ");
  
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");


  //elimine deste vetor os elementos inválidos
  for (int i=0; i<n; i++) {
    if (!valido_r(v[i])) {
      while (!valido_r(v[n-1])) { /* testa se a ùltima posição é valida até achar uma válida */
        n--;
      }
      if (i != n) { /* esse if impede que o último caso se elimine, mesmo sendo válido */
        v[i] = v[n-1];
        n--;
      }
    }
    // se for valido, verificar se o denominador é menor que zero, se for, trocar o sinal do numerador e do denominador
    if (v[i].den < 0) {
      v[i].num = -1 * v[i].num;
      v[i].den = -1 * v[i].den;
    }
    simplifica_r (v[i]);
  }


  //imprima "VETOR = " e o conteúdo do vetor resultante
  printf ("VETOR = ");
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");
  
  
  //ordene este vetor
  bubblesort (v, n);

  //imprima "VETOR = " e o conteúdo do vetor resultante
  printf ("VETOR = ");
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");


  //calcule a soma de todos os elementos do vetor
  r3 = cria_r (0, 1);
  for (int i = 0; i<n; i++) {
    soma_r (r3, v[i], &r3);
  }


  //imprima "SOMA = " e a soma calculada acima
  //nova linha
  printf ("SOMA = ");
  imprime_r (r3);
  printf ("\n");

  return (0);
}