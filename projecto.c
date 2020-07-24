/*  
    - Ficheiro : projecto.c
    - Autor : Tomas de Araujo Tavares 
    - Numero : 95680

    - Descricao : Sistema de gestao de uma base de dados
                  de jogos de futbol amigaveis.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista_jogos.h"
#include "lista_equipas.h"

#include "hash_jogos.h"
#include "hash_equipas.h"

/* Tamanho maximo de uma string */
#define TAMANHO_MAX 1024

/* Tamanho das hash*/
#define TAMANHO_HASH 911

/* Declaracao de Funcoes */
void obter_comando(HashEquipas *equipas, ListaJogos *jogos_ordenados, HashJogos *jogos);

void a_adiciona_jogo(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos, HashEquipas *equipas);
void l_lista_jogos(int NL, ListaJogos *jogos_ordenados);
void p_procura_jogo(int NL, HashJogos *jogos);
void r_remove_jogo(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos);
void s_altera_resultado(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos);

void A_adiciona_equipa(int NL, HashEquipas *equipas);
void P_procura_equipa(int NL, HashEquipas *equipas);
void g_lista_equipas(int NL, HashEquipas *equipas);

int comparar_string(void const *a, void const *b);



/* Variaveis Globais */
/* Informacao sobre se o programa esta a correr */
int a_correr = 1;

int main() {
    /* Obtem o comando e os seus argumentos, e executa a funcao 
    associada ao comando, enquanto o programa nao for terminado */

    HashEquipas equipas; 

    ListaJogos jogos_ordenados;
    HashJogos jogos;

    inicializa_HashEquipas(&equipas, TAMANHO_HASH);

    inicializa_HashJogos(&jogos, TAMANHO_HASH);
    inicializa_ListaJogos(&jogos_ordenados);


    while(a_correr)
        obter_comando(&equipas, &jogos_ordenados, &jogos);


    return 0;
}


void obter_comando(HashEquipas *equipas, ListaJogos *jogos_ordenados, HashJogos *jogos) {
    /* Le o comando passado pelo standar input e executa 
                a sua funcionaliadade */

    /* Numero da linha do comando de input */
    static int numero_linha = 1;

    char comando;
    comando = getchar();

    switch (comando)
    {
        case 'a':
            a_adiciona_jogo(numero_linha, jogos_ordenados, jogos, equipas);
            numero_linha++;
            break;
        case 'A':
            A_adiciona_equipa(numero_linha, equipas);
            numero_linha++;
            break;
        case 'l':
            l_lista_jogos(numero_linha, jogos_ordenados);
            numero_linha++;
            break;
        case 'p':
            p_procura_jogo(numero_linha, jogos);
            numero_linha++;
            break;
        case 'P':
            P_procura_equipa(numero_linha, equipas);
            numero_linha++;
            break;
        case 'r':
            r_remove_jogo(numero_linha, jogos_ordenados, jogos);
            numero_linha++;
            break;
        case 's':
            s_altera_resultado(numero_linha, jogos_ordenados, jogos);
            numero_linha++;
            break;
        case 'g':
            g_lista_equipas(numero_linha, equipas);
            numero_linha++;
            break;
        case 'x':
            /* Liberta memoria das hash tables e da lista */
            free_ListaJogo(jogos_ordenados);
            free_HashJogo(jogos);
            free_HashEquipas(equipas);
            /* Termina o programa */ 
            a_correr = 0;
            break;
    }
}


void a_adiciona_jogo(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos, HashEquipas *equipas)
{
    /*  - Comando : a nome:equipa1:equipa2:score1:score2
        - Descricao : Adiciona um novo jogo com as caracteristicas
                      passadas pelos argumentos
        - Erros : -> Jogo ja existe na lista
                  -> Alguma das equipas nao existe
     */

    /* Obter argumentos */
    Equipa *equipa1, *equipa2;
    Jogo *jogo;

    char nome[TAMANHO_MAX], equipa1_nome[TAMANHO_MAX], equipa2_nome[TAMANHO_MAX];
    int score1, score2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, 
            equipa1_nome, equipa2_nome, &score1, &score2);

    /* Erros */
    jogo = procuraJogo_HashJogo(jogos, nome);
    if (jogo != NULL) {
        printf("%d Jogo existente.\n", NL);
        return; 
    }

    equipa1 = procura_HashEquipas(equipas, equipa1_nome);
    equipa2 = procura_HashEquipas(equipas, equipa2_nome);
    if (equipa1 == NULL || equipa2 == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    /* Adicionar os elementos */
    adicionaJogo_HashJogo(jogos, nome, equipa1, equipa2, score1, score2);
    adiciona_jogo(jogos_ordenados, nome, equipa1, equipa2, score1, score2);

    /* Verificar quem esta a ganhar o jogo e adiciona a 
            vitoria  a equipa que esta a ganhar*/

    jogo = jogos_ordenados->inicio->jogo;
    adiciona_vitoria(jogo, 1);
}


void l_lista_jogos(int NL, ListaJogos *jogos_ordenados)
{
    /*  - Comando : l 
        - Descricao : Lista todos os jogos por ordem que foram
                      introduzidos
        - Formato Saida : NL nome equipa1 equipa2 score1 score2 
     */

    /* Apenas da print de alguma coisa se houver 
        ja tiverem sido introduzidos jogos */
    if (jogos_ordenados->inicio != NULL) 
        print_ListaJogosReverse(NL, jogos_ordenados->inicio);
}


void p_procura_jogo(int NL, HashJogos *jogos)
{
    /*  - Comando : p nome
        - Descricao : Procura por um jogo que tem como nome
                      o nome passado como argumento
        - Formato Saida : NL nome equipa1 equipa2 score1 score2
        - Erros : -> Jogo nao existe 
     */

    Jogo *jogo;
    char nome[TAMANHO_MAX];

    /* Obter argumento */
    scanf(" %[^:\n]", nome);
    jogo = procuraJogo_HashJogo(jogos, nome);

    /* Erro */
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    
    /* Print do jogo no formato desejado */
    print_jogo(NL, jogo);
}


void r_remove_jogo(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos)
{
    /*  - Comando : r nome
        - Descricao : Remove o jogo que tem como nome
                      o nome passado como argumento
        - Erros : -> Jogo nao existe 
     */

    Jogo *jogo;
    char nome[TAMANHO_MAX];

    /* Obter argumento */
    scanf(" %[^:\n]", nome);
    jogo = procuraJogo_HashJogo(jogos, nome);

    /* Erro */
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /* Verificar quem esta a ganhar o jogo e remover
         a vitoria daquele que esta a ganhar */
    adiciona_vitoria(jogo, -1);    

    /* Remover o jogo */
    removeJogo_HashJogo(jogos, nome);
    remove_jogo(jogos_ordenados, nome);
}

void s_altera_resultado(int NL, ListaJogos *jogos_ordenados, HashJogos *jogos)
{
    /*  - Comando : s nome:score1:score2
        - Descricao : Altera o score de um jogo que tem como
                    nome um nome passado como argumento para
                    um novo score passado por argumento tambem
        - Erros : -> Jogo nao existe 
     */

    Jogo *jogo_hash, *jogo_lista;
    char nome[TAMANHO_MAX];
    int score1, score2;

    /* Obter argumento */
    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    jogo_hash = procuraJogo_HashJogo(jogos, nome);
    jogo_lista = procura_jogo(jogos_ordenados, nome);

    /* Erro */
    if (jogo_hash == NULL || jogo_lista == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /* Remover a vitoria do que esta a ganhar */
    adiciona_vitoria(jogo_hash, -1);

    /* Alterar o resultado do jogo */
    altera_resultado(jogo_hash, score1, score2);
    altera_resultado(jogo_lista, score1, score2);

    /* Atualuzar as vitorias tendo em conta 
          o novo resultado do jogo */
    adiciona_vitoria(jogo_hash, 1);
}

void A_adiciona_equipa(int NL, HashEquipas *equipas)
{
    /*  - Comando : A nome
        - Descricao : Adiciona uma nova equipa com o nome
                      passado pelos argumentos do comando
        - Erros : -> Equipa ja existe 
     */

    char nome[TAMANHO_MAX];
    Equipa *equipa;

    /* Obter argumento */
    scanf(" %[^:\n]", nome);

    equipa = procura_HashEquipas(equipas, nome);

    /* Erros */
    if (equipa != NULL) {
        printf("%d Equipa existente.\n", NL);
        return;
    }

    adiciona_HashEquipas(equipas, nome);
}

void P_procura_equipa(int NL, HashEquipas *equipas)
{
    /*  - Comando : P nome
        - Descricao : Procura por uma equipa com o nome
                      passado pelos argumentos do comando
        - Erros : -> Equipa nao existe
     */

    char nome[TAMANHO_MAX];
    Equipa *equipa;

    /* Obter argumento */
    scanf(" %[^:\n]", nome);

    equipa = procura_HashEquipas(equipas, nome);

    /* Erros */
    if (equipa == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    print_equipa(NL, equipa);
}


int comparar_string(void const *a, void const *b)
{ 
    /* Funcao que comapra duas strings */
    char const *string1 = *(char const **)a;
    char const *string2 = *(char const **)b;

    return strcmp(string1, string2);
}

void g_lista_equipas(int NL, HashEquipas *equipas)
{
    /*  - Comando : g
        - Descricao : Lista todas as equipas com o
                    maior numero de vitorias por ordem
                    lexicografica 
        - Formato de saida : NL Melhores num-vitorias
                             NL * nome-equipa1
                             NL * nome_equipa2
                             ...
    */
    int i;
    int max_vitorias = -1, quantidade = 0;
    char **nomes_equipas;

    /* Calcular o numero de equipas com numero maximo de vitorias */
    maior_numero_vitorias(equipas, &max_vitorias, &quantidade);

    if (max_vitorias != -1) {
        /* Juntar todos os nomes das equipas com vitorias igual a max_vitorias */
        nomes_equipas = (char**) malloc(sizeof(char*) * quantidade);
        procura_equipasVitoriaHash(equipas, nomes_equipas, max_vitorias, quantidade);

        /* Organizar por ordem alfabetica */
        qsort(nomes_equipas, quantidade, (sizeof(char*)), comparar_string);


        /* formato de saida do nome das equipas com  
         vitorias max_vitorias por ordem alfabetica */
        printf("%d Melhores %d\n", NL, max_vitorias);

        /* Print dos nomes das equipas */   
        for (i = 0; i < quantidade; i++)
            printf("%d * %s\n",NL, nomes_equipas[i]);

        /* Liberta a memoria da lista de strings */
        free(nomes_equipas);
    }
}
