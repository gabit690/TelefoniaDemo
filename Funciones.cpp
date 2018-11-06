/*
 * Funciones.cpp
 *
 *  Created on: 25 de may. de 2016
 *      Author: lnx
 */

#include "Funciones.h"
using namespace std;
string ingresarNombreDelArchivo(ifstream& archivo)
{
	string nombreDeArchivo;
	bool salirDelBucle = false;
	do
	{
	cout << ">>> Ingrese el nombre de un archivo de texto con su extension para procesar.\n\n";
	cout << "Su respuesta: ";
	cin >> nombreDeArchivo;
	cin.ignore(256,'\n');
	archivo.open(nombreDeArchivo.c_str());
	if(archivo.is_open())
	{
		salirDelBucle = true;
	}
	else
	{
		cout << endl;
		cout << "¡¡¡ El nombre del archivo ingresado no existe. !!!" << endl << endl;
	}
	}while(salirDelBucle == false);
	return (nombreDeArchivo);
}

void procesarArchivo(ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas)
{
	string tipoDeOperacion;
	Lista<Comunicacion*> listaDeComunicaciones;
	while(!archivo.eof()){
		archivo >> tipoDeOperacion;
		if(tipoDeOperacion == "Antena"){
			conectarAntena(archivo, listaAntenas);
		}
		if(tipoDeOperacion == "Conectar"){
			tratarConexion(archivo, listaCelulares, listaAntenas);
		}
		if(tipoDeOperacion == "Desconectar"){
			tratarDesconexion(archivo, listaCelulares, listaAntenas);
		}
		if(tipoDeOperacion == "Inicio"){
			tratarInicio(archivo, listaCelulares, listaDeComunicaciones);
		}
		if(tipoDeOperacion == "Fin"){
			tratarFin(archivo, listaCelulares, listaAntenas, listaDeComunicaciones);
		}
	}
}

void conectarAntena(ifstream& archivo, Lista<Antena*>& listaAntenas){
	Antena* nuevaAntena = new Antena;
	string nombreDeAntena;
	unsigned int capacidadDeOperacionesSimultaneas;
	archivo >> nombreDeAntena >> capacidadDeOperacionesSimultaneas;
	nuevaAntena->asignarNombre(nombreDeAntena);
	nuevaAntena->asignarCantidadDeOperacionesSoportadas(capacidadDeOperacionesSimultaneas);
	nuevaAntena->asignarComunicacionesDisponibles(capacidadDeOperacionesSimultaneas);
	listaAntenas.agregarElemento(nuevaAntena);

}

void tratarConexion(ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroLeido;
	string nombreAntena;
	unsigned int tiempoDeOperacion;
	archivo >> numeroLeido >> nombreAntena >> tiempoDeOperacion;
	Antena* antenaAconectar = buscarAntena(nombreAntena, listaAntenas);
	if(existeElCelular(numeroLeido, listaCelulares)){
		Celular* celularAtratar = buscarCelular(numeroLeido, listaCelulares);
		celularAtratar->asignarAntenaConectada(antenaAconectar);
		celularAtratar->asignarUltimaAntena(nombreAntena);
		if(celularAtratar->obtenerCelularVinculado()){
			analizarEsperaEnConexion(celularAtratar, tiempoDeOperacion);
		}
		controlarActividadEnAntena(celularAtratar);
	}
	else{
		Celular* nuevoCelular = new Celular;
		nuevoCelular->asignarCodigo(listaCelulares.obtenerTamanio()+1);
		nuevoCelular->asignarNumero(numeroLeido);
		nuevoCelular->asignarUltimaAntena(nombreAntena);
		nuevoCelular->asignarAntenaConectada(antenaAconectar);
		listaCelulares.agregarElemento(nuevoCelular);
		controlarActividadEnAntena(nuevoCelular);
	}
}

Antena* buscarAntena(string nombreDeAntena, Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorDeAntenas = listaAntenas.obtenerPrimerNodo();
	while((cursorDeAntenas!=0)&&(cursorDeAntenas->obtenerDato()->obtenerNombreDeAntena()!=nombreDeAntena)){
		cursorDeAntenas = cursorDeAntenas->obtenerNodoSiguiente();
	}
	return cursorDeAntenas->obtenerDato();
}

Celular* buscarCelular(unsigned int numeroCelular, Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorDeCelulares = listaCelulares.obtenerPrimerNodo();
	Celular* punteroAlCelular = 0;
	bool celularEncontrado = false;
	while((cursorDeCelulares!=0)&&(!celularEncontrado)){
		if(cursorDeCelulares->obtenerDato()->obtenerNumero()==numeroCelular){
			punteroAlCelular = cursorDeCelulares->obtenerDato();
			celularEncontrado = true;
		}
		cursorDeCelulares = cursorDeCelulares->obtenerNodoSiguiente();
	}
	return punteroAlCelular;
}

bool existeElCelular(unsigned int numeroCelular, Lista<Celular*>& listaCelulares){
	bool existencia = false;
	Celular* celularBuscado = buscarCelular(numeroCelular, listaCelulares);
	if(celularBuscado != 0){
		existencia = true;
	}
	return existencia;
}

void analizarEsperaEnConexion(Celular* celularAtratar, unsigned int tiempoDeOperacion){
	Nodo<Comunicacion*>* comunicacionEnEspera = buscarLlamadaEnEspera(celularAtratar);
	if(!mismaAntena(celularAtratar)){
		if(celularAtratar->obtenetAntenaActual()->obtenerOperacionesDisponibles() > 0){
			celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->agregarElemento(comunicacionEnEspera->obtenerDato());
			celularAtratar->obtenetAntenaActual()->disminuirComunicacionesDisponibles();
			modificarComunicacionEnEsperaQueContinua(comunicacionEnEspera, celularAtratar, tiempoDeOperacion);
			agregadoAntenaQueIntervieneEnComunicacion(celularAtratar, comunicacionEnEspera);
			celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(comunicacionEnEspera);
			modificarOperacionesMaximasEnAntena(celularAtratar->obtenetAntenaActual());
		}
		else{
			celularAtratar->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->agregarElemento(comunicacionEnEspera->obtenerDato());
			modificarComunicacionEnEsperaQueNoContinua(comunicacionEnEspera, celularAtratar);
		}

	}
	else{
		modificarComunicacionEnEsperaQueContinua(comunicacionEnEspera, celularAtratar, tiempoDeOperacion);
		agregadoAntenaQueIntervieneEnComunicacion(celularAtratar, comunicacionEnEspera);
		celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(comunicacionEnEspera);
	}
}

bool mismaAntena(Celular* celularAtratar){
	bool respuesta = false;
	if(celularAtratar->obtenetAntenaActual() == celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()){
		respuesta = true;
	}
	return respuesta;
}

Nodo<Comunicacion*>* buscarLlamadaEnEspera(Celular* celularAtratar){
	Nodo<Comunicacion*>* cursorLlamadaEnEspera = celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->obtenerPrimerNodo();
	while((cursorLlamadaEnEspera->obtenerDato()->obtenerNumeroEmisor()!=celularAtratar->obtenerNumero()) && (cursorLlamadaEnEspera->obtenerDato()->obtenerNumeroReceptor()!=celularAtratar->obtenerNumero())){
		cursorLlamadaEnEspera = cursorLlamadaEnEspera->obtenerNodoSiguiente();
	}
	return cursorLlamadaEnEspera;
}

void agregadoAntenaQueIntervieneEnComunicacion(Celular* celularAtratar,Nodo<Comunicacion*>* comunicacionEnEspera){
	string* antenaAgregar = new string;
	*antenaAgregar = celularAtratar->obtenerUltimaAntena();
	if(celularAtratar->obtenerNumero() == comunicacionEnEspera->obtenerDato()->obtenerNumeroEmisor()){
		Nodo<RegistroLlamada*>* cursorLlamadaEmisor = celularAtratar->obtenerListaDeRealizadas()->obtenerPrimerNodo();
		Nodo<RegistroLlamada*>* cursorLlamadaReceptor = celularAtratar->obtenerCelularVinculado()->obtenerListaDeRecibidas()->obtenerPrimerNodo();
		buscarRegistroYagregarAntena(cursorLlamadaEmisor, cursorLlamadaReceptor, comunicacionEnEspera, antenaAgregar);
	}
	else{
		Nodo<RegistroLlamada*>* cursorLlamadaEmisor = celularAtratar->obtenerCelularVinculado()->obtenerListaDeRealizadas()->obtenerPrimerNodo();
		Nodo<RegistroLlamada*>* cursorLlamadaReceptor = celularAtratar->obtenerListaDeRecibidas()->obtenerPrimerNodo();
		buscarRegistroYagregarAntena(cursorLlamadaEmisor, cursorLlamadaReceptor, comunicacionEnEspera, antenaAgregar);
	}
}

void buscarRegistroYagregarAntena(Nodo<RegistroLlamada*>* cursorLlamadaEmisor,Nodo<RegistroLlamada*>* cursorLlamadaReceptor, Nodo<Comunicacion*>* comunicacionEnEspera, string* antenaAgregar){
	while((cursorLlamadaEmisor->obtenerDato()->obtenerCelularInvolucrado()!=comunicacionEnEspera->obtenerDato()->obtenerNumeroReceptor())||(cursorLlamadaEmisor->obtenerDato()->obtenerTiempoDeFinalizacion()!=0)){
			cursorLlamadaEmisor = cursorLlamadaEmisor->obtenerNodoSiguiente();
	}
	while((cursorLlamadaReceptor->obtenerDato()->obtenerCelularInvolucrado()!=comunicacionEnEspera->obtenerDato()->obtenerNumeroEmisor())||(cursorLlamadaReceptor->obtenerDato()->obtenerTiempoDeFinalizacion()!=0)){
		cursorLlamadaReceptor = cursorLlamadaReceptor->obtenerNodoSiguiente();
	}
	cursorLlamadaEmisor->obtenerDato()->obtenerListadoDeAntenas()->agregarElemento(antenaAgregar);
	cursorLlamadaReceptor->obtenerDato()->obtenerListadoDeAntenas()->agregarElemento(antenaAgregar);
}

void modificarOperacionesMaximasEnAntena(Antena* antenaAtratar){
	if(antenaAtratar->obtenerCantidadDeComunicacionesEstablecidas() < antenaAtratar->obtenerListaDeOperacionesConcurrentes()->obtenerTamanio()){
		antenaAtratar->aumentarTotalDeComunicacionesEstablecidas();
	}
}

void modificarComunicacionEnEsperaQueContinua(Nodo<Comunicacion*>* comunicacionEnEspera, Celular* celularAtratar, unsigned int tiempoDeOperacion){
	if(comunicacionEnEspera->obtenerDato()->obtenerNumeroEmisor() == celularAtratar->obtenerNumero()){
		comunicacionEnEspera->obtenerDato()->ingresarNombreAntenaEmisor(celularAtratar->obtenerUltimaAntena());
	}
	else{
		comunicacionEnEspera->obtenerDato()->ingresarNombreAntenaReceptor(celularAtratar->obtenerUltimaAntena());
	}
	comunicacionEnEspera->obtenerDato()->ingresarInicioDeLlamada(tiempoDeOperacion);
	comunicacionEnEspera->obtenerDato()->ingresarFinDeLlamada(0);
}

void modificarComunicacionEnEsperaQueNoContinua(Nodo<Comunicacion*>* comunicacionEnEspera, Celular* celularAtratar){
	if(comunicacionEnEspera->obtenerDato()->obtenerNumeroEmisor() == celularAtratar->obtenerNumero()){
		comunicacionEnEspera->obtenerDato()->ingresarNombreAntenaEmisor(celularAtratar->obtenerUltimaAntena());
	}
	else{
		comunicacionEnEspera->obtenerDato()->ingresarNombreAntenaReceptor(celularAtratar->obtenerUltimaAntena());
	}
	comunicacionEnEspera->obtenerDato()->ingresarInicioDeLlamada(0);
	comunicacionEnEspera->obtenerDato()->ingresarFinDeLlamada(0);
}

void tratarDesconexion(ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroLeido;
	string nombreAntena;
	unsigned int tiempoDeOperacion;
	archivo >> numeroLeido >> nombreAntena >> tiempoDeOperacion;
	Celular* celularAtratar = buscarCelular(numeroLeido, listaCelulares);
	if(celularAtratar->obtenerCelularVinculado()){
			analizarEsperaEnDesconexion(celularAtratar, tiempoDeOperacion);
		}
	celularAtratar->asignarAntenaConectada(0);
}

void analizarEsperaEnDesconexion(Celular* celularAtratar, unsigned int tiempoDeOperacion){
	Nodo<Comunicacion*>* comunicacionEnEspera = buscarEnComunicacionesEstablecidas(celularAtratar);
	if(comunicacionEnEspera->obtenerDato()->obtenerInicioDeLlamada()!=0){
		comunicacionEnEspera->obtenerDato()->ingresarFinDeLlamada(tiempoDeOperacion);
		unsigned int tiempoParaRegistrar = tiempoDeOperacion-comunicacionEnEspera->obtenerDato()->obtenerInicioDeLlamada();
		if(comunicacionEnEspera->obtenerDato()->obtenerNombreAntenaEmisor() != comunicacionEnEspera->obtenerDato()->obtenerNombreAntenaReceptor()){
			pasajeAesperaEnAntenasDistintas(celularAtratar, comunicacionEnEspera, tiempoParaRegistrar);
		}
		else{
			pasajeAesperaEnAntenasIguales(celularAtratar, comunicacionEnEspera, tiempoParaRegistrar);
		}
		//celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->agregarElemento(comunicacionEnEspera->obtenerDato());
		modificarComunicacionAespera(celularAtratar, comunicacionEnEspera);
	}
	else{
		Nodo<Comunicacion*>* cursorLlamadasEnEspera = celularAtratar->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->obtenerPrimerNodo();
		while(cursorLlamadasEnEspera->obtenerDato() != comunicacionEnEspera->obtenerDato()){
			cursorLlamadasEnEspera = cursorLlamadasEnEspera->obtenerNodoSiguiente();
		}
		celularAtratar->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(cursorLlamadasEnEspera);
	}
}

Nodo<Comunicacion*>* buscarEnComunicacionesEstablecidas(Celular* celularAtratar){
	Nodo<Comunicacion*>* cursorDeComunicaciones = celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerPrimerNodo();
	while((cursorDeComunicaciones->obtenerDato()->obtenerNumeroEmisor()!=celularAtratar->obtenerNumero())&&(cursorDeComunicaciones->obtenerDato()->obtenerNumeroReceptor()!=celularAtratar->obtenerNumero())){
		cursorDeComunicaciones = cursorDeComunicaciones->obtenerNodoSiguiente();
	}
	return cursorDeComunicaciones;
}

void pasajeAesperaEnAntenasDistintas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnEspera, unsigned int tiempoParaRegistrar){
	if(esEmisor(celularAtratar, comunicacionEnEspera)){
		celularAtratar->obtenerActividad()->aumentarTiempoRealizadas(tiempoParaRegistrar);
		celularAtratar->obtenerCelularVinculado()->obtenerActividad()->aumentarTiempoRecibidas(tiempoParaRegistrar);
		aumentarDuracionesEnDistintasAntenas(celularAtratar->obtenerNumero(), celularAtratar->obtenerCelularVinculado()->obtenerNumero(), celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), tiempoParaRegistrar);
	}
	else{
		celularAtratar->obtenerActividad()->aumentarTiempoRecibidas(tiempoParaRegistrar);
		celularAtratar->obtenerCelularVinculado()->obtenerActividad()->aumentarTiempoRealizadas(tiempoParaRegistrar);
		aumentarDuracionesEnDistintasAntenas(celularAtratar->obtenerCelularVinculado()->obtenerNumero(), celularAtratar->obtenerNumero(), celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), tiempoParaRegistrar);
	}
	celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->agregarElemento(comunicacionEnEspera->obtenerDato());
	celularAtratar->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
	Nodo<Comunicacion*>* cursorDeComunicacion = celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerPrimerNodo();
	while(cursorDeComunicacion->obtenerDato()!=comunicacionEnEspera->obtenerDato()){
		cursorDeComunicacion = cursorDeComunicacion->obtenerNodoSiguiente();
	}
	celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorDeComunicacion);
}

void pasajeAesperaEnAntenasIguales(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnEspera, unsigned int tiempoParaRegistrar){
	if(esEmisor(celularAtratar, comunicacionEnEspera)){
		celularAtratar->obtenerActividad()->aumentarTiempoRealizadas(tiempoParaRegistrar);
		celularAtratar->obtenerCelularVinculado()->obtenerActividad()->aumentarTiempoRecibidas(tiempoParaRegistrar);
		aumentarDuracionesEnMismaAntena(celularAtratar->obtenerNumero(), celularAtratar->obtenerCelularVinculado()->obtenerNumero(), celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), tiempoParaRegistrar);
	}
	else{
		celularAtratar->obtenerActividad()->aumentarTiempoRecibidas(tiempoParaRegistrar);
		celularAtratar->obtenerActividad()->aumentarTiempoRealizadas(tiempoParaRegistrar);
		aumentarDuracionesEnMismaAntena(celularAtratar->obtenerCelularVinculado()->obtenerNumero(), celularAtratar->obtenerNumero(), celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada(), tiempoParaRegistrar);
	}
	celularAtratar->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->agregarElemento(comunicacionEnEspera->obtenerDato());
}

bool esEmisor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacion){
	bool respuesta = false;
	if(celularAtratar->obtenerNumero() == comunicacion->obtenerDato()->obtenerNumeroEmisor()){
		respuesta = true;
	}
	return respuesta;
}

void modificarComunicacionAespera(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacion){
	if(esEmisor(celularAtratar, comunicacion)){
		comunicacion->obtenerDato()->ingresarNombreAntenaEmisor("");

	}
	else{
		comunicacion->obtenerDato()->ingresarNombreAntenaReceptor("");
	}
	comunicacion->obtenerDato()->ingresarInicioDeLlamada(0);
	comunicacion->obtenerDato()->ingresarFinDeLlamada(0);
}

void aumentarDuracionesEnMismaAntena(unsigned int emisor, unsigned int receptor,  Lista<RegistroActividadCelular*>* actividadEnAntena, unsigned int tiempoParaRegistrar){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = actividadEnAntena->obtenerPrimerNodo();
	while(cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular()!=emisor){
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	cursorActividadEnAntena->obtenerDato()->aumentarTiempoRealizadas(tiempoParaRegistrar);
	cursorActividadEnAntena = actividadEnAntena->obtenerPrimerNodo();
	while(cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular()!=receptor){
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	cursorActividadEnAntena->obtenerDato()->aumentarTiempoRecibidas(tiempoParaRegistrar);
}

void aumentarDuracionesEnDistintasAntenas(unsigned int emisor, unsigned int receptor,  Lista<RegistroActividadCelular*>* actividadEnAntenaEmisor, Lista<RegistroActividadCelular*>* actividadEnAntenaReceptor, unsigned int tiempoParaRegistrar){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntenaEmisor = actividadEnAntenaEmisor->obtenerPrimerNodo();
	while(cursorActividadEnAntenaEmisor->obtenerDato()->obtenerNumeroDeCelular()!=emisor){
		cursorActividadEnAntenaEmisor = cursorActividadEnAntenaEmisor->obtenerNodoSiguiente();
	}
	cursorActividadEnAntenaEmisor->obtenerDato()->aumentarTiempoRealizadas(tiempoParaRegistrar);
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntenaReceptor = actividadEnAntenaReceptor->obtenerPrimerNodo();
	while(cursorActividadEnAntenaReceptor->obtenerDato()->obtenerNumeroDeCelular()!=receptor){
		cursorActividadEnAntenaReceptor = cursorActividadEnAntenaReceptor->obtenerNodoSiguiente();
	}
	cursorActividadEnAntenaReceptor->obtenerDato()->aumentarTiempoRecibidas(tiempoParaRegistrar);
}

void tratarInicio(ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Comunicacion*>& listaComunicaciones){
	unsigned int numeroEmisor;
	unsigned int numeroReceptor;
	unsigned int tiempoDeOperacion;
	archivo >> numeroEmisor >> numeroReceptor >> tiempoDeOperacion;
	Celular* celularEmisor = buscarCelular(numeroEmisor, listaCelulares);
	if(existeElCelular(numeroReceptor, listaCelulares)){
		Celular* celularReceptor = buscarCelular(numeroReceptor, listaCelulares);
		if(!celularReceptor->obtenerCelularVinculado()){
			controlarDsponibilidadDeAntenasYprocesar(celularEmisor, celularReceptor, tiempoDeOperacion, listaComunicaciones);
		}
		else{
			celularEmisor->obtenerActividad()->aumentarRealizadasOcupadas();
			Nodo<RegistroActividadCelular*>* registroEmisorEnAntena = buscarActividadEnAntena(celularEmisor);
			registroEmisorEnAntena->obtenerDato()->aumentarRealizadasOcupadas();
			celularReceptor->obtenerActividad()->aumentarRecibidasOcupadas();
			Nodo<RegistroActividadCelular*>* registroReceptorEnAntena = buscarActividadEnAntena(celularReceptor);
			registroReceptorEnAntena->obtenerDato()->aumentarRecibidasOcupadas();
			registrarLlamadaQueDioOcupadoEnRealizada(celularEmisor, numeroReceptor);
			registrarLlamadaQueDioOcupadoEnRecibida(celularReceptor, numeroEmisor);
		}
	}
	else{
		celularEmisor->obtenerActividad()->aumentarRealizadasOcupadas();
		Nodo<RegistroActividadCelular*>* registroEnAntena = buscarActividadEnAntena(celularEmisor);
		registroEnAntena->obtenerDato()->aumentarRealizadasOcupadas();
		registrarLlamadaQueDioOcupadoEnRealizada(celularEmisor, numeroReceptor);
	}
}

void registrarLlamadaQueDioOcupadoEnRealizada(Celular* celularAtratar, unsigned int numeroQueDioOcupado){
	unsigned int* numeroAagregar = new unsigned int(numeroQueDioOcupado);
	celularAtratar->obtenerListaDeNumerosQueDieronOcupadoEnRealizadas()->agregarElemento(numeroAagregar);
}

void registrarLlamadaQueDioOcupadoEnRecibida(Celular* celularAtratar, unsigned int numeroQueLlamo){
	unsigned int* numeroAagregar = new unsigned int(numeroQueLlamo);
	celularAtratar->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas()->agregarElemento(numeroAagregar);
}

void controlarActividadEnAntena(Celular* celularAtratar){
	Nodo<RegistroActividadCelular*>* registroDelEmisorEnAntena = buscarActividadEnAntena(celularAtratar);
	if(!registroDelEmisorEnAntena){
		RegistroActividadCelular* registroDeNuevoCelular = new RegistroActividadCelular;
		registroDeNuevoCelular->ingresarNumeroDeCelular(celularAtratar->obtenerNumero());
		celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada()->agregarElemento(registroDeNuevoCelular);
	}
}

Nodo<RegistroActividadCelular*>* buscarActividadEnAntena(Celular* celularAtratar){
	Nodo<RegistroActividadCelular*>* cursorActividad = celularAtratar->obtenetAntenaActual()->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	bool datoEncontrado = false;
	while(cursorActividad && !datoEncontrado){
		if(cursorActividad->obtenerDato()->obtenerNumeroDeCelular()==celularAtratar->obtenerNumero()){
			datoEncontrado = true;
			break;
		}
		cursorActividad = cursorActividad->obtenerNodoSiguiente();
	}
	return cursorActividad;
}

void controlarDsponibilidadDeAntenasYprocesar(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones){
	if(celularEmisor->obtenetAntenaActual()!=celularReceptor->obtenetAntenaActual()){
		disponibilidadEnAntenasDistintas(celularEmisor, celularReceptor, tiempoDeOperacion, listaComunicaciones);
	}
	else{
		disponibilidadEnAntenaComun(celularEmisor, celularReceptor, tiempoDeOperacion, listaComunicaciones);
	}
}

void disponibilidadEnAntenasDistintas(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones){
	if((celularEmisor->obtenetAntenaActual()->obtenerOperacionesDisponibles()!=0)&&(celularReceptor->obtenetAntenaActual()->obtenerOperacionesDisponibles()!=0)){
		celularEmisor->asignarCelularVinculado(celularReceptor);
		celularReceptor->asignarCelularVinculado(celularEmisor);
		celularEmisor->obtenerActividad()->aumentarRealizadas();
		celularReceptor->obtenerActividad()->aumentarRecibidas();
		Nodo<RegistroActividadCelular*>* cursorActividadEmisorEnAntena =  buscarActividadEnAntena(celularEmisor);
		cursorActividadEmisorEnAntena->obtenerDato()->aumentarRealizadas();
		Nodo<RegistroActividadCelular*>* cursorActividadReceptorEnAntena =  buscarActividadEnAntena(celularReceptor);
		cursorActividadReceptorEnAntena->obtenerDato()->aumentarRecibidas();
		registrarLlamadaRealizada(celularEmisor,tiempoDeOperacion);
		registrarLlamadaRecibida(celularReceptor,tiempoDeOperacion);
		registrarComunicacionAntenasDistintas(celularEmisor, celularReceptor, tiempoDeOperacion, listaComunicaciones);
	}
	else{
		celularEmisor->obtenetAntenaActual()->aumentarCantidadDeLlamadasAnuladas();
		celularReceptor->obtenetAntenaActual()->aumentarCantidadDeLlamadasAnuladas();
	}
}

void disponibilidadEnAntenaComun(Celular* celularEmisor, Celular* celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones){
	if(celularEmisor->obtenetAntenaActual()->obtenerOperacionesDisponibles()!=0){
		celularEmisor->asignarCelularVinculado(celularReceptor);
		celularReceptor->asignarCelularVinculado(celularEmisor);
		celularEmisor->obtenerActividad()->aumentarRealizadas();
		celularReceptor->obtenerActividad()->aumentarRecibidas();
		Nodo<RegistroActividadCelular*>* cursorActividadEmisorEnAntena =  buscarActividadEnAntena(celularEmisor);
		cursorActividadEmisorEnAntena->obtenerDato()->aumentarRealizadas();
		Nodo<RegistroActividadCelular*>* cursorActividadReceptorEnAntena =  buscarActividadEnAntena(celularReceptor);
		cursorActividadReceptorEnAntena->obtenerDato()->aumentarRecibidas();
		registrarLlamadaRealizada(celularEmisor,tiempoDeOperacion);
		registrarLlamadaRecibida(celularReceptor,tiempoDeOperacion);
		registrarComunicacionMismaAntena(celularEmisor, celularReceptor, tiempoDeOperacion, listaComunicaciones);
	}
	else{
		celularEmisor->obtenetAntenaActual()->aumentarCantidadDeLlamadasAnuladas();
	}
}

void registrarLlamadaRealizada(Celular* celularEmisor, unsigned int tiempoDeOperacion){
	RegistroLlamada* nuevaLlamada = new RegistroLlamada;
	nuevaLlamada->asignarCelularInvolucrado(celularEmisor->obtenerCelularVinculado()->obtenerNumero());

	if(!mismaAntena(celularEmisor)){
		string* antenaDelEmisor = new string;
		*antenaDelEmisor = celularEmisor->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(antenaDelEmisor);

		string* antenaDelReceptor = new string;
		*antenaDelReceptor = celularEmisor->obtenerCelularVinculado()->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(antenaDelReceptor);
	}
	else{
		string* unicaAntenaInvolucrada = new string;
		*unicaAntenaInvolucrada = celularEmisor->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(unicaAntenaInvolucrada);
	}

	nuevaLlamada->asignarInicioDeLlamada(tiempoDeOperacion);
	celularEmisor->obtenerListaDeRealizadas()->agregarElemento(nuevaLlamada);
}

void registrarLlamadaRecibida(Celular* celularReceptor, unsigned int tiempoDeOperacion){
	RegistroLlamada* nuevaLlamada = new RegistroLlamada;
	nuevaLlamada->asignarCelularInvolucrado(celularReceptor->obtenerCelularVinculado()->obtenerNumero());

	if(!mismaAntena(celularReceptor)){
		string* antenaDelReceptor = new string;
		*antenaDelReceptor = celularReceptor->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(antenaDelReceptor);

		string* antenaDelEmisor = new string;
		*antenaDelEmisor = celularReceptor->obtenerCelularVinculado()->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(antenaDelEmisor);
	}
	else{
		string* unicaAntenaInvolucrada = new string;
		*unicaAntenaInvolucrada = celularReceptor->obtenerUltimaAntena();
		nuevaLlamada->obtenerListadoDeAntenas()->agregarElemento(unicaAntenaInvolucrada);
	}

	nuevaLlamada->asignarInicioDeLlamada(tiempoDeOperacion);
	celularReceptor->obtenerListaDeRecibidas()->agregarElemento(nuevaLlamada);
}

void registrarComunicacionAntenasDistintas(Celular* celularEmisor, Celular*  celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones){
	Comunicacion* nuevaComunicacion = new Comunicacion;
	nuevaComunicacion->ingresarNumeroEmisor(celularEmisor->obtenerNumero());
	nuevaComunicacion->ingresarNombreAntenaEmisor(celularEmisor->obtenerUltimaAntena());
	nuevaComunicacion->ingresarNumeroReceptor(celularReceptor->obtenerNumero());
	nuevaComunicacion->ingresarNombreAntenaReceptor(celularReceptor->obtenerUltimaAntena());
	nuevaComunicacion->ingresarInicioDeLlamada(tiempoDeOperacion);
	listaComunicaciones.agregarElemento(nuevaComunicacion);

	celularEmisor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->agregarElemento(nuevaComunicacion);
	if(celularEmisor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerTamanio()>celularEmisor->obtenetAntenaActual()->obtenerCantidadDeComunicacionesEstablecidas()){
		celularEmisor->obtenetAntenaActual()->aumentarTotalDeComunicacionesEstablecidas();
	}
	celularEmisor->obtenetAntenaActual()->disminuirComunicacionesDisponibles();

	celularReceptor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->agregarElemento(nuevaComunicacion);
	if(celularReceptor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerTamanio()>celularReceptor->obtenetAntenaActual()->obtenerCantidadDeComunicacionesEstablecidas()){
		celularReceptor->obtenetAntenaActual()->aumentarTotalDeComunicacionesEstablecidas();
	}
	celularReceptor->obtenetAntenaActual()->disminuirComunicacionesDisponibles();
}

void registrarComunicacionMismaAntena(Celular* celularEmisor, Celular*  celularReceptor, unsigned int tiempoDeOperacion, Lista<Comunicacion*>& listaComunicaciones){
	Comunicacion* nuevaComunicacion = new Comunicacion;
	nuevaComunicacion->ingresarNumeroEmisor(celularEmisor->obtenerNumero());
	nuevaComunicacion->ingresarNombreAntenaEmisor(celularEmisor->obtenerUltimaAntena());
	nuevaComunicacion->ingresarNumeroReceptor(celularReceptor->obtenerNumero());
	nuevaComunicacion->ingresarNombreAntenaReceptor(celularReceptor->obtenerUltimaAntena());
	nuevaComunicacion->ingresarInicioDeLlamada(tiempoDeOperacion);
	listaComunicaciones.agregarElemento(nuevaComunicacion);

	celularEmisor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->agregarElemento(nuevaComunicacion);
	if(celularEmisor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerTamanio()>celularEmisor->obtenetAntenaActual()->obtenerCantidadDeComunicacionesEstablecidas()){
		celularEmisor->obtenetAntenaActual()->aumentarTotalDeComunicacionesEstablecidas();
	}
	celularEmisor->obtenetAntenaActual()->disminuirComunicacionesDisponibles();
}

void tratarFin(ifstream& archivo, Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas, Lista<Comunicacion*>& listaComunicaciones){
	unsigned int numeroEmisor;
	unsigned int numeroReceptor;
	unsigned int tiempoDeOperacion;
	archivo >> numeroEmisor >> numeroReceptor >> tiempoDeOperacion;
	Celular* celularEmisor = buscarCelular(numeroEmisor, listaCelulares);
	Celular* celularReceptor = buscarCelular(numeroReceptor, listaCelulares);
		if((existeElCelular(numeroReceptor, listaCelulares))&&(celularEmisor->obtenerCelularVinculado() == celularReceptor)){
			if((celularEmisor->obtenerCelularVinculado()->obtenetAntenaActual()!=0)&&(celularEmisor->obtenetAntenaActual()!=0)){
				analisisDeAntenasInvolucradas(celularEmisor, listaComunicaciones, tiempoDeOperacion, listaCelulares);
			}
			else{
				analizarFinDeLlamadaConUnCelularDesconectado(celularEmisor, listaComunicaciones, tiempoDeOperacion, listaCelulares);
			}
		}
}

void analizarFinDeLlamadaConUnCelularDesconectado(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares){
	if(celularEmisor->obtenetAntenaActual()==0){
		//DEsconectado emisor.
		Nodo<Comunicacion*>* cursorComunicacionEnAntena = buscarEnComunicacionesEstablecidas(celularEmisor);
		Nodo<Comunicacion*>* cursorComunicacionEnEsperaEnAntena = buscarLlamadaEnEspera(celularEmisor);
		Nodo<Comunicacion*>* cursorComunicacionEnLista = buscarEnListaDeComunicaciones(celularEmisor, listaComunicaciones);
		cursorComunicacionEnLista->obtenerDato()->ingresarFinDeLlamada(tiempoDeOperacion);
		finalizarLlamadaEnCelularEmisor(celularEmisor, cursorComunicacionEnLista, tiempoDeOperacion);
		finalizarLlamadaEnCelularReceptor(celularEmisor->obtenerCelularVinculado(), cursorComunicacionEnLista, tiempoDeOperacion);
		finalizarOperacionEnAntenaConectada(celularEmisor->obtenerCelularVinculado()->obtenetAntenaActual(), cursorComunicacionEnAntena, cursorComunicacionEnEsperaEnAntena);
		finalizarLlamadaEnListaDeComunicacion(cursorComunicacionEnLista , listaComunicaciones);
		controlarLlamadasEnEsperaEnAntena(celularEmisor->obtenerCelularVinculado()->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
	else{
		//DEsconectado receptor.
		Nodo<Comunicacion*>* cursorComunicacionEnAntena = buscarEnComunicacionesEstablecidas(celularEmisor->obtenerCelularVinculado());
		Nodo<Comunicacion*>* cursorComunicacionEnEsperaEnAntena = buscarLlamadaEnEspera(celularEmisor->obtenerCelularVinculado());
		Nodo<Comunicacion*>* cursorComunicacionEnLista = buscarEnListaDeComunicaciones(celularEmisor->obtenerCelularVinculado(), listaComunicaciones);
		cursorComunicacionEnLista->obtenerDato()->ingresarFinDeLlamada(tiempoDeOperacion);
		finalizarLlamadaEnCelularReceptor(celularEmisor->obtenerCelularVinculado(), cursorComunicacionEnLista, tiempoDeOperacion);
		finalizarLlamadaEnCelularEmisor(celularEmisor, cursorComunicacionEnLista, tiempoDeOperacion);
		finalizarOperacionEnAntenaConectada(celularEmisor->obtenetAntenaActual(), cursorComunicacionEnAntena, cursorComunicacionEnEsperaEnAntena);
		finalizarLlamadaEnListaDeComunicacion(cursorComunicacionEnLista , listaComunicaciones);
		controlarLlamadasEnEsperaEnAntena(celularEmisor->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
	celularEmisor->obtenerCelularVinculado()->asignarCelularVinculado(0);
	celularEmisor->asignarCelularVinculado(0);
}

Nodo<Comunicacion*>* buscarEnListaDeComunicaciones(Celular* celularAtratar, Lista<Comunicacion*>& listaComunicaciones){
	Nodo<Comunicacion*>* cursorDeComunicaciones = listaComunicaciones.obtenerPrimerNodo();
	while((cursorDeComunicaciones->obtenerDato()->obtenerNumeroEmisor()!=celularAtratar->obtenerNumero())&&(cursorDeComunicaciones->obtenerDato()->obtenerNumeroReceptor()!=celularAtratar->obtenerNumero())){
		cursorDeComunicaciones = cursorDeComunicaciones->obtenerNodoSiguiente();
	}
	return cursorDeComunicaciones;
}

void finalizarLlamadaEnCelularEmisor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion){
	Nodo<RegistroLlamada*>* cursorllamadaRealizada = busquedaLlamadaEnListaDeRealizadas(celularAtratar);
	cursorllamadaRealizada->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
}

void finalizarLlamadaEnCelularReceptor(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion){
	Nodo<RegistroLlamada*>* cursorllamadaRecibida = busquedaLlamadaEnListaRecibidas(celularAtratar);
	cursorllamadaRecibida->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
}

void finalizarOperacionEnAntenaConectada(Antena* antenaAtratar, Nodo<Comunicacion*>* comunicacionEnAntena, Nodo<Comunicacion*>* esperaEnAntena){
	antenaAtratar->obtenerListaDeLlamadasEnEspera()->quitarNodo(esperaEnAntena);
	antenaAtratar->obtenerListaDeOperacionesConcurrentes()->quitarNodo(comunicacionEnAntena);
	antenaAtratar->aumentarComunicacionesDisponibles();
}

void finalizarLlamadaEnListaDeComunicacion(Nodo<Comunicacion*>* comunicacionEnLista ,Lista<Comunicacion*>& listaComunicaciones){
	listaComunicaciones.quitarElemento(comunicacionEnLista->obtenerDato());
}

Nodo<RegistroLlamada*>* busquedaLlamadaEnListaDeRealizadas(Celular* celularAtratar){
	Nodo<RegistroLlamada*>* cursorEnListaDeRealizadas = celularAtratar->obtenerListaDeRealizadas()->obtenerPrimerNodo();
	while(cursorEnListaDeRealizadas->obtenerNodoSiguiente() != 0){
		cursorEnListaDeRealizadas = cursorEnListaDeRealizadas->obtenerNodoSiguiente();
	}
	return cursorEnListaDeRealizadas;
}

Nodo<RegistroLlamada*>* busquedaLlamadaEnListaRecibidas(Celular* celularAtratar){
	Nodo<RegistroLlamada*>* cursorEnListaDeRealizadas = celularAtratar->obtenerListaDeRecibidas()->obtenerPrimerNodo();
	while(cursorEnListaDeRealizadas->obtenerNodoSiguiente() != 0){
		cursorEnListaDeRealizadas = cursorEnListaDeRealizadas->obtenerNodoSiguiente();
	}
	return cursorEnListaDeRealizadas;
}

void controlarLlamadasEnEsperaEnAntena(Antena* antenaAtratar, unsigned int nuevoTiempoDeInicio, Lista<Celular*>& listaCelulares){
	bool hayLlamadasEnEsperaParaContinuar = false;
	Nodo<Comunicacion*>* cursorEnListaDeEspera = antenaAtratar->obtenerListaDeLlamadasEnEspera()->obtenerPrimerNodo();
	while(cursorEnListaDeEspera!=0){
		if((cursorEnListaDeEspera->obtenerDato()->obtenerNombreAntenaEmisor()!="")&&(cursorEnListaDeEspera->obtenerDato()->obtenerNombreAntenaReceptor()!="")){
			hayLlamadasEnEsperaParaContinuar = true;
			break;
		}
		cursorEnListaDeEspera = cursorEnListaDeEspera->obtenerNodoSiguiente();
	}
	bool ContinuarLlamadaEncontrada = true;
	Nodo<Comunicacion*>* cursorEnComunicacionesConcurrentesEnAntena = antenaAtratar->obtenerListaDeOperacionesConcurrentes()->obtenerPrimerNodo();
	while((cursorEnComunicacionesConcurrentesEnAntena!=0)&&(cursorEnListaDeEspera!=0)){
		if(cursorEnComunicacionesConcurrentesEnAntena->obtenerDato()==cursorEnListaDeEspera->obtenerDato()){
			ContinuarLlamadaEncontrada = false;
			break;
		}
		cursorEnComunicacionesConcurrentesEnAntena = cursorEnComunicacionesConcurrentesEnAntena->obtenerNodoSiguiente();
	}
	if((hayLlamadasEnEsperaParaContinuar)&&(ContinuarLlamadaEncontrada)){
		unsigned int numeroEmisorEnEspera = cursorEnListaDeEspera->obtenerDato()->obtenerNumeroEmisor();
		Celular* emisorEnEspera = buscarCelular(numeroEmisorEnEspera, listaCelulares);
		cursorEnListaDeEspera->obtenerDato()->ingresarInicioDeLlamada(nuevoTiempoDeInicio);
		if(emisorEnEspera->obtenerUltimaAntena()==antenaAtratar->obtenerNombreDeAntena()){
			Nodo<Comunicacion*>* llamadaEnEsperaEnAntenaReceptor = buscarLlamadaEnEspera(emisorEnEspera);
			emisorEnEspera->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(llamadaEnEsperaEnAntenaReceptor);
		}
		else{
			Nodo<Comunicacion*>* llamadaEnEsperaEnAntenaEmisor = buscarLlamadaEnEspera(emisorEnEspera->obtenerCelularVinculado());
			emisorEnEspera->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(llamadaEnEsperaEnAntenaEmisor);
		}
		antenaAtratar->obtenerListaDeOperacionesConcurrentes()->agregarElemento(cursorEnListaDeEspera->obtenerDato());
		antenaAtratar->obtenerListaDeLlamadasEnEspera()->quitarNodo(cursorEnListaDeEspera);
		antenaAtratar->disminuirComunicacionesDisponibles();
		string* antenaAagregarAlEmisor = new string;
		*antenaAagregarAlEmisor = antenaAtratar->obtenerNombreDeAntena();
		Nodo<RegistroLlamada*>* llamadaRealizadaAagregarAntena = busquedaLlamadaEnListaDeRealizadas(emisorEnEspera);
		llamadaRealizadaAagregarAntena->obtenerDato()->obtenerListadoDeAntenas()->agregarElemento(antenaAagregarAlEmisor);
		Nodo<RegistroLlamada*>* llamadaRecibidaAagregarAntena = busquedaLlamadaEnListaRecibidas(emisorEnEspera->obtenerCelularVinculado());
		string* antenaAagregarAlReceptor = new string;
		*antenaAagregarAlReceptor = antenaAtratar->obtenerNombreDeAntena();
		llamadaRecibidaAagregarAntena->obtenerDato()->obtenerListadoDeAntenas()->agregarElemento(antenaAagregarAlReceptor);
	}
}

void analisisDeAntenasInvolucradas(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares){
	if(celularEmisor->obtenetAntenaActual() != celularEmisor->obtenerCelularVinculado()->obtenetAntenaActual()){
		//En antenas distintas
		analizarFinalizacionEnAntenasDistintas(celularEmisor, listaComunicaciones, tiempoDeOperacion, listaCelulares);
	}
	else{
		//En antenas iguales
		analizarFinalizacionEnAntenasIguales(celularEmisor, listaComunicaciones, tiempoDeOperacion);
		controlarLlamadasEnEsperaEnAntena(celularEmisor->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
	celularEmisor->obtenerCelularVinculado()->asignarCelularVinculado(0);
	celularEmisor->asignarCelularVinculado(0);
}

void analizarFinalizacionEnAntenasIguales(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion){
	Nodo<Comunicacion*>* cursorDeComunicacionEstablecida = buscarEnListaDeComunicaciones(celularEmisor, listaComunicaciones);
	unsigned int tiempoAagregar = tiempoDeOperacion-cursorDeComunicacionEstablecida->obtenerDato()->obtenerInicioDeLlamada();
	Nodo<Comunicacion*>* cursorDeComunicacionEnAntena = buscarEnComunicacionesEstablecidas(celularEmisor);
	cursorDeComunicacionEstablecida->obtenerDato()->ingresarFinDeLlamada(tiempoDeOperacion);
	Nodo<RegistroActividadCelular*>* cursorActividadDelEmisorEnAntena = buscarActividadEnAntena(celularEmisor);
	cursorActividadDelEmisorEnAntena->obtenerDato()->aumentarTiempoRealizadas(tiempoAagregar);
	Nodo<RegistroActividadCelular*>* cursorActividadDelEmisor = buscarActividadEnAntena(celularEmisor);
	cursorActividadDelEmisor->obtenerDato()->aumentarTiempoRealizadas(tiempoAagregar);
	Nodo<RegistroActividadCelular*>* cursorActividadDelReceptorEnAntena = buscarActividadEnAntena(celularEmisor->obtenerCelularVinculado());
	cursorActividadDelReceptorEnAntena->obtenerDato()->aumentarTiempoRecibidas(tiempoAagregar);
	Nodo<RegistroActividadCelular*>* cursorActividadDelReceptor = buscarActividadEnAntena(celularEmisor->obtenerCelularVinculado());
	cursorActividadDelReceptor->obtenerDato()->aumentarTiempoRecibidas(tiempoAagregar);
	celularEmisor->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorDeComunicacionEnAntena);
	celularEmisor->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
	Nodo<RegistroLlamada*>* cursorLlamadaRezalizada = busquedaLlamadaEnListaDeRealizadas(celularEmisor);
	cursorLlamadaRezalizada->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
	Nodo<RegistroLlamada*>* cursorLlamadaRecibida = busquedaLlamadaEnListaRecibidas(celularEmisor->obtenerCelularVinculado());
	cursorLlamadaRecibida->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
	listaComunicaciones.quitarElemento(cursorDeComunicacionEstablecida->obtenerDato());
}

void analizarFinalizacionEnAntenasDistintas(Celular* celularEmisor, Lista<Comunicacion*>& listaComunicaciones, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares){
	Nodo<Comunicacion*>* cursorDeComunicacionEstablecida = buscarEnListaDeComunicaciones(celularEmisor, listaComunicaciones);
	if(cursorDeComunicacionEstablecida->obtenerDato()->obtenerInicioDeLlamada()!=0){
		//LLAMADA QUE EN PROGRESO
		cursorDeComunicacionEstablecida->obtenerDato()->ingresarFinDeLlamada(tiempoDeOperacion);
		analizarFinalizacionDeRealizadaEnDosAntenas(celularEmisor, cursorDeComunicacionEstablecida, tiempoDeOperacion);
		controlarLlamadasEnEsperaEnAntena(celularEmisor->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
		controlarLlamadasEnEsperaEnAntena(celularEmisor->obtenerCelularVinculado()->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
	else{
		//LLAMADA QUE EN ESPERA
		analizarFinalizacionEnEsperaEnDosAntenas(celularEmisor, cursorDeComunicacionEstablecida, tiempoDeOperacion, listaCelulares);
	}
	Nodo<RegistroLlamada*>* cursorLlamadaRezalizada = busquedaLlamadaEnListaDeRealizadas(celularEmisor);
	cursorLlamadaRezalizada->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
	Nodo<RegistroLlamada*>* cursorLlamadaRecibida = busquedaLlamadaEnListaRecibidas(celularEmisor->obtenerCelularVinculado());
	cursorLlamadaRecibida->obtenerDato()->asignarFinDeLlamada(tiempoDeOperacion);
	listaComunicaciones.quitarElemento(cursorDeComunicacionEstablecida->obtenerDato());
}

void analizarFinalizacionDeRealizadaEnDosAntenas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion){
	unsigned int tiempoAagregar = tiempoDeOperacion-comunicacionEnLista->obtenerDato()->obtenerInicioDeLlamada();

	Nodo<RegistroActividadCelular*>* cursorActividadDelEmisorEnAntena = buscarActividadEnAntena(celularAtratar);
	cursorActividadDelEmisorEnAntena->obtenerDato()->aumentarTiempoRealizadas(tiempoAagregar);
	celularAtratar->obtenerActividad()->aumentarTiempoRealizadas(tiempoAagregar);

	Nodo<RegistroActividadCelular*>* cursorActividadDelReceptorEnAntena = buscarActividadEnAntena(celularAtratar->obtenerCelularVinculado());
	cursorActividadDelReceptorEnAntena->obtenerDato()->aumentarTiempoRecibidas(tiempoAagregar);
	celularAtratar->obtenerCelularVinculado()->obtenerActividad()->aumentarTiempoRecibidas(tiempoAagregar);

	Nodo<Comunicacion*>* cursorDeComunicionEnAntenaEmisor = buscarEnComunicacionesEstablecidas(celularAtratar->obtenerCelularVinculado());
	celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorDeComunicionEnAntenaEmisor);
	celularAtratar->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
	Nodo<Comunicacion*>* cursorDeComunicionEnAntenaReceptor = buscarEnComunicacionesEstablecidas(celularAtratar);
	celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorDeComunicionEnAntenaReceptor);
	celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
}

void analizarFinalizacionEnEsperaEnDosAntenas(Celular* celularAtratar, Nodo<Comunicacion*>* comunicacionEnLista, unsigned int tiempoDeOperacion, Lista<Celular*>& listaCelulares){
	Nodo<Comunicacion*>* cursorBusquedaDeLlamadaEnAntenaEmisor = celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->obtenerPrimerNodo();
	while(cursorBusquedaDeLlamadaEnAntenaEmisor!=0){
		if(cursorBusquedaDeLlamadaEnAntenaEmisor->obtenerDato()==comunicacionEnLista->obtenerDato()){
			break;
		}
		cursorBusquedaDeLlamadaEnAntenaEmisor = cursorBusquedaDeLlamadaEnAntenaEmisor->obtenerNodoSiguiente();
	}
	Nodo<Comunicacion*>* cursorEnListaDeEsperaAntenaEmisor = buscarLlamadaEnEspera(celularAtratar->obtenerCelularVinculado());
	celularAtratar->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(cursorEnListaDeEsperaAntenaEmisor);
	Nodo<Comunicacion*>* cursorEnListaDeEsperaAntenaReceptor = buscarLlamadaEnEspera(celularAtratar);
	celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeLlamadasEnEspera()->quitarNodo(cursorEnListaDeEsperaAntenaReceptor);
	if(cursorBusquedaDeLlamadaEnAntenaEmisor == 0){
		//Antena Emisor Tiene el registro solo en la lista de espera.
		Nodo<Comunicacion*>* cursorBusquedaDeLlamadaEnAntenaReceptor = buscarEnComunicacionesEstablecidas(celularAtratar);
		celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorBusquedaDeLlamadaEnAntenaReceptor);
		celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
		controlarLlamadasEnEsperaEnAntena(celularAtratar->obtenerCelularVinculado()->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
	else{
		//Antena Receptor Tiene el registro solo en la lista de espera.
		Nodo<Comunicacion*>* cursorBusquedaDeLlamadaEnAntenaEmisor = buscarEnComunicacionesEstablecidas(celularAtratar->obtenerCelularVinculado());
		celularAtratar->obtenetAntenaActual()->obtenerListaDeOperacionesConcurrentes()->quitarNodo(cursorBusquedaDeLlamadaEnAntenaEmisor);
		celularAtratar->obtenetAntenaActual()->aumentarComunicacionesDisponibles();
		controlarLlamadasEnEsperaEnAntena(celularAtratar->obtenetAntenaActual(), tiempoDeOperacion, listaCelulares);
	}
}
