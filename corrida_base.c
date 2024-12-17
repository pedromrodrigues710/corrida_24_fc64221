#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "corrida.h"

/************************************************************************
 * Protótipos de funções auxiliares com âmbito restrito a este ficheiro *
 ************************************************************************/

/* função auxiliar de inicializaAtletas;
   copia a substring de vectorOrigem para vectorDestino desde
   indiceInicial até ser encontrado terminador, o qual não é copiado*/
void preencheAte( char *vectorDestino, const char *vectorOrigem,
                  int indiceInicial, char terminador );

/* função auxiliar de inicializaAtletas;
   devolve o índice da próxima ocorrência de chave em vector
   a partir de indiceInicial;
   vector é uma string bem formada (terminada com '\0');
   chave não pode ser '\0';
   devolve -1 se não encontrar chave */
int proximaOcorrencia( const char *vector, int indiceInicial, char chave );

/* função auxiliar de ordenaPorTempoPassagem;
 * funde duas metades ordenadas do vector vec
 */
void fundir( RegistoPassagem vec[], int inicio, int meio, int fim );

/* função auxiliar de ordenaPorPosicaoFinal;
 * funde duas metades ordenadas do vector vec
 */
void fundirPF( Atleta vec[], int inicio, int meio, int fim );

/********************************************
 * Implementação das funções de "corrida.h" *
 ********************************************/

int converteParaHorasAposInicio( const char *diaDaSemana, int horaDoDia )
{
  int horasAposInicio = 0; /* variável redundante mas explanatória */

  if ( !strcmp( diaDaSemana, "Fri." ) )
    horasAposInicio = horaDoDia - 18;
  else if ( !strcmp( diaDaSemana, "Sat." ) )
    horasAposInicio = horaDoDia + 6;
  else /* diaDaSemana é "Sun." */
    horasAposInicio = horaDoDia + 30;

  return horasAposInicio;
}

int minutosEmProva( Tempo tempo )
{
  return tempo.horasAposInicio * 60 + tempo.minutosAposHorasAposInicio;
}

int dorsal( Atleta atleta )
{
  return atleta.dorsal;
}

char *nome( Atleta *atletaPtr )
{
  return atletaPtr->nome;
}

char *nacionalidade( Atleta *atletaPtr )
{
  return atletaPtr->nacionalidade;
}

char *escalao( Atleta *atletaPtr )
{
  return atletaPtr->escalao;
}

int posicaoFinalAbsoluta( Atleta atleta )
{
  return atleta.posicaoFinalAbsoluta;
}

int posicaoFinalEscalao( Atleta atleta )
{
  return atleta.posicaoFinalEscalao;
}

int *tempoNaMeta( Atleta *atletaPtr )
{
  return atletaPtr->tempoNaMeta;
}

int *temposPassagem( Atleta *atletaPtr )
{
  return atletaPtr->temposPassagem;
}

Tempo tempo( int tempoPassagem )
{
  Tempo resultado;

  if ( tempoPassagem < 360 )  /* 6 horas */
  {
    strcpy( resultado.diaDaSemana, "Fri." );
    resultado.horaDoDia = tempoPassagem / 60 + 18;
  }
  else if ( tempoPassagem < 1800 )  /* 30 horas */
  {
    strcpy( resultado.diaDaSemana, "Sat." );
    resultado.horaDoDia = ( tempoPassagem - 360 ) / 60;
  }
  else
  {
    strcpy( resultado.diaDaSemana, "Sun." );
    resultado.horaDoDia = ( tempoPassagem - 1800 ) / 60;
  }
  resultado.minutoAposHoraDoDia = tempoPassagem % 60;
  resultado.horasAposInicio = tempoPassagem / 60;
  resultado.minutosAposHorasAposInicio = resultado.minutoAposHoraDoDia;

  return resultado;
}

/* faz-se programação defensiva mínima */
int inicializaAtletas( Atleta listaAtletas[], const char *nomeFicheiro )
{
  FILE *readPtr = fopen( nomeFicheiro, "r" );

  if ( readPtr == NULL )
    puts( "ERRO\n" );

  int conta = 0;  /* índice que percorre as linhas do ficheiro e listaAtletas */
  char linha[MAX_COLS_FICH_STARTERS + 2];  /* guardará 1 linha de cada vez */
  char membro[TAMANHO_MAX_NOME_EQUIPA + 1];  /* parte de uma linha */
  int indicePontoVirgula; /* índice onde se encontra um ';' no array linha */

  /* descarta as 3 primeiras linhas do ficheiro */
  for ( conta = 0; conta < 3; conta++ )
    fgets( linha, MAX_COLS_FICH_STARTERS + 2, readPtr );

  /* lê os detalhes de identificação de cada atleta em cada linha do ficheiro,
     descartando a identificação da equipa */
  conta = 0;
  while ( fgets( linha, MAX_COLS_FICH_STARTERS + 2, readPtr ) != NULL )
  {
    preencheAte( membro, linha, 0, ';' );
    listaAtletas[conta].dorsal = atoi( membro ); /* converte para int */
    indicePontoVirgula = proximaOcorrencia( linha, 0, ';' );

    preencheAte( membro, linha, indicePontoVirgula + 1 , ';' );
    strcpy( listaAtletas[conta].nome, membro );
    indicePontoVirgula = proximaOcorrencia( linha, indicePontoVirgula + 1, ';' );

    preencheAte( membro, linha, indicePontoVirgula + 1 , ';' );
    /* a equipa é ignorada */
    indicePontoVirgula = proximaOcorrencia( linha, indicePontoVirgula + 1, ';' );

    preencheAte( membro, linha, indicePontoVirgula + 1 , ';' );
    strcpy( listaAtletas[conta].escalao, membro );
    indicePontoVirgula = proximaOcorrencia( linha, indicePontoVirgula + 1, ';' );

    preencheAte( membro, linha, indicePontoVirgula + 1 , '\n' );
    strcpy( listaAtletas[conta].nacionalidade, membro );

    listaAtletas[conta].posicaoFinalAbsoluta = 9999;

    conta++;
  }

  fclose( readPtr );

  return conta;
}

int atribuiResultadosNaMeta( Atleta listaAtletas[], const char *nomeFicheiro )
{
  FILE *readPtr = fopen( nomeFicheiro, "r" );

  if ( readPtr == NULL )
    puts( "ERRO\n" );

  int conta = 0;  /* índice que percorre listaAtletas */
  int contaLidos = 0;  /* índice que percorre as linhas do ficheiro */
  char linha[MAX_COLS_FICH_FINAL + 2];  /* guardará 1 linha de cada vez */
  char membro[TAMANHO_MAX_NOME_EQUIPA + 1];  /* parte de uma linha */
  int indiceSeparador; /* índice onde se encontra um ';' ou ':' no array linha */
  int guardaPosicaoFinalAbsoluta;
  int guardaDorsal;
  int guardaPosicaoFinalEscalao;
  int guardaTempoNaMeta[3];

  /* descarta as 3 primeiras linhas do ficheiro */
  for ( contaLidos = 0; contaLidos < 3; contaLidos++ )
    fgets( linha, MAX_COLS_FICH_FINAL + 2, readPtr );

  /* repõe o contador de linhas lidas do ficheiro */
  contaLidos = 0;

  /* lê os detalhes de desempenho de cada atleta em cada linha do ficheiro,
     descartando a informação desnecessária */
  while ( fgets( linha, MAX_COLS_FICH_FINAL + 2, readPtr ) != NULL )
  {
    /* ler os valores dos membros e guardá-los em variáveis temporárias */

    preencheAte( membro, linha, 0, ';' );
    guardaPosicaoFinalAbsoluta = atoi( membro ); /* converte para int */
    indiceSeparador = proximaOcorrencia( linha, 0, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    guardaDorsal = atoi( membro ); /* converte para int */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    /* o nome é ignorado */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    /* a equipa é ignorada */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    /* o escalão é ignorado */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    guardaPosicaoFinalEscalao = atoi( membro ); /* converte para int */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    /* próximo separador é ':' */
    preencheAte( membro, linha, indiceSeparador + 1 , ':' );
    guardaTempoNaMeta[0] = atoi( membro );
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ':' );
    /* próximo separador é ':' */
    preencheAte( membro, linha, indiceSeparador + 1 , ':' );
    guardaTempoNaMeta[1] = atoi( membro );
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ':' );
    /* próximo separador é novamente ';' */
    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    guardaTempoNaMeta[2] = atoi( membro );

    /* os restantes 2 campos do ficheiro são ignorados */

    /* procurar o atleta pelo número de dorsal,
       e atribuir-lhe os valores guardados temporariamente */

    while ( listaAtletas[conta].dorsal != guardaDorsal )
      conta++;

    listaAtletas[conta].posicaoFinalAbsoluta = guardaPosicaoFinalAbsoluta;
    listaAtletas[conta].posicaoFinalEscalao = guardaPosicaoFinalEscalao;
    listaAtletas[conta].tempoNaMeta[0] = guardaTempoNaMeta[0];
    listaAtletas[conta].tempoNaMeta[1] = guardaTempoNaMeta[1];
    listaAtletas[conta].tempoNaMeta[2] = guardaTempoNaMeta[2];

    contaLidos++;
  }

  fclose( readPtr );

  return contaLidos;
}

int atribuiTemposPassagem( Atleta listaAtletas[], const char *nomeFicheiro )
{
  FILE *readPtr = fopen( nomeFicheiro, "r" );

  if ( readPtr == NULL )
    puts( "ERRO\n" );

  int nrPontosPassagem = 0;  /* determinado usando a primeira linha do ficheiro */
  int conta = 0;  /* índice que percorre listaAtletas */
  char linha[MAX_COLS_FICH_PROGRESS + 2];  /* guardará 1 linha de cada vez */
  int indice;  /* índice de um char arbitrário no array linha */
  char membro[TAMANHO_MAX_NOME_ATLETA + 1];  /* parte de uma linha */
  int indiceSeparador; /* índice de um ';' ou ' ' ou ':' no array linha */
  int dorsal;
  int contaPostos;  /* contador a usar no ciclo que percorre temposPassagem[] */
  char diaDaSemana[5];
  int horaDoDia;
  int minutoAposHoraDoDia;

  /* lê a primeira linha do ficheiro */
  fgets( linha, MAX_COLS_FICH_PROGRESS + 2, readPtr );

  /* usa a primeira linha para determinar o número de pontos de passagem,
     calculando nrPontosPassagem = (número de ocorrências de ';') - 2 */
  for ( indice = 0; linha[indice] != '\0'; indice++ )
  {
    nrPontosPassagem += linha[indice] == ';';
  }
  nrPontosPassagem -= 2;

  /* lê os tempos de passagem de cada atleta em cada linha do ficheiro,
     descartando a informação desnecessária */
  conta = 0;
  while ( fgets( linha, MAX_COLS_FICH_PROGRESS + 2, readPtr ) != NULL )
  {
    /* ler os valores dos membros e guardá-los em variáveis temporárias */

    preencheAte( membro, linha, 0, ';' );
    dorsal = atoi( membro ); /* converte para int */
    indiceSeparador = proximaOcorrencia( linha, 0, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    /* o nome é ignorado */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    preencheAte( membro, linha, indiceSeparador + 1 , ';' );
    /* o escalão é ignorado */
    indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );

    /* procurar o atleta pelo número de dorsal */
    while ( listaAtletas[conta].dorsal != dorsal )
      conta++;

    /* encontrado o atleta, preenche-se listaAtletas[conta].temposPassagem[] */

    for ( contaPostos = 0; contaPostos < nrPontosPassagem - 1; contaPostos++ )
    {
      preencheAte( membro, linha, indiceSeparador + 1 , ';' );
      if ( membro[0] == '.' ) /* atleta não passou neste posto de controle */
      {
        listaAtletas[conta].temposPassagem[contaPostos] = 10000;
        indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );
      }
      else /* atleta tem hora de passagem registada neste posto de controle */
      {
        preencheAte( membro, linha, indiceSeparador + 1 , ' ' );
        strcpy( diaDaSemana, membro );
        indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ' ' );
        preencheAte( membro, linha, indiceSeparador + 1 , ':' );
        horaDoDia = atoi( membro ); /* converte para int */
        indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ':' );
        preencheAte( membro, linha, indiceSeparador + 1 , ';' );
        minutoAposHoraDoDia = atoi( membro ); /* converte para int */
        indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ';' );
        listaAtletas[conta].temposPassagem[contaPostos] =
            converteParaHorasAposInicio( diaDaSemana, horaDoDia ) * 60
            + minutoAposHoraDoDia;
      }
    }

    /* último posto de controle */
    preencheAte( membro, linha, indiceSeparador + 1 , '\n' );
    if ( membro[0] == '.' )  /* atleta não passou neste posto de controle */
      listaAtletas[conta].temposPassagem[contaPostos] = 10000;
    else /* atleta tem hora de passagem registada neste posto de controle */
    {
      preencheAte( membro, linha, indiceSeparador + 1 , ' ' );
      strcpy( diaDaSemana, membro );
      indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ' ' );
      preencheAte( membro, linha, indiceSeparador + 1 , ':' );
      horaDoDia = atoi( membro ); /* converte para int */
      indiceSeparador = proximaOcorrencia( linha, indiceSeparador + 1, ':' );
      preencheAte( membro, linha, indiceSeparador + 1 , '\n' );
      minutoAposHoraDoDia = atoi( membro ); /* converte para int */
      listaAtletas[conta].temposPassagem[contaPostos] =
          converteParaHorasAposInicio( diaDaSemana, horaDoDia ) * 60
          + minutoAposHoraDoDia;
    }
  }
  fclose( readPtr );

  return nrPontosPassagem;
}

void preencheAte( char *vectorDestino, const char *vectorOrigem,
                  int indiceInicial, char terminador )
{
  int i = 0; /* índice para percorrer vectorDestino */
  int j = indiceInicial; /* índice para percorrer vectorOrigem */

  while ( vectorOrigem[j] != terminador )
  {
    vectorDestino[i] = vectorOrigem[j];
    i++;
    j++;
  }
  vectorDestino[i] = '\0';
}

int proximaOcorrencia( const char *vector, int indiceInicial, char chave )
{
  int j = indiceInicial; /* índice para percorrer vector */

  while ( vector[j] != chave  && vector[j] != '\0' )
    j++;

  if ( vector[j]  == '\0' )
    j = -1;

  return j;
}

void preencheTabelaPassagens( Atleta listaAtletas[], int tamanhoLista,
                              RegistoPassagem tabela[][NR_MAX_ATLETAS],
                              int nPostos )
{
  int contaPostos;
  int contaAtletas;

  for ( contaPostos = 0; contaPostos < nPostos; contaPostos++ )
    for ( contaAtletas = 0; contaAtletas < tamanhoLista; contaAtletas++ )
    {
      tabela[contaPostos][contaAtletas].dorsal =
        listaAtletas[contaAtletas].dorsal;
      tabela[contaPostos][contaAtletas].tempoPassagem =
        listaAtletas[contaAtletas].temposPassagem[contaPostos];
    }
}


/**
 * Baseado em código de Francisco Martins modificado por Carlos Lourenço.
 * Maio 2007; Maio 2008; Dezembro 2023.
 */
/* implementa a ordenação por fusão */
void ordenaPorTempoPassagem( RegistoPassagem vec[], int inicio, int fim )
{
  int meio;

  if ( inicio >= fim )
    return;

  meio = ( inicio + fim ) / 2;

  ordenaPorTempoPassagem( vec, inicio, meio );
  ordenaPorTempoPassagem( vec, meio + 1, fim );
  fundir( vec, inicio, meio, fim );
}

void fundir( RegistoPassagem vec[], int inicio, int meio, int fim )
{
  RegistoPassagem *aux = calloc( fim - inicio + 1, sizeof( RegistoPassagem ) );
  int part1 = inicio;
  int part2 = meio + 1;
  int destino = 0;

  while ( part1 <= meio && part2 <= fim)
    /* usar <= em vez de < na comparação de modo a a ordenação ser estável */
    aux [destino++] = vec[part1].tempoPassagem <= vec[part2].tempoPassagem ?
                      vec[part1++] : vec[part2++];

  if ( part1 <= meio )
    while ( part1 <= meio )
      aux[destino++] = vec[part1++];
  else
    while ( part2 <= fim )
      aux[destino++] = vec[part2++];

  for ( part1 = inicio, destino = 0; part1 <= fim; part1++, destino++ )
    vec[part1] = aux[destino];

  free( aux );
}

void ordenaTabelaPassagens( int nAtletas, RegistoPassagem tabela[][NR_MAX_ATLETAS],
                            int nPostos )
{
  int posto;
  for ( posto = 0; posto < nPostos; posto++ )
    ordenaPorTempoPassagem( tabela[posto], 0, nAtletas - 1 );
}

/**
 * Baseado em código de Francisco Martins modificado por Carlos Lourenço.
 * Maio 2007; Maio 2008; Dezembro 2023.
 */
/* implementa a ordenação por fusão */
void ordenaPorPosicaoFinal( Atleta vec[], int inicio, int fim )
{
  int meio;

  if ( inicio >= fim )
    return;

  meio = ( inicio + fim ) / 2;

  ordenaPorPosicaoFinal( vec, inicio, meio );
  ordenaPorPosicaoFinal( vec, meio + 1, fim );
  fundirPF( vec, inicio, meio, fim );
}

void fundirPF( Atleta vec[], int inicio, int meio, int fim )
{
  Atleta *aux = calloc( fim - inicio + 1, sizeof( Atleta ) );
  int part1 = inicio;
  int part2 = meio + 1;
  int destino = 0;

  while ( part1 <= meio && part2 <= fim)
    /* usar <= em vez de < na comparação de modo a a ordenação ser estável */
    aux [destino++] = vec[part1].posicaoFinalAbsoluta
                      <= vec[part2].posicaoFinalAbsoluta ?
                      vec[part1++] : vec[part2++];

  if ( part1 <= meio )
    while ( part1 <= meio )
      aux[destino++] = vec[part1++];
  else
    while ( part2 <= fim )
      aux[destino++] = vec[part2++];

  for ( part1 = inicio, destino = 0; part1 <= fim; part1++, destino++ )
    vec[part1] = aux[destino];

  free( aux );
}

int indiceAtleta( Atleta vec[], int tamanho, int dorsal )
{
  int i, resultado = -1;

  for ( i = 0; i < tamanho && resultado == -1; i++ )
    if ( vec[i].dorsal == dorsal )
      resultado = i;

  return resultado;
}

Atleta getAtleta( Atleta vec[], int tamanho, int dorsal )
{
  return vec[ indiceAtleta( vec, tamanho, dorsal ) ];
}

int indiceRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal )
{
  int i, resultado = -1;

  for ( i = 0; i < tamanho && resultado == -1; i++ )
    if ( vec[i].dorsal == dorsal )
      resultado = i;

  return resultado;
}

RegistoPassagem getRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal )
{
  return vec[ indiceRegistoPassagem( vec, tamanho, dorsal ) ];
}

void registaPosicoesPostos( int nAtletas, RegistoPassagem tabela[][NR_MAX_ATLETAS],
                            int nPostos, int dorsal, int posicoes[] )
{
  int posto;
  for ( posto = 0; posto < nPostos; posto++ )
    posicoes[posto] = indiceRegistoPassagem( tabela[posto], nAtletas, dorsal ) + 1;
}
