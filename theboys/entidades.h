#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conjunto.h"
#include "fprio.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 524600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS 50
#define N_BASES 10
#define N_MISSOES 5246


#ifndef ENTIDADES_H
#define ENTIDADES_H

struct mundo_t {
  int t_inicial;               // tempo inicial = 0
  int t_final;                 // tempo final = 525600
  int tam_mundo;               // tamanho do mundo = 20000
  int hab;                     // número de habilidades = 10
  int herois;      // número de heróis = N_HABILIDADES * 5
  struct heroi_t vherois [50];
  int bases;                   // número de bases = N_HEROIS / 5
  struct base_t vbases [10];      
  int missoes;                 // T_FIM_DO_MUNDO / 100
  struct missao_t vmissoes [T_FIM_DO_MUNDO / 100];
  int relogio;
};  


struct heroi_t {
  int id;                      // = número sequencial [0...N_HEROIS-1]
  int xp;                      // experiência do herói = 0
  int paciencia;               // = número aleatório [0...100]
  int vel;                     // velocidade do herói = número aleatório [50...5000]  (em metros/minuto = 3 Km/h a 300 Km/h)
  struct cjto_t *hab;          // = conjunto com tamanho aleatório [1...3] de habilidades aleatórias
};


struct base_t {
  int id;                      // = número sequencial [0...N_BASES-1]
  int lot;                     // = número aleatório [3...10]
  struct cjto_t *presentes;    // = conjunto vazio (com capacidade para armazenar IDs de heróis até a lotação da base)
  struct fprio *espera;          // fila vaiza
  int local [2];               // = par de números aleatórios [0...N_TAMANHO_MUNDO-1]
};


struct missao_t {
  int id;                      // = número sequencial [0...N_MISSOES-1]
  int local [2];               // = par de números aleatórios [0...N_TAMANHO_MUNDO-1]
  struct cjto_t *hab;          // = conjunto com tamanho aleatório [6...10] de habilidades aleatórias
  int perigo;                  // = número aleatório [0...100] 
};

int cria_mundo (struct mundo_t *p, int ti, int tf, int tam, int ha, int he, int b,int m);


int cria_heroi ();

#endif