/*
 * Antena.h
 *
 *  Created on: 19 de may. de 2016
 *      Author: lnx
 */

#ifndef ANTENA_H_
#define ANTENA_H_

#include "Lista.h"
#include "Comunicacion.h"
#include "RegistroActividadCelular.h"


/* Representa una antena que permite a objetos Celulares
 * realizar operaciones dentro de un sistema de Telefonia.
 */
class Antena{
private:
	std::string nombre;
	unsigned int comunicacionesSoportadas;
	unsigned int comunicacionesDisponibles;
	Lista<Comunicacion*>* comunicacionesConcurrentes;
	unsigned int cantidadMaximaDeComunicacionesEstablecidas;
	unsigned int cantidadDeLlamadasAnuladas;
	Lista<Comunicacion*>* llamadasEnEspera;
	Lista<RegistroActividadCelular*>* actividadRegistrada;

public:
	/* PRE: -.
	 * POST: Genera un objeto Antena con sus datos inicializados pidiendo los recursos necesarios
	 */
	Antena();

	/* PRE: -.
	 * POST: asigna al objeto Antena una denominacion para ser identificada.
	 */
	void asignarNombre(std::string nombreDeAntena);

	/* PRE: operacionesSoportadas > 0.
	 * POST: asigna la cantidad de operaciones simultaneas que permite establecer el objeto Antena.
	 */
	void asignarCantidadDeOperacionesSoportadas(unsigned int operacionesSoportadas);

	/* PRE: cantidadDeDisponibles tiene que ser igual a la cantidad de operaciones soportadas.
	 * POST: asigna la cantidad de operaciones disponibles que puede establecer el objeto Antena.
	 */
	void asignarComunicacionesDisponibles(unsigned int cantidadDeDisponibles);

	/* PRE:  la cantidad de comunicaciones disponibles no puede ser superior a la cantidad de operaciones soportadas.
	 * POST: aumenta la cantidad de operaciones disponibles que puede establecer el objeto Antena.
	 */
	void aumentarComunicacionesDisponibles();

	/* PRE: la cantidad de comunicaciones disponibles tiene que ser > 0.
	 * POST: disminuye la cantidad de operaciones disponibles que puede establecer el objeto Antena.
	 */
	void disminuirComunicacionesDisponibles();

	/* PRE: -.
	 * POST: incrementa en 1 la cantidad de comunicaciones establecidas relacionadas a la antena.
	 */
	void aumentarTotalDeComunicacionesEstablecidas();

	/* PRE: -.
	 * POST: incrementa en 1 la cantidad de comunicaciones anuladas relacionadas a la antena.
	 */
	void aumentarCantidadDeLlamadasAnuladas();

	/* PRE: -.
	 * POST: obtiene el nombre que identifica a la Antena dentro del sistema.
	 */
	std::string obtenerNombreDeAntena();

	/* PRE: -.
	 * POST: obtiene la cantidad de comunicaciones soportadas por la Antena.
	 */
	unsigned int obtenerComunicacionesSoportadas();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de Comunicaciones que estan en marcha en la Antena.
	 */
	Lista<Comunicacion*>* obtenerListaDeOperacionesConcurrentes();

	/* PRE: -.
	 * POST: obtiene la cantidad de operaciones disponibles que tiene la Antena.
	 */
	unsigned int obtenerOperacionesDisponibles();

	/* PRE: -.
	 * POST: obtiene la cantidad de comunicaciones que se llevaron a cabo mediante la Antena.
	 */
	unsigned int obtenerCantidadDeComunicacionesEstablecidas();

	/* PRE: -.
	 * POST: obtiene la cantidad de comunicaciones que fueron anuladas por la Antena.
	 */
	unsigned int obtenerCantidadDeComunicacionesAnuladas();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de comunicaciones que se encuentran en Espera en la Antena.
	 */
	Lista<Comunicacion*>* obtenerListaDeLlamadasEnEspera();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de actividades totales que realizaron los celulares conectados en algun momento en la Antena.
	 */
	Lista<RegistroActividadCelular*>* obtenerListaDeActividadRegistrada();

	/* PRE: -.
	 * POST: Libera los recursos asociados al objeto Antena.
	 */
	~Antena();
};

#endif /* ANTENA_H_ */
