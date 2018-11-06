/*
 * Antena.cpp
 *
 *  Created on: 19 de may. de 2016
 *      Author: lnx
 */

#include "Antena.h"

Antena::Antena(){
	this->nombre = "";
	this->comunicacionesSoportadas = 0;
	this->comunicacionesConcurrentes = new Lista<Comunicacion*>;
	this->comunicacionesDisponibles = 0;
	this->cantidadMaximaDeComunicacionesEstablecidas = 0;
	this->cantidadDeLlamadasAnuladas = 0;
	this->llamadasEnEspera = new Lista<Comunicacion*>;
	this->actividadRegistrada = new Lista<RegistroActividadCelular*>;
}

void Antena::asignarNombre(std::string nombreDeAntena){
	this->nombre = nombreDeAntena;
}

void Antena::asignarCantidadDeOperacionesSoportadas(unsigned int operacionesSoportadas){
	this->comunicacionesSoportadas = operacionesSoportadas;
}

void Antena::asignarComunicacionesDisponibles(unsigned int cantidadDeDisponibles){
	this->comunicacionesDisponibles = cantidadDeDisponibles;
}

void Antena::aumentarComunicacionesDisponibles(){
	this->comunicacionesDisponibles++;
}

void Antena::disminuirComunicacionesDisponibles(){
	this->comunicacionesDisponibles--;
}

void Antena::aumentarTotalDeComunicacionesEstablecidas(){
	this->cantidadMaximaDeComunicacionesEstablecidas++;
}

void Antena::aumentarCantidadDeLlamadasAnuladas(){
	this->cantidadDeLlamadasAnuladas++;
}

std::string Antena::obtenerNombreDeAntena(){
	return this->nombre;
}

unsigned int Antena::obtenerComunicacionesSoportadas(){
	return this->comunicacionesSoportadas;
}

Lista<Comunicacion*>* Antena::obtenerListaDeOperacionesConcurrentes(){
	return this->comunicacionesConcurrentes;
}

unsigned int Antena::obtenerOperacionesDisponibles(){
	return this->comunicacionesDisponibles;
}

unsigned int Antena::obtenerCantidadDeComunicacionesEstablecidas(){
	return this->cantidadMaximaDeComunicacionesEstablecidas;
}

unsigned int Antena::obtenerCantidadDeComunicacionesAnuladas(){
	return this->cantidadDeLlamadasAnuladas;
}

Lista<Comunicacion*>* Antena::obtenerListaDeLlamadasEnEspera(){
	return this->llamadasEnEspera;
}

Lista<RegistroActividadCelular*>* Antena::obtenerListaDeActividadRegistrada(){
	return this->actividadRegistrada;
}

Antena::~Antena(){
	delete this->comunicacionesConcurrentes;
	delete this->llamadasEnEspera;
	delete this->actividadRegistrada;
}
