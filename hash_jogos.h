#ifndef hash_jogos
#define hash_jogos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_jogos.h"

typedef struct hash_Jogo
{
        /* Definicao de uma hash table que guarda jogos
    contendo um ponteiro para um vetor de listas de jogos */

    ListaJogos *jogos;
    int tamanho;
} HashJogos;

int hash_function(char *string, int tamanho);

void inicializa_HashJogos(HashJogos *hash_table, int tamanho);
void adicionaJogo_HashJogo(HashJogos *hash_table, char *nome, Equipa *equipa1, Equipa *equipa2, int score1, int score2);
void removeJogo_HashJogo(HashJogos *hash_table, char *nome);
Jogo* procuraJogo_HashJogo(HashJogos *hash_table, char *nome);
void free_HashJogo(HashJogos *hash_table);

#endif