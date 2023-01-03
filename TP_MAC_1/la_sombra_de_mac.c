#include "la_sombra_de_mac.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool coordenadas_iguales(coordenada_t a, coordenada_t b){
	
	bool coordenada_resultado = false;

	if(a.fila == b.fila && a.col == b.col){
		
			coordenada_resultado = true;
	}
	return coordenada_resultado;
}


void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje){

	(*ref_personaje).posicion = arranque_personaje;
	(*ref_personaje).vida = 3;
	(*ref_personaje).puntos = 0;
	(*ref_personaje).tiene_llave = false;
	(*ref_personaje).interruptor_apretado = false;
}


void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra){

	(*ref_sombra).posicion = arranque_sombra;
	(*ref_sombra).esta_viva = true;
}


bool es_movimiento_valido(char movimiento){

	bool validacion = false;

	if(movimiento == 'W' || movimiento == 'A' || movimiento == 'S' || movimiento == 'D'|| movimiento == 'w' || movimiento =='a'|| movimiento =='s'|| movimiento =='d'){
		validacion = true;
	}
	return validacion;
}


void pedir_movimiento(char* ref_movimiento){

	printf("\n\n                   W\n                 A S D\n\n");
	scanf(" %c",ref_movimiento);

	while(!es_movimiento_valido(*ref_movimiento)){

		scanf(" %c",ref_movimiento);
	}
}


bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho){

	bool dentro_rango = false;

	if((posicion.fila < max_ancho) && (posicion.col < max_alto) && (posicion.fila >= 0) && (posicion.col >= 0)){
		dentro_rango = true;
	}
	return dentro_rango;
}


void mover_personaje(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento){

	if((movimiento == 'W' || movimiento == 'w') && ((*ref_personaje).posicion.fila > 0) && ((*ref_personaje).posicion.fila < MAX_COLUMNAS)){
		(*ref_personaje).posicion.fila--;
	}
	if((movimiento == 'W' || movimiento == 'w') && ((*ref_sombra).posicion.fila > 0) && ((*ref_personaje).posicion.fila < MAX_COLUMNAS)){
		(*ref_sombra).posicion.fila--;
	}


	if((movimiento == 'A' || movimiento == 'a') && ((*ref_personaje).posicion.col > 0)){
		(*ref_personaje).posicion.col--;	
	}
	if((movimiento == 'A' || movimiento == 'a') && (*ref_sombra).posicion.col < (MAX_COLUMNAS - 1)){
		(*ref_sombra).posicion.col++;
	}


	if((movimiento == 'S' || movimiento == 's') && ((*ref_personaje).posicion.fila < (MAX_FILAS - 1))){
		(*ref_personaje).posicion.fila++;
	}
	if((movimiento == 'S' || movimiento == 's') && ((*ref_sombra).posicion.fila < (MAX_FILAS - 1))){
		(*ref_sombra).posicion.fila++;
	}


	if((movimiento == 'D' || movimiento == 'd') && ((*ref_personaje).posicion.col < (MAX_COLUMNAS - 1))){
		(*ref_personaje).posicion.col++;
	}
	if((movimiento == 'D' || movimiento == 'd') && ((*ref_sombra).posicion.col > 0)){
		(*ref_sombra).posicion.col--;
	}
}


coordenada_t coordenada_aleatoria(int max_alto, int max_ancho){

	srand ((unsigned)time(NULL));

	coordenada_t posicion;

	posicion.fila = rand() % max_ancho;
	posicion.col = rand() % max_alto;

	return posicion;
}


int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion){

	int retorno = -1;

	for(int i = 0; i < tope; i++){
		if((elementos[i].posicion.fila == posicion.fila) && (elementos[i].posicion.col == posicion.col)){
			retorno = i;
			i = tope;
		}
	}
	return retorno;
}


void imprimir_terreno(juego_t juego){

	char pantalla[MAX_FILAS][MAX_COLUMNAS];

	for(int i = 0; i < MAX_FILAS; i++){
		for(int j = 0; j < MAX_COLUMNAS; j++){

			pantalla[i][j] = '.';	
		}
	}

	pantalla[juego.sombra.posicion.fila][juego.sombra.posicion.col] = 'B';
	pantalla[juego.personaje.posicion.fila][juego.personaje.posicion.col] = 'M';
	
	system("clear");

	for(int i = 0; i < MAX_FILAS; i++){

		printf("\n");

		for(int j = 0; j < MAX_COLUMNAS; j++){

			printf("%c ", pantalla[i][j]);
		}
	}
}