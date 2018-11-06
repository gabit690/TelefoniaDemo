/*
 * RegistroLLamada.cpp
 *
 *  Created on: 23 de may. de 2016
 *      Author: lnx
 */

#include "RegistroLlamada.h"

RegistroLlamada::RegistroLlamada(){
	this->celularInvolucrado = 0;
	this->antenasInvolucradas = new Lista<std::string*>;
	this->inicioDeLlamada = 0;
	this->finDeLlamada = 0;
}

void RegistroLlamada::asignarCelularInvolucrado(unsigned int numeroDeCelular){
	this->celularInvolucrado = numeroDeCelular;
}

void RegistroLlamada::asignarInicioDeLlamada(unsigned int tiempoDeInicio){
	this->inicioDeLlamada = tiempoDeInicio;
}

void RegistroLlamada::asignarFinDeLlamada(unsigned int tiempoDeFinalizacion){
	this->finDeLlamada = tiempoDeFinalizacion;
}

unsigned int RegistroLlamada::obtenerCelularInvolucrado(){
	return this->celularInvolucrado;
}

Lista<std::string*>* RegistroLlamada::obtenerListadoDeAntenas(){
	return this->antenasInvolucradas;
}

unsigned int RegistroLlamada::obtenerTiempoDeInicio(){
	return this->inicioDeLlamada;
}

unsigned int RegistroLlamada::obtenerTiempoDeFinalizacion(){
	return this->finDeLlamada;
}

RegistroLlamada::~RegistroLlamada(){
	delete this->antenasInvolucradas;
}
