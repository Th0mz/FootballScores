/*  
    - Ficheiro : lista_ligada.c
    - Autor : Tomas de Araujo Tavares 
    - Numero : 95685

    - Descricao : Definicao de uma hash table de jogos
*/

#include "hash_jogos.h"

int hash_function(char *string, int tamanho)
{
    /* Funcao que tansfora uma string em 
         um indice da hash table */
        int chave, a = 31415, b = 27183;
    
        for (chave = 0; *string != '\0'; string++, a = a*b % (tamanho-1))
            chave = (a*chave + *string) % tamanho;

        return chave;
}

void inicializa_HashJogos(HashJogos *hash_table, int tamanho)
{
    /* Inicializa a hash table com os seus conteudos */
    int i;

    /* Alocar memoria de um vetor de lista de jogos com TAMANHO_HASH */
    hash_table->tamanho = tamanho;
    hash_table->jogos = (ListaJogos*) malloc(sizeof(ListaJogos*) * tamanho);

    for(i = 0; i < tamanho; i++)
        inicializa_ListaJogos(&(hash_table->jogos[i]));
}


void adicionaJogo_HashJogo(HashJogos *hash_table, char *nome, Equipa *equipa1, Equipa *equipa2, int score1, int score2)
{
    /* Adiciona o jogo com as caracteristicas 
       passadas como argumento a hash table */
    int chave;

    chave = hash_function(nome, hash_table->tamanho);
    adiciona_jogo(&(hash_table->jogos[chave]), nome, equipa1, equipa2, score1, score2);
}

void removeJogo_HashJogo(HashJogos *hash_table, char *nome)
{
    /* Remove o jogo da hash table se ele existir */
    int chave;
    
    chave = hash_function(nome, hash_table->tamanho);
    remove_jogo(&(hash_table->jogos[chave]), nome);
}

Jogo* procuraJogo_HashJogo(HashJogos *hash_table, char *nome)
{
    /* Procura por um jogo na hash table */
    Jogo *jogo;
    int chave;

    chave = hash_function(nome, hash_table->tamanho);
    jogo = procura_jogo(&(hash_table->jogos[chave]), nome);

    return jogo;
}

void free_HashJogo(HashJogos *hash_table)
{
    /* Liberta memoria de uma hash table de jogos */
    int i;

    for (i = 0; i < hash_table->tamanho; i++) 
        free_ListaJogo(&(hash_table->jogos[i]));

    free(hash_table->jogos);
}