#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

struct mundo {
  int t_inicial;               // tempo inicial = 0
  int t_final;                 // tempo final = 525600
  int tam_mundo;               // tamanho do mundo = 20000
  int hab;                     // número de habilidades = 10
  int herois;                  // número de heróis = N_HABILIDADES * 5
  int bases;                   // número de bases = N_HEROIS / 5
  int missoes;                 // T_FIM_DO_MUNDO / 100
};  


struct heroi {
  int id;                      // = número sequencial [0...N_HEROIS-1]
  int xp;                      // experiência do herói = 0
  int paciencia;               // = número aleatório [0...100]
  int vel;                     // velocidade do herói = número aleatório [50...5000]  (em metros/minuto = 3 Km/h a 300 Km/h)
  struct cjto_t *hab;          // = conjunto com tamanho aleatório [1...3] de habilidades aleatórias
};


struct base {
  int id;                      // = número sequencial [0...N_BASES-1]
  int local [2];               // = par de números aleatórios [0...N_TAMANHO_MUNDO-1]
  int lot;                     // = número aleatório [3...10]
  struct cjto_t *presentes;    // = conjunto vazio (com capacidade para armazenar IDs de heróis até a lotação da base)
  // fila de espera            // fila vaiza
};


struct missao {
  int id;                      // = número sequencial [0...N_MISSOES-1]
  int local [2];               // = par de números aleatórios [0...N_TAMANHO_MUNDO-1]
  int *hab;                    // = conjunto com tamanho aleatório [6...10] de habilidades aleatórias
  int perigo;                  // = número aleatório [0...100] 
};

int cria_mundo (struct mundo *p, int ti, int tf, int tam, int ha, int he, int b,int m);


int cria_heroi ();