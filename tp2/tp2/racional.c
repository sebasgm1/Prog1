/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

int valido_r (struct racional r) {
  return r.den != 0; /* quer dizer se for diferente de 0, return 1, else return 0*/
}

long absoluto (long x) { /* é equivente a funcao abs, porém funciona para tipos LONG e nao apenas INT */
  if (x<0)
    x = -x;
  return x;
}

long mdc (long a, long b) /* funciona tanto para (a>b) ou (a<b) ou (a<0 e b<0) */
{
  a = absoluto (a);
  b = absoluto (b);
  while (b != 0) {
    long resto = a%b;
    a = b;
    b = resto;
  }
  return a;
  }

struct racional simplifica_r (struct racional r)
{
  int divisor;
  int a = r.num;
  int b = r.den;

  divisor = mdc (a, b);

  if (!valido_r (r))
    return r;

  if (b<0) { /* se apenas o DEN for NEGATIVO, já abrangindo o caso do NUM e DEN serem ambos negativos */  
    r.num = -1* r.num / divisor; /* inverte o sinal do numerador e simplifica */
    r.den = -1* r.den / divisor; /* inverte o sinal do denominador e simplifica */

    return r;
  }

  /* se chegou até aqui, é por que NUM é negativo ou tanto NUM como DEN são positivos */
  r.num /= divisor;
  r.den /= divisor;
  return r;
}

struct racional cria_r (long numerador, long denominador) { /* serve como uma funçao intermediária que armazena o valores do numerador e denominador na struct, muito útil */
  struct racional r;
  r.den = denominador;
  r.num = numerador;
  return simplifica_r(r);
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  return min + rand () % (max - min +1);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return (a*b) / mdc (a, b);
}



struct racional sorteia_r (long min, long max) { /* usando a funçao aleat, ele junta um númerador aleatório e um denominador aletório na mesma struct (usando a cria_r) */
  long numerador = aleat (min, max);
  long denominador = aleat (min, max);

  return cria_r(numerador, denominador); /* sempre vai retornar simplificado */
}

void imprime_r (struct racional r) {
  long numerador = r.num;
  long denominador = r.den;

  if (!valido_r (r)) { /* se o valor for inválido, imprime INVALIDO e já retorna, saindo da função */
      printf ("NAN ");
      return;
  }

  else if (numerador == 0) /* se o numerador for 0, só printa 0*/
    printf ("0 ");
  
  else if (denominador == 1) /* se o denominador for 1, só printa o numerador */
    printf ("%ld ", numerador);

  else if (numerador == denominador) /* se o numerador e o denominador forem iguais, apenas printa 1 */
    printf ("1 ");
  
  else if (denominador<0) /* vale tanto para den<0, como para num<0 e den<0. isso para corrigir o sinal */
    printf ("%ld/%ld ", (-1 * numerador), (-1 * denominador));
  else {
    /* caso o denominador seja positivo, imprime do jeito que veio, não precisa mudar nada */
    printf ("%ld/%ld ", numerador, denominador);
  }
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  float a = (float)r1.num/r1.den;
  float b = (float)r2.num/r2.den;

  if (a<b)
    return -1;
  
  if (a==b)
    return 0;
  
  if (a>b)
    return 1;
  
  return 7; // se retornar 7 é por que deu tudo errado
}