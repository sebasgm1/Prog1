/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main ()
{
  int n;
  scanf ("%d", &n);

  // aloque dinamicamente um vetor com n ponteiros para números racionais
  struct racional **vetor;
  vetor[n] = malloc (n * sizeof (struct racional));

  if (vetor == NULL) {
    printf ("nao conseguiu alocar o vetor\n");
    return 1;
  }
  for (int i = 0; i<n; i++) {
    long a, b;
    vetor[i] = malloc (sizeof(struct racional));

    scanf ("%ld, %ld", &a, &b);
    vetor[i] = cria_r (a, b);
  }
  // preencha o vetor com n números racionais lidos da entrada
  // (leia o numerador e o denominador de cada racional)

  // imprima "VETOR = " e os racionais apontados pelo vetor

  // elimine do vetor os racionais inválidos
  // imprima "VETOR = " e o vetor resultante

  // ordene o vetor em ordem crescente
  // imprima "VETOR = " e os racionais apontados pelo vetor

  // calcule a soma dos racionais apontados pelo vetor
  // imprima "SOMA = " e a soma calculada acima

  // libere os racionais apontados pelo vetor
  // imprima "VETOR = " e os racionais apontados pelo vetor

  // libere o vetor de ponteiros
  // libere o espaço utilizado para fazer o cálculo da soma
  return (0) ;
}

