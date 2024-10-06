#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

int valido_r (struct racional r) {
  return (r.den != 0); /* quer dizer se for diferente de 0, return 1, else return 0 */
}


long absoluto (long x) { /* funçao abs que funciona para tipos LONG e nao apenas INT */
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
  if (!valido_r (r))
    return r;
  
  long divisor = mdc (r.num, r.den);

  if (r.den<0) { /* se apenas o DEN for NEGATIVO, já abrangindo o caso do NUM e DEN serem ambos negativos */  
    r.num = -1* r.num / divisor;
    r.den = -1* r.den / divisor;

    return r;
  }
  /* se chegou até aqui, é por que NUM é negativo ou tanto NUM como DEN são positivos */
  r.num /= divisor;
  r.den /= divisor;

  return r;
}


struct racional cria_r (long numerador, long denominador) {
  struct racional r;
  r.num = numerador;
  r.den = denominador;

  return simplifica_r(r);
}


long aleat (long min, long max) {
  return min + rand () % (max - min +1);
}


long mmc (long a, long b) {
  return (a*b) / mdc (a, b);
}


struct racional sorteia_r (long min, long max) { /* usando a funçao aleat, ele junta um númerador aleatório e um denominador aletório na mesma struct (usando a cria_r) */
  long numerador = aleat (min, max);
  long denominador = aleat (min, max);

  return cria_r(numerador, denominador); /* sempre vai retornar simplificado */
}


void imprime_r (struct racional r) {
  if (!valido_r (r)) {
      printf ("NaN ");
      return;
  }
  r = simplifica_r (r);
  
  if (r.den == 1 || r.num == 0) {/* se o num for 0, se o den for 1, se o num = den, vai fincionar */
    printf ("%ld ", r.num);
    return;
  }

  if (r.den<0) /* vale tanto para den<0, como para num<0 e den<0. isso para corrigir o sinal */
    printf ("%ld/%ld ", (-1 * r.num), (-1 * r.den));
  else {
    /* caso o denominador seja positivo, imprime do jeito que veio, não precisa mudar nada */
    printf ("%ld/%ld ", r.num, r.den);
  }
  return;
}


int compara_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  long a = r1.num * r2.den;
  long b = r1.den * r2.num;

  if (a<b)
    return -1;
  
  if (a==b)
    return 0;
  
  if (a>b)
    return 1;
  
  return 7; /* se retornar 7 é por que deu tudo errado */
}


int soma_r (struct racional r1, struct racional r2, struct racional *r3){
  if (!valido_r(r1) || !valido_r (r2))
    return 0;
  
  long divisor = mmc (r1.den, r2.den);
  long a = (divisor/r1.den)*r1.num;
  long b = (divisor/r2.den)*r2.num;

  r3->num = a+b;
  r3->den = divisor;

  *r3 = simplifica_r(*r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;
  
  long divisor = mmc (r1.den, r2.den);
  long a = (divisor/r1.den)*r1.num;
  long b = (divisor/r2.den)*r2.num;

  r3->num = a-b;
  r3->den = divisor;

  *r3 = simplifica_r(*r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;

  r3->num = r1.num*r2.num;
  r3->den = r1.den*r2.den;

  *r3 = simplifica_r(*r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;

  r3->num = r1.num*r2.den;
  r3->den = r1.den*r2.num;

  *r3 = simplifica_r(*r3);

  if (r3->num == 0)
    return 0;

  return 1;
}