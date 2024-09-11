/* Ian Patrick da Costa Soares                      */
/* Turma 28.1                                       */
/* Exercício 1: Torre de Controle                   */
/*                                                  */
/* Programa compilado com Visual Studio Code 1.92.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Incluir as bibliotecas usadas */

typedef struct Voo noh;
/* Definir um sinônimo para a struct Voo */

void iniciarVariaveis();
void imprimirCabecalho();
void fecharArquivos();
noh *Noh();
void lerLinhas();
void gerenciarComandos(char *info[]);
void pedePouso(char *info[]);
void pistaLiberada();
void urgencia(char *info[]);
void escreverELiberar();
/* Declaração de funções */

struct Voo
{
    char flight[5];
    char from[30];
    noh *prox;
};
/* Criação da struct Voo */

FILE *entrada = NULL;
FILE *saida = NULL;
noh *start = NULL;
/* Declaração de variáveis */

void iniciarVariaveis()
{
    entrada = fopen("data/entrada1.txt", "r");
    saida = fopen("output/saida1.txt", "w");
    if (entrada == NULL || saida == NULL)
    {
        perror("Erro ao abrir arquivos");
        exit(1);
    }
    start = Noh();
    imprimirCabecalho();
}
/* Abre os arquivos, cria um noh e imprime o cabecalho */
/*--------------------------------------------------*/

void imprimirCabecalho()
{
    fprintf(saida, "Bla bla bla\n");
    fprintf(saida, "Ble\n");
    fprintf(saida, "AUTORIZACOES DE POUSO\n");
    fprintf(saida, "=========================================\n");
    fprintf(saida, "FLIGHT  FROM\n");
    fprintf(saida, "\n");
}
/* Imprime o cabecalho */
/*--------------------------------------------------*/

void fecharArquivos()
{
    if (entrada != NULL)
    {
        fclose(entrada);
    }
    if (saida != NULL)
    {
        fclose(saida);
    }
}
/* Fecha os arquivos */
/*--------------------------------------------------*/

noh *Noh()
{
    noh *novoNoh = (noh *)malloc(sizeof(noh));
    if (novoNoh == NULL)
    {
        perror("Erro ao alocar memória");
        exit(1);
    }
    novoNoh->prox = NULL; /* Novos voos não possuem voos seguintes, como padrão */
    return novoNoh;
}
/* Dinamiza a criação de um noh */
/*--------------------------------------------------*/

void lerLinhas()
{
    char linha[70] = "";
    int flag = 0;

    while (fgets(linha, sizeof(linha), entrada) != NULL)
    {
        linha[strcspn(linha, "\r\n")] = '\0';

        if (!flag)
        {
            if (strncmp(linha, "INICIO", 6) == 0)
            {
                flag = 1;
            }
        }
        /* As instruções começam após a linha que contém INICIO */
        else
        {
            char *info[30] = {NULL};
            int i = 0;

            char *p = strtok(linha, " ");
            while (p != NULL && i < 30)
            {
                info[i++] = p;
                p = strtok(NULL, " ");
            }
            /* Divide as informações contidas em cada linha */
            gerenciarComandos(info);
        }
    }
}
/* Itera pelas linhas do arquivo, pegando as informações importantes e chamando a função gerenciarComandos */
/*--------------------------------------------------*/

void gerenciarComandos(char *info[])
{
    if (strcmp(info[0], "pede_pouso") == 0)
    {
        pedePouso(info);
    }
    else if (strcmp(info[0], "pista_liberada") == 0)
    {
        pistaLiberada();
    }
    else if (strcmp(info[0], "URGENCIA") == 0)
    {
        urgencia(info);
    }
}
/* Delega qual função deve ser chamada, baseando-se na mensagem */
/*--------------------------------------------------*/

void pedePouso(char *info[])
{
    noh *voo = Noh();
    strcpy(voo->flight, info[1]);
    strcpy(voo->from, info[2]);
    int i = 0;
    while (info[3 + i] != NULL)
    {
        strcat(voo->from, " ");
        strcat(voo->from, info[3 + i]);
        i++;
    }
    /* Caso as origens possuam mais de uma palavra, como San Francisco */

    noh *aux = start;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = voo;
}
/* Cria um novo noh e o inclui na lista encadeada */
/*--------------------------------------------------*/

void pistaLiberada()
{
    if (start->prox != NULL)
    {
        noh *aux = start->prox;
        start->prox = aux->prox;
        fprintf(saida, "%s    %s\n", aux->flight, aux->from);
        free(aux);
    }
    else
    {
        fprintf(saida, "0000    Nenhum aviao pousando\n");
    }
}
/* Atualiza a fila e libera memória */
/*--------------------------------------------------*/

void urgencia(char *info[])
{
    noh *aux1 = start;
    noh *aux2 = start->prox;
    while (aux2 != NULL && strcmp(aux2->flight, info[1]) != 0)
    {
        aux1 = aux2;
        aux2 = aux2->prox;
    }
    if (aux2 != NULL)
    {
        aux1->prox = aux2->prox;
        aux2->prox = start->prox;
        start->prox = aux2;
    }
    /* O uso de dois auxiliares ajuda a manter o código mais legível */
}
/* Atualiza a fila, com base na urgencia do voo */
/*--------------------------------------------------*/

void escreverELiberar()
{
    fprintf(saida, "\n");
    fprintf(saida, "Situacao da fila\n");
    while (start->prox != NULL)
    {
        noh *temp = start->prox;
        start->prox = temp->prox;
        fprintf(saida, "\n");
        fprintf(saida, "%s    %s", temp->flight, temp->from);

        free(temp);
    }
    free(start);
}
/* Escreve a situacao do resto da fila */
/*--------------------------------------------------*/

int main()
{
    iniciarVariaveis();
    atexit(fecharArquivos);
    lerLinhas();
    escreverELiberar();
    return 0;
}
