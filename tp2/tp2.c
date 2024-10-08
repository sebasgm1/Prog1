/* 

  Este arquivo lê números reais com fração em um vetor de structs de reais
  Verifĩca se os valores inseridos são válidos ou inválidos e retira os valores inválidos
  Ordena o vetor
  Mostra a soma de todas as frações

*/

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


int main ()
{
  struct racional v[max];
  struct racional r3;
  int n;
  struct racional *p = v;

  scanf ("%d", &n);

  if (n>100 || n<1) {
    printf ("Entrada inválida, digide um número entre 1 e 100\n");
    scanf ("%d", &n);
  }

  /* limpa o vetor antes de receber os valores, tipo um barman limpando taças de vinho, coisa fina */
  for (int i=0; i<n; i++) {
    (p+i)->num = 0;
    (p+i)->den = 0;
  }

  /* preencha o vetor com n números racionais lidos da entrada */
  for (int i=0; i<n; i++) { 
    scanf ("%ld", &(p+i)->num);
    scanf ("%ld", &(p+i)->den);
  }

  printf ("VETOR = ");
  
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");


  /* elimina do vetor os elementos inválidos e trata o sinal deles */
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

  }


  /* imprima "VETOR = " e o conteúdo do vetor resultante */
  printf ("VETOR = ");
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");
  
  
  /* ordena o vetor e imprime ele */
  bubblesort (v, n);

  printf ("VETOR = ");
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");


  /* calcula a soma de todos os elementos do vetor e implrime a soma */
  r3 = cria_r (0, 1);
  for (int i = 0; i<n; i++) {
    if (!soma_r (r3, v[i], &r3))
    printf ("nao foi somado\n");
  }

  printf ("SOMA = ");
  imprime_r (r3);
  printf ("\n");

  return (0);
}
