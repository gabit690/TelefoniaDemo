/*
 * RegistroLlamada.h
 *
 *  Created on: 23 de may. de 2016
 *      Author: lnx
 */

#ifndef REGISTROLLAMADA_H_
#define REGISTROLLAMADA_H_

#include "Lista.h"
#include <string>

/* Contiene informacion detallada que identifica una operacion
 * realizada o recibida asociada al celular.
 */
class RegistroLlamada{
private:
	unsigned int celularInvolucrado;
	Lista<std::string*>* antenasInvolucradas;
	unsigned int inicioDeLlamada;
	unsigned int finDeLlamada;

public:
	/* PRE: -.
	 * POST: Genera un registro de llamada con sus datos inicializados pidiendo los recursos necesarios.
	 */
	RegistroLlamada();

	/* PRE: numeroDeCelular distinto de un numero negativo y 0;
	 * POST: asigna el numero corresponiente a numeroDeCelular para identificar al otro Celular que interviene en la operacion.
	 */
	void asignarCelularInvolucrado(unsigned int numeroDeCelular);

	/* PRE: tiempoDeInicio mayor o igual a 0.
	 * POST: asigna el numero corresponiente al inicio de la operacion.
	 */
	void asignarInicioDeLlamada(unsigned int tiempoDeInicio);

	/* PRE: tiempoDeFinalizacion mayor o igual a 0.
	 * POST: asigna el numero corresponiente a la finalizacion de la operacion.
	 */
	void asignarFinDeLlamada(unsigned int tiempoDeFinalizacion);

	/* PRE: -.
	 * POST: obtiene el numero de celular que intervine en la operacion registrada.
	 */
	unsigned int obtenerCelularInvolucrado();

	/* PRE: -.
	 * POST: obtiene un puntero a la lista que contiene los nombres de las antenas involucradas en la operacion registrada.
	 */
	Lista<std::string*>* obtenerListadoDeAntenas();

	/* PRE: -.
	 * POST: obtiene el tiempo en el cual inicio la operacion registrada.
	 */
	unsigned int obtenerTiempoDeInicio();

	/* PRE: -.
	 * POST: obtiene el tiempo en el cual finalizo la operacion registrada.
	 */
	unsigned int obtenerTiempoDeFinalizacion();

	/* PRE: -.
	 * POST: Libera los recursos asociados al registro de llamada.
	 */
	~RegistroLlamada();
};

#endif /* REGISTROLLAMADA_H_ */
