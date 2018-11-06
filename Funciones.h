/*
 * Funciones.h
 *
 *  Created on: 25 de may. de 2016
 *      Author: lnx
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include "Celular.h"
#include <iostream>
#include <fstream>

	/* PRE: -.
	 * POST: obtiene un nombre de un archivo de texto valido para su posterior procesamiento.
	 */
	std::string ingresarNombreDelArchivo(std::ifstream& archivo);

	/* PRE: archivo abierto y cuyos datos este bien organizados.
	 * POST: procesa la informacion contenida en el archivo para generar las listas de Celulares y Antenas existentes.
	 */
	void procesarArchivo(std::ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: Crea una Antena con los datos obtenidos del archivo y luego la lista en su correspondiente idem.
	 */
	void conectarAntena(std::ifstream& archivo, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: Analiza los datos involucrados en una conexion y realiza las operaciones pertinentes.
	 */
	void tratarConexion(std::ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve un puntero hacia la Antena cuyo nombre es nombreDeAntena o un puntero a NULL si no existe.
	 */
	Antena* buscarAntena(std::string nombreDeAntena, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve un puntero hacia el Celular que tiene el numero numeroCelular o un puntero a NULL si no existe.
	 */
	Celular* buscarCelular(unsigned int numeroCelular, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: Determina si existe dentro de la lista vinculada a los celulares el dispositivo asociado a numeroCelular.
	 */
	bool existeElCelular(unsigned int numeroCelular, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: Analiza si el celular a conectar se encuentra en una llamada en espera y realiza las operaciones pertinentes.
	 */
	void analizarEsperaEnConexion(Celular* celularAtratar, unsigned int tiempoDeOperacion);

	/* PRE: celularAtratar tiene que estar vinculado a otro celular.
	 * POST: Verifica si los celulares involucrados en una operacion estan conectados a la misma Antena.
	 */
	bool mismaAntena(Celular* celularAtratar);

	/* PRE: celularAtratar tiene que estar en una llamada en espera.
	 * POST: Devuelve un puntero al nodo de la lista de llamadas en espera de la Antena
	 * a la que esta conectada el celular vinculado a celularAtratar.
	 */
	Nodo<Comunicacion*>* buscarLlamadaEnEspera(Celular* celularAtratar);

	/* PRE: celularAtratar tiene que estar en una llamada en espera.
	 * POST: analiza la inclusion de la nueva antena involucrada en una comunicacion en espera.
	 */
	void agregadoAntenaQueIntervieneEnComunicacion(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnEspera);

	/* PRE: -.
	 * POST: agrega a los registros de llamada de cada celular involucrado la nueva Antena a la cual
	 * unos de los celulares se acaba de conectar.
	 */
	void buscarRegistroYagregarAntena(Nodo<RegistroLlamada*>* cursorLlamadaEmisor,Nodo<RegistroLlamada*>* cursorLlamadaReceptor, Nodo<Comunicacion*>* comunicacionEnEspera, std::string* antenaAgregar);

	/* PRE: -.
	 * POST: controla si la cantidad de comunicaciones maximas establecidas aumento y en caso afirmativo guarda el nuevo registro.
	 */
	void modificarOperacionesMaximasEnAntena(Antena* antenaAtratar);

	/* PRE: comunicacionEnEspera tiene que ser una comunicacionn que esta en espera.
	 * POST: hace las modificaciones necesarias para que una comunicacion que esta en espera prosiga.
	 */
	void modificarComunicacionEnEsperaQueContinua(Nodo<Comunicacion*>* comunicacionEnEspera, Celular* celularAtratar, unsigned int tiempoDeOperacion);

	/* PRE: comunicacionEnEspera tiene que ser una comunicacionn que esta en espera.
	 * POST: hace las modificaciones pertinentes para el caso de una comunicacion que esta en espera que no continua.
	 */
	void modificarComunicacionEnEsperaQueNoContinua(Nodo<Comunicacion*>* comunicacionEnEspera, Celular* celularAtratar);

	/* PRE: -.
	 * POST: Analiza los datos involucrados en una desconexion y realiza las operaciones pertinentes.
	 */
	void tratarDesconexion(std::ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: celularAtratar tiene que estar involucrado en una llamada que esta en espera.
	 * POST: analiza si hay llamadas en espera en las antenas involucradas en la comunicacion del celularAtratar
	 * y realiza las operaciones pertinentes del caso.
	 */
	void analizarEsperaEnDesconexion(Celular* celularAtratar, unsigned int tiempoDeOperacion);

	/* PRE: celularAtratar tiene que estar vinculado a otro y en medio de una comunicacion.
	 * POST: devuelve un puntero hacia un nodo de la lista de las comunicaciones establecidas el cual contiene
	 * la direccion de la comunicacion establecida entre los celulares involucrados.
	 */
	Nodo<Comunicacion*>* buscarEnComunicacionesEstablecidas(Celular* celularAtratar);

	/* PRE: -.
	 * POST: Analiza el paso de una comunicacion que estaba en progreso a espera entre antenas distintas
	 * actualizando los registros pertinentes.
	 */
	void pasajeAesperaEnAntenasDistintas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnEspera, unsigned int tiempoParaRegistrar);

	/* PRE: -.
	 * POST: Analiza el paso de una comunicacion que estaba en progreso a espera en una misma antena
	 * actualizando los registros pertinentes.
	 */
	void pasajeAesperaEnAntenasIguales(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnEspera, unsigned int tiempoParaRegistrar);

	/* PRE: -.
	 * POST: evalua si celularAtratar es el emisor en la comunicaion registrada.
	 */
	bool esEmisor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacion);

	/* PRE: -.
	 * POST: cambia el registro de la comunicacion que paso a estar en espera para que sea identificable.
	 */
	void modificarComunicacionAespera(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacion);

	/* PRE: -.
	 * POST: Busca y actualiza los registros de duracion de operaciones del emisor y receptor dentro de la antena.
	 */
	void aumentarDuracionesEnMismaAntena(unsigned int emisor, unsigned int receptor, Lista<RegistroActividadCelular*>* actividadEnAntena, unsigned int tiempoParaRegistrar);

	/* PRE: -.
	 * POST: Busca y actualiza los registros de duracion de operaciones del emisor y receptor en su antena correspondiente.
	 */
	void aumentarDuracionesEnDistintasAntenas(unsigned int emisor, unsigned int receptor,  Lista<RegistroActividadCelular*>* actividadEnAntenaEmisor, Lista<RegistroActividadCelular*>* actividadEnAntenaReceptor, unsigned int tiempoParaRegistrar);

	/* PRE: -.
	 * POST: Analiza los datos involucrados en un inicio de llamada y realiza las operaciones pertinentes.
	 */
	void tratarInicio(std::ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: Agregada a la lista de numeros que dieron ocupado en una operacion realizada..
	 */
	void registrarLlamadaQueDioOcupadoEnRealizada(Celular* celularAtratar, unsigned int numeroQueDioOcupado);

	/* PRE: -.
	 * POST: Agregada a la lista de numeros que dieron ocupado en una operacion recibida..
	 */
	void registrarLlamadaQueDioOcupadoEnRecibida(Celular* celularAtratar, unsigned int numeroQueLlamo);


	/* PRE: celularEmisor conectado a una antena.
	 * POST: busca en los registros de la antena del emisor el registro perteneciente a celularEmisor
	 * sino no lo encuentra genera uno.
	 */
	void controlarActividadEnAntena(Celular* celularAtratar);

	/* PRE: -.
	 * POST: Devuelve un puntero hacia el nodo que contiene la direccion del registro de
	 * la actividad efectuada por celularEmisor dentro de la antena a la que esta conectada.
	 */
	Nodo<RegistroActividadCelular*>* buscarActividadEnAntena(Celular* celularAtratar);

	/* PRE: -.
	 * POST: controla si los celulares involucrados en la comunicacion estan el antenas distintas
	 * o no y continua con el procesamiento
	 */
	void controlarDsponibilidadDeAntenasYprocesar(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: analiza si la antena permite que se efectue una llamada.
	 */
	void disponibilidadEnAntenaComun(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: agrega a los registro de llamadas del emisor la operacion realizada.
	 */
	void registrarLlamadaRealizada(Celular* celularEmisor, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: agrega a los registro de llamadas del receptor la operacion recibida.
	 */
	void registrarLlamadaRecibida(Celular* celularReceptor, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: agrega a la lista de comunicaciones establecidas la nueva comunicacion entre el celularEmisor y el celularReceptor en antenas diferentes.
	 */
	void registrarComunicacionAntenasDistintas(Celular* celularEmisor, Celular*  celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: agrega a la lista de comunicaciones establecidas la nueva comunicacion entre el celularEmisor y el celularReceptor en la misma antena.
	 */
	void registrarComunicacionMismaAntena(Celular* celularEmisor, Celular*  celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones);


	/* PRE: -.
	 * POST: analiza si las antenas involucradas permiten que se realice la comunicacion.
	 */
	void disponibilidadEnAntenasDistintas(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: Analiza los datos involucrados en una finalizacion de llamada y realiza las operaciones pertinentes.
	 */
	void tratarFin(std::ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: analiza los casos en los que se termina una llamada y uno de los dos celulares se encuentra desconectado.
	 */
	void analizarFinDeLlamadaConUnCelularDesconectado(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares);

	/* PRE: .-
	 * POST: devuelve un puntero al nodo de la lista de comunicaciones establecidas que contiene la direccion de la
	 * comunicacion en la que esta involucrada celularAtratar.
	 */
	Nodo<Comunicacion*>* buscarEnListaDeComunicaciones(Celular* celularAtratar, Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: busca el registro de la llamada realizada y actualiza los datos  al momento de su finalizacion.
	 */
	void finalizarLlamadaEnCelularEmisor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: busca el registro de la llamada recibida y actualiza los datos  al momento de su finalizacion.
	 */
	void finalizarLlamadaEnCelularReceptor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: desvincula la comunicacion que esta en espera en la cual uno de los celulares no se encuentra
	 * conectado a ninguna antena.
	 */
	void finalizarOperacionEnAntenaConectada(Antena* antenaAtratar, Nodo<Comunicacion*>* comunicacionEnAntena, Nodo<Comunicacion*>* esperaEnAntena);

	/* PRE: -.
	 * POST: Saca de la lista de comunicaciones establecidas el nodo comunicacionEnLista.
	 */
	void finalizarLlamadaEnListaDeComunicacion(Nodo<Comunicacion*>* comunicacionEnLista ,Lista<Comunicacion*>& listaComunicaciones);

	/* PRE: -.
	 * POST: Busca el ultimo nodo de la lista de llamadas rrealizadas de celularAtratar
	 * el cual corresponde a la ultima operacion establecida.
	 */
	Nodo<RegistroLlamada*>* busquedaLlamadaEnListaDeRealizadas(Celular* celularAtratar);

	/* PRE: -.
	 * POST: Busca el ultimo nodo de la lista de llamadas recibidas de celularAtratar
	 * el cual corresponde a la ultima operacion establecida.
	 */
	Nodo<RegistroLlamada*>* busquedaLlamadaEnListaRecibidas(Celular* celularAtratar);

	/* PRE: -.
	 * POST: Chequea la existencia de llamadas que se encuentran en espera en antenaAtratar y
	 * vuelve a poner en continuacion una llamada si hay disponibilidad en la misma.
	 */
	void controlarLlamadasEnEsperaEnAntena(Antena* antenaAtratar,  unsigned int nuevoTiempoDeInicio, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: determina la/s antena/s involucrada/s en la comunicacion que finaliza. Posteriormente sigue analizando
	 * otras caracteristicas del termino de la comunicacion.
	 */
	void analisisDeAntenasInvolucradas(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: realiza todas la modificaciones en los registros totales de los celuares involucrados y en la antena que intervino en
	 * la comunicacion durante el transcurso de la misma.
	 */
	void analizarFinalizacionEnAntenasIguales(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: determina si la llamada que finaliza se encontraba en progreso o estaba en espera. Posteriormente analiza
	 * el caso resultante.
	 */
	void analizarFinalizacionEnAntenasDistintas(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: concluye una llamada que se encontraba en progreso y realiza todas la modificaciones en los registros totales
	 * de los celulares involucrados y en las antenas que intervinieron en la comunicacion durante el transcurso de la misma.
	 */
	void analizarFinalizacionDeRealizadaEnDosAntenas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion);

	/* PRE: -.
	 * POST: concluye una llamada que se encontraba en espera y realiza todas la modificaciones en los registros totales
	 * de los celulares involucrados y en las antenas que estan relacionadas a la comunicacion que finaliza.
	 */
	void analizarFinalizacionEnEsperaEnDosAntenas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares);

#endif /* FUNCIONES_H_ */
