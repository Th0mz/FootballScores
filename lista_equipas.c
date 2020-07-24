/*  
    - Ficheiro : lista_ligada.c
    - Autor : Tomas de Araujo Tavares 
    - Numero : 95680

    - Descricao: Definicao da estrutura lista cujos nodes
                  guardam informacao de uma equipa 
*/

#include "lista_equipas.h"

char* duplica_string(char *string)
{
    /* Cria um ponteiro com o tamanho necessario para 
        guardar a string passada como argumento */
        
    char *string_duplicada;
    string_duplicada = (char*) malloc((strlen(string) + 1));
    strcpy(string_duplicada, string);

    return string_duplicada;
}



/* Funcoes sobre equipa */
Equipa* cria_equipa(char *nome)
{   
    /* Cria uma nova equipa inicializando-a */
    Equipa *nova_equipa;
    char *nome_equipa;

    /* Alocar memoria */
    nova_equipa = (Equipa*) malloc(sizeof(struct equipa));

    /* Inicializar as componentes da equipa */
    nome_equipa = duplica_string(nome);
    nova_equipa->nome = nome_equipa;
    nova_equipa->vitorias = 0;

    return nova_equipa;
}

void print_equipa(int numero_linha, Equipa *equipa)
{
    /* Da display da equipa no standard output */
    if (equipa == NULL)
        return;

    printf("%d %s %d\n", numero_linha, equipa->nome, equipa->vitorias);
}

void free_equipa(Equipa *equipa)
{
    /* Liberta memoria de uma equipa */
    free(equipa->nome);
    free(equipa);
}



/* Funcoes sobre node equipa */
NodeEquipa* cria_NodeEquipa (Equipa *equipa)
{
    /* Cria um novo node de uma equipa inicializando-o */
    NodeEquipa *node_equipa;

    /* Alocar memoria */
    node_equipa = (NodeEquipa*) malloc(sizeof(struct node_equipa));

    /* Inicializar as componentes do node */
    node_equipa->equipa = equipa;
    node_equipa->proximo = NULL;

    return node_equipa;
}

void free_NodeEquipa(NodeEquipa *node_equipa)
{
    /* Liberta memoria de um node equipa */
    free_equipa(node_equipa->equipa);
    free(node_equipa);
}


/* Funcoes sobre ListasJogos */
void inicializa_ListaEquipas(ListaEquipas *lista)
{
    /* Inicializa a lista como sendo uma lista vazia */
    lista->inicio = NULL;
}


void adiciona_equipa(ListaEquipas *lista, char *nome)
{
    /* Adiciona a equipa passada como argumento ao inicio da lista */
    NodeEquipa *nova_equipa;
    Equipa *equipa;

    equipa = cria_equipa(nome);
    nova_equipa = cria_NodeEquipa(equipa);

    nova_equipa->proximo = lista->inicio;
    lista->inicio = nova_equipa;
}

Equipa* procura_equipa(ListaEquipas *lista, char *nome)
{
    /* Procura na lista a equipa que tem o nome e retorna:
        - NULL : Se a equipa nao se encontrar na lista
        - Equipa* : Ponteiro para a equipa que se esta a procura 
                  se ela estiver na lista   */

    NodeEquipa *node_equipa;
    if (lista->inicio == NULL)
        return NULL;
    
    /* Percorrer todos os elementos da lista a procura daquele que tem o nome */
    for(node_equipa = lista->inicio; node_equipa != NULL; node_equipa = node_equipa->proximo)
        if(strcmp(node_equipa->equipa->nome, nome) == 0)
            return node_equipa->equipa;
    
    /* Nenhum jogo tem o nome pertendido */
    return NULL;
}

int procura_equipaVitorias(ListaEquipas *lista, char** nomes_equipas, int vitorias, int posicao, int quantidade)
{
    /* Procura na lista de equipas os jogos com o numero de vitorias 
    passadas como argumento e adiciona o seu nome a lista de nomes de 
     equipas no fim retorna a proxima posicao a adiocionar o nome */

    NodeEquipa *node_equipa;
    if (lista->inicio == NULL)
        return posicao;

    /* Percorrer todas as equipas a procura daquelas que tem o numero de vitorias */
    for(node_equipa = lista->inicio; node_equipa != NULL; node_equipa = node_equipa->proximo) {
        if(node_equipa->equipa->vitorias == vitorias) {
            nomes_equipas[posicao] = node_equipa->equipa->nome;
            posicao++;

            if(quantidade == posicao)
                return posicao;
        }
    }

    
    return posicao;
}

void mais_vitorias(ListaEquipas *lista, int *max_vitorias, int *quantidade)
{
    /* Percorre toda a lista a procura da equipa com mais
         vitorias e altera o numero max_vitorias e a
    quantidade de equipas que tem esse numero de vitorias */

    NodeEquipa *node_equipa;

    /* Lista Vazia */
    if (lista->inicio == NULL) {
        return;
    }

    for(node_equipa = lista->inicio ; node_equipa != NULL; node_equipa = node_equipa->proximo) {
        if (node_equipa->equipa->vitorias > *max_vitorias) {
            *max_vitorias = node_equipa->equipa->vitorias;
            *quantidade = 1;
        } else if (node_equipa->equipa->vitorias == *max_vitorias)
            *quantidade += 1;
    }
}

void free_ListaEquipas(ListaEquipas *lista)
{
    /* Liberta memoria de uma lista de equipas */
    NodeEquipa *equipa, *proxima_equipa;

    equipa = lista->inicio;
    while(equipa != NULL) {
        proxima_equipa = equipa->proximo;
        free_NodeEquipa(equipa);
        equipa = proxima_equipa;
    }
}



