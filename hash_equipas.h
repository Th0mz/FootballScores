#ifndef hash_equipas
#define hash_equipas

#include "lista_equipas.h"
#include "hash_jogos.h"

typedef struct hash_Equipas
{
        /* Definicao de uma hash table que guarda jogos
    contendo um ponteiro para um vetor de listas de jogos */

    ListaEquipas *equipas;
    int tamanho;
} HashEquipas;


void inicializa_HashEquipas(HashEquipas *hash_table, int tamanho);
void adiciona_HashEquipas(HashEquipas *hash_table, char *nome_equipa);
Equipa* procura_HashEquipas(HashEquipas *hash_table, char *nome_equipa);
void procura_equipasVitoriaHash(HashEquipas *hash_table, char** nomes_equipas, int vitorias, int quantidade);
void maior_numero_vitorias(HashEquipas *hash_table, int *max_vitorias, int *quantidade);
void free_HashEquipas(HashEquipas *hash_table);

#endif