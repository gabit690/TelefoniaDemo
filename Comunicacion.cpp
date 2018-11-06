/*
 * Comunicacion.cpp
 *
 *  Created on: 23 de may. de 2016
 *      Author: lnx
 */

#include "Comunicacion.h"

Comunicacion::Comunicacion()
{
	this->celularEmisor = 0;
	this->antenaDelEmisor = "";
	this->celularReceptor = 0;
	this->antenaDelReceptor = "";
	this->inicioDeLlamada = 0;
	this->finDeLlamada = 0;
}

void Comunicacion::ingresarNumeroEmisor(unsigned int numeroEmisor){
	this->celularEmisor = numeroEmisor;
}

void Comunicacion::ingresarNombreAntenaEmisor(std::string nombreAntenaDelEmisor){
	this->antenaDelEmisor = nombreAntenaDelEmisor;
}

void Comunicacion::ingresarNumeroReceptor(unsigned int numeroReceptor){
	this->celularReceptor = numeroReceptor;
}

void Comunicacion::ingresarNombreAntenaReceptor(std::string nombreAntenaDelReceptor){
	this->antenaDelReceptor = nombreAntenaDelReceptor;
}

void Comunicacion::ingresarInicioDeLlamada(unsigned int tiempoDeInicio){
	this->inicioDeLlamada = tiempoDeInicio;
}

void Comunicacion::ingresarFinDeLlamada(unsigned int tiempoDeFinalizacion){
	this->finDeLlamada = tiempoDeFinalizacion;
}

unsigned int Comunicacion::obtenerNumeroEmisor(){
	return this->celularEmisor;
}

std::string Comunicacion::obtenerNombreAntenaEmisor(){
	return this->antenaDelEmisor;
}

unsigned int Comunicacion::obtenerNumeroReceptor(){
	return this->celularReceptor;
}

std::string Comunicacion::obtenerNombreAntenaReceptor(){
	return this->antenaDelReceptor;
}

unsigned int Comunicacion::obtenerInicioDeLlamada(){
	return this->inicioDeLlamada;
}

unsigned int Comunicacion::obtenerFinDeLlamada(){
	return this->finDeLlamada;
}
