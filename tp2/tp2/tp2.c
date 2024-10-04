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

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main ()
{
  struct racional v[max];
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
      if (valido_r(v[n-1])) { /* testa se a última posiçâo é valida */
        v[i] = v[n-1];
        --n;
      }
      else {
        --n; /* diminui o número do vetor, pois a última posição é NaN*/
        while (!valido_r(v[n])) {
          n--;
        }
        v[i] = v[n];

      }
      
    }
  }

  //imprima "VETOR = " e o conteúdo do vetor resultante
  printf ("VETOR = ");
  for (int i=0; i<n; i++) {
    imprime_r (v[i]);
  }
  printf ("\n");


  //ordene este vetor
  //imprima "VETOR = " e o conteúdo do vetor resultante

  //calcule a soma de todos os elementos do vetor
  //imprima "SOMA = " e a soma calculada acima
  //nova linha

  return (0);
}
