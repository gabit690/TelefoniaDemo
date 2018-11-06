#ifndef CELULAR_H_
#define CELULAR_H_

#include "Lista.h"
#include "Llamada.h"
#include "ActividadDelCelular.h"
#include "Antena.h"
#include "Mensaje.h"


/* Representa cada dispositivo Celular
 * existente en la red de Telefonia.
 */
class Celular{

private:
	unsigned int codigo;
	unsigned int numero;
	Antena* antenaActual;
	std::string ultimaAntenaConectada;
	Celular* celularVinculado;
	Lista<Llamada*>* llamadasRealizadas;
	Lista<Llamada*>* llamadasRecibidas;
	ActividadDelCelular* actividadTotal;
    Lista<Mensaje>*	mensajesEnviados;
    Lista<Mensaje>*	mensajesRecibidos;
    Lista<Mensaje>*	mensajesParaProcesar;
	
public:
	/* PRE: codigoDeCelular > 0 y numeroDeCelular > 0.
	 * POST: Genera un objeto Celular de la siguiente manera:
	 *
	 * 	codigo = codigoDeCelular;
	 * 	numero = numeroDeCelular;
	 * 	antenaActual = NULL;
	 * 	ultimaAntenaConectada = "";
	 * 	CelularVinculado = NULL;
	 * 	Y pide memoria para el resto de los atributos.
	 *
	 */
	Celular(unsigned int codigoDeCelular, unsigned int numeroDeCelular);

	/* PRE: antenaAconectar debe ser un puntero a una antena existente o NULL.
	 * POST: vincula al objeto celular con la antena apuntada por antenaAconectar.
	 */
	void asignarAntenaConectada(Antena* antenaAconectar);

	/* PRE: nombreDeAntena correspondiente al nombre de una Antena existente dentro del sistema.
	 * POST: asigna al objeto Celular el nombre de la ultima antena a la cual se conecto.
	 */
	void asignarUltimaAntena(std::string nombreDeAntena);

	/* PRE: celularAvincular debe ser un puntero a otro celular conectado a una Antena o NULL.
	 * POST: vincula al objeto celular con el celular apuntado por celularAvincular.
	 */
	void asignarCelularVinculado(Celular* celularAvincular);

	/* PRE: -.
	 * POST: obtiene el codigo de identificacion del objeto Celular.
	 */
	unsigned int obtenerCodigo();

	/* PRE: -.
	 * POST: obtiene el numero de comunicacion del objeto Celular.
	 */
	unsigned int obtenerNumero();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la antena en la cual esta conectado el objeto Celular.
	 */
	Antena* obtenerAntenaActual();

	/* PRE: -.
	 * POST: obtiene el nombre de la ultima antena a la cual se conecto el objeto Celular.
	 */
	std::string obtenerUltimaAntena();

	/* PRE: -.
	 * POST: obtiene un puntero hacia el Celular con el cual esta vinculado el objeto Celular en una llamada.
	 */
	Celular* obtenerCelularVinculado();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de llamadas que realizo el objeto Celular.
	 */
	Lista<Llamada*>* obtenerListaDeLlamadasRealizadas();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de llamadas que recibio el objeto Celular.
	 */
	Lista<Llamada*>* obtenerListaDeLlamadasRecibidas();

	/* PRE: -.
	 * POST: obtiene un puntero hacia el registro que va guardando las duraciones y cantidades totales correspondientes a
	 * las diferentes comunicaciones en la que el objeto Celular estuvo involucrado.
	 */
	ActividadDelCelular* obtenerActividad();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de mensajes enviados por el objeto Celular.
	 */
	Lista<Mensaje>* obtenerListaDeMensajesEnviados();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de mensajes recibidos por el objeto Celular.
	 */
	Lista<Mensaje>* obtenerListaDeMensajesRecibidos();

	/* PRE: -.
	 * POST: obtiene un puntero hacia la lista de mensajes que aun no fueron procesados.
	 */
	Lista<Mensaje>* obtenerListaDeMensajesParaProcesar();

	/* PRE: -.
	 * POST: Libera la memoria pedida por los distintos punteros.
	 */
	~Celular();

};

#endif /* CELULAR_H_ */
