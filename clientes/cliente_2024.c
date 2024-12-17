#include <stdio.h>
#include "corrida.h"
#include "graficos.h"

int main( void )
{
  FILE *resultPtr = fopen( "resultadoTestes2024.txt", "w" );
  int i;  /* contador a usar em ciclos */
  Tempo t;
  int minutos;

  fprintf( resultPtr, "\n-- Testando criaCorrida()\n" );

  Corrida utmb2024 = criaCorrida( 2024,
                                  "UTMB_2024-starters.csv",
                                  "UTMB_2024-final.csv",
                                  "UTMB_2024-progress.csv" );

  fprintf( resultPtr, "\n-- Ano bem inicializado?\n" );

  fprintf( resultPtr, "        ano da corrida = %d\n", utmb2024.ano );

  fprintf( resultPtr, "\n-- Dados de identificacao dos atletas bem inicializados?\n" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "        dorsal = %d\n",
                      utmb2024.listaAtletas[1000].dorsal );
  fprintf( resultPtr, "          nome = %s\n",
                      utmb2024.listaAtletas[1000].nome );
  fprintf( resultPtr, " nacionalidade = %s\n",
                      utmb2024.listaAtletas[1000].nacionalidade );
  fprintf( resultPtr, "       escalao = %s\n",
                      utmb2024.listaAtletas[1000].escalao );

  fprintf( resultPtr, "\n-- Resultados na meta bem atribuidos?\n" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "  posicaoFinalAbsoluta = %d\n",
                      utmb2024.listaAtletas[1000].posicaoFinalAbsoluta );
  fprintf( resultPtr, "   posicaoFinalEscalao = %d\n",
                      utmb2024.listaAtletas[1000].posicaoFinalEscalao );
  fprintf( resultPtr, "           tempoNaMeta = %2d:%2d:%2d\n",
                      utmb2024.listaAtletas[1000].tempoNaMeta[0],
                      utmb2024.listaAtletas[1000].tempoNaMeta[1],
                      utmb2024.listaAtletas[1000].tempoNaMeta[2] );

  fprintf( resultPtr, "\n-- Tempos de passagem bem atribuidos?\n" );

  fprintf( resultPtr, "\n   -- Numero de postos bem calculado?\n" );

  fprintf( resultPtr, "           numero de pontos de passagem = %d\n",
                                    utmb2024.numeroPontosPassagem );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "   tempos de passagem em minutos; \n" );
  for ( i = 0; i < utmb2024.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", utmb2024.listaAtletas[1000].temposPassagem[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  fprintf( resultPtr, "\n-- Tabela de passagens bem preenchida e ordenada?\n" );

  fprintf( resultPtr, "Atletas a passar em Courmayeur nas posicoes 1001 a 1005\n" );
  for ( i = 1000; i < 1005; i++ )
    fprintf( resultPtr, "%11d |", utmb2024.tabelaPassagens[11][i].dorsal );
  fprintf( resultPtr, "\n" );
  for ( i = 1000; i < 1005; i++ )
  {
    minutos = utmb2024.tabelaPassagens[11][i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, " %s %2d:%2d |", t.diaDaSemana,
               t.horaDoDia, t.minutoAposHoraDoDia );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "\n-- Testando ordenaPorPosicaoFinal()\n" );

  Atleta listaAtletasOrdemChegada[NR_MAX_ATLETAS];

  for ( i = 0; i < utmb2024.numeroDeAtletas; i++ )
    listaAtletasOrdemChegada[i] = utmb2024.listaAtletas[i];

  ordenaPorPosicaoFinal( listaAtletasOrdemChegada, 0, utmb2024.numeroDeAtletas - 1 );

  fprintf( resultPtr, "Os 10 primeiros atletas a chegarem foram:\n" );
  for ( i = 0; i < 10; i++ )
    fprintf( resultPtr, "%4d %4d %23s  %2d:%2d:%2d\n",
             i + 1,
             listaAtletasOrdemChegada[i].dorsal,
             listaAtletasOrdemChegada[i].nome,
             listaAtletasOrdemChegada[i].tempoNaMeta[0],
             listaAtletasOrdemChegada[i].tempoNaMeta[1],
             listaAtletasOrdemChegada[i].tempoNaMeta[2] );

  fprintf( resultPtr, "\n-- Testando indiceAtleta()\n" );

  if ( indiceAtleta( utmb2024.listaAtletas, utmb2024.numeroDeAtletas, 3000 ) == -1 )
    fprintf( resultPtr, "Nao existe nenhum atleta com o dorsal 3000 em listaAtletas.\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 surge em listaAtletas"
                      " com o indice %d.\n",
                      indiceAtleta( utmb2024.listaAtletas,
                        utmb2024.numeroDeAtletas, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getAtleta()\n" );

  Atleta devolvido = getAtleta( utmb2024.listaAtletas,
                                utmb2024.numeroDeAtletas, 1000 );
  fprintf( resultPtr, "O atleta com o dorsal 1000 chama-se %s\n",
                      devolvido.nome );

  fprintf( resultPtr, "\n-- Testando indiceRegistoPassagem()\n" );

  if ( indiceRegistoPassagem( utmb2024.tabelaPassagens[11],
                                utmb2024.numeroDeAtletas, 3000 ) == -1 )
    fprintf( resultPtr, "Em Courmayeur nao passou nenhum atleta com o dorsal 3000.\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem passagem registada"
           " em Courmayeur com o indice %d.\n",
           indiceRegistoPassagem( utmb2024.tabelaPassagens[11],
                                    utmb2024.numeroDeAtletas, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getRegistoPassagem()\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem tempo de passagem"
           " em Courmayeur = %d  minutos.\n",
           getRegistoPassagem( utmb2024.tabelaPassagens[11],
                                 utmb2024.numeroDeAtletas, 1000 ).tempoPassagem );

  fprintf( resultPtr, "\n-- Testando a deteccao de batota na edicao de 2024\n" );

  /* calculado com os tempos do vencedor de 2024, menos 40% */
  fprintf( resultPtr, "O atleta vencedor tem indice 89 na lista de atletas:\n" );
  fprintf( resultPtr, "        dorsal = %d\n",
                      utmb2024.listaAtletas[89].dorsal );
  fprintf( resultPtr, "          nome = %s\n",
                      utmb2024.listaAtletas[89].nome );
  fprintf( resultPtr, "Atleta com o indice 89 na lista de atletas,\n" );
  fprintf( resultPtr, "  tempos de passagem em minutos:\n" );
  for ( i = 0; i < utmb2024.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", utmb2024.listaAtletas[89].temposPassagem[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }
  fprintf( resultPtr, "  diferencas entre postos, do vencedor, em minutos:\n" );
  fprintf( resultPtr, " %5d", 0 );  /* não se calcula na partida */
  for ( i = 1; i < utmb2024.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", utmb2024.listaAtletas[89].temposPassagem[i]
                                - utmb2024.listaAtletas[89].temposPassagem[i - 1] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }
  fprintf( resultPtr, "  0.6 x diferencas entre postos, do vencedor, em minutos:\n" );
  fprintf( resultPtr, " %5d", 0 );  /* não se calcula na partida */
  for ( i = 1; i < utmb2024.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", (int)(0.6 * (utmb2024.listaAtletas[89].temposPassagem[i]
                                - utmb2024.listaAtletas[89].temposPassagem[i - 1])) );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  int arrayRef2024[24] = {  0, 43, 24, 31, 35, 34,
                           16, 47, 28, 23, 13, 15,
                           30, 30, 19, 30, 33, 48,
                           45, 23, 25, 32, 57, 27 };

  Atleta investigado = getAtleta( (&utmb2024)->listaAtletas,
                                  (&utmb2024)->numeroDeAtletas,
                                  28 );

  fprintf( resultPtr, "\nO atleta com o dorsal 28 no UTMB 2024 " );

  if ( !umAtletaFezBatotaNumCertoPosto( investigado, 6, arrayRef2024[6] ) )
    fprintf( resultPtr, "nao fez batota no posto de indice 6.\n" );

  if ( umAtletaFezBatotaNumCertoPosto( investigado, 14, arrayRef2024[14] ) )
  {
    fprintf( resultPtr, "Assinala batota no posto de indice 14,\n" );
    fprintf( resultPtr, "mas eh um falso positivo, pois nao passou nesse posto " );
    fprintf( resultPtr, "nem no anterior.\n" );
  }

  /* fazendo testes com o vencedor */
  investigado = getAtleta( (&utmb2024)->listaAtletas,
                           (&utmb2024)->numeroDeAtletas,
                           139 );
  if( umAtletaFezBatotaEmQuePosto( investigado, (&utmb2024)->numeroPontosPassagem,
                                   arrayRef2024 ) == -1 )
    fprintf( resultPtr, "\nO vencedor nao fez batota em nenhum posto.\n" );

  fprintf( resultPtr, "\nAumentando artificialmente a referencia no posto 5,\n" );
  arrayRef2024[5] = 340;
  fprintf( resultPtr, "o vencedor assinala batota no posto %d.\n",
           umAtletaFezBatotaEmQuePosto( investigado,
                                        (&utmb2024)->numeroPontosPassagem,
                                        arrayRef2024 ) );

  fclose( resultPtr );

  return 0;
}
