#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entidades.h"
#include "conjunto.h"
#include "lista.h"
#include "fprio.h"


#define T_INICIO 0
#define T_FIM_DO_MUNDO 524600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS 50
#define N_BASES 10
#define N_MISSOES 5246


int aleat (int min, int max){
  return  min + (rand() % max-min+1);
}

// Cria o mundo e inicializa todas suas variáveis
// Retorna 1 se der certo, 0 em caso de erro
int cria_mundo (struct mundo_t *p, int ti, int tf, int tam, int ha, int he, int b,int m) {
  struct mundo_t *mundo = malloc (sizeof (struct mundo_t));
  if (mundo == NULL)
    return 0;
  
  p = mundo;
  
  mundo->t_inicial = ti;          // 0;
  mundo->t_final = tf;            // 524600;
  mundo->tam_mundo = tam;         // 20000;
  mundo->hab = ha;                // 10;
  mundo->herois = he;             // 50;
  // cria_heroi (mundo);                    // TEM QUE ARRUMAR ESSA FUNÇÃO


  mundo->bases = b;               // 10;
  if (cria_base(mundo))
    printf ("Criou a base!\n");
  else
    printf ("ERRO: Não criou a base\n");
  

  mundo->missoes = m;             // 5256;
  if (cria_missoes (mundo))
    printf ("Criou todas as missões!\n"):
  else
    printf ("ERRO: Não criou alguma missão");
  
  return 1;
}

struct cjto_t *cria_hab () {
  int hab = 0;

  struct cjto_t *habilidades = cjto_cria (10);      
  if (habilidades == NULL)
    return NULL;


  int num_hab = aleat (1, 3);

  for (int i=0; i<num_hab; i++) {
    hab = aleat (0, 9);

    while (cjto_pertence (habilidades, hab))       // Já pertence? então acha outro valor
      hab = aleat (0, 9);

    cjto_insere (habilidades, hab);
  }

  return habilidades;
}


// Cria um herói só e inicializa todas suas variáveis
// Retorna 1 se der certo, 0 em caso de erro
int cria_herois (struct mundo_t *mundo, int he) {
  for (int id=0; id<he-1; id++) {
    mundo->vherois[id].id = id;
    mundo->vherois[id].xp = 0;
    mundo->vherois[id].paciencia = aleat (0, 100);
    mundo->vherois[id].vel = aleat (50, 5000);

    mundo->vherois[id].hab = cjto_aleat (3, 10);
    if (mundo->vherois[id].hab == NULL)
      return 0;
  
  }
  return 1;
}
// a capacidade do conjunto é 10 (0 a 9) e a cardinalidade deve ser no maximo 3


// Função que vai cria uma base e preencher seus campos aleatoriamente
// Retorna o 1 se deu certo, em caso de erro retorna 0
int cria_base (struct mundo_t *mundo) {
  for (int id = 0; id<mundo->bases; id++) {
    mundo->vbases[id].id = id;
    mundo->vbases[id].lot = aleat (3, 10);

    struct cjto_t *present = malloc (sizeof (struct cjto_t));
    if (present == NULL) {
      return 0;
    }
    mundo->vbases[id].presentes = present;

    struct fprio *fila_p = malloc (sizeof (struct fprio_t));
    if (fila_p == NULL) {
      free (mundo->vbases[id].presentes);
      return 0;
    }
    mundo->vbases[id].espera = fila_p;

    mundo->vbases[id].local [0] = aleat (0, 20000);
    mundo->vbases[id].local [1] = aleat (0, 20000);
  }

  return 1;
}


// Cria todas as missões
// Se der boa, retorna 1, deu ruim, retorna 0
int cria_missoes (struct mundo_t *mundo) {
  int cap = 0;

  for (int id=0; id<T_FIM_DO_MUNDO / 100; id++) {
    mundo->vmissoes[id].id = id;
    mundo->vmissoes[id].local[0] = aleat (0, N_TAMANHO_MUNDO-1);
    mundo->vmissoes[id].local[1] = aleat (0, N_TAMANHO_MUNDO-1);

    cap = aleat (6, 10);
    mundo->vmissoes[id].hab = cjto_aleat (aleat (0, cap-1), cap);
    if (mundo->vmissoes[id].hab == NULL) {
      printf ("Não criou o conjunto da missão %d\n", id);
      return 0;
    }
    
    mundo->vmissoes[id].perigo = aleat (0, 100);
  }
  return 1;
}




// serve só pra testar tudo foi feito
int main () {
  srand(0);

  // Inicializa variaveis auxiliares pra criar o heroi
    int paci = 0;
    int vel = 0;
    int xp = 0;
    struct cjto_t *habilidades = NULL;


  // Incializa os ponteiros de cada TAD
  struct mundo_t *mundo = NULL;
  // struct base_t *base;
  // struct missao *missao;


  // inicializa os valores do mundo, pra testar mesmo
  int t_inicial = 0;
  int t_final = 524600;
  int tam_mundo = 20000;
  int n_habilidades = 10;
  int n_herois = 50;
  int n_bases = 10;
  int n_missoes = 5256;


  // Aloca dinamincamente cada um deles
  if (cria_mundo(&mundo, t_inicial, t_final, tam_mundo, n_habilidades, n_herois, n_bases, n_missoes))
    printf ("Criou o mundo!\n");
  else
    printf ("ERRO -> cria_tudo: ao criar o mundo\n");

  

  return 0;
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
  //      struct heroi_t *pheroi;   // ponteiro pro heroi
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

