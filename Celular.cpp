
#include "Celular.h"

Celular::Celular(unsigned int codigoDeCelular, unsigned int numeroDeCelular){
	this->codigo = codigoDeCelular;
	this->numero = numeroDeCelular;
	this->antenaActual = NULL;
	this->ultimaAntenaConectada = "";
	this->celularVinculado = NULL;
	this->llamadasRealizadas = new Lista<Llamada*>;
	this->llamadasRecibidas = new Lista<Llamada*>;
	this->actividadTotal = new ActividadDelCelular;
	this->mensajesEnviados = new Lista<Mensaje>;
	this->mensajesRecibidos = new Lista<Mensaje>;
	this->mensajesParaProcesar = new Lista<Mensaje>;
}

void Celular::asignarAntenaConectada(Antena* antenaAconectar){
	this->antenaActual = antenaAconectar;
}

void Celular::asignarUltimaAntena(std::string nombreDeAntena){
	this->ultimaAntenaConectada = nombreDeAntena;
}

void Celular::asignarCelularVinculado(Celular* celularAvincular){
	this->celularVinculado = celularAvincular;
}

unsigned int Celular::obtenerCodigo(){
	return this->codigo;
}

unsigned int Celular::obtenerNumero(){
	return this->numero;
}

Antena* Celular::obtenerAntenaActual(){
	return this->antenaActual;
}

std::string Celular::obtenerUltimaAntena(){
	return this->ultimaAntenaConectada;
}

Celular* Celular::obtenerCelularVinculado(){
	return this->celularVinculado;
}

Lista<Llamada*>* Celular::obtenerListaDeLlamadasRealizadas(){
	return this->llamadasRealizadas;
}

Lista<Llamada*>* Celular::obtenerListaDeLlamadasRecibidas(){
	return this->llamadasRecibidas;
}

ActividadDelCelular* Celular::obtenerActividad(){
	return this->actividadTotal;
}

Lista<Mensaje>* Celular::obtenerListaDeMensajesEnviados(){
	return this->mensajesEnviados;
}

Lista<Mensaje>* Celular::obtenerListaDeMensajesRecibidos(){
	return this->mensajesRecibidos;
}

Lista<Mensaje>* Celular::obtenerListaDeMensajesParaProcesar(){
	return this->mensajesParaProcesar;
}

Celular::~Celular(){
	delete this->llamadasRealizadas;
	delete this->llamadasRecibidas;
	delete this->actividadTotal;
	delete this->mensajesEnviados;
	delete this->mensajesRecibidos;
	delete this->mensajesParaProcesar;
}
