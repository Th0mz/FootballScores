/*  
    - Ficheiro : lista_ligada.c
    - Autor : Tomas de Araujo Tavares 
    - Numero : 95680

    - Descricao : Definicao da estrutura lista cujos nodes
                guardam informacao de um jogo 
*/

#include "lista_jogos.h"

   
/* Funcoes sobre o jogo */
Jogo* cria_jogo(char *nome, Equipa *equipa1, Equipa *equipa2, int score1, int score2)
{
    /* Cria um novo jogo inicializando-o */
    Jogo *novo_jogo;
    char *nome_jogo;

    /* Alocar memoria */
    novo_jogo = (Jogo*) malloc(sizeof(Jogo));

    /* Inicializar as componentes do jogo */
    nome_jogo = duplica_string(nome);

    novo_jogo->nome = nome_jogo;
    novo_jogo->equipa1 = equipa1;
    novo_jogo->equipa2 = equipa2;
    novo_jogo->resultado[0] = score1;
    novo_jogo->resultado[1] = score2;

    return novo_jogo;
}

Jogo* procura_jogo(ListaJogos *lista, char *nome)
{
    /* Procura na lista o jogo que tem o nome e retorna:
        - NULL : Se o jogo nao se encontrar na lista
        - Jogo* : Ponteiro para o jogo que se esta a procura 
                  se ele estiver na lista   */

    NodeJogo *node_jogo;
    if (lista->inicio == NULL)
        return NULL;
    
    /* Percorrer todos os elementos da lista a procura daquele que tem o nome */
    for(node_jogo = lista->inicio; node_jogo != NULL; node_jogo = node_jogo->proximo)
        if(strcmp(node_jogo->jogo->nome, nome) == 0)
            return node_jogo->jogo;
    
    /* Nenhum jogo tem o nome pertendido */
    return NULL;
}

void altera_resultado(Jogo* jogo, int score1, int score2)
{
    /* Altera o resultado de um jogo */
    jogo->resultado[0] = score1;
    jogo->resultado[1] = score2;
}

void print_jogo(int numero_linha, Jogo *jogo)
{
    /* Da display do jogo no standard output */
    if (jogo == NULL)
        return;

    printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->equipa1->nome, 
                jogo->equipa2->nome, jogo->resultado[0], jogo->resultado[1]);
}

Equipa* vencedor_jogo(Jogo *jogo)
{
    /* Verifica que equipa esta a ganhar o jogo e devolve 
       a mesma equipa se houver empate retorna NULL */

    if (jogo->resultado[0] > jogo->resultado[1])
        return jogo->equipa1;

    if (jogo->resultado[0] < jogo->resultado[1])
        return jogo->equipa2;

    return NULL;
}

void adiciona_vitoria(Jogo *jogo, int quantidade)
{
    /* Adiciona a quantidade de vitorias a equipa que ganhou */
    Equipa *a_ganhar = vencedor_jogo(jogo);

    if (a_ganhar == jogo->equipa1)
        jogo->equipa1->vitorias += quantidade;

    if (a_ganhar == jogo->equipa2)
        jogo->equipa2->vitorias += quantidade;
}

void free_jogo(Jogo *jogo)
{
    /* Liberta memoria de um jogo */
    free(jogo->nome);
    free(jogo);
}


/* Funcoes sobre o node jogo */
NodeJogo* cria_NodeJogo(Jogo *jogo)
{
    /* Cria um novo node de um jogo inicializando-o */
    NodeJogo *node_jogo;

    /* Alocar memoria */
    node_jogo = (NodeJogo*) malloc(sizeof(NodeJogo));

    /* Inicializar as componentes do node */
    node_jogo->jogo = jogo;
    node_jogo->proximo = NULL;

    return node_jogo;
}

void free_NodeJogo(NodeJogo *node_jogo)
{
    /* Liberta memoria de um node jogo */
    free_jogo(node_jogo->jogo);
    free(node_jogo);
}



/* Funcoes sobre lista jogos */
void inicializa_ListaJogos(ListaJogos *lista)
{
    /* Inicializa a lista como sendo uma lista vazia */
    lista->inicio = NULL;
}

void adiciona_jogo(ListaJogos *lista, char *nome, Equipa *equipa1, 
                    Equipa *equipa2, int score1, int score2)
{
    /* Adiciona o jogo passado com argumento ao inicio da lista */
    NodeJogo *novo_jogo;
    Jogo *jogo;

    jogo = cria_jogo(nome, equipa1, equipa2, score1, score2);
    novo_jogo = cria_NodeJogo(jogo);

    novo_jogo->proximo = lista->inicio;
    lista->inicio = novo_jogo;
}

void remove_jogo(ListaJogos *lista, char *nome)
{
    NodeJogo *t, *anterior;

    for (t = lista->inicio, anterior = NULL; t != NULL; anterior = t, t = t->proximo) {
        if(strcmp(t->jogo->nome, nome) == 0) {
            /* Se o elemento a remover for o primeiro elemento da lista */
            if (t == lista->inicio) {
                lista->inicio = lista->inicio->proximo;
                
                free_NodeJogo(t);
                /* Sair do loop */
                break;
            } else {
                anterior->proximo = t->proximo;

                free_NodeJogo(t);
                /* Sair do loop */
                break;
            }
        }
    }
}

void print_ListaJogosReverse(int numero_linha, NodeJogo *incio_lista)
{
    /* Funcao recursiva que da displau de todos os elementos 
          de uma lista so que do fim para o inicio */
    if (incio_lista == NULL)
        return;

    /* Chamada recursiva */
    print_ListaJogosReverse(numero_linha, incio_lista->proximo);

    /* Dar display dos elementos */
    print_jogo(numero_linha, incio_lista->jogo);
}

void free_ListaJogo(ListaJogos *lista)
{
    /* Liberta memoria de uma lista de jogos */
    NodeJogo *jogo, *proximo_jogo;

    jogo = lista->inicio;
    while(jogo != NULL) {
        proximo_jogo = jogo->proximo;
        free_NodeJogo(jogo);
        jogo = proximo_jogo;
    }
}