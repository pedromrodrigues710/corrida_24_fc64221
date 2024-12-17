#include <stdio.h>
#include "corrida.h"
#include "graficos.h"

int main( void )
{
  FILE *resultPtr = fopen( "resultadoTestes2023.txt", "w" );
  int i;  /* contador a usar em ciclos */
  Tempo t;
  int minutos;

  fprintf( resultPtr, "-- Testando converteParaHorasAposInicio()\n" );

  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Fri.", 21 ) );
  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Sat.", 10 ) );
  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Sun.", 7 ) );

  fprintf( resultPtr, "\n-- Testando as funcoes getter e de conversao\n" );

  Tempo primeiraPassagemZeNinguem = { "Fri.", 21, 27, 3, 27 };

  Atleta zeNinguem = { 6666, "Jose Ninguem", "POR (PT)", "40-44M",
                       3000, 30, {46, 29, 59},
                       { 0, 117, 234, 351, 468, 585, 702, 819, 936 , 1053,
                         1117, 1234, 1351, 1468, 1585, 1702, 1819, 1936, 2053,
                         2117, 2234, 2351, 2468, 2790 } };

  Atleta *zeNinguemPtr = &zeNinguem;

  fprintf( resultPtr, "%d\n", minutosEmProva( primeiraPassagemZeNinguem ) );

  fprintf( resultPtr, "%d\n", dorsal( zeNinguem ) );
  fprintf( resultPtr, "%s\n", nome( zeNinguemPtr ) );
  fprintf( resultPtr, "%s\n", nacionalidade( zeNinguemPtr ) );
  fprintf( resultPtr, "%s\n", escalao( zeNinguemPtr ) );
  fprintf( resultPtr, "%d\n", posicaoFinalAbsoluta( zeNinguem ) );
  fprintf( resultPtr, "%d\n", posicaoFinalEscalao( zeNinguem ) );
  fprintf( resultPtr, "%d:%d:%d\n",
                      tempoNaMeta( zeNinguemPtr )[0],
                      tempoNaMeta( zeNinguemPtr )[1],
                      tempoNaMeta( zeNinguemPtr )[2] );
  fprintf( resultPtr, "%d\n", temposPassagem( zeNinguemPtr )[9] );

  primeiraPassagemZeNinguem = tempo( 207 );
  Tempo *primeiraPassagemZeNinguemPtr = &primeiraPassagemZeNinguem;
  fprintf( resultPtr, "%s ", primeiraPassagemZeNinguemPtr->diaDaSemana );
  fprintf( resultPtr, "%d:%d ", primeiraPassagemZeNinguem.horaDoDia,
                      primeiraPassagemZeNinguem.minutoAposHoraDoDia );
  fprintf( resultPtr, "(%d:%d apos o inicio)\n",
                      primeiraPassagemZeNinguem.horasAposInicio,
                      primeiraPassagemZeNinguem.minutosAposHorasAposInicio );

  fprintf( resultPtr, "\n-- Testando criaCorrida()\n" );

  Corrida utmb2023 = criaCorrida( 2023,
                                  "UTMB_2023-starters.csv",
                                  "UTMB_2023-final.csv",
                                  "UTMB_2023-progress.csv" );

  fprintf( resultPtr, "\n-- Ano bem inicializado?\n" );

  fprintf( resultPtr, "        ano da corrida = %d\n", utmb2023.ano );

  fprintf( resultPtr, "\n-- Dados de identificacao dos atletas bem inicializados?\n" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "        dorsal = %d\n",
                      utmb2023.listaAtletas[1000].dorsal );
  fprintf( resultPtr, "          nome = %s\n",
                      utmb2023.listaAtletas[1000].nome );
  fprintf( resultPtr, " nacionalidade = %s\n",
                      utmb2023.listaAtletas[1000].nacionalidade );
  fprintf( resultPtr, "       escalao = %s\n",
                      utmb2023.listaAtletas[1000].escalao );

  fprintf( resultPtr, "\n-- Resultados na meta bem atribuidos?\n" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "  posicaoFinalAbsoluta = %d\n",
                      utmb2023.listaAtletas[1000].posicaoFinalAbsoluta );
  fprintf( resultPtr, "   posicaoFinalEscalao = %d\n",
                      utmb2023.listaAtletas[1000].posicaoFinalEscalao );
  fprintf( resultPtr, "           tempoNaMeta = %2d:%2d:%2d\n",
                      utmb2023.listaAtletas[1000].tempoNaMeta[0],
                      utmb2023.listaAtletas[1000].tempoNaMeta[1],
                      utmb2023.listaAtletas[1000].tempoNaMeta[2] );

  /* na última linha do ficheiro "UTMB_2023-final.csv" */
  fprintf( resultPtr, "Atleta com o indice 2680 na lista de atletas:\n" );
  fprintf( resultPtr, "  posicaoFinalAbsoluta = %d\n",
                      utmb2023.listaAtletas[2680].posicaoFinalAbsoluta );
  fprintf( resultPtr, "   posicaoFinalEscalao = %d\n",
                      utmb2023.listaAtletas[2680].posicaoFinalEscalao );
  fprintf( resultPtr, "           tempoNaMeta = %2d:%2d:%2d\n",
                      utmb2023.listaAtletas[2680].tempoNaMeta[0],
                      utmb2023.listaAtletas[2680].tempoNaMeta[1],
                      utmb2023.listaAtletas[2680].tempoNaMeta[2] );

  fprintf( resultPtr, "\n-- Tempos de passagem bem atribuidos?\n" );

  fprintf( resultPtr, "\n   -- Numero de postos bem calculado?\n" );

  fprintf( resultPtr, "           numero de pontos de passagem = %d\n",
                                    utmb2023.numeroPontosPassagem );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "   tempos de passagem em minutos; \n" );
  for ( i = 0; i < utmb2023.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", utmb2023.listaAtletas[1000].temposPassagem[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  fprintf( resultPtr, "\n-- Tabela de passagens bem preenchida e ordenada?\n" );

  fprintf( resultPtr, "Atletas a passar em Courmayeur nas posicoes 1001 a 1005\n" );
  for ( i = 1000; i < 1005; i++ )
    fprintf( resultPtr, "%11d |", utmb2023.tabelaPassagens[11][i].dorsal );
  fprintf( resultPtr, "\n" );
  for ( i = 1000; i < 1005; i++ )
  {
    minutos = utmb2023.tabelaPassagens[11][i].tempoPassagem;
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

  for ( i = 0; i < utmb2023.numeroDeAtletas; i++ )
    listaAtletasOrdemChegada[i] = utmb2023.listaAtletas[i];

  ordenaPorPosicaoFinal( listaAtletasOrdemChegada, 0, utmb2023.numeroDeAtletas - 1 );

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

  if ( indiceAtleta( utmb2023.listaAtletas, utmb2023.numeroDeAtletas, 3000 ) == -1 )
    fprintf( resultPtr, "Nao existe nenhum atleta com o dorsal 3000 em listaAtletas.\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 surge em listaAtletas"
                      " com o indice %d.\n",
                      indiceAtleta( utmb2023.listaAtletas,
                        utmb2023.numeroDeAtletas, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getAtleta()\n" );

  Atleta devolvido = getAtleta( utmb2023.listaAtletas,
                                utmb2023.numeroDeAtletas, 1000 );
  fprintf( resultPtr, "O atleta com o dorsal 1000 chama-se %s\n",
                      devolvido.nome );

  fprintf( resultPtr, "\n-- Testando indiceRegistoPassagem()\n" );

  if ( indiceRegistoPassagem( utmb2023.tabelaPassagens[11],
                                utmb2023.numeroDeAtletas, 3000 ) == -1 )
    fprintf( resultPtr, "Em Courmayeur nao passou nenhum atleta com o dorsal 3000.\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem passagem registada"
           " em Courmayeur com o indice %d.\n",
           indiceRegistoPassagem( utmb2023.tabelaPassagens[11],
                                    utmb2023.numeroDeAtletas, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getRegistoPassagem()\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem tempo de passagem"
           " em Courmayeur = %d  minutos.\n",
           getRegistoPassagem( utmb2023.tabelaPassagens[11],
                                 utmb2023.numeroDeAtletas, 1000 ).tempoPassagem );

  fprintf( resultPtr, "\n-- Testando registaPosicoesPostos()\n" );

  int posicoes1[NR_MAX_PONTOS_PASSAGEM];  /* para guardar as posições do atleta 1 */
  registaPosicoesPostos( utmb2023.numeroDeAtletas, utmb2023.tabelaPassagens,
                         utmb2023.numeroPontosPassagem, 1000, posicoes1 );
  fprintf( resultPtr, "As posicoes do atleta com o dorsal 1000 sao\n" );
  for ( i = 0; i < utmb2023.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", posicoes1[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  int posicoes2[NR_MAX_PONTOS_PASSAGEM];  /* para guardar as posições do atleta 2 */
  registaPosicoesPostos( utmb2023.numeroDeAtletas, utmb2023.tabelaPassagens,
                         utmb2023.numeroPontosPassagem, 700, posicoes2 );
  fprintf( resultPtr, "As posicoes do atleta com o dorsal 700 sao\n" );
  for ( i = 0; i < utmb2023.numeroPontosPassagem; i++ )
  {
    fprintf( resultPtr, " %5d", posicoes2[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  fprintf( resultPtr, "\n-- Desenhando a serie temporal de posicoes do atleta"
                      " com o dorsal 1000\n"
                      "  -> ver ficheiro atleta1000.png\n" );

  double postos[NR_MAX_PONTOS_PASSAGEM];
  double posicoes1double[NR_MAX_PONTOS_PASSAGEM];
  for ( i = 0; i < utmb2023.numeroPontosPassagem; i++ )
  {
    postos[i] = i + 1.0;
    posicoes1double[i] = posicoes1[i] * 1.0;
  }

  desenhaSerieTemporal( postos, posicoes1double, utmb2023.numeroPontosPassagem,
                        600, 400, "atleta1000" );

  fprintf( resultPtr, "\n-- Comparando as series temporais de posicoes dos atletas"
                      " com os dorsais 1000 e 700\n"
                      "  -> ver ficheiro atletas_1000_700.png\n" );

  double posicoes2double[NR_MAX_PONTOS_PASSAGEM];
  for ( i = 0; i < utmb2023.numeroPontosPassagem; i++ )
  {
    posicoes2double[i] = posicoes2[i] * 1.0;
  }

  comparaSeriesTemporais( postos, posicoes1double, utmb2023.numeroPontosPassagem,
                          postos, posicoes2double, utmb2023.numeroPontosPassagem,
                          600, 400, "atletas_1000_700" );

  fprintf( resultPtr, "\n-- Testando filtraEscalaoNacionalidade()"
                      " para as 4 combinacoes possiveis dos filtros\n" );

  /* guarda no array destino todas as mulheres 40-44 anos de idade E que são francesas */
  Atleta francesas40_44[10];
  int quantasFrancesas40_44 = filtraEscalaoNacionalidade( listaAtletasOrdemChegada,
                                francesas40_44, utmb2023.numeroDeAtletas,
                                "40-44W", "FRA (FR)" );

  fprintf( resultPtr, "\nClassificacao mulheres francesas 40-44 anos:\n" );
  fprintf( resultPtr, "%5s %7s %6s %23s %13s %13s %8s\n",
         "Pos. escalao", "Geral", "Dorsal", "Nome", "Escalao", "Nacionalidade", "Tempo" );
  for ( i = 0; i < quantasFrancesas40_44; i++ )
    fprintf( resultPtr, "  %10d %7d %6d %23s %13s %13s %2d:%2d:%2d\n",
             francesas40_44[i].posicaoFinalEscalao,
             francesas40_44[i].posicaoFinalAbsoluta,
             francesas40_44[i].dorsal,
             francesas40_44[i].nome,
             francesas40_44[i].escalao,
             francesas40_44[i].nacionalidade,
             francesas40_44[i].tempoNaMeta[0],
             francesas40_44[i].tempoNaMeta[1],
             francesas40_44[i].tempoNaMeta[2] );

  /* guarda no array destino todas as mulheres 40-44 anos de idade,
     de qualquer nacionalidade */
  Atleta mulheres40_44[70];
  int quantasMulheres40_44 = filtraEscalaoNacionalidade( listaAtletasOrdemChegada,
                                mulheres40_44, utmb2023.numeroDeAtletas,
                                "40-44W", "" );

  fprintf( resultPtr, "\nHa %d mulheres 40-44 anos.\n",
                      quantasMulheres40_44 );
  fprintf( resultPtr, "10 primeiras mulheres 40-44 anos, de qualquer nacionalidade:\n" );
  fprintf( resultPtr, "%5s %7s %6s %23s %13s %13s %8s\n",
         "Pos. escalao", "Geral", "Dorsal", "Nome", "Escalao", "Nacionalidade", "Tempo" );
  for ( i = 0; i < 10; i++ )
    fprintf( resultPtr, "  %10d %7d %6d %23s %13s %13s %2d:%2d:%2d\n",
             mulheres40_44[i].posicaoFinalEscalao,
             mulheres40_44[i].posicaoFinalAbsoluta,
             mulheres40_44[i].dorsal,
             mulheres40_44[i].nome,
             mulheres40_44[i].escalao,
             mulheres40_44[i].nacionalidade,
             mulheres40_44[i].tempoNaMeta[0],
             mulheres40_44[i].tempoNaMeta[1],
             mulheres40_44[i].tempoNaMeta[2] );

  /* guarda no array destino todos os atletas, de qualquer escalão, que são franceses */
  Atleta franceses[780];
  int quantosFranceses = filtraEscalaoNacionalidade( listaAtletasOrdemChegada,
                                franceses, utmb2023.numeroDeAtletas,
                                "", "FRA (FR)" );


  fprintf( resultPtr, "\nHa %d atletas franceses.\n",
                      quantosFranceses );
  fprintf( resultPtr, "10 primeiros atletas franceses, de qualquer escalao:\n" );
  fprintf( resultPtr, "%5s %7s %6s %23s %13s %13s %8s\n",
         "Pos. escalao", "Geral", "Dorsal", "Nome", "Escalao", "Nacionalidade", "Tempo" );
  for ( i = 0; i < 10; i++ )
    fprintf( resultPtr, "  %10d %7d %6d %23s %13s %13s %2d:%2d:%2d\n",
             franceses[i].posicaoFinalEscalao,
             franceses[i].posicaoFinalAbsoluta,
             franceses[i].dorsal,
             franceses[i].nome,
             franceses[i].escalao,
             franceses[i].nacionalidade,
             franceses[i].tempoNaMeta[0],
             franceses[i].tempoNaMeta[1],
             franceses[i].tempoNaMeta[2] );

  /* guarda no array destino os primeiros utmb2023.numeroDeAtletas/2 atletas
     sem aplicar qualquer filtro */

  /* o array semFiltro é criado com tamanho NR_MAX_ATLETAS/2 em vez de
     NR_MAX_ATLETAS, para evitar criar um array demasiado grande,
     que poderia esgotar a memória disponível */

  /* em coerência, o parâmetro tamanhoOrigem de filtraEscalaoNacionalidade é
     instanciado com utmb2023.numeroDeAtletas/2 em vez de utmb2023.numeroDeAtletas */
  Atleta semFiltro[NR_MAX_ATLETAS / 2];

  int quantosAtletas = filtraEscalaoNacionalidade( listaAtletasOrdemChegada,
                                semFiltro, utmb2023.numeroDeAtletas / 2, "", "" );

  fprintf( resultPtr, "\nForam copiados os primeiros %d atletas sem qualquer filtro.\n",
                      quantosAtletas );
  fprintf( resultPtr, "15 primeiros atletas, de qualquer escalao e nacionalidade:\n" );
  fprintf( resultPtr, "%5s %7s %6s %23s %13s %13s %8s\n",
         "Pos. escalao", "Geral", "Dorsal", "Nome", "Escalao", "Nacionalidade", "Tempo" );
  for ( i = 0; i < 15; i++ )
    fprintf( resultPtr, "  %10d %7d %6d %23s %13s %13s %2d:%2d:%2d\n",
             semFiltro[i].posicaoFinalEscalao,
             semFiltro[i].posicaoFinalAbsoluta,
             semFiltro[i].dorsal,
             semFiltro[i].nome,
             semFiltro[i].escalao,
             semFiltro[i].nacionalidade,
             semFiltro[i].tempoNaMeta[0],
             semFiltro[i].tempoNaMeta[1],
             semFiltro[i].tempoNaMeta[2] );

  fclose( resultPtr );

  return 0;
}
