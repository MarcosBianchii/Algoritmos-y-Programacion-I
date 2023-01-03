#include "la_sombra_de_mac.h"

#include <stdio.h>
#include <stdlib.h>

int main(){

	char movimiento;

	coordenada_t posicion_mac, posicion_blu;
	
	personaje_t personaje;
	sombra_t sombra;

	juego_t juego;

	posicion_mac = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);
	posicion_blu.fila = posicion_mac.fila;
	posicion_blu.col = MAX_COLUMNAS - posicion_mac.col - 1;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	inicializar_personaje(&personaje, posicion_mac);
	inicializar_sombra(&sombra, posicion_blu);
/*
	printf("Mac {%i, %i}\n", personaje.posicion.fila, personaje.posicion.col);
	printf("Blu {%i, %i}\n", sombra.posicion.fila, sombra.posicion.col);
*/
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	while(0 == 0){

//		(personaje.vida > 0) && (sombra.esta_viva)

		juego.personaje = personaje;
		juego.sombra = sombra;

		imprimir_terreno(juego);

		pedir_movimiento(&movimiento);
	
		mover_personaje(&personaje, &sombra, movimiento);
	}

/*
	printf("Mac {%i, %i}\n", personaje.posicion.fila, personaje.posicion.col);
	printf("Blu {%i, %i}\n", sombra.posicion.fila, sombra.posicion.col);
*/

	return 0;
}