/**
 * Cria uma imagem com uma s�rie temporal
 *
 * xs cont�m as abscissas; ys cont�m as ordenadas.
 * Requires:
 *   nomeFicheiroImagem n�o pode ter mais de 70 caracteres vis�veis.
 * Ensures:
 *   cria um ficheiro PNG cujo nome � nomeFicheiroImagem concatenado com ".png";
 *   se j� existir um ficheiro com esse nome, � reescrito;
 *   devolve 0 em caso de sucesso, 1 em caso de erro.
 */
int desenhaSerieTemporal( double xs[], double ys[], int tamanhoSerie,
                          double larguraImagem, double alturaImagem,
                          char *nomeFicheiroImagem );

/**
 * Cria uma imagem com duas s�ries temporais
 *
 * xsPrimeira cont�m as abscissas da primeira s�rie; ysPrimeira cont�m as ordenadas
 * respectivas; idem para xsSegunda, ysSegunda.
 * Requires:
 *   nomeFicheiroImagem n�o pode ter mais de 70 caracteres vis�veis.
 * Ensures:
 *   cria um ficheiro PNG cujo nome � nomeFicheiroImagem concatenado com ".png";
 *   se j� existir um ficheiro com esse nome, � reescrito;
 *   devolve 0 em caso de sucesso, 1 em caso de erro.
 */
int comparaSeriesTemporais( double xsPrimeira[], double ysPrimeira[],
                            int tamanhoPrimeira,
                            double xsSegunda[], double ysSegunda[],
                            int tamanhoSegunda,
                            double larguraImagem, double alturaImagem,
                            char *nomeFicheiroImagem );

