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

/* Cria um número racional com o numerador e denominador indicados
 * e retorna um ponteiro que aponta para ele.
 * A memória para o número racional deve ser alocada dinamicamente
 * por esta função. Retorna NULL se não conseguiu alocar a memória. */
struct racional *cria_r (long numerador, long denominador) {
  struct racional *r = malloc (sizeof (struct racional));

  if (r == NULL) {
    printf ("cria_r -> nao pôde alocar memória\n");
    return NULL;
  }

  r->num = numerador;
  r->den = denominador;
  return r;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r (struct racional *r) {
  if (r != NULL)
    free (r);
}


long absoluto (long x) { /* funçao abs que funciona para tipos LONG e nao apenas INT */
  if (x<0)
    x = -x;
  return x;
}


long mdc (long a, long b)
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


long mmc (long a, long b)
{
  return (a*b) / mdc (a, b);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. Um racional
 * é inválido se o denominador for zero ou se ele não tiver sido alocado. */
int valido_r (struct racional *r) {
  return (r->den != 0 && r != NULL); /* se der V e V retorna 1, se pelo menos um der F, retorna 0 */
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
void simplifica_r (struct racional *r)
{
  if (!valido_r (r))
    return;
  
  long divisor = mdc (r->num, r->den);

  if (r->den<0) { /* se apenas o DEN for NEGATIVO, já abrangindo o caso do NUM e DEN serem ambos negativos */  
    r->num = -1 * r->num / divisor;
    r->den = -1 * r->den / divisor;

    return;
  }
  /* se chegou até aqui, é por que NUM é negativo ou tanto NUM como DEN são positivos */
  r->num /= divisor;
  r->den /= divisor;

  return;
}


/* Imprime um racional r, respeitando estas regras:
   - o racional deve estar na forma simplificada;
   - não use espacos em branco e não mude de linha;
   - o formato de saída deve ser "num/den", a menos dos casos abaixo;
     - se o ponteiro for nulo, imprime a mensagem "NULL";
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal é impresso antes do número;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional *r) {

  if (!valido_r (r)) {
    if (r == NULL) {
      printf (" NULL");
      return;
    }
      printf (" NaN");
      return;
  }
  
  simplifica_r (&r);
  
  if (r->den == 1 || r->num == 0) {/* se o num for 0, se o den for 1, se o num = den, vai fincionar */
    printf (" %ld", r->num);
    return;
  }

  if (r->den<0) /* vale tanto para den<0, como para num<0 e den<0. isso para corrigir o sinal */
    printf (" %ld/%ld", (-1 * r->num), (-1 * r->den));
  else {
    /* caso o denominador seja positivo, imprime do jeito que veio, não precisa mudar nada */
    printf (" %ld/%ld", r->num, r->den);
  }
  return;
}


/* Compara dois números racionais r1 e r2.
 * Retorna -2 se r1 ou r2 for inválido ou se o respectivo ponteiro for nulo.
 * Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2.
 * Atenção: faça a comparação normalizando os denominadores pelo MMC.
 * Fazer a comparação baseado na divisão do numerador pelo denominador
 * pode gerar erro de arredondamento e falsear o resultado. */
int compara_r (struct racional *r1, struct racional *r2) {
  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  long a = r1->num * r2->den;
  long b = r1->den * r2->num;

  if (a<b)
    return -1;
  
  if (a==b)
    return 0;
  
  if (a>b)
    return 1;
  
  return 7; /* se retornar 7 é por que deu tudo errado */
}


/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;
  
  long divisor = mmc (r1->den, r2->den);
  long a = (divisor/r1->den)*r1->num;
  long b = (divisor/r2->den)*r2->num;

  r3->num = a+b;
  r3->den = divisor;

  simplifica_r (&r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;
  
  long divisor = mmc (r1->den, r2->den);
  long a = (divisor/r1->den)*r1->num;
  long b = (divisor/r2->den)*r2->num;

  r3->num = a-b;
  r3->den = divisor;

  simplifica_r(&r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;

  r3->num = r1->num*r2->num;
  r3->den = r1->den*r2->den;

  simplifica_r(&r3);

  if (r3->num == 0)
    return 0;

  return 1;
}


/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r (r2))
    return 0;

  r3->num = r1->num*r2->den;
  r3->den = r1->den*r2->num;

  simplifica_r(&r3);

  if (r3->num == 0)
    return 0;

  return 1;
}

/* implemente as demais funções de racional.h aqui */