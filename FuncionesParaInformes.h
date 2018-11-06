/*
 * FuncionesParaInformes.h
 *
 *  Created on: 10 de jun. de 2016
 *      Author: lnx
 */

#ifndef FUNCIONESPARAINFORMES_H_
#define FUNCIONESPARAINFORMES_H_

#include "Celular.h"
#include <iostream>
#include <fstream>

	/* PRE: -.
	 * POST: Pide la seleccion de una accion del menu de tareas del programa.
	 */
	void realizarTarea(char tareaSeleccionada, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);



	/* PRE: -.
	 * POST: devuelve el primer codigo correcto que corresponde al celular seleccionado por el usuario.
	 */
	unsigned int elegirPrimerCelular(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: devuelve el segundo codigo correcto que corresponde al celular seleccionado por el usuario.
	 */
	unsigned int elegirSegundoCelular(Lista<Celular*>& listaCelulares, unsigned int primerCelularElegido);

	/* PRE: -.
	 * POST: devuelve un puntero al celular cuyo codigo es igual a codigoDeCelular.
	 */
	Celular* buscarCelularPorCodigo(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: contiene los metodos necesarios para realizar los distintos recorridos y acumular los datos
	 * relacionados con las operaciones establecidas entre los celulares.
	 */
	void procesarLlamadasEntreLosCelulares(Celular* eleccion1, Celular* eleccion2, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, unsigned int& numeroDeVecesOcupado, Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: recorre la lista de operaciones realizadas por el primer celular al numeroCelularAComparar y acumula los resultados obtenidos.
	 */
	void recorrerListaDeLlamadasRealizadasPorElPrimerCelularYobtenerDatos(Lista<RegistroLlamada*>* listaDeRealizadas, unsigned int numeroCelularAComparar, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: obtiene las antenas que intervinieron en las operaciones establecidas entre los dos celulares seleccionados.
	 */
	void chequearAntenasInvolucradas(Lista<std::string*>* listaDeAntenasDelRegistro, Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: controla si nombreDeLaAntenaAbuscar ya fue registrada en la lista de antenas involucradas en las operaciones
	 * establecidas entre los dos celulares seleccionados.
	 */
	bool antenaInvolucradaYaFueAcumulada(std::string nombreDeLaAntenaAbuscar,Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: recorre la lista de operaciones recibidas por el primer celular por parte de numeroCelularAComparar y acumula los resultados obtenidos.
	 */
	void recorrerListaDeLlamadasRecibidasPorElPrimerCelularYobtenerDatos(Lista<RegistroLlamada*>* listaDeRecibidas, unsigned int numeroCelularAComparar, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: recorre la lista de operaciones realizadas que dieron ocupado del primer celular hacia el numeroCelularAComparar y acumula los resultados obtenidos.
	 */
	void recorrerListaDeLlamadasRealizadasOcupadasDelPrimerCelularYobtenerDatos(Lista<unsigned int*>* listaDeOcupadasRealizadas, unsigned int numeroCelularAcomparar, unsigned int& cantidadDeVecesOcupado);

	/* PRE: -.
	 * POST: recorre la lista de operaciones recibidas que dieron ocupado del primer celular realizadas por numeroCelularAComparar y acumula los resultados obtenidos.
	 */
	void recorrerListaDeLlamadasRecibidasOcupadasDelPrimerCelularYobtenerDatos(Lista<unsigned int*>* listaDeOcupadasRecibidas, unsigned int numeroCelularAcomparar, unsigned int& cantidadDeVecesOcupado);

	/* PRE: -.
	 * POST: Determina cual es el celular que mas hablo en todo el sistema y en cada antena.
	 */
	void celularQueMasHablo(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la duracion maxima del tiempo empleado en las llamadas realizadas de la lista de celulares.
	 */
	unsigned int numeroMaximoDeDuracionEnLlamadasRealizadasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadDuracionMaximaEnRealizadas en todo el sistema.
	 */
	void imprimirCelularesQueMasHablaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDuracionMaximaEnRealizadas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que invirtieron el mayor tiempo
	 * en sus llamadas realizadas en una antena.
	 */
	void imprimirCelularesQueMasHablaronEnCadaAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la duracion maxima de tiempo empleado durante llamadas realizadas por algun celular
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int numeroDeDuracionEnLlamadasRealizadasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor duracion empleada
	 * durante las llamadas realizadas.
	 */
	void imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRealizadasEsLaMayor(Antena* antenaAtratar, unsigned int duracionEnLlamadasRealizadas);

	/* PRE: -.
	 * POST: Determina cual es el celular que mas llamo en todo el sistema y en cada antena.
	 */
	void celularQueMasLlamo(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la mayor cantidad de llamadas realizadas de la lista de celulares.
	 */
	unsigned int numeroMaximoDeLlamadasRealizadasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadDeLlamadasRealizadas en todo el sistema.
	 */
	void imprimirCelularesQueMasLlamaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDeLlamadasRealizadas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que realizaron mas llamadas por cada antena.
	 */
	void imprimirCelularesQueMasLlamaronEnCadaAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la maypr cantidad de llamadas realizadas por algun celular
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int cantidadDeLlamadasRealizadasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor cantidad
	 * de llamadas realizadas en la antena.
	 */
	void imprimirActividadEnAntenaConMayorCantidadDeLlamadasRealizadas(Antena* antenaAtratar, unsigned int cantidadDeLlamadasRealizadas);

	/* PRE: -.
	 * POST: Determina cual es el celular realizo mas llamadas que dieron ocupadas en todo el
	 * sistema y en cada antena.
	 */
	void celularQueMasLeDioOcupadoSusLlamadasRealizadas(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la cantidad maxima de llamadas realizadas que dieron ocupado en la lista de celulares.
	 */
	unsigned int numeroMaximoDeLlamadasRealizadasOcupadasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadMaximaDeOcupadas en todo el sistema.
	 */
	void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadas(Lista<Celular*>& listaCelulares, unsigned int cantidadMaximaDeOcupadas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron mas llamadas realizadas ocupadas en una antena.
	 */
	void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadasEnAntenas(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la cantidad maxima de llamadas realizadas que dieron ocupado que se encontro
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int numeroMaximoDeOcupadasRealizadasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor cantidad de llamadas
	 * realizadas que dieron ocupado en antenaAtratar.
	 */
	void imprimirActividadEnAntenaQueTieneMaximoDeOcupadasRealizadas(Antena* antenaAtratar, unsigned int cantidadMaximaDeOcupadas);

	/* PRE: -.
	 * POST: Determina cual es el celular al que mas llamaron en todo el sistema y en cada antena.
	 */
	void celularAlQueMasLlamaron(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la mayor cantidad de llamadas recibidas de la lista de celulares.
	 */
	unsigned int numeroMaximoDeLlamadasRecibidasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadDeLlamadasRecibidas en todo el sistema.
	 */
	void imprimirCelularesAlQueMasLlamaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDeLlamadasRecibidas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que recibieron mas llamadas por cada antena.
	 */
	void imprimirCelularesAlQueMasLlamaronEnCadaAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la maypr cantidad de llamadas recibidas por algun celular
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int cantidadDeLlamadasRecibidasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor cantidad
	 * de llamadas recibidas en la antena.
	 */
	void imprimirActividadEnAntenaConMayorCantidadDeLlamadasRecibidas(Antena* antenaAtratar, unsigned int cantidadDeLlamadasRecibidas);

	/* PRE: -.
	 * POST: Determina cual es el celular al que mas le hablaron en todo el sistema y en cada antena.
	 */
	void celularAlQueMasLeHablaron(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la duracion maxima del tiempo empleado en las llamadas recibidas de la lista de celulares.
	 */
	unsigned int numeroMaximoDeDuracionEnLlamadasRecibidasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadDuracionMaximaEnRecibidas en todo el sistema.
	 */
	void imprimirCelularesAlosQueMasLeHablaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDuracionMaximaEnRecibidas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que invirtieron el mayor tiempo
	 * en sus llamadas recibidas en una antena.
	 */
	void imprimirCelularesAlosQueMasLeHablaronEnCadaAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la duracion maxima de tiempo empleado durante llamadas recibidas por algun celular
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int numeroDeDuracionEnLlamadasRecibidasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor duracion empleada
	 * durante las llamadas recibidas.
	 */
	void imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRecibidaEsLaMayor(Antena* antenaAtratar, unsigned int duracionEnLlamadasRecibidas);

	/* PRE: -.
	 * POST: Determina cual es el celular que recibio mas llamadas que dieron ocupadas en todo el
	 * sistema y en cada antena.
	 */
	void celularQueMasDioOcupado(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la cantidad maxima de llamadas recibidas que dieron ocupado en la lista de celulares.
	 */
	unsigned int numeroMaximoDeLlamadasRecibidasOcupadasEnListaDeCelulares(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron cantidadMaximaDeOcupadas en todo el sistema.
	 */
	void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidas(Lista<Celular*>& listaCelulares, unsigned int cantidadMaximaDeOcupadas);

	/* PRE: -.
	 * POST: imprime por pantalla los datos de los celulares que tuvieron mas llamadas recibidas ocupadas en una antena.
	 */
	void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidasEnAntenas(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la cantidad maxima de llamadas recibidas que dieron ocupado que se encontro
	 * en la lista de actividades de antenaAtratar.
	 */
	unsigned int numeroMaximoDeOcupadasRecibidasEnActividadAntena(Antena* antenaAtratar);

	/* PRE: -.
	 * POST: imprime los datos correspondientes al registro que contiene la mayor cantidad de llamadas
	 * recibidas que dieron ocupado en antenaAtratar.
	 */
	void imprimirActividadEnAntenaQueTieneMaximoDeOcupadasRecibidas(Antena* antenaAtratar, unsigned int cantidadMaximaDeOcupadas);

	/* PRE: -.
	 * POST: imprime por pantalla el detalle de las llamadas recibidas por un Celular determinado posteriormente.
	 */
	void detalleDellamdadasEmitidas(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla el detalle de las llamdas recibidas por un Celular cuyo codigo es igual a codigoDeCelular.
	 */
	void imprimirLlamadasRealizadasDeCelular(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla el detalle de las llamdas recibidas por un Celular determinado posteriormente.
	 */
	void detalleDellamdadasRecibidas(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla los celulares existentes dentro del sistema.
	 */
	void mostrarCelularesDelSistema(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla el detalle de las llamdas recibidas por un Celular cuyo codigo es igual a codigoDeCelular.
	 */
	void imprimirLlamadasRecibidasDeCelular(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: imprime por pantalla el registro de una llamada.
	 */
	void imprimirRegistroDeLlamada(RegistroLlamada* registroAimprimir);

	/* PRE: -.
	 * POST: imprime por pantalla la cantidad de operaciones maximas que se establecieron
	 * concurrentemente por antena.
	 */
	void cantidadMaximaDeOperacionesEstablecidasConcurrentementePorAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: muestra los celulares existentes en el sistema y pide que realice
	 * las elecciones para mostrar las llamadas recibidas hechas por un celular seleccionado hacia otro.
	 */
	void detalleDellamadasRecibidasDeUnCelularEntreDosAelegir(Lista<Celular*>& listaCelulares);

	/* PRE: -.
	 * POST: contiene los metodos necesarios para realizar los distintos recorridos y acumular los datos
	 * relacionados con las llamadas recibidas hechas por un celular seleccionado hacia otro.
	 */
	void procesarLlamadasRecibidasPorElPrimerCelularElegido(Celular* eleccion1, Celular* eleccion2, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, unsigned int& numeroDeVecesOcupado, Lista<std::string*>* antenasUtilizadas);

	/* PRE: -.
	 * POST: imprime por pantalla la cantidad de operaciones anuladas por antena ordenadas de manera descendiente.
	 */
	void cantidadDeAnuladasPorFaltaDeCapacidadPorAntena(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: devuelve la cantidad maxima de operaciones que fueron anuladas por las antenas en todo el sistema.
	 */
	unsigned int buscarCantidadMaxDeOperacionesAnuladasEnElSistema(Lista<Antena*>& listaAntenas);

	/* PRE: -.
	 * POST: revisa las antenas e imprime la que tiene la cantidad de llamadas anuladas igual a numeroDeAnuladas.
	 */
	void recorrerListaDeAntenasBuscansdoAnuladas(Lista<Antena*>& listaAntenas, unsigned int numeroDeAnuladas);



#endif /* FUNCIONESPARAINFORMES_H_ */
