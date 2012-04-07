/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Ejercicio3.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

static void Llegada_Nuevo_Cliente();
static void Agregar_Pan_Inferior();
static void Agregar_Condimento();
static void Agregar_Carne();
static void Agregar_Queso();
static void Agregar_Panceta();
static void Agregar_Lechuga();
static void Agregar_Tomate();
static void Agregar_Pan_Superior();
static void Entregar();
static void Agregar(t_Ingredientes ingrediente);

static char* Ingrediente_ToString(t_Ingredientes ingrediente);
static bool Esta_Bien_Armada();

t_hamburguesa hamburgesa;
pthread_mutex_t mutex;

int main(void) {
	pthread_t h0, h1, h2, h3, h4, h5, h6, h7, h8;
	hamburgesa.embalada = false;
	hamburgesa.ingredientes = queue_create();

	pthread_create(&h0, NULL, (void*) Llegada_Nuevo_Cliente, NULL);
	pthread_create(&h1, NULL, (void*) Agregar_Pan_Inferior, NULL);
	pthread_create(&h2, NULL, (void*) Agregar_Condimento, NULL);
	pthread_create(&h3, NULL, (void*) Agregar_Carne, NULL);
	pthread_create(&h4, NULL, (void*) Agregar_Queso, NULL);
	pthread_create(&h5, NULL, (void*) Agregar_Panceta, NULL);
	pthread_create(&h6, NULL, (void*) Agregar_Lechuga, NULL);
	pthread_create(&h7, NULL, (void*) Agregar_Tomate, NULL);
	pthread_create(&h7, NULL, (void*) Agregar_Pan_Superior, NULL);
	pthread_create(&h8, NULL, (void*) Entregar, NULL);

	pthread_join(h1, (void**) NULL);
	pthread_join(h2, (void**) NULL);
	pthread_join(h3, (void**) NULL);
	pthread_join(h4, (void**) NULL);
	pthread_join(h5, (void**) NULL);
	pthread_join(h6, (void**) NULL);
	pthread_join(h7, (void**) NULL);
	pthread_join(h8, (void**) NULL);

	return EXIT_SUCCESS;
}

static void Llegada_Nuevo_Cliente() {
	while (1) {
		printf("Esperando nuevo cliente...\n");
		sleep(3);
		printf("Lllego un nuevo cliente...\n");
	}
}

static void Agregar_Pan_Inferior() {
	while (1) {
		Agregar(PANINFERIOR);
	}
}

static void Agregar_Condimento() {
	while (1) {
		Agregar(CONDIMENTOS);
	}
}

static void Agregar_Carne() {
	while (1) {
		Agregar(CARNE);
	}
}

static void Agregar_Queso() {
	while (1) {
		Agregar(QUESO);
	}
}

static void Agregar_Panceta() {
	while (1) {
		Agregar(PANCETA);
	}
}

static void Agregar_Lechuga() {
	while (1) {
		Agregar(LECHUGA);
	}
}

static void Agregar_Tomate() {
	while (1) {
		Agregar(TOMATE);
	}
}

static void Agregar_Pan_Superior() {
	while (1) {
		Agregar(PANSUPERIOR);
	}
}

static void Entregar() {
	while (1) {
		if (!Esta_Bien_Armada()) {
			printf("Error en el armado de la hamburguesa!!\n");
			printf("El cliente se fue a comerse un triple bacon a mc :(\n");
		} else {
			printf("Hamburguesa armada perfectamente!!\n");
			printf("Le hemos tapado 5 arterias al cliente!! :)\n");
		}
	}
}

static void Agregar(t_Ingredientes ingrediente) {
	pthread_mutex_lock(&mutex);
	printf("Agregando ingrediente %s\n", Ingrediente_ToString(ingrediente));
	int *i = malloc(sizeof(int));
	*i = ingrediente;
	queue_push(hamburgesa.ingredientes, i);
	pthread_mutex_unlock(&mutex);
}

static bool Esta_Bien_Armada() {
	/*Esta correctamente armada si tiene todos los ingredientes,
	 *  y los tiene definidos en el orden dado por el enum t_Ingredientes*/

	for (int i = 0; (((t_Ingredientes) i) <= PANSUPERIOR); i++) {
		t_Ingredientes ingredienteCorrecto = (t_Ingredientes) i;
		t_Ingredientes ingredienteHamburguesa;

		pthread_mutex_lock(&mutex);
		int* ingrediente = queue_pop(hamburgesa.ingredientes);
		pthread_mutex_unlock(&mutex);

		if (ingrediente == NULL) {
			printf("Faltaron ingredientes!\n");
			return false;
		}

		ingredienteHamburguesa = (t_Ingredientes) *ingrediente;
		if (ingredienteHamburguesa != ingredienteCorrecto) {
			printf("Ingrediente incorrecto debia ser %s y era %s\n",
					Ingrediente_ToString(ingredienteCorrecto), Ingrediente_ToString(ingredienteHamburguesa));

			free(ingrediente);
			return false;
		}
	}

	return true;
}

static char* Ingrediente_ToString(t_Ingredientes ingrediente) {
	char* ingredienteChar;
	switch (ingrediente) {
	case PANINFERIOR:
		ingredienteChar = "PANINFERIOR";
		break;
	case PANSUPERIOR:
		ingredienteChar = "PANSUPERIOR";
		break;
	case CARNE:
		ingredienteChar = "CARNE";
		break;
	case QUESO:
		ingredienteChar = "QUESO";
		break;
	case PANCETA:
		ingredienteChar = "PANCETA";
		break;
	case LECHUGA:
		ingredienteChar = "LECHUGA";
		break;
	case TOMATE:
		ingredienteChar = "TOMATE";
		break;
	case CONDIMENTOS:
		ingredienteChar = "CONDIMENTOS";
		break;
	default:
		ingredienteChar = "Esto no debería ir en la hamburguesa!";
		break;

	}

	return ingredienteChar;

}
