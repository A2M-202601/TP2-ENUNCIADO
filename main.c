#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X_MAXIMO 20
#define Y_MAXIMO 20

struct jugador {
	unsigned x;
	unsigned y;
};

struct juego {
	struct jugador jugadores[2];
	unsigned iteraciones_restantes;
	int ultimo_numero;
	unsigned int semilla;
};

int logica_del_juego(int tecla, void *ctx)
{
	struct juego *juego = ctx;

	if (tecla == 'q' || tecla == TECLA_ESC)
		return 1;

	if (tecla == 'r')
		juego->ultimo_numero = rand();

	if (tecla == 'w' && juego->jugadores[0].y > 0)
		juego->jugadores[0].y--;
	if (tecla == 's' && juego->jugadores[0].y < Y_MAXIMO - 1)
		juego->jugadores[0].y++;
	if (tecla == 'a' && juego->jugadores[0].x > 0)
		juego->jugadores[0].x--;
	if (tecla == 'd' && juego->jugadores[0].x < X_MAXIMO - 1)
		juego->jugadores[0].x++;

	if (tecla == TECLA_ARRIBA && juego->jugadores[1].y > 0)
		juego->jugadores[1].y--;
	if (tecla == TECLA_ABAJO && juego->jugadores[1].y < Y_MAXIMO - 1)
		juego->jugadores[1].y++;
	if (tecla == TECLA_IZQUIERDA && juego->jugadores[1].x > 0)
		juego->jugadores[1].x--;
	if (tecla == TECLA_DERECHA && juego->jugadores[1].x < X_MAXIMO - 1)
		juego->jugadores[1].x++;

	printf("Jugador 1 (wasd):    " ANSI_COLOR_RED ANSI_COLOR_BOLD
	       "%u/%u" ANSI_COLOR_RESET ANSI_CLEAR_LINE_TO_END "\n",
	       juego->jugadores[0].x, juego->jugadores[0].y);
	printf("Jugador 2 (flechas): " ANSI_COLOR_BLUE ANSI_COLOR_BOLD
	       "%u/%u" ANSI_COLOR_RESET ANSI_CLEAR_LINE_TO_END "\n",
	       juego->jugadores[1].x, juego->jugadores[1].y);
	printf("Semilla: " ANSI_COLOR_GREEN ANSI_COLOR_BOLD
	       "%u" ANSI_COLOR_RESET ANSI_CLEAR_LINE_TO_END "\n",
	       juego->semilla);
	printf("Ultimo numero generado: " ANSI_COLOR_BLUE ANSI_COLOR_BOLD
	       "%i" ANSI_COLOR_RESET ANSI_CLEAR_LINE_TO_END "\n",
	       juego->ultimo_numero % 100);
	printf("Tiempo restante: %us" ANSI_CLEAR_LINE_TO_END "\n",
	       juego->iteraciones_restantes / 5);
	printf("Presione Q/ESC para salir, R para nuevo numero\n\n");

	for (unsigned y = 0; y < Y_MAXIMO; y++) {
		for (unsigned x = 0; x < X_MAXIMO; x++) {
			if (x == juego->jugadores[0].x &&
			    y == juego->jugadores[0].y)
				printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
				       "1" ANSI_COLOR_RESET);
			else if (x == juego->jugadores[1].x &&
				 y == juego->jugadores[1].y)
				printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
				       "2" ANSI_COLOR_RESET);
			else
				printf(".");
		}
		printf(ANSI_CLEAR_LINE_TO_END "\n");
	}

	juego->iteraciones_restantes--;

	return juego->iteraciones_restantes == 0;
}

int main(int argc, char *argv[])
{
	struct jugador j1 = { .x = 0, .y = 10 };
	struct jugador j2 = { .x = 6, .y = 1 };

	struct juego juego;
	juego.jugadores[0] = j1;
	juego.jugadores[1] = j2;
	juego.iteraciones_restantes = 1 * 60 * 5;

	srand((unsigned)time(NULL));
	juego.semilla = (unsigned)rand();

	juego.ultimo_numero = rand();

	game_loop(logica_del_juego, &juego);

	printf("Saliendo....\n");
	return 0;
}
