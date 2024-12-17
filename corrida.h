/*************************
 * Constantes simbólicas *
 *************************/

#define NR_MAX_PONTOS_PASSAGEM 24
#define NR_MAX_ATLETAS 2800
#define TAMANHO_MAX_NOME_ATLETA 40
#define TAMANHO_MAX_NOME_EQUIPA 110
#define MAX_COLS_FICH_STARTERS 140
#define MAX_COLS_FICH_FINAL 170
#define MAX_COLS_FICH_PROGRESS 320

/*********
 * Tipos *
 *********/

/**
 * Data-hora-minuto absoluto e tempo decorrido em prova
 *
 * diaDaSemana é um de entre {"Fri.", "Sat.", "Sun."};
 * 0 <= horaDoDia <= 23 (hora que um relógio normal mostra);
 * 0 <= minutoAposHoraDoDia <= 59 (minuto que um relógio normal mostra);
 * horasRelativas e minutosRelativos são contados a partir de Fri. 18:00;
 * 0 <= horasAposInicio <= 53 (ou 46, respeitando o tempo limite de 46:30);
 * 0 <= minutosAposHorasAposInicio <= 59
 */
typedef struct {
  char diaDaSemana[5];
  int horaDoDia;
  int minutoAposHoraDoDia;
  int horasAposInicio;
  int minutosAposHorasAposInicio;
} Tempo;

/**
 * Detalhes de um atleta
 *
 * dorsal > 0;
 * nacionalidade é uma string contendo 3 letras maiúsculas, 1 espaço,
 *   e 2 letras maiúsculas dentro de parênteses;
 * escalao se masculino: "20-34M", "35-39M", "40-44M", e assim sucessivamente;
 * escalao se feminino: "20-34W", "35-39W", "40-44W", e assim sucessivamente;
 * posicaoFinalEscalao e tempoNaMeta ficam com valores indeterminados caso
 *   o atleta não tenha chegado à meta;
 * posicaoFinalAbsoluta fica com o valor 9999 caso o atleta não tenha chegado à meta;
 * tempoNaMeta: {horas desde a partida, minutos, segundos};
 * tempos de passagem medidos em minutos totais após a partida;
 * se o atleta não passou num ponto de passagem, tempo de passagem = 10000 aí;
 *   portanto, tempo de passagem = 10000 na meta caso o atleta não tenha lá chegado
 */
typedef struct {
  int dorsal;
  char nome[TAMANHO_MAX_NOME_ATLETA + 1];
  char nacionalidade[9];
  char escalao[7];
  int posicaoFinalAbsoluta;
  int posicaoFinalEscalao;
  int tempoNaMeta[3];
  int temposPassagem[NR_MAX_PONTOS_PASSAGEM];
} Atleta;

/**
 * Registo simples de passagem de um atleta por um posto de controlo
 *
 * dorsal > 0;
 * tempo de passagem medido em minutos totais após a partida;
 * se o atleta não passou neste ponto de passagem, tempo de passagem = -1 aqui
 */
typedef struct {
  int dorsal;
  int tempoPassagem;
} RegistoPassagem;

/**
 * Detalhes de uma corrida
 *
 * ano é o ano em que esta edição da corrida teve lugar;
 *   as instâncias de corrida deste tipo começam sempre às 18h00m de uma sexta-feira;
 * numeroDeAtletas é o número de atletas que partiram;
 * numeroPontosPassagem é o número de pontos de passagem que esta edição teve;
 * listaAtletas contém todos os atletas, ordenados por número de dorsal;
 *   apenas são instanciados os primeiros numeroDeAtletas atletas em listaAtletas;
 * tabelaPassagens contém os registos de passagem dos atletas;
 *   cada linha da tabela corresponde a um ponto de passagem, a.k.a. posto
 *     de controlo;
 *   em cada linha da tabela, ficam os registos de passagem de todos os
 *     atletas por ordem crescente de tempoPassagem;
 *   apenas são instanciadas as primeiras numeroPontosPassagem linhas
 *     e as primeira numeroDeAtletas colunas em ltabelaPassagens
 */
typedef struct {
  int ano;
  int numeroDeAtletas;
  int numeroPontosPassagem;
  Atleta listaAtletas[NR_MAX_ATLETAS];
  RegistoPassagem tabelaPassagens[NR_MAX_PONTOS_PASSAGEM][NR_MAX_ATLETAS];
} Corrida;

/***********
 * Funções *
 ***********/

/*******************
 * Função auxiliar *
 *******************/

/**
 * Obtém as horas decorridas em prova a partir da data-hora absoluta
 *
 * Nesta função ignora-se os minutos decorridos em prova.
 * Requires:
 *  diaDaSemana pode ser "Fri.", "Sat." ou "Sun.";
 *  0 <= horaDoDia <= 23
 */
int converteParaHorasAposInicio( const char *diaDaSemana, int horaDoDia );

/*********************************************************
 * Funções observadoras (getters) e funções de conversão *
 *********************************************************/

int minutosEmProva( Tempo tempo );

int dorsal( Atleta atleta );
char *nome( Atleta *atletaPtr );
char *nacionalidade( Atleta *atletaPtr );
char *escalao( Atleta *atletaPtr );
int posicaoFinalAbsoluta( Atleta atleta );
int posicaoFinalEscalao( Atleta atleta );
int *tempoNaMeta( Atleta *atletaPtr );
int *temposPassagem( Atleta *atletaPtr );

/**
 * Obtém o Tempo correspondente a um tempo de passagem em minutos
 *
 * Requires: 0 <= tempoPassagem < 3240 (54 horas)
 */
Tempo tempo( int tempoPassagem );

/*************************************
 * Função que inicializa uma corrida *
 *************************************/

/**
 * Cria uma corrida a partir de 3 ficheiros
 *
 * Requires:
 *   as 3 strings argumento são paths de ficheiros de texto alcançável;
 *   os ficheiros contém os 3 tipos de dados dos atletas
 *     e estão no formato exemplificado neste projecto;
 *   cada ficheiro contém pelo menos 1 atleta
 * Ensures:
 *   devolve uma instância de Corrida, onde
 *   os atletas são instanciados como detalhado na documentação de inicializaAtletas,
 *     atribuiResultadosNaMeta e atribuiTemposPassagem, respectivamente.
 */
Corrida criaCorrida( int ano,
                     const char *nomeFicheiroStarters,
                     const char *nomeFicheiroFinal,
                     const char *nomeFicheiroProgress );

/******************************************************
 * Funções de obtenção de dados a partir de ficheiros *
 ******************************************************/

/**
 * Obtém os dados de identificação dos atletas que iniciaram uma prova
 *
 * Requires:
 *   nomeFicheiro é o path de um ficheiro de texto alcançável;
 *   o ficheiro contém os dados dos atletas
 *     e está no formato exemplificado neste projecto
 *     (atletas ordenados por número de dorsal);
 *   o ficheiro contém pelo menos 1 atleta
 * Ensures:
 *   devolve o número de atletas lidos do ficheiro;
 *   inicializa, para cada atleta lido, os membros
 *     dorsal,
 *     nome,
 *     nacionalidade,
 *     escalao;
 *   inicializa também, PROVISORIAMENTE, o membro posicaoFinalAbsoluta
 *     com o valor arbitrário 9999.
 * Ficam por preencher, nos atletas, todos os dados de desempenho na prova.
 * Esse preenchimento é feito pela função atribuiResultadosNaMeta.
 * Os atletas que não tenham chegado à meta ficarão permanentemente com
 * o valor 9999 de posicaoFinalAbsoluta, e ficarão com valores indeterminados em
 * posicaoFinalEscalao e tempoNaMeta.
 */
int inicializaAtletas( Atleta listaAtletas[], const char *nomeFicheiro );

/**
 * Preenche os resultados finais dos atletas que terminaram uma prova
 *
 * Requires:
 *   tamanhoLista > 0;
 *   nomeFicheiro é o path de um ficheiro de texto alcançável;
 *   o ficheiro contém os resultados dos atletas
 *     e está no formato exemplificado neste projecto
 *     (atletas ordenados por número de dorsal);
 *   o ficheiro contém pelo menos 1 atleta;
 *   os atletas a preencher têm de ter o membro dorsal instanciado.
 * Ensures:
 *   devolve o número de atletas lidos do ficheiro, sendo APENAS os finalistas;
 *   instancia, em cada atleta lido, os membros
 *     posicaoFinalAbsoluta,
 *     posicaoFinalEscalao,
 *     tempoNaMeta.
 * Ficam por preencher, nos atletas, os tempos de passagem nos postos de controlo.
 */
int atribuiResultadosNaMeta( Atleta listaAtletas[], const char *nomeFicheiro );

/**
 * Atribui os tempos de passagem a todos os atletas que realizaram uma certa prova
 *
 * Requires:
 *   tamanhoLista > 0;
 *   nomeFicheiro é o path de um ficheiro de texto alcançável;
 *   o ficheiro contém os valores dia-hora de passagem de cada atleta
 *     e está no formato exemplificado neste projecto
 *     (atletas ordenados por número de dorsal);
 *   o ficheiro contém pelo menos 1 atleta;
 *   os atletas a preencher têm de ter o membro dorsal instanciado.
 * Ensures:
 *   devolve o número de postos de controlo;
 *   instancia, em cada atleta lido, o membro temposPassagem; os atletas cujos dados
 *     são lidos deverão ser os mesmos que iniciaram a prova
 */
int atribuiTemposPassagem( Atleta listaAtletas[], const char *nomeFicheiro );

/**
 * Preenche uma tabela com registos de passagem dos atletas de uma prova
 *
 * Cada linha da tabela corresponde a um ponto de passagem, a.k.a. posto
 * de controlo.
 * Assume-se que cada atleta tem temposPassagem[] correctamente preenchido.
 * Requires:
 *   tamanhoLista > 0
 * Ensures:
 *   coloca, em cada linha da tabela, os registos de passagem de todos os
 *     atletas pela mesma ordem em que os atletas estão em listaAtletas;
 *   os tempos são medidos em minutos após a partida.
 */
void preencheTabelaPassagens( Atleta listaAtletas[], int tamanhoLista,
                              RegistoPassagem tabela[][NR_MAX_ATLETAS],
                              int nPostos );

/************************
 * Funções de ordenação *
 ************************/

/**
 * Ordena vec por ordem crescente de tempo, entre os índices inicio e fim inclusive
 *
 * A ordenação é pelo membro tempoPassagem de cada vec[i].
 * Requires: 0 <= inicio < fim.
 */
void ordenaPorTempoPassagem( RegistoPassagem vec[], int inicio, int fim );

/**
 * Ordena uma tabela que contém registos de passagem dos atletas
 *
 * Cada linha da tabela corresponde a um ponto de passagem, a.k.a. posto
 * de controlo.
 * Assume-se que a tabela está correctamente preenchida com os tempos de
 * passagem dos atletas em minutos após a partida.
 * Requires:
 *   nAtletas > 0
 * Ensures:
 *   ordena cada linha da tabela por ordem crescente de tempoPassagem.
 */
void ordenaTabelaPassagens( int nAtletas, RegistoPassagem tabela[][NR_MAX_ATLETAS],
                            int nPostos );

/**
 * Ordena vec por ordem crescente de posição, entre os índices inicio e fim inclusive
 *
 * A ordenação é pelo membro posicaoFinalAbsoluta de cada vec[i].
 * Requires: 0 <= inicio < fim.
 */
void ordenaPorPosicaoFinal( Atleta vec[], int inicio, int fim );

/***********************
 * Funções de pesquisa *
 ***********************/

/**
 * Pesquisa um atleta num vector de atletas, por dorsal
 *
 * Não se pode assumir que o vector está ordenado por dorsal.
 * Requires:
 *   atletas com o dorsal correctamente instanciado;
 *   tamanho > 0.
 * Ensures:
 *   o índice da primeira ocorrência de dorsal, caso exista,
 *   -1, caso não ocorra.
 */
int indiceAtleta( Atleta vec[], int tamanho, int dorsal );

/**
 * Devolve um atleta num vector de atletas, por dorsal
 *
 * Não se pode assumir que o vector está ordenado por dorsal.
 * Requires:
 *   atletas com o dorsal correctamente instanciado;
 *   tamanho > 0;
 *   existe no vector um atleta com o dorsal indicado.
 * Ensures:
 *   devolve o primeiro atleta com o dorsal indicado.
 */
Atleta getAtleta( Atleta vec[], int tamanho, int dorsal );

/**
 * Pesquisa um RegistoPassagem num vector de RegistoPassagem, por dorsal
 *
 * Não se pode assumir que o vector está ordenado por dorsal.
 * Requires:
 *   tamanho > 0.
 * Ensures:
 *   o índice da primeira ocorrência de dorsal, caso exista,
 *   -1, caso não ocorra.
 */
int indiceRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal );

/**
 * Devolve um RegistoPassagem num vector de RegistoPassagem, por dorsal
 *
 * Não se pode assumir que o vector está ordenado por dorsal.
 * Requires:
 *   tamanho > 0;
 *   existe no vector um RegistoPassagem com o dorsal indicado.
 * Ensures:
 *   devolve o primeiro RegistoPassagem com o dorsal indicado.
 */
RegistoPassagem getRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal );

/*********************************************
 * Avaliação de desempenho ao longo da prova *
 *********************************************/

 /**
 * Regista a posição de um atleta em cada um dos postos de controlo.
 *
 * Requires:
 *   nAtletas > 0, nPostos > 0;
 *   dorsal ocorre na tabela;
 *   a tabela está ordenada em cada posto de controlo, por tempo de passagem.
 * Ensures:
 *   preenche o vector posicoes com as posicões do atleta em cada um dos postos
 *   de controlo.
 */
void registaPosicoesPostos( int nAtletas, RegistoPassagem tabela[][NR_MAX_ATLETAS],
                            int nPostos, int dorsal, int posicoes[] );

/**************************************
 * Processamento de resultados finais *
 **************************************/

/**
 * Filtra um vector de atletas por escalão e/ou nacionalidade.
 *
 * Requires:
 *   0 < tamanhoOrigem (é o tamanho efectivo de vecOrigem);
 *   vecDestino tem de ter tamanho suficiente para guardar os elementos filtrados;
 *   escalao e nacionalidade têm de ser etiquetas válidas, ou a string vazia.
 * Ensures:
 *   copia para vecDestino os elementos de vecOrigem que têm o escalão e/ou
 *   a nacionalidade indicados;
 *   é preservada a ordem dos elementos como está em vecOrigem;
 *   assim, se vecOrigem estiver ordenado (por exemplo, por posicaoFinalAbsoluta),
 *   vecDestino também o estará;
 *   se escalao ou nacionalidade forem a string vazia, não é aplicado o respectivo
 *   filtro;
 *   devolve o número de elementos copiados para vecDestino.
 */
int filtraEscalaoNacionalidade( Atleta vecOrigem[], Atleta vecDestino[],
                                int tamanhoOrigem,
                                const char *escalao, const char *nacionalidade );

/**********************
 * Detecção de batota *
 **********************/

/**
 * Um certo atleta fez batota num certo posto de controlo?
 *
 * Assinala-se batota se a diferença de tempo para o posto anterior for inferior a
 *   um intervalo de tempo de referência.
 * Não faz sentido aplicar esta função a um posto onde o atleta não passou; em geral,
 *   assinala um falso positivo.
 * Requires:
 *   1 <= posto <= (numeroPontosPassagem - 1)
 * Ensures:
 *   devolve 1 caso o atleta tenha feito batota, 0 caso não tenha feito.
 */
int umAtletaFezBatotaNumCertoPosto( Atleta atleta, int posto, int referencia );

/**
 * Em que posto de controlo um certo atleta fez batota?
 *
 * Assinala-se batota se alguma diferença de tempo para o posto anterior for inferior
 *   a um intervalo de tempo de referência, registado em arrayReferencia.
 * Não faz sentido aplicar esta função caso o atleta não tenha passado num certo
 *   número de postos; em geral, assinala um falso positivo.
 * Requires:
 *   arrayReferencia contém pelo menos nPostos elementos, mas o de índice 0 não é usado.
 * Ensures:
 *   devolve o índice do primeiro posto onde a batota seja detectada,
 *     -1 caso o atleta não tenha feito batota.
 */
int umAtletaFezBatotaEmQuePosto( Atleta atleta, int nPostos, int arrayReferencia[] );
