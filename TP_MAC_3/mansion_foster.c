#include "la_sombra_de_mac.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]){

	srand((unsigned)time(NULL));

// ARCHIVOS

	config_t config[MAX_NIVELES];

	int arch_return = archivos(argc, argv, config);

	if(arch_return != 0) return arch_return;

// JUEGO

	juego_t juego;

	inicializar_juego(&juego, config);

	while(estado_nivel(juego) == 0 && estado_juego(juego) != -1){

		imprimir_terreno(juego);
		realizar_jugada(&juego);
	}

	return 0;
}