#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "corrida.h"

void startersData(Corrida *corrida, const char *nomeFicheiroStarters)
{
    FILE *startersFile = fopen(nomeFicheiroStarters, "r");
    if (startersFile == NULL)
    {
        perror("Erro ao abrir ficheiro");
        exit(-1);
    }

    char line[1024];
    int conta = 0;

    int contaLidos = 0;
    for (contaLidos = 0; contaLidos < 3; contaLidos++)
        fgets(line, sizeof(line), startersFile);

    while (fgets(line, sizeof(line), startersFile) && conta < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[conta];

        char *ptr = line;
        char *field;

        field = strsep(&ptr, ";");
        atleta->dorsal = atoi(field);

        field = strsep(&ptr, ";");
        strncpy(atleta->nome, field, sizeof(atleta->nome) - 1);

        strsep(&ptr, ";");

        field = strsep(&ptr, ";");
        strncpy(atleta->escalao, field, sizeof(atleta->escalao) - 1);

        field = strsep(&ptr, "\n");
        strncpy(atleta->nacionalidade, field, sizeof(atleta->nacionalidade) - 1);

        conta++;
    }

    corrida->numeroDeAtletas = conta;
    fclose(startersFile);
}

void progressData(Corrida *corrida, const char *nomeFicheiroProgress)
{
    FILE *progressFile = fopen(nomeFicheiroProgress, "r");
    if (progressFile == NULL)
    {
        perror("Erro ao abrir ficheiro");
        exit(-1);
    }

    char line[1024];
    int conta = 0;

    fgets(line, sizeof(line), progressFile);

    while (fgets(line, sizeof(line), progressFile) && conta < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[conta];

        char *ptr = line;
        char *field;

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
        conta++;
    }

    corrida->numeroDeAtletas = conta;
    fclose(progressFile);
}

/*
void finalData(Corrida *corrida, const char *nomeFicheiroFinal)
{
}
*/

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
    /* finalData(&corrida, nomeFicheiroFinal); */
    progressData(&corrida, nomeFicheiroProgress);

    return corrida;
}

int main()
{
    Corrida corrida = criaCorrida(2024,
                                  "./UTMB_2024-starters.csv",
                                  "./UTMB_2024-final.csv",
                                  "./UTMB_2024-progress.csv");

    printf("Ano: %d\n", corrida.ano);
    /* printf("Número de atletas: %d\n", corrida.numeroDeAtletas); */

    int contador;
    for (contador = 0; contador < 10; contador++)
    {
        printf("Dorsal: %d, Nome: %s, Escalão: %s, Nacionalidade: %s\n",
               corrida.listaAtletas[contador].dorsal,
               corrida.listaAtletas[contador].nome,
               corrida.listaAtletas[contador].escalao,
               corrida.listaAtletas[contador].nacionalidade);

        int i;
        for (i = 0; i < NR_MAX_PONTOS_PASSAGEM; i++)
        {
            printf("%d, ", corrida.listaAtletas[contador].temposPassagem[i]);
        }
        printf("\n");
    }

    return 0;
}