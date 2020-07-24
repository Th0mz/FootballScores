/*  
    - Ficheiro : hash_equipas.c
    - Autor : Tomas de Araujo Tavares 
    - Numero : 95680

    - Descricao : Definicao de uma hash table de equipas
*/

#include "hash_equipas.h"

void inicializa_HashEquipas(HashEquipas *hash_table, int tamanho)
{
    /* Inicializa a hash table com as suas caracteristicas */
    int i;

    /* Alocar memoria de um vetor de lista de jogos com TAMANHO_HASH */
    hash_table->tamanho = tamanho;
    hash_table->equipas = (ListaEquipas*) malloc(sizeof(ListaEquipas*) * tamanho);

    for(i = 0; i < tamanho; i++)
        inicializa_ListaEquipas(&(hash_table->equipas[i]));
}

void adiciona_HashEquipas(HashEquipas *hash_table, char *nome_equipa)
{
    /* Adiciona um nova equipa a hash table com as 
        caracteristicas passados como arugmento */
    int chave;

    chave = hash_function(nome_equipa, hash_table->tamanho);
    adiciona_equipa(&(hash_table->equipas[chave]), nome_equipa);
}

Equipa* procura_HashEquipas(HashEquipas *hash_table, char *nome_equipa)
{
    /* Procura a equipa que tem o nome na hash_table */
    Equipa *equipa;
    int chave;

    chave = hash_function(nome_equipa, hash_table->tamanho);
    equipa = procura_equipa(&(hash_table->equipas[chave]), nome_equipa);

    return equipa;
}

void procura_equipasVitoriaHash(HashEquipas *hash_table, char** nomes_equipas, int vitorias, int quantidade)
{
    /* Percorre todas as listas da hash a procuca das equipas que tem
      o numero de vitorias pertendido adicionando o seu nome a lista */

    int i, posicao = 0;

    for (i = 0; i < hash_table->tamanho; i++) {
        posicao = procura_equipaVitorias(&(hash_table->equipas[i]), nomes_equipas, vitorias, posicao, quantidade);
        
        if (posicao >= quantidade)
            return;
    }
}

void maior_numero_vitorias(HashEquipas *hash_table, int *max_vitorias, int *quantidade)
{
    /* Percorre toda a hash table a procuca da equipa com
       mais vitorias alterando assim os valores de max_vitorias
       e quantidade */

    int i;

    for (i = 0; i < hash_table->tamanho; i++) {
        mais_vitorias(&(hash_table->equipas[i]), max_vitorias, quantidade);        
    }
}

void free_HashEquipas(HashEquipas *hash_table)
{
    /* Liberta memoria de uma hash table de equipas */
    int i;

    for (i = 0; i < hash_table->tamanho; i++) 
        free_ListaEquipas(&(hash_table->equipas[i]));

    free(hash_table->equipas);
}