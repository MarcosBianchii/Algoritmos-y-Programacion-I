#include "la_sombra_de_mac.h"

#include <stdlib.h>
#include <time.h>

int main(){

	srand((unsigned)time(NULL));

	juego_t juego;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	inicializar_juego(&juego);

	while(estado_nivel(juego) == 0 && estado_juego(juego) != -1){

		imprimir_terreno(juego);

		realizar_jugada(&juego);
	}
	
	return 0;
}