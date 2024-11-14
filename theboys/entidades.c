#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entidades.h"
#include "conjunto.h"



// Cria o mundo e inicializa todas suas variáveis
// Retorna 1 se der certo, 0 em caso de erro
int cria_mundo (struct mundo *p, int ti, int tf, int tam, int ha, int he, int b,int m) {
  struct mundo *mundo = malloc (sizeof (struct mundo));
  if (mundo == NULL)
    return 0;
  
  p = mundo;
  
  mundo->t_inicial = ti;      // 0;
  mundo->t_final = tf;        // 524600;
  mundo->tam_mundo = tam;     // 20000;
  mundo->hab = ha;            // 10;
  mundo->herois = he;         // 50;
  mundo->bases = b;           // 10;
  mundo->missoes = m;         // 5256;
  return 1;
}


// Cria um herói só e inicializa todas suas variáveis
// Retorna 1 se der certo, 0 em caso de erro
int cria_heroi (struct heroi *p, int id) {
  struct heroi *heroi = malloc (sizeof (struct heroi));
  if (heroi == NULL)
    return 0;
  
  p = heroi;

  heroi->id = id;
  heroi->xp = 0;
  heroi->paciencia = rand() % 101;
  heroi->vel = 50 + (rand() % 5000-50+1); // vai encontrar um número ente 50 e 5000

  int num_habilidades = 1 + (rand() % 3);
  heroi->hab = cjto_cria (num_habilidades);   // TA ERRADO ISSO AQUI, tenho que criar as habilidades 

  for (int i=0; i<num_habilidades) {
    int hab_sorteada = rand() % 10;
    while (cjto_pertence(heroi->hab->flag, hab_sorteada)) {  // pertence?, se sim, sorteia um novo
      int hab_sorteada = rand() % 10;
    }
    
    cjto_insere (heroi->hab->flag, hab_sorteada);    // As habilidades vao ser sorteadas de 1 a 10
  }

  return 1;
}
// a capacidade do conjunto é 10 (0 a 9) e a cardinalidade deve ser no maximo 3


// serve só pra testar tudo foi feito
void cria_tudo () {
  srand(0);

  // Incializa os ponteiros de cada TAD
  struct mundo *mundo;
  struct heroi *heroi;
  struct base *base;
  struct missao *missao;

  // inicializa os valores do mundo, pra testar mesmo
  int t_inicial = 0;
  int t_final = 524600;
  int tam_mundo = 20000;
  int n_habilidades = 10;
  int n_herois = 50;
  int n_bases = 10;
  int n_missoes = 5256;

  // Aloca dinamincamente cada um deles
  if (cria_mundo(mundo, t_inicial, t_final, tam_mundo, n_habilidades, n_herois, n_bases, n_missoes))
    printf ("Criou o mundo\n");
  else
    printf ("ERRO ao criar o mundo\n");


  // cria 50 heróis, cada um com seu ID
  for (int i = 0; i<50; i++) {
    if (cria_heroi(heroi, i))
      printf ("Criou o Heroi %d!\n", i);
    else
      printf ("ERRO ao criar o Herói %d!\n", i);
  }


  


}



/* =================== DUVIDAS =================*/
  // 1) O que quer dizer "Ignora se item não estiver entre 0 e CAP-1"? 

  //    Insere um item no conjunto. Ignora se item não estiver entre 0 e CAP-1.
  //    Retorno: número de itens no conjunto após a operação ou -1 em erro.
  //    int cjto_insere (struct cjto_t *c, int item) ;


  // 2) Percebi que eu vou criar um monte de heróis e pensei em armazenar
  //    todos os ponteiros para as struts deles numa lista!, dai a medida que ele morre
  //    retiro ele da lista e ela já se organiza.
  //    Nesse caso eu teria que mudar a struct pra ter um ponteiro pro herói
  

  //    ====== ANTES
  //    struct item_t
  //    {
  //      int valor ;			        // valor do item
  //      struct item_t *ant ;		// item anterior
  //      struct item_t *prox ;	  // próximo item
  //     } ;
  //
  //
  //    ====== DEPOIS
  //    struct item_t
  //    {
  //      int id ;			          // id do herói
  //      struct item_t *ant ;		// item anterior
  //      struct item_t *prox ;	  // próximo item
  //      struct heroi *pheroi;   // ponteiro pro heroi
  //     } ;
  //
  //      Nesse caso pra apontar pra struct herói definida no entidades.h
  //      Isso dá certo?, uma struct do lista.h apontando pra struct do
  //      entidades.h


  //               PENSAMENTOS LIVRES

  // 3) Eu vou usar o conjunto pra armazenar quais heróis estao vivos
  
  // 4) Posso também usar o conjunto pra armazenar quais habilidades estão presentes naquela base

  // 5) Acho que seria melhor usar a lista pra determinar quais poderes o heroi tem

  // 6) Na verdade vai ser melhor fazer tudo em conjutos com vetor booleano
  //    pois depois eu vou poder fazer a união (de poderes por exemplo), intersecção...

