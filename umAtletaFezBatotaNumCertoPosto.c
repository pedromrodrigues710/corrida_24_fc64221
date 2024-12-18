#include <stdio.h>

#include <corrida.h>

int umAtletaFezBatotaNumCertoPosto(Atleta atleta, int posto, int referencia) {
	
	int batota; {
	
		int TempoAtual = Atleta_TemposDePassagem[posto];
		int TempoAnterior = Atleta_TemposDEPassagem[posto - 1];
	
		int DiferencaTempos = TempoAtual - TempoAnterior;
	
		if ( DiferencaTempos < referencia ) {
		
			batota = 1; /*batota = 1 se o atleta fez batota*/
		}
		
		else {
			
			batota = 0; /*batota = 0 se o atleta NAO fez batota*/
		}
		
	return batota;
	}
}