#include "ActividadDelCelular.h"

ActividadDelCelular::ActividadDelCelular(unsigned int numeroDeCelular){
	this->numeroDeCelular = numeroDeCelular;
	this->cantidadDeLlamadasRealizadas = 0;
	this->duracionTotalDeLlamadasRealizadas = 0;
	this->llamadasRealizadasOcupadas = 0;
	this->cantidadDeLlamadasRecibidas = 0;
	this->duracionTotalDeLlamadasRecibidas = 0;
	this->llamadasRecibidasOcupadas = 0;
}

void ActividadDelCelular::aumentarCantidadDeRealizadas(){
	this->cantidadDeLlamadasRealizadas++;
}

void ActividadDelCelular::aumentarTiempoDeRealizadas(unsigned int duracionDeLlamadaRealizada){
	this->duracionTotalDeLlamadasRealizadas += duracionDeLlamadaRealizada;
}

void ActividadDelCelular::aumentarCantidadDeRealizadasOcupadas(){
	this->llamadasRealizadasOcupadas++;
}

void ActividadDelCelular::aumentarCantidadDeRecibidas(){
	this->cantidadDeLlamadasRecibidas++;
}

void ActividadDelCelular::aumentarTiempoDeRecibidas(unsigned int duracionDeLlamadaRecibida){
	this->duracionTotalDeLlamadasRecibidas += duracionDeLlamadaRecibida;
}

void ActividadDelCelular::aumentarCantidadDeRecibidasOcupadas(){
	this->llamadasRecibidasOcupadas++;
}

unsigned int ActividadDelCelular::obtenerNumeroDeCelular(){
	return this->numeroDeCelular;
}

unsigned int ActividadDelCelular::obtenerCantidadDeRealizadas(){
	return this->cantidadDeLlamadasRealizadas;
}

unsigned int ActividadDelCelular::obtenerTiempoDeRealizadas(){
	return this->duracionTotalDeLlamadasRealizadas;
}

unsigned int ActividadDelCelular::obtenerCantidadDeRealizadasOcupadas(){
	return this->llamadasRealizadasOcupadas;
}

unsigned int ActividadDelCelular::obtenerCantidadDeRecibidas(){
	return this->cantidadDeLlamadasRecibidas;
}

unsigned int ActividadDelCelular::obtenerTiempoDeRecibidas(){
	return this->duracionTotalDeLlamadasRecibidas;
}

unsigned int ActividadDelCelular::obtenerCantidadDeRecibidasOcupadas(){
	return this->llamadasRecibidasOcupadas;
}
