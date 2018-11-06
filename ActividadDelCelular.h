#ifndef ACTIVIDADDELCELULAR_H_
#define ACTIVIDADDELCELULAR_H_

#include <string>

/* Registro que se encarga de almacenar los datos totales correspondientes
 * a las llamadas que el Celular fue realizando o recibiendo en una Antena determinada.
 */
class ActividadDelCelular{

private:

	unsigned int numeroDeCelular;
	unsigned int cantidadDeLlamadasRealizadas;
	unsigned int duracionTotalDeLlamadasRealizadas;
	unsigned int llamadasRealizadasOcupadas;
	unsigned int cantidadDeLlamadasRecibidas;
	unsigned int duracionTotalDeLlamadasRecibidas;
	unsigned int llamadasRecibidasOcupadas;

public:

	/* PRE: numeroDeCelular > 0.
	* POST: Genera un registro de actividad total correspondiente al Celular numeroDeCelular
	* con los datos inicializados en 0.
	*/
	ActividadDelCelular(unsigned int numeroDeCelular);

	/* PRE:-.
	* POST: aumenta en 1 la cantidad de llamadas realizadas por el celular.
	*/
	void aumentarCantidadDeRealizadas();

	/* PRE: duracionDeLlamadaRealizada > 0.
	* POST: aumenta la duracion total del tiempo invertido en las llamadas realizadas.
	*/
	void aumentarTiempoDeRealizadas(unsigned int duracionDeLlamadaRealizada);

	/* PRE: -.
	* POST: aumenta en 1 la cantidad de llamadas realizadas por el celular que dieron ocupado.
	*/
	void aumentarCantidadDeRealizadasOcupadas();

	/* PRE: -.
	* POST: aumenta en 1 la cantidad de llamadas recibidas por el celular.
	*/
	void aumentarCantidadDeRecibidas();

	/* PRE: duracionDeLlamadaRecibida > 0.
	* POST: aumenta la duracion total del tiempo invertido en las llamadas recibidas.
	*/
	void aumentarTiempoDeRecibidas(unsigned int duracionDeLlamadaRecibida);

	/* PRE: -.
	* POST: aumenta en 1 la cantidad de llamadas recibidas por el celular que dieron ocupado.
	*/
	void aumentarCantidadDeRecibidasOcupadas();

	/* PRE: -.
	* POST: obtiene el numero del Celular al cual pertenece el registro.
	*/
	unsigned int obtenerNumeroDeCelular();

	/* PRE: -.
	* POST: obtiene la cantidad de llamadas realizadas por el Celular.
	*/
	unsigned int obtenerCantidadDeRealizadas();

	/* PRE: -.
	* POST: obtiene la duracion total de llamadas realizadas por el Celular.
	*/
	unsigned int obtenerTiempoDeRealizadas();

	/* PRE: -.
	* POST: obtiene la cantidad de llamadas realizadas por el Celular, que dieron ocupado.
	*/
	unsigned int obtenerCantidadDeRealizadasOcupadas();

	/* PRE: -.
	* POST: obtiene la cantidad de llamadas recibidas por el Celular.
	*/
	unsigned int obtenerCantidadDeRecibidas();

	/* PRE: -.
	* POST: obtiene la duracion total de llamadas recibidas por el Celular.
	*/
	unsigned int obtenerTiempoDeRecibidas();

	/* PRE: -.
	* POST: obtiene la cantidad de llamadas recibidas por el Celular que dieron ocupado.
	*/
	unsigned int obtenerCantidadDeRecibidasOcupadas();

};

#endif /* ACTIVIDADDELCELULAR_H_ */
