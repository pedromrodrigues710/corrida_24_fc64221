/**
 * Cria uma imagem com uma série temporal
 *
 * xs contém as abscissas; ys contém as ordenadas.
 * Requires:
 *   nomeFicheiroImagem não pode ter mais de 70 caracteres visíveis.
 * Ensures:
 *   cria um ficheiro PNG cujo nome é nomeFicheiroImagem concatenado com ".png";
 *   se já existir um ficheiro com esse nome, é reescrito;
 *   devolve 0 em caso de sucesso, 1 em caso de erro.
 */
int desenhaSerieTemporal( double xs[], double ys[], int tamanhoSerie,
                          double larguraImagem, double alturaImagem,
                          char *nomeFicheiroImagem );

/**
 * Cria uma imagem com duas séries temporais
 *
 * xsPrimeira contém as abscissas da primeira série; ysPrimeira contém as ordenadas
 * respectivas; idem para xsSegunda, ysSegunda.
 * Requires:
 *   nomeFicheiroImagem não pode ter mais de 70 caracteres visíveis.
 * Ensures:
 *   cria um ficheiro PNG cujo nome é nomeFicheiroImagem concatenado com ".png";
 *   se já existir um ficheiro com esse nome, é reescrito;
 *   devolve 0 em caso de sucesso, 1 em caso de erro.
 */
int comparaSeriesTemporais( double xsPrimeira[], double ysPrimeira[],
                            int tamanhoPrimeira,
                            double xsSegunda[], double ysSegunda[],
                            int tamanhoSegunda,
                            double larguraImagem, double alturaImagem,
                            char *nomeFicheiroImagem );

