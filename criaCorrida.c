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
    int index = 0;

    fgets(line, sizeof(line), startersFile);
    fgets(line, sizeof(line), startersFile);
    fgets(line, sizeof(line), startersFile);

    while (fgets(line, sizeof(line), startersFile) && index < NR_MAX_ATLETAS)
    {
        Atleta *atleta = &corrida->listaAtletas[index];

        char *ptr = line;
        char *field;

        field = strsep(&ptr, ";");
        atleta->dorsal = atoi(field);

        field = strsep(&ptr, ";");
        strncpy(atleta->nome, field, sizeof(atleta->nome) - 1);

        field = strsep(&ptr, ";");

        field = strsep(&ptr, ";");
        strncpy(atleta->escalao, field, sizeof(atleta->escalao) - 1);

        field = strsep(&ptr, ";");
        strncpy(atleta->nacionalidade, field, sizeof(atleta->nacionalidade) - 1);

        index++;
    }

    corrida->numeroDeAtletas = index;
    fclose(startersFile);
}


/* 
void progressData(Corrida *corrida, const char *nomeFicheiroProgress)
{
}
*/

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
    /* progressData(&corrida, nomeFicheiroProgress); */

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
    for (contador = 0; contador < corrida.numeroDeAtletas; contador++)
    {
        printf("Dorsal: %d, Nome: %s, Escalão: %s, Nacionalidade: %s\n",
               corrida.listaAtletas[contador].dorsal,
               corrida.listaAtletas[contador].nome,
               corrida.listaAtletas[contador].escalao,
               corrida.listaAtletas[contador].nacionalidade);
    }

    return 0;
}