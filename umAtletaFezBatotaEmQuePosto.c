#include <stdio.h>

#include "corrida.h"

int umAtletaFezBatotaEmQuePosto( Atleta atleta, int nPostos, int arrayReferencia[] )
{
	int DiferencaTempos , i;
	
	for ( i = 1; i < nPostos; i++ )
	{
		int TempoAtual = atleta.temposPassagem[i];
		int TempoAnterior = atleta.temposPassagem[i - 1];
	
		DiferencaTempos = TempoAtual - TempoAnterior;
	
		if ( DiferencaTempos < arrayReferencia[i] ) {
		
			return i; /*batota = 1 se o atleta fez batota*/
		}
	}		
	return -1;
}