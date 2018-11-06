/*
 * Comunicacion.h
 *
 *  Created on: 23 de may. de 2016
 *      Author: lnx
 */

#ifndef COMUNICACION_H_
#define COMUNICACION_H_

#include <string>

/* Contiene informacion detallada que identifica una llamada realizada
 * satisfactoriamente.
 */
class Comunicacion{

private:
	unsigned int celularEmisor;
	std::string antenaDelEmisor;
	unsigned int celularReceptor;
	std::string antenaDelReceptor;
	unsigned int inicioDeLlamada;
	unsigned int finDeLlamada;

public:

	/*PRE: -.
	 *POST: Genera un registro de una comunicacion con sus datos inicializados.
	 */
	Comunicacion();

	/*PRE: numeroEmisor > 0.
	*POST: ingresa el numero del Celular que realizo la llamada.
	*/
	void ingresarNumeroEmisor(unsigned int numeroEmisor);

	/*PRE: -.
	*POST: ingresa el nombre que identifica a la antena donde esta conectado el Celular emisor.
	*/
	void ingresarNombreAntenaEmisor(std::string nombreAntenaDelEmisor);

	/*PRE: numeroReceptor > 0.
	*POST: ingresa el numero del Celular que recibio la llamada.
	*/
	void ingresarNumeroReceptor(unsigned int numeroReceptor);

	/*PRE: -.
	*POST: ingresa el nombre que identifica a la antena donde esta conectado el Celular receptor.
	*/
	void ingresarNombreAntenaReceptor(std::string nombreAntenaDelReceptor);

	/*PRE: tiempoDeInicio >= 0.
	*POST: ingresa el tiempo en el cual se efectuo el inicio de la llamada.
	*/
	void ingresarInicioDeLlamada(unsigned int tiempoDeInicio);

	/*PRE: tiempoDeFinalizacion >= 0.
	*POST: ingresa el tiempo en el cual se finalizo la llamada.
	*/
	void ingresarFinDeLlamada(unsigned int tiempoDeFinalizacion);

	/*PRE: -.
	*POST: obtiene el numero del Celular que emitio la llamada.
	*/
	unsigned int obtenerNumeroEmisor();

	/*PRE: -.
	*POST: obtiene el nombre de la antena del emisor de la llamada.
	*/
	std::string obtenerNombreAntenaEmisor();

	/*PRE: -.
	*POST: obtiene el numero del Celular que recibio la llamada.
	*/
	unsigned int obtenerNumeroReceptor();

	/*PRE: -.
	*POST: obtiene el nombre de la antena del receptor de la llamada.
	*/
	std::string obtenerNombreAntenaReceptor();

	/*PRE: -.
	*POST: obtiene el tiempo de inicio de la llamada registrada.
	*/
	unsigned int obtenerInicioDeLlamada();

	/*PRE: -.
	*POST: obtiene el tiempo de finalizacion de la llamada registrada.
	*/
	unsigned int obtenerFinDeLlamada();
};

#endif /* COMUNICACION_H_ */
