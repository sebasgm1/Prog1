#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

long aleat (long min, long max) /* vai gerar o número aleatório de uma maneira muito genial, me pergunte que eu explico */
{
  return min + rand () % (max - min +1);
}


struct racional cria_r (long numerador, long denominador) { /* serve como uma funçao intermediária que armazena o valores do numerador e denominador na struct, muito útil */
  struct racional r;
  r.den = denominador;
  r.num = numerador;
  return r;
}


long absoluto (long x) { /* é equivente a funcao abs, porém funciona para tipos LONG e nao apenas INT */
  if (x<0)
    x = -x;
  return x;
}


long mdc (long a, long b) /* funciona tanto para (a>b) ou (a<b) ou (a<0 e b<0) */
{
  /* atribuir o valor absoluto as variáveis garante que funcione até com números negativos */
  a = absoluto (a);
  b = absoluto (b);
  while (b != 0) {
    long resto = a%b;
    a = b;
    b = resto;
  }
  return a;
}


long mmc (long a, long b) /* apenas fiz o MMC como o comentário dizia pra fazer */
{
  return (a*b) / mdc (a, b);
}


int valido_r (struct racional r) { /* simples assim */
  return r.den != 0;
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


struct racional sorteia_r (long min, long max) { /* usando a funçao aleat, ele junta um númerador aleatório e um denominador aletório na mesma struct (usando a cria_r) */
  long numerador = aleat (min, max);
  long denominador = aleat (min, max);

  return simplifica_r(cria_r(numerador, denominador)); /* sempre vai retornar simplificado */
}


void imprime_r (struct racional r) {
  long numerador = r.num;
  long denominador = r.den;

  if (!valido_r (r)) { /* se o valor for inválido, imprime INVALIDO e já retorna, saindo da função */
      printf ("INVALIDO ");
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


struct racional soma_r (struct racional r1, struct racional r2) { /* foi feito igual se faz no papel */
  long numerador = (r1.num * r2.den) + (r2.num * r1.den);
  long denominador = r1.den * r2.den;

  return simplifica_r (cria_r (numerador, denominador));
}


struct racional subtrai_r (struct racional r1, struct racional r2) { /* foi feito igual a função de soma porém subtraíndo */
  long numerador = (r1.num * r2.den) - (r2.num * r1.den);
  long denominador = r1.den * r2.den;

  return simplifica_r (cria_r (numerador, denominador));
}


struct racional multiplica_r (struct racional r1, struct racional r2) { /* apenas multiplica o numerador com numerador e denominador com denominador */
  long numerador = r1.num * r2.num;
  long denominador = r1.den * r2.den;

  return simplifica_r (cria_r (numerador, denominador));
}


struct racional divide_r (struct racional r1, struct racional r2) { /* repete o primeiro e multiplica pelo inverso do segundo */
  long numerador = r1.num * r2.den;
  long denominador = r2.num * r1.den;

  return simplifica_r (cria_r (numerador, denominador));
}