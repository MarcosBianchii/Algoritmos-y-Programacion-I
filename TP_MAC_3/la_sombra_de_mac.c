#include "la_sombra_de_mac.h"
#include "utiles.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIDA_INICIAL 3
#define PUNTOS_INICIALES 0
#define COSTE_VIDA_EXTRA 200
#define COSTE_REVIVIR_SOMBRA 50

#define ARRIBA 'W'
#define IZQUIERDA 'A'
#define ABAJO 'S'
#define DERECHA 'D'
#define VIDA_EXTRA 'V'

#define VACIO '.'
#define PUERTA 'D'
#define ESCALERAS 'E'
#define LLAVE 'L'
#define MONEDAS 'C'
#define POZOS 'W'
#define INTERRUPTORES 'O'
#define PORTALES 'P'
#define VELAS 'V'
#define PAREDES 'X'

#define MAC 'M'
#define BLOO 'B'

#define PUERTA_ABIERTA_EMOJI "\U0001f6aa"
#define PUERTA_CERRADA_EMOJI "\U0001f512"
#define ESCALERAS_EMOJI "\U0001fa9c"
#define LLAVE_EMOJI "\U0001f5dd"
#define MONEDAS_EMOJI "\U0001f4b0"
#define POZOS_EMOJI "\U0001f573"
#define INTERRUPTORES_ESPEJADO_EMOJI "\U0001f534"
#define INTERRUPTORES_COPIA_EMOJI "\U0001f7e2"
#define PORTALES_EMOJI "\U0001f300"
#define VELAS_EMOJI "\U0001f56f"
#define PAREDES_EMOJI "\U0001f9f1"

#define VIDAS_EMOJI "\U0001f90d"
#define CALAVERA_EMOJI "\U0001f480"

#define MAC_EMOJI "\U0001f466"
#define MAC_SOMBRA_MUERTA_EMOJI "\U0001f926\u200D"
#define BLOO_EMOJI "\U0001f47b"
#define BLOO_MUERTO_EMOJI "\U0001f6cf"

#define READ "r"
#define WRITE "w"
#define CANTIDAD_ELEMS_JUEGO 21
#define UNA_PUERTA 1

// Procedimiento que usa el archivo config_juego.
int config_juego(config_t config[MAX_PARTIDA], char *argv[])
{

	config_elems_t config_elems[CANTIDAD_ELEMS_JUEGO];

	int tope;
	int linea = 0;

	FILE *arch = fopen(argv[1], READ);
	if (!arch)
	{

		perror("F config_juego");
		return -1;
	}

	// LEER ARCHIVO

	while (!feof(arch))
	{

		fscanf(arch, "N%i_%[^=]=%i\n", &config_elems[linea].nivel, config_elems[linea].elemento, &config_elems[linea].cantidad);

		if (config_elems[linea].cantidad < 0)
			config_elems[linea].cantidad *= -1;

		linea++;
	}

	tope = linea;

	// CARGAR DATOS

	for (int i = 0; i < tope; i++)
	{

		if (strcmp(config_elems[i].elemento, "POZOS") == 0)
			config[config_elems[i].nivel - 1].pozos = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "VELAS") == 0)
			config[config_elems[i].nivel - 1].velas = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "INTERRUPTORES") == 0)
			config[config_elems[i].nivel - 1].interruptores = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "PORTALES") == 0)
			config[config_elems[i].nivel - 1].portales = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "MONEDAS") == 0)
			config[config_elems[i].nivel - 1].monedas = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "ESCALERAS") == 0)
			config[config_elems[i].nivel - 1].escaleras = config_elems[i].cantidad;
		if (strcmp(config_elems[i].elemento, "LLAVES") == 0)
			config[config_elems[i].nivel - 1].llaves = config_elems[i].cantidad;
	}

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		config[i].tope_obstaculos = config[i].pozos + config[i].velas + config[i].interruptores + config[i].portales;
		config[i].tope_herramientas = config[i].monedas + config[i].escaleras + config[i].llaves + UNA_PUERTA;
	}

	fclose(arch);
	return 0;
}

// Procedimiento que carga las configuracines default del juego.
void cargar_configuraciones_default(config_t config[MAX_NIVELES])
{

	// NIVEL 1

	config[0].pozos = 15;
	config[0].velas = 5;
	config[0].interruptores = 1;
	config[0].portales = 0;
	config[0].monedas = 10;
	config[0].escaleras = 10;
	config[0].llaves = 0;
	config[0].tope_obstaculos = 21;
	config[0].tope_herramientas = 21;

	// NIVEL 2

	config[1].pozos = 20;
	config[1].velas = 10;
	config[1].interruptores = 2;
	config[1].portales = 2;
	config[1].monedas = 15;
	config[1].escaleras = 15;
	config[1].llaves = 1;
	config[1].tope_obstaculos = 34;
	config[1].tope_herramientas = 32;

	// NIVEL 3

	config[2].pozos = 30;
	config[2].velas = 12;
	config[2].interruptores = 4;
	config[2].portales = 4;
	config[2].monedas = 15;
	config[2].escaleras = 15;
	config[2].llaves = 1;
	config[2].tope_obstaculos = 50;
	config[2].tope_herramientas = 32;
}

// Procedimiento que agrega una nueva partida al archivo partidas.csv de forma ordenada.
void agregar_partida(partida_t partidas[MAX_PARTIDA], int *tope, partida_t partida, partida_t aux, char gano[MAX_GANO])
{

	system("clear");
	printf("Ingrese el nombre del jugador: ");
	scanf("%s", partida.jugador);
	printf("Ingrese el nivel alcanzado: ");
	scanf("%i", &partida.nivel_llegado);
	printf("Ingrese la cantidad de puntos obtenida: ");
	scanf("%i", &partida.puntos);
	printf("Ingrese la cantidad de vidas restantes: ");
	scanf("%i", &partida.vidas_restantes);
	printf("Ingrese si termino la partida: ");
	scanf("%s", gano);
	system("clear");

	if (strcmp("Si", gano) == 0)
		partida.gano = true;
	else if (strcmp("No", gano) == 0)
		partida.gano = false;

	for (int i = 0; i < (*tope); i++)
	{

		if (strcmp(partidas[i].jugador, partida.jugador) == 0)
		{

			if (partidas[i].puntos >= partida.puntos)
			{

				aux = partidas[i];
				partidas[i] = partida;
				partida = aux;
			}
		}

		else if (strcmp(partidas[i].jugador, partida.jugador) > 0)
		{

			aux = partidas[i];
			partidas[i] = partida;
			partida = aux;
		}
	}

	partidas[*tope] = partida;
	(*tope)++;

	system("clear");
	printf("listo rey ;)\n");
}

// Procedimiento que elimina una partida del archivo partidas.csv.
void eliminar_partida(partida_t partidas[MAX_PARTIDA], int *tope, partida_t partida, char *argv[])
{

	int pos_a_eliminar;
	bool encontro_posicion = false;

	for (int i = 0; i < (*tope) && !encontro_posicion; i++)
	{

		if (strcmp(partidas[i].jugador, argv[3]) == 0)
		{

			pos_a_eliminar = i;
			encontro_posicion = true;

			for (int j = pos_a_eliminar; j < (*tope) - 1; j++)
			{

				partidas[j] = partidas[j + 1];
			}

			(*tope)--;
		}
	}

	system("clear");

	if (!encontro_posicion)
	{

		perror("No entonctre lo que estabas buscando\n");
	}

	else if (encontro_posicion)
	{

		printf("listo rey ;)\n");
	}
}

// Procedimiento que ordena las partidas del archivo partidas.csv.
void ordenar_partidas(partida_t partidas[MAX_PARTIDA], int *tope, partida_t aux)
{

	for (int i = 1; i < (*tope); i++)
	{

		for (int j = 0; j < (*tope) - i; j++)
		{

			if (strcmp(partidas[j].jugador, partidas[j + 1].jugador) == 0)
			{

				if (partidas[j].puntos >= partidas[j + 1].puntos)
				{

					aux = partidas[j];
					partidas[j] = partidas[j + 1];
					partidas[j + 1] = aux;
				}
			}

			if (strcmp(partidas[j].jugador, partidas[j + 1].jugador) > 0)
			{

				aux = partidas[j];
				partidas[j] = partidas[j + 1];
				partidas[j + 1] = aux;
			}
		}
	}

	system("clear");
	printf("listo rey ;)\n");
}

// Procedimiento que usa el archivo partidas.csv.
int partidas_csv(partida_t partidas[MAX_PARTIDA], char *argv[])
{

	int partidas_csv = 0;

	partida_t partida;
	partida_t aux;

	int tope;
	int linea = 0;
	char gano[MAX_GANO];

	FILE *arch = fopen(argv[2], READ);
	if (!arch)
	{

		perror("F Archivo Original\n");
		return -1;
	}

	FILE *arch_aux = fopen("aux.txt", WRITE);
	if (!arch_aux)
	{

		fclose(arch);
		perror("F Archivo Auxiliar\n");
		return -1;
	}

	// LEER ARCHIVO

	while (!feof(arch))
	{

		fscanf(arch, "%[^;];%i;%i;%i;%[^\n]\n",
		       partidas[linea].jugador, &partidas[linea].nivel_llegado,
		       &partidas[linea].puntos, &partidas[linea].vidas_restantes, gano);

		if (strcmp(gano, "Si") == 0)
			partidas[linea].gano = true;
		if (strcmp(gano, "No") == 0)
			partidas[linea].gano = false;

		linea++;
	}

	tope = linea;

	// AGREGAR PARTIDA

	if (strcmp(argv[1], "agregar_partida") == 0)
	{

		agregar_partida(partidas, &tope, partida, aux, gano);
		partidas_csv = 1;
	}

	// ELIMINAR PARTIDA

	else if (strcmp(argv[1], "eliminar_partida") == 0)
	{

		eliminar_partida(partidas, &tope, partida, argv);
		partidas_csv = 1;
	}

	// ORDENAR PARTIDAS

	else if (strcmp(argv[1], "ordenar_partidas") == 0)
	{

		ordenar_partidas(partidas, &tope, aux);
		partidas_csv = 1;
	}

	// IMPRIMIR AUX PARTIDAS

	for (int i = 0; i < tope; i++)
	{

		if (partidas[i].gano)
		{

			fprintf(arch_aux, "%s;%i;%i;%i;Si\n", partidas[i].jugador, partidas[i].nivel_llegado,
				partidas[i].puntos, partidas[i].vidas_restantes);
		}

		else if (!partidas[i].gano)
		{

			fprintf(arch_aux, "%s;%i;%i;%i;No\n", partidas[i].jugador, partidas[i].nivel_llegado,
				partidas[i].puntos, partidas[i].vidas_restantes);
		}
	}

	fclose(arch_aux);
	fclose(arch);
	rename("aux.txt", argv[2]);
	return partidas_csv;
}

// Procedimiento que maneja los archivos.
int archivos(int argc, char *argv[], config_t config[MAX_NIVELES])
{

	partida_t partidas[MAX_PARTIDA];

	if (argc > 1)
	{

		// CONFIG_JUEGO

		if (strcmp(argv[1], "config_juego") == 0)
		{

			return config_juego(config, argv);
		}

		// PARTIDAS.CSV

		if (argc > 2)
		{

			return partidas_csv(partidas, argv);
		}

		return -1;
	}

	cargar_configuraciones_default(config);
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Funcion que compara 2 coordenadas para saber si son iguales.
bool coordenadas_iguales(coordenada_t a, coordenada_t b)
{

	return (a.fila == b.fila && a.col == b.col);
}

// Le saque la coordenada_t arranque_personaje porque ya hay una
// funcion que se encarga de darle la posicion al personaje.
//
// Ademas le agregue el vector config para usar distintos emojis
// para la puerta del primer nivel si es que existe una llave.
void inicializar_personaje(personaje_t *personaje, config_t config[MAX_PARTIDA])
{

	(*personaje).vida = VIDA_INICIAL;
	(*personaje).puntos = PUNTOS_INICIALES;
	(*personaje).interruptor_apretado = false;

	if (config[0].llaves < 1)
		(*personaje).tiene_llave = true;
	if (config[0].llaves > 0)
		(*personaje).tiene_llave = false;
}

// Le saque la coordenada_t arranque_sombra porque ya hay una
// funcion que se encarga de darle la posicion a la sombra.
void inicializar_sombra(sombra_t *sombra)
{

	(*sombra).esta_viva = true;
}

// Funcion que valida el movimiento del jugador.
bool es_movimiento_valido(char movimiento)
{

	return (movimiento == ARRIBA || movimiento == IZQUIERDA || movimiento == ABAJO ||
		movimiento == DERECHA || movimiento == VIDA_EXTRA);
}

// Agregue un juego_t para poder llamar a la funcion imprimir terreno.
void pedir_movimiento(juego_t juego, char *ref_movimiento)
{

	scanf(" %c", ref_movimiento);

	while (!es_movimiento_valido(*ref_movimiento))
	{

		imprimir_terreno(juego);

		printf("\n\
Controles:\n\
\n\
%c -> Arriba\n\
%c -> Izquierda\n\
%c -> Abajo\n\
%c -> Derecha\n\
%c -> Vida Extra\n\
\n\
%i  -> Coste de revivir a la sombra\n\
%i -> Coste para una vida extra\n\n",
		       ARRIBA, IZQUIERDA, ABAJO, DERECHA,
		       VIDA_EXTRA, COSTE_REVIVIR_SOMBRA,
		       COSTE_VIDA_EXTRA);

		scanf(" %c", ref_movimiento);
	}
}

// Funcion que valida si una posicion esta dentro de un rango.
bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho)
{

	return ((posicion.fila < max_alto) && (posicion.col < max_ancho) &&
		(posicion.fila >= 0) && (posicion.col >= 0));
}

// Funcion que devuelve una coordenada aleatoria.
coordenada_t coordenada_aleatoria(int max_alto, int max_ancho)
{

	coordenada_t posicion;

	posicion.fila = rand() % max_alto;
	posicion.col = rand() % max_ancho;

	return posicion;
}

// Procedimiento que ubica a Bloo tomando en cuenta la posicion de Mac.
void formula_sombra(personaje_t *personaje, sombra_t *sombra)
{

	(*sombra).posicion.fila = (*personaje).posicion.fila;
	(*sombra).posicion.col = MAX_COLUMNAS - (*personaje).posicion.col - 1;
}

// Funcion que busca una coordenada dentro de un vector de elementos tipo elemento_t.
int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion)
{

	int buscar_elemento = -1;
	bool encontro_posicion = false;

	for (int i = 0; i < tope && !encontro_posicion; i++)
	{

		if (coordenadas_iguales(elementos[i].coordenada, posicion))
		{

			buscar_elemento = i;
			encontro_posicion = true;
		}
	}

	return buscar_elemento;
}

// Procedimiento que carga la matriz pantalla con
// los elementos en sus respectivas coordenadas.
void cargar_pantalla(juego_t juego, char pantalla[MAX_FILAS][MAX_COLUMNAS])
{

	for (int i = 0; i < MAX_FILAS; i++)
	{

		for (int j = 0; j < MAX_COLUMNAS; j++)
		{

			pantalla[i][j] = VACIO;
		}
	}

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++)
	{

		pantalla[juego.niveles[juego.nivel_actual - 1].paredes[i].fila]
			[juego.niveles[juego.nivel_actual - 1].paredes[i].col] = PAREDES;
	}

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_obstaculos; i++)
	{

		pantalla[juego.niveles[juego.nivel_actual - 1].obstaculos[i].coordenada.fila]
			[juego.niveles[juego.nivel_actual - 1].obstaculos[i].coordenada.col] =
			    juego.niveles[juego.nivel_actual - 1].obstaculos[i].tipo;
	}

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++)
	{

		pantalla[juego.niveles[juego.nivel_actual - 1].herramientas[i].coordenada.fila]
			[juego.niveles[juego.nivel_actual - 1].herramientas[i].coordenada.col] =
			    juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo;
	}

	pantalla[juego.sombra.posicion.fila][juego.sombra.posicion.col] = BLOO;
	pantalla[juego.personaje.posicion.fila][juego.personaje.posicion.col] = MAC;
}

// Procedimiento que imprime la matriz pantalla en la terminal.
void imprimir_matriz(juego_t juego, char pantalla[MAX_FILAS][MAX_COLUMNAS])
{

	system("clear");

	for (int i = 0; i < MAX_FILAS; i++)
	{

		for (int j = 0; j < MAX_COLUMNAS; j++)
		{

			if (pantalla[i][j] == VACIO)
				printf("  ");
			if (pantalla[i][j] == LLAVE)
				printf("%s ", LLAVE_EMOJI);
			if (pantalla[i][j] == MONEDAS)
				printf("%s", MONEDAS_EMOJI);
			if (pantalla[i][j] == POZOS)
				printf("%s ", POZOS_EMOJI);
			if (pantalla[i][j] == PORTALES)
				printf("%s", PORTALES_EMOJI);
			if (pantalla[i][j] == VELAS)
				printf("%s ", VELAS_EMOJI);
			if (pantalla[i][j] == PAREDES)
				printf("%s", PAREDES_EMOJI);
			if (pantalla[i][j] == ESCALERAS)
				printf("%s ", ESCALERAS_EMOJI);

			// PUERTA

			if (juego.personaje.tiene_llave)
			{

				if (pantalla[i][j] == PUERTA)
					printf("%s", PUERTA_ABIERTA_EMOJI);
			}
			if (!juego.personaje.tiene_llave)
			{

				if (pantalla[i][j] == PUERTA)
					printf("%s", PUERTA_CERRADA_EMOJI);
			}

			// INTERRUPTORES

			if (!juego.personaje.interruptor_apretado)
			{

				if (pantalla[i][j] == INTERRUPTORES)
					printf("%s", INTERRUPTORES_ESPEJADO_EMOJI);
			}
			if (juego.personaje.interruptor_apretado)
			{

				if (pantalla[i][j] == INTERRUPTORES)
					printf("%s", INTERRUPTORES_COPIA_EMOJI);
			}

			// MAC Y BLOO

			if (juego.sombra.esta_viva)
			{

				if (pantalla[i][j] == MAC)
					printf("%s", MAC_EMOJI);
				if (pantalla[i][j] == BLOO)
					printf("%s", BLOO_EMOJI);
			}
			if (!juego.sombra.esta_viva)
			{

				if (pantalla[i][j] == MAC)
					printf("%s", MAC_SOMBRA_MUERTA_EMOJI);
				if (pantalla[i][j] == BLOO)
					printf("%s ", BLOO_MUERTO_EMOJI);
			}
		}

		printf("\n");
	}
}

// Procedimiento que imprime la interfaz
// mostrando la informacion del personaje.
void imprimir_interfaz(juego_t juego)
{

	if (juego.personaje.vida == 1)
	{
		printf("\
%s                                        Nivel: %i\n\
%s: %i\n\
                         %c\n\
                       %c %c %c\n",
		       VIDAS_EMOJI, juego.nivel_actual, MONEDAS_EMOJI,
		       juego.personaje.puntos, ARRIBA, IZQUIERDA, ABAJO, DERECHA);
	}

	if (juego.personaje.vida == 2)
	{
		printf("\
%s%s                                      Nivel: %i\n\
%s: %i\n\
                         %c\n\
                       %c %c %c\n",
		       VIDAS_EMOJI, VIDAS_EMOJI, juego.nivel_actual, MONEDAS_EMOJI,
		       juego.personaje.puntos, ARRIBA, IZQUIERDA, ABAJO, DERECHA);
	}

	if (juego.personaje.vida == 3)
	{
		printf("\
%s%s%s                                    Nivel: %i\n\
%s: %i\n\
                         %c\n\
                       %c %c %c\n",
		       VIDAS_EMOJI, VIDAS_EMOJI, VIDAS_EMOJI, juego.nivel_actual,
		       MONEDAS_EMOJI, juego.personaje.puntos, ARRIBA, IZQUIERDA, ABAJO, DERECHA);
	}
}

// Procedimiento que imprime el terreno
// del juego en la terminal.
void imprimir_terreno(juego_t juego)
{

	char pantalla[MAX_FILAS][MAX_COLUMNAS];

	cargar_pantalla(juego, pantalla);
	imprimir_matriz(juego, pantalla);
	imprimir_interfaz(juego);
}

// Funcion que compara la posicion de un elemento con las posiciones
// dentro del vector de paredes y si matchean devuelve un true.
bool elemento_sobre_pared(coordenada_t elemento, coordenada_t paredes[MAX_PAREDES], int tope)
{

	bool elemento_sobre_pared = false;

	for (int i = 0; i < tope && !elemento_sobre_pared; i++)
	{

		if (coordenadas_iguales(elemento, paredes[i]))
			elemento_sobre_pared = true;
	}

	return elemento_sobre_pared;
}

// Funcion que calcula una distancia Manhattan.
int distancia_manhattan(coordenada_t a, coordenada_t b)
{

	int resultado;

	int resta_filas = a.fila - b.fila;
	int resta_col = a.col - b.col;

	if (resta_filas < 0)
		resta_filas *= -1;
	if (resta_col < 0)
		resta_col *= -1;

	resultado = resta_filas + resta_col;

	return resultado;
}

// Funcion que recibe una coordenada y devuelve
// true si esta a una posicion de distancia.
bool sombra_rango_vela(coordenada_t pos_sombra, coordenada_t pos_vela)
{

	bool sombra_rango_vela = false;

	coordenada_t pos_1, pos_2, pos_3, pos_4;

	pos_1.fila = pos_vela.fila - 1;
	pos_1.col = pos_vela.col - 1;
	pos_2.fila = pos_vela.fila - 1;
	pos_2.col = pos_vela.col + 1;
	pos_3.fila = pos_vela.fila + 1;
	pos_3.col = pos_vela.col - 1;
	pos_4.fila = pos_vela.fila + 1;
	pos_4.col = pos_vela.col + 1;

	if (coordenadas_iguales(pos_sombra, pos_1) ||
	    coordenadas_iguales(pos_sombra, pos_2) ||
	    coordenadas_iguales(pos_sombra, pos_3) ||
	    coordenadas_iguales(pos_sombra, pos_4) ||
	    distancia_manhattan(pos_sombra, pos_vela) <= 1)
	{

		sombra_rango_vela = true;
	}

	return sombra_rango_vela;
}

// Procedimiento que le da numero a los niveles
// y llama a la funcion obtener_mapa().
void asignar_numero_niveles(juego_t *juego)
{

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		obtener_mapa((*juego).niveles[i].paredes, (&(*juego).niveles[i].tope_paredes));

		(*juego).niveles[i].numero_nivel = i + 1;
	}
}

// Procedimiento que carga que tipo de elemento es cada posicion de los vectores
// obstaculos y herramientas.
void inicializar_niveles_tipo(nivel_t niveles[MAX_NIVELES], config_t config[MAX_NIVELES])
{

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		// OBSTACULOS

		niveles[i].tope_obstaculos = config[i].tope_obstaculos;

		for (int j = 0; j < niveles[i].tope_obstaculos; j++)
		{

			niveles[i].obstaculos[j].tipo = POZOS;
			if (j >= config[i].pozos)
				niveles[i].obstaculos[j].tipo = VELAS;
			if (j >= config[i].pozos + config[i].velas)
				niveles[i].obstaculos[j].tipo = INTERRUPTORES;
			if (j >= config[i].pozos + config[i].velas + config[i].interruptores)
				niveles[i].obstaculos[j].tipo = PORTALES;
		}

		// HERRAMIENTAS

		niveles[i].tope_herramientas = config[i].tope_herramientas;

		for (int j = 0; j < niveles[i].tope_herramientas; j++)
		{

			niveles[i].herramientas[j].tipo = MONEDAS;
			if (j >= config[i].monedas)
				niveles[i].herramientas[j].tipo = LLAVE;
			if (j >= config[i].monedas + config[i].llaves)
				niveles[i].herramientas[j].tipo = ESCALERAS;
			if (j >= config[i].monedas + config[i].llaves + config[i].escaleras)
				niveles[i].herramientas[j].tipo = PUERTA;
		}
	}
}

// Procedimiento que ubica a los obstaculos en todos los
// niveles y se fija que no se solape con otro elemento.
void asignar_coordenadas_obstaculos(juego_t *juego)
{

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		for (int j = 0; j < (*juego).niveles[i].tope_obstaculos; j++)
		{

			do
				(*juego).niveles[i].obstaculos[j].coordenada = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);

			while ((buscar_elemento((*juego).niveles[i].obstaculos, j, (*juego).niveles[i].obstaculos[j].coordenada) != -1) ||
			       elemento_sobre_pared((*juego).niveles[i].obstaculos[j].coordenada, (*juego).niveles[i].paredes, (*juego).niveles[i].tope_paredes));
		}
	}
}

// Procedimiento que ubica a las herramientas en todos los
// niveles y se fija que no se solape con otro elemento.
void asignar_coordenadas_herramientas(juego_t *juego)
{

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		for (int j = 0; j < (*juego).niveles[i].tope_herramientas; j++)
		{

			do
				(*juego).niveles[i].herramientas[j].coordenada = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);

			while ((buscar_elemento((*juego).niveles[i].herramientas, j, (*juego).niveles[i].herramientas[j].coordenada) != -1) ||
			       (buscar_elemento((*juego).niveles[i].obstaculos, (*juego).niveles[i].tope_obstaculos, (*juego).niveles[i].herramientas[j].coordenada) != -1) ||
			       elemento_sobre_pared((*juego).niveles[i].herramientas[j].coordenada, (*juego).niveles[i].paredes, (*juego).niveles[i].tope_paredes));
		}
	}
}

// Procedimiento que ubica las escaleras
// sobre espacios ocupados por paredes.
void asignar_coordenadas_escaleras(juego_t *juego)
{

	for (int i = 0; i < MAX_NIVELES; i++)
	{

		for (int j = 0; j < (*juego).niveles[i].tope_herramientas; j++)
		{

			if ((*juego).niveles[i].herramientas[j].tipo == ESCALERAS)
			{

				do
					(*juego).niveles[i].herramientas[j].coordenada = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);

				while (!elemento_sobre_pared((*juego).niveles[i].herramientas[j].coordenada, (*juego).niveles[i].paredes, (*juego).niveles[i].tope_paredes) ||
				       buscar_elemento((*juego).niveles[i].herramientas, j, (*juego).niveles[i].herramientas[j].coordenada) != -1);
			}
		}
	}
}

// Procedimiento que ubica a los personajes fuera de
// cualquier elemento y los reubica si la sombra queda
// cerca de una vela.
void asignar_coordenadas_personajes(juego_t *juego)
{

	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos; i++)
	{

		do
		{

			(*juego).personaje.posicion = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);
			formula_sombra((&(*juego).personaje), (&(*juego).sombra));
		}

		while ((buscar_elemento((*juego).niveles[(*juego).nivel_actual - 1].obstaculos,
					(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos, (*juego).personaje.posicion) != -1) ||
		       (buscar_elemento((*juego).niveles[(*juego).nivel_actual - 1].obstaculos,
					(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos, (*juego).sombra.posicion) != -1) ||

		       (buscar_elemento((*juego).niveles[(*juego).nivel_actual - 1].herramientas,
					(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas, (*juego).personaje.posicion) != -1) ||
		       (buscar_elemento((*juego).niveles[(*juego).nivel_actual - 1].herramientas,
					(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas, (*juego).sombra.posicion) != -1) ||

		       elemento_sobre_pared((*juego).personaje.posicion, (*juego).niveles[(*juego).nivel_actual - 1].paredes,
					    (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes) ||
		       elemento_sobre_pared((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].paredes,
					    (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes) ||

		       sombra_rango_vela((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].coordenada));
	}
}

// Procedimiento que llama a otros
// procedimientos para que ubiquen
// los elementos y los personajes.
void asignar_coordenadas(juego_t *juego)
{

	asignar_coordenadas_obstaculos(juego);
	asignar_coordenadas_herramientas(juego);
	asignar_coordenadas_escaleras(juego);
	asignar_coordenadas_personajes(juego);
}

// Procedimiento que inicializa los niveles.
void inicilaizar_niveles(juego_t *juego, config_t config[MAX_NIVELES])
{

	asignar_numero_niveles(juego);
	inicializar_niveles_tipo((*juego).niveles, config);
	asignar_coordenadas(juego);
}

// Procedimiento que declara el primer nivel e inicializa el juego.
void inicializar_juego(juego_t *juego, config_t config[MAX_NIVELES])
{

	(*juego).nivel_actual = 1;

	cargar_mapas();
	inicilaizar_niveles(juego, config);
	inicializar_personaje(&((*juego).personaje), config);
	inicializar_sombra(&((*juego).sombra));
}

// Procedimiento que imprime la pantalla
// de victoria al ganar la partida.
void imprimir_victoria(int puntos)
{

	system("clear");

	printf("\
# # # # # # # # # # # # # # # # # # # # # # # # #\n\
#     #     #     #     #     #     #     #     #\n\
         #           #           #           #   \n\
   #           #           #           #         \n\
       #           #           #           #     \n\
                                                 \n\
                                                 \n\
                                                 \n\
                                                 \n\
                  %s GANASTE %s                  \n\
                    PUNTOS %i                    \n\
                                                 \n\
                                                 \n\
                                                 \n\
                                                 \n\
       #           #           #           #     \n\
   #           #           #           #         \n\
         #           #           #           #   \n\
#     #     #     #     #     #     #     #     #\n\
# # # # # # # # # # # # # # # # # # # # # # # # #\n",
	       MAC_EMOJI, BLOO_EMOJI, puntos);
}

// Procedimiento que imprime la pantalla
// de derrota al perder la partida.
void imprimir_derrota(int puntos)
{

	system("clear");

	printf("\
# # # # # # # # # # # # # # # # # # # # # # # # #\n\
#     #     #     #     #     #     #     #     #\n\
         #           #           #           #   \n\
   #           #           #           #         \n\
       #           #           #           #     \n\
                                                 \n\
                                                 \n\
                                                 \n\
                                                 \n\
                 %s PERDISTE %s                  \n\
                   PUNTOS  %i                    \n\
                                                 \n\
                                                 \n\
                                                 \n\
                                                 \n\
       #           #           #           #     \n\
   #           #           #           #         \n\
         #           #           #           #   \n\
#     #     #     #     #     #     #     #     #\n\
# # # # # # # # # # # # # # # # # # # # # # # # #\n",
	       CALAVERA_EMOJI, CALAVERA_EMOJI, puntos);
}

// Funcion que verifica que el
// jugador sigue o no en partida.
int estado_juego(juego_t juego)
{

	int estado_juego = 0;

	if (juego.personaje.vida < 1)
	{

		estado_juego = -1;

		imprimir_derrota(juego.personaje.puntos);
	}

	else if (juego.nivel_actual == 3 && juego.sombra.esta_viva)
	{

		estado_juego = 1;
	}

	return estado_juego;
}

// Funcion que verifica que el
// jugador termino o no el nivel actual.
int estado_nivel(juego_t juego)
{

	int estado_nivel = 0;

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas; i++)
	{

		if (juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo == PUERTA)
		{

			if (distancia_manhattan(juego.personaje.posicion, juego.niveles[juego.nivel_actual - 1].herramientas[i].coordenada) <= 1 &&
			    distancia_manhattan(juego.sombra.posicion, juego.niveles[juego.nivel_actual - 1].herramientas[i].coordenada) <= 1 &&
			    juego.sombra.esta_viva)
			{

				if (juego.nivel_actual == 1)
					estado_nivel = 1;

				if (juego.nivel_actual > 1 && juego.personaje.tiene_llave)
					estado_nivel = 1;
			}
		}
	}

	return estado_nivel;
}

// Procedimiento que elimina un obstaculo del
// vector de obstaculos de manera ordenada.
void eliminar_obstaculo(juego_t *juego, int pos)
{

	for (int i = pos; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos - 1; i++)
	{

		(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i] = (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i + 1];
	}

	(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos--;
}

// Procedimiento que elimina una herramienta del
// vector de herramientas de manera ordenada.
void eliminar_herramienta(juego_t *juego, int pos)
{

	for (int i = pos; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas - 1; i++)
	{

		(*juego).niveles[(*juego).nivel_actual - 1].herramientas[i] = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i + 1];
	}

	(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas--;
}

// Funcion que devuelve un
// numero aleatorio para darle
// un valor a las monedas recolectadas.
int valor_monedas_random()
{

	return rand() % 11 + 10;
}

// Funcion que analiza los alrededores del personaje en busca de paredes.
bool destino_pared_mac(juego_t juego, coordenada_t pos_personaje, char movimiento)
{

	bool hay_pared = false;

	if (movimiento == ARRIBA)
		pos_personaje.fila--;
	if (movimiento == IZQUIERDA)
		pos_personaje.col--;
	if (movimiento == ABAJO)
		pos_personaje.fila++;
	if (movimiento == DERECHA)
		pos_personaje.col++;

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++)
	{

		if (coordenadas_iguales(pos_personaje, juego.niveles[juego.nivel_actual - 1].paredes[i]))
		{

			hay_pared = true;
		}
	}

	return hay_pared;
}

// Funcion que analiza los alrededores de la sombra en busca de paredes.
bool destino_pared_bloo(juego_t juego, coordenada_t pos_sombra, char movimiento)
{

	bool hay_pared = false;

	if (movimiento == ARRIBA)
		pos_sombra.fila--;
	if (movimiento == ABAJO)
		pos_sombra.fila++;

	if (!juego.personaje.interruptor_apretado)
	{

		if (movimiento == IZQUIERDA)
			pos_sombra.col++;
		if (movimiento == DERECHA)
			pos_sombra.col--;
	}

	if (juego.personaje.interruptor_apretado)
	{

		if (movimiento == IZQUIERDA)
			pos_sombra.col--;
		if (movimiento == DERECHA)
			pos_sombra.col++;
	}

	for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++)
	{

		if (coordenadas_iguales(pos_sombra, juego.niveles[juego.nivel_actual - 1].paredes[i]))
		{

			hay_pared = true;
		}
	}

	return hay_pared;
}

// Funcion que calcula si la proxima posicion
// del personaje esta fuera de la matriz.
bool posicion_futura_fuera_de_rango(coordenada_t pos_personaje, char movimiento)
{

	bool posicion_futura_fuera_de_rango = false;

	if (movimiento == ARRIBA)
		pos_personaje.fila--;
	if (movimiento == IZQUIERDA)
		pos_personaje.col--;
	if (movimiento == ABAJO)
		pos_personaje.fila++;
	if (movimiento == DERECHA)
		pos_personaje.col++;

	if (!esta_dentro_rango(pos_personaje, MAX_FILAS, MAX_COLUMNAS))
	{

		posicion_futura_fuera_de_rango = true;
	}

	return posicion_futura_fuera_de_rango;
}

// Procedimiento que realiza las jugadas
// relacionadas con los obstaculos.
void jugada_obstaculos(juego_t *juego)
{

	// PERSONAJE

	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos; i++)
	{

		if (coordenadas_iguales((*juego).personaje.posicion, (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].coordenada))
		{

			// POZOS

			if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == POZOS)
			{

				(*juego).personaje.vida--;
				asignar_coordenadas_personajes(juego);
			}

			// INTERRUPTORES

			else if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == INTERRUPTORES)
			{

				if ((*juego).personaje.interruptor_apretado == false)
					(*juego).personaje.interruptor_apretado = true;

				else if ((*juego).personaje.interruptor_apretado == true)
					(*juego).personaje.interruptor_apretado = false;
			}

			// VELAS

			else if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == VELAS)
				eliminar_obstaculo(juego, i);
		}

		// SOMBRA

		if (coordenadas_iguales((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].coordenada))
		{

			// PORTALES

			if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == PORTALES)
			{

				coordenada_t aux;

				aux = (*juego).personaje.posicion;
				(*juego).personaje.posicion = (*juego).sombra.posicion;
				(*juego).sombra.posicion = aux;
			}
		}

		// VELAS

		if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == VELAS)
		{

			if (sombra_rango_vela((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].coordenada))
			{

				(*juego).sombra.esta_viva = false;
			}
		}
	}
}

// Procedimiento que realiza las jugadas
// relacionadas con las herramientas.
void jugada_herramientas(juego_t *juego)
{

	// PERSONAJE

	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas; i++)
	{

		if (coordenadas_iguales((*juego).personaje.posicion, (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].coordenada))
		{

			// MONEDAS

			if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == MONEDAS)
			{

				(*juego).personaje.puntos += valor_monedas_random();

				eliminar_herramienta(juego, i);
			}

			// LLAVE

			else if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == LLAVE)
			{

				(*juego).personaje.tiene_llave = true;

				eliminar_herramienta(juego, i);
			}
		}

		// SOMBRA

		if (coordenadas_iguales((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].coordenada))
		{

			// MONEDAS

			if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == MONEDAS)
			{

				(*juego).personaje.puntos += valor_monedas_random();

				eliminar_herramienta(juego, i);
			}
		}
	}
}

// Procedimiento que recibe un movimiento y mueve unicamente a Mac.
void mover_mac(personaje_t *personaje, char movimiento)
{

	if (esta_dentro_rango((*personaje).posicion, MAX_FILAS, MAX_COLUMNAS))
	{

		if (movimiento == ARRIBA && (*personaje).posicion.fila != 0)
			(*personaje).posicion.fila--;
		if (movimiento == IZQUIERDA && (*personaje).posicion.col != 0)
			(*personaje).posicion.col--;
		if (movimiento == ABAJO && (*personaje).posicion.fila != (MAX_FILAS - 1))
			(*personaje).posicion.fila++;
		if (movimiento == DERECHA && (*personaje).posicion.col != (MAX_COLUMNAS - 1))
			(*personaje).posicion.col++;
	}
}

// Procedimiento que recibe un movimiento y mueve unicamente a Bloo.
void mover_sombra(personaje_t personaje, sombra_t *sombra, char movimiento)
{

	if (esta_dentro_rango((*sombra).posicion, MAX_FILAS, MAX_COLUMNAS))
	{

		if ((*sombra).esta_viva)
		{

			if ((movimiento == ARRIBA) && (*sombra).posicion.fila != 0)
				(*sombra).posicion.fila--;
			if ((movimiento == ABAJO) && (*sombra).posicion.fila != (MAX_FILAS - 1))
				(*sombra).posicion.fila++;

			if (!(personaje).interruptor_apretado)
			{

				if ((movimiento == IZQUIERDA) && (*sombra).posicion.col != (MAX_COLUMNAS - 1))
					(*sombra).posicion.col++;
				if ((movimiento == DERECHA) && (*sombra).posicion.col != 0)
					(*sombra).posicion.col--;
			}

			if ((personaje).interruptor_apretado)
			{

				if ((movimiento == IZQUIERDA) && (*sombra).posicion.col != 0)
					(*sombra).posicion.col--;
				if ((movimiento == DERECHA) && (*sombra).posicion.col != (MAX_COLUMNAS - 1))
					(*sombra).posicion.col++;
			}
		}
	}
}

// Procedimiento que realiza las jugadas relacionadas con las paredes.
void jugada_paredes(juego_t *juego, personaje_t *personaje, sombra_t *sombra, personaje_t *aux, char movimiento)
{

	if (!destino_pared_mac(*juego, (*personaje).posicion, movimiento) &&
	    !destino_pared_bloo(*juego, (*sombra).posicion, movimiento))
	{

		mover_mac(personaje, movimiento);
		mover_sombra(*personaje, sombra, movimiento);
	}

	else if (destino_pared_mac(*juego, (*personaje).posicion, movimiento) &&
		 !destino_pared_bloo(*juego, (*sombra).posicion, movimiento))
	{

		mover_sombra(*personaje, sombra, movimiento);
	}

	else if (!destino_pared_mac(*juego, (*personaje).posicion, movimiento) &&
		 destino_pared_bloo(*juego, (*sombra).posicion, movimiento))
	{

		mover_mac(personaje, movimiento);
	}

	mover_mac(aux, movimiento);
}

// Procedimiento que realiza las jugadas relacionadas con las escaleras.
// Se fija que el personaje no quede adentro de una pared ni fuera de la matriz.
void jugada_escaleras(juego_t *juego, personaje_t *aux, char movimiento)
{

	coordenada_t coordenadas_escaleras_usadas[MAX_ELEMENTOS];
	int tope_escaleras = 0;
	int indice_j = 0;
	int posicion_buscada;

	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas; i++)
	{

		if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == ESCALERAS)
		{

			while (coordenadas_iguales((*aux).posicion, (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].coordenada) &&
			       !posicion_futura_fuera_de_rango((*aux).posicion, movimiento))
			{

				mover_mac(aux, movimiento);

				tope_escaleras++;

				for (int j = indice_j; j < tope_escaleras; j++)
				{

					coordenadas_escaleras_usadas[j] = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].coordenada;
				}

				indice_j++;

				if (!elemento_sobre_pared((*aux).posicion, (*juego).niveles[(*juego).nivel_actual - 1].paredes, (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes))
				{

					(*juego).personaje.posicion = (*aux).posicion;

					for (int j = 0; j < tope_escaleras; j++)
					{

						posicion_buscada = buscar_elemento((*juego).niveles[(*juego).nivel_actual - 1].herramientas,
										   (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas, coordenadas_escaleras_usadas[j]);

						eliminar_herramienta(juego, posicion_buscada);
					}
				}

				i = -1;
			}
		}
	}
}

// Procedimiento que le agrega una vida al personaje y le resta su coste
// en puntos solo si el personaje tiene menos de su vida inicial.
void agregar_vida(personaje_t *personaje, char movimiento)
{

	if ((movimiento == VIDA_EXTRA) && ((*personaje).vida < VIDA_INICIAL) && ((*personaje).puntos > COSTE_VIDA_EXTRA))
	{

		(*personaje).vida++;
		(*personaje).puntos -= COSTE_VIDA_EXTRA;
	}
}

// Le sume un parametro juego_t* juego.
// Ahora puede comparar las posiciones de los personajes con la de otros elementos.
void mover_personaje(juego_t *juego, personaje_t *personaje, sombra_t *sombra, char movimiento)
{

	personaje_t aux;
	aux.posicion = (*juego).personaje.posicion;

	jugada_paredes(juego, personaje, sombra, &aux, movimiento);
	jugada_escaleras(juego, &aux, movimiento);

	agregar_vida(personaje, movimiento);
}

// Procedimiento que revive a Bloo.
void revivir_sombra(juego_t *juego)
{

	if (((*juego).sombra.esta_viva == false) && (coordenadas_iguales((*juego).personaje.posicion, (*juego).sombra.posicion)))
	{

		(*juego).sombra.esta_viva = true;
		(*juego).personaje.puntos -= COSTE_REVIVIR_SOMBRA;
	}

	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos; i++)
	{

		if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == VELAS)
		{

			if (sombra_rango_vela((*juego).sombra.posicion, (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].coordenada))
			{

				(*juego).sombra.esta_viva = false;
			}
		}
	}
}

// Procedimiento que le da instrucciones
// al programa una vez que estado_nivel()
// devuelve 1.
void terminar_nivel(juego_t *juego)
{

	if (estado_nivel(*juego) == 1)
	{

		if ((*juego).nivel_actual < 3)
		{

			(*juego).nivel_actual++;
			(*juego).personaje.interruptor_apretado = false;
			(*juego).personaje.tiene_llave = false;

			asignar_coordenadas_personajes(juego);
		}

		else if ((*juego).nivel_actual == 3)
		{

			imprimir_victoria((*juego).personaje.puntos);
		}
	}
}

// Procedimiento que determina que le
// sucedera al jugador en cada turno.
void realizar_jugada(juego_t *juego)
{

	char movimiento;

	pedir_movimiento(*juego, &movimiento);
	mover_personaje(juego, &((*juego).personaje), (&(*juego).sombra), movimiento);

	jugada_obstaculos(juego);
	jugada_herramientas(juego);

	revivir_sombra(juego);

	terminar_nivel(juego);
}