#ifndef lista_jogos
#define lista_jogos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_equipas.h"

/* Numero de resultados de cada jogo(2 - uma para cada equipa) */
#define NUM_SCORES 2

/* Definicao de estruturas */
typedef struct jogo
{
    /* Definicao de jogo que contem:
        - Nome : nome do jogo
        - Equipa1, Equipa2: Equipas que participam no jogo
        - Resultado : Resultado do jogo */
            
    char *nome;
    Equipa *equipa1, *equipa2;
    int resultado[NUM_SCORES];
} Jogo;


typedef struct node_jogo
{
    /* Definicao de um node de uma lista que
        guarda os dados de um jogo */
            
    Jogo *jogo;
    struct node_jogo *proximo;
} NodeJogo;


typedef struct lista_Jogos
{
    /* Definicao de uma lista de jogos um lista
    com um ponteiro para um node de um jogo */

    NodeJogo *inicio;
} ListaJogos;



/* Funcoes sobre a estrutura jogo */
Jogo* procura_jogo(ListaJogos *lista, char *nome);
void altera_resultado(Jogo* jogo, int score1, int score2);
void print_jogo(int numero_linha, Jogo *jogo);
void adiciona_vitoria(Jogo *jogo, int quantidade);


/* Funcoes sobre a estrutura lista_jogos */
void inicializa_ListaJogos(ListaJogos *lista);
void adiciona_jogo(ListaJogos *lista, char *nome, Equipa *equipa1, Equipa *equipa2, int score1, int score2);
void remove_jogo(ListaJogos *lista, char *nome);
void print_ListaJogosReverse(int numero_linha, NodeJogo *incio_lista);
void free_ListaJogo(ListaJogos *lista);

#endif