#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void imprime_vet (struct racional *v[], int n) {
  printf ("VETOR =");
  for (int i = 0; i<n; i++) {
    imprime_r (&v[i]);
  }
  printf ("\n");  
}

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
      if (compara_r (&v[i], &v[i+1]) == 1) {
        troca (&v[i], &v[i+1]);
        trocou = 1;
      }
    }
  }
}


/* programa principal */
int main ()
{
  int n;
  scanf ("%d", &n);

  // aloque dinamicamente um vetor com n ponteiros para números racionais
  // preencha o vetor com n números racionais lidos da entrada
  // (leia o numerador e o denominador de cada racional)

  struct racional **v = malloc (n * sizeof (struct raciona*));

  if (v == NULL) {
    printf ("nao conseguiu alocar o vetor\n");
    return 1;
  }
  for (int i = 0; i<n; i++) {
    long a, b;
    scanf ("%ld, %ld", &a, &b);

    v[i] = cria_r (a, b); /* ponteiro recebendo endereço de outro ponteiro */
  }

  // imprima "VETOR = " e os racionais apontados pelo vetor
  imprime_vet (&v, n);

  // elimine do vetor os racionais inválidos
  // imprima "VETOR = " e o vetor resultante
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

  // ordene o vetor em ordem crescente
  // imprima "VETOR = " e os racionais apontados pelo vetor
  bubblesort (v, n);
  imprime_vet (&v, n);


  // calcule a soma dos racionais apontados pelo vetor
  // imprima "SOMA = " e a soma calculada acima
  struct racional *r3 = cria_r (0, 1);
  for (int i = 0; i<n; i++) {
    if (!soma_r (&r3, &v[i], &r3))
    printf ("nao foi somado\n");
  }

  printf ("SOMA = ");
  imprime_r (r3);
  printf ("\n");


  // libere os racionais apontados pelo vetor
  // imprima "VETOR = " e os racionais apontados pelo vetor
    for (int i = 0; i<n; i++) {
      destroi_r (&&v[i]);
  }
  imprime_vet (&v, n); /* se der erro vai ser AQUI */


  // libere o vetor de ponteiros
  // libere o espaço utilizado para fazer o cálculo da soma
  for (int i = 0; i<n; i++) {
    if (v[i] != NULL) {
      destroi_r (&v[i]);
      v[i] = NULL;
    }
  }
  free(r3);
  r3 = NULL;

  return (0) ;
}
