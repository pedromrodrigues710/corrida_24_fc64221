#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "corrida.h"

/*Ficheiro starters*/
void startersData(Corrida *corrida, const char *nomeFicheiroStarters)
{
    FILE *startersFile = fopen(nomeFicheiroStarters, "r"); /*Abrir o ficheiro starters*/

    char line[1024]; /*Criar buffer para as linhas*/
    int conta = 0;   /*Contagem do numero de atletas*/

    /*Saltar as 3 primeiras linhas*/
    int contaLidos = 0;
    for (contaLidos = 0; contaLidos < 3; contaLidos++)
        fgets(line, sizeof(line), startersFile);

    /*Extrair todas as linhas*/
    while (fgets(line, sizeof(line), startersFile) && conta < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[conta]; /*Cria uma estrutura atleta por linha*/

        char *ptr = line;
        char *field;

        field = strsep(&ptr, ";"); /*Extrair 1º campo até ";"*/
        atleta->dorsal = atoi(field);

        field = strsep(&ptr, ";"); /*Extrair 2º campo até ";"*/
        strncpy(atleta->nome, field, sizeof(atleta->nome) - 1);

        strsep(&ptr, ";"); /*Ignorar 3º campo (clube)*/

        field = strsep(&ptr, ";"); /*Extrair 4º campo até ";"*/
        strncpy(atleta->escalao, field, sizeof(atleta->escalao) - 1);

        field = strsep(&ptr, "\n"); /*Extrair 5º campo até ";"*/
        strncpy(atleta->nacionalidade, field, sizeof(atleta->nacionalidade) - 1);

        conta++; /*Incrementar o numero de atletas a cada nova linha*/
    }

    corrida->numeroDeAtletas = conta; /*Atualizar numero de atletas*/
    fclose(startersFile);
}

/*Ficheiro progress*/
void progressData(Corrida *corrida, const char *nomeFicheiroProgress)
{
    FILE *progressFile = fopen(nomeFicheiroProgress, "r"); /*Abrir o ficheiro progress*/

    char line[1024]; /*Criar buffer para as linhas*/
    int conta = 0;   /*Contagem do numero de atletas*/

    /*Saltar a primeira linha*/
    fgets(line, sizeof(line), progressFile);

    while (fgets(line, sizeof(line), progressFile) && conta < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[conta]; /*Cria uma estrutura atleta por linha*/

        char *ptr = line;
        char *field;

        /*Ignorar campos "dorsal" / "nome" / "escalao"*/
        strsep(&ptr, ";");
        strsep(&ptr, ";");
        strsep(&ptr, ";");

        /* Tempos de Passagem */
        int i;
        for (i = 0; i < NR_MAX_PONTOS_PASSAGEM; i++)
        {
            field = strsep(&ptr, ";");

            int hora = 0, minuto = 0;
            if (sscanf(field, "%*s %d:%d", &hora, &minuto) == 2)
            {
                atleta->temposPassagem[i] = hora * 60 + minuto;
            }
            else
            {
                atleta->temposPassagem[i] = 0;
            }
        }
        conta++; /*Incrementar o numero de atletas a cada nova linha*/
    }

    fclose(progressFile);
}

/*Ficheiro final*/
void finalData(Corrida *corrida, const char *nomeFicheiroFinal)
{
    FILE *finalFile = fopen(nomeFicheiroFinal, "r"); /*Abrir o ficheiro final*/

    char line[1024]; /*Criar buffer para as linhas*/
    int conta = 0;  /*Contagem do numero de atletas*/

    /*Saltar as 3 primeiras linhas*/
    int contaLidos = 0;
    for (contaLidos = 0; contaLidos < 3; contaLidos++)
        fgets(line, sizeof(line), finalFile);

    /*Extrair todas as linhas*/
    while (fgets(line, sizeof(line), finalFile) && conta < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[conta]; /*Cria uma estrutura atleta por linha*/

        char *ptr = line;
        char *field;

        field = strsep(&ptr, ";"); /*Extrair 1º campo até ";"*/
        atleta->posicaoFinalAbsoluta = atoi(field);

        /*Ignorar campos "dorsal" / "nome" / "clube" / "escalao"*/
        strsep(&ptr, ";");
        strsep(&ptr, ";");
        strsep(&ptr, ";");
        strsep(&ptr, ";");
        
        field = strsep(&ptr, ";"); /*Extrair posiçao final absoluta*/
        atleta->posicaoFinalEscalao = atoi(field);

        /* Tempos na Meta */
        field = strsep(&ptr, ";");
        int hora = 0, minuto = 0, segundo = 0;
        if (sscanf(field, "%2d:%2d:%2d", &hora, &minuto, &segundo) == 3)
        {
            atleta->tempoNaMeta[0] = hora;
            atleta->tempoNaMeta[1] = minuto;
            atleta->tempoNaMeta[2] = segundo;
        }
        else
        {
            atleta->tempoNaMeta[0] = 0;
            atleta->tempoNaMeta[1] = 0;
            atleta->tempoNaMeta[2] = 0;
        }

        /*Ignora "diferença para o 1º" / "nacionalidade"*/
        strsep(&ptr, ";");
        strsep(&ptr, "\n");

        conta++; /*Incrementar o numero de atletas a cada nova linha*/
    }

    fclose(finalFile);
}

/*Funçao cria corrida com base nos ficheiros csv*/
Corrida criaCorrida(int ano,
                    const char *nomeFicheiroStarters,
                    const char *nomeFicheiroFinal,
                    const char *nomeFicheiroProgress)
{
    Corrida corrida;
    corrida.ano = ano;
    corrida.numeroDeAtletas = 0;

    /* Dados */
    startersData(&corrida, nomeFicheiroStarters);
    finalData(&corrida, nomeFicheiroFinal);
    progressData(&corrida, nomeFicheiroProgress);

    return corrida;
}