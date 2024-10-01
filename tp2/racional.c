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

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

int valido_r (struct racional r) {
  if (r.den = 0)
    return 0;
  return 1;
}


/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  /* implemente aqui */
}

/* Vai me auxiliar no MDC */
long modulo (long x) { 
  if (x<0)
    x = -x;
  return x;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
  /* Os módulos garamtem que o MDC sempre dará certo */
  a = modulo (a);
  b = modulo (b);
  while (b != 0) {
    long resto = a&b;
    a = b;
    b = resto;
  }
  return a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return (a*b) / mdc (a, b);
}

struct racional cria_r (long numerador, long denominador) {
  struct racional r;
  r.num = numerador;
  r.den = denominador;
  return r;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  if (!valido (r))
    return r;

  long divisor = mdc (r.num, r.den);
  long a = r.num/divisor; /* simplificado */
  long b = r.den/divisor; /* simplificado */

  if (b < 0)
    return cria_r (-a, -b);
  

  /* implemente aqui */
}


void imprime_r (struct racional r) {
}


/* implemente as demais funções de racional.h aqui */
