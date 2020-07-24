#ifndef lista_equipas
#define lista_equipas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao de estruturas */
typedef struct equipa
{
    /* Definicao de equipa que contem:
        - Nome : nome da equipa */
    char *nome;
    int vitorias;
} Equipa;


typedef struct node_equipa
{
    /* Definicao de um node de uma lista que
        guarda os dados de uma equipa */

    Equipa *equipa;
    struct node_equipa *proximo;
} NodeEquipa;


typedef struct lista_Equipas
{
    NodeEquipa *inicio;
} ListaEquipas;


/* Funcoes auxiliares */
char* duplica_string(char *string);

/* Funcoes sobre a estrutura equipa */
void print_equipa(int numero_linha, Equipa *equipa);

/* Funcoes sobre a estrutura lista equipas */
void inicializa_ListaEquipas(ListaEquipas *lista);
void adiciona_equipa(ListaEquipas *lista, char *nome);
Equipa* procura_equipa(ListaEquipas *lista, char *nome);
int procura_equipaVitorias(ListaEquipas *lista, char** nomes_equipas, int vitorias, int posicao, int quantidade);
void mais_vitorias(ListaEquipas *lista, int *max_vitorias, int *quantidade);
void free_ListaEquipas(ListaEquipas *lista);

#endif