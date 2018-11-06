/*
 * plantilla.h
 *
 *  Created on: 5 de may. de 2016
 *      Author: lnx
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "Nodo.h"

template<typename Dato>

/* Estructura dinamica ordenada de elementos de forma posicional
 * Los nodos estan conectados mediante un enlace simple.
 */
class Lista{
private:
	Nodo<Dato>* primerNodo;
	unsigned int tamanio;
public:
	/* PRE: -
	 * POST: Crea una lista con 0 elementos que apunta a NULL
	 */
	Lista()
	{
		this->primerNodo = 0;
		this->tamanio = 0;
	}
	/* PRE: Lista creada, no vacia.
	 * POST: Devuelve la direccion del primer Nodo.
	 */
	Nodo<Dato>* obtenerPrimerNodo(){
		return this->primerNodo;
	}
	/* PRE: La lista esta creada.
	 * POST: Devuelve true si esta vacia en caso contrario devuelve false.
	 */
	bool listaVacia()
	{
		return (this->primerNodo == 0);
	}
	/* PRE: La lista esta creada.
	 * POST: Agrega al final de la lista un nuevo nodo que contiene
	 * la direccion del nuevo elemento y aumenta el tamanio en 1.
	 */
	void agregarElemento(Dato elementoNuevo)
	{
		Nodo<Dato>* nuevoElemento = new Nodo<Dato>;

		nuevoElemento->asignarDato(elementoNuevo);
		if (this->primerNodo)
		{
			Nodo<Dato>* elementoDeLaLista = this->primerNodo;
			while(elementoDeLaLista->obtenerNodoSiguiente())
			{
				elementoDeLaLista = elementoDeLaLista->obtenerNodoSiguiente();
			}
			elementoDeLaLista->conectarNodo(nuevoElemento);
		}
		else
		{
			this->primerNodo = nuevoElemento;
		}
		this->tamanio++;
	}
	/* PRE: La lista esta creada y nodo a sacar tien que pertenecer a la lista.
	* POST: Quita de la lista el nodo apuntado y reduce el tamanio en 1.
	*/
	void quitarNodo(Nodo<Dato>* nodoASacar){
		Nodo<Dato>* nodoAnteriorAlBuscado =  this->primerNodo;
		if(nodoAnteriorAlBuscado != nodoASacar)
		{
/*
			do{
				nodoAnteriorAlBuscado = nodoAnteriorAlBuscado->obtenerNodoSiguiente();
			}while(nodoAnteriorAlBuscado->obtenerNodoSiguiente() != nodoASacar);
			nodoAnteriorAlBuscado->conectarNodo(nodoASacar->obtenerNodoSiguiente());

*/
			while(nodoAnteriorAlBuscado->obtenerNodoSiguiente() != nodoASacar){
				nodoAnteriorAlBuscado = nodoAnteriorAlBuscado->obtenerNodoSiguiente();
			}
			nodoAnteriorAlBuscado->conectarNodo(nodoASacar->obtenerNodoSiguiente());
		}
		else
		{
			this->primerNodo = nodoASacar->obtenerNodoSiguiente();

		}
		delete nodoASacar;
		this->tamanio--;
	}
	/* PRE: La lista esta creada.
	* POST: Quita de la lista el nodo apuntado liberando los recursos pedidos por el mismo y reduce el tamanio en 1.
	*/
	void quitarElemento(Dato elementoParaSacar)
	{
		Nodo<Dato>* nodoAnteriorAlBuscado = this->primerNodo;
		Nodo<Dato>* nodoParaQuitar =  this->primerNodo;
		if(nodoAnteriorAlBuscado->obtenerDato()!= elementoParaSacar)
		{
			while(nodoParaQuitar->obtenerDato() != elementoParaSacar)
			{
				nodoAnteriorAlBuscado = nodoParaQuitar;
				nodoParaQuitar = nodoParaQuitar->obtenerNodoSiguiente();
			}
			nodoAnteriorAlBuscado->conectarNodo(nodoParaQuitar->obtenerNodoSiguiente());
		}
		else
		{
			this->primerNodo = nodoAnteriorAlBuscado->obtenerNodoSiguiente();

		}
		delete nodoParaQuitar->obtenerDato();
		delete nodoParaQuitar;
		this->tamanio--;
	}
	/* PRE: Lista creada.
	 * POST: Devuelve la cantidad del tamaño de la lista.
	 */
	unsigned int obtenerTamanio()
	{
		return this->tamanio;
	}
	/* PRE: Lista creada.
	 * POST: Libera todos los recursos asociados a la lista.
	 */
	~Lista()
	{
		while(!this->listaVacia())
		{
			Nodo<Dato>* eliminador = this->primerNodo;
			this->primerNodo = eliminador->obtenerNodoSiguiente();
			eliminador->conectarNodo(0);
			delete eliminador->obtenerDato();
			delete eliminador;
		}
	}
};

#endif /* LISTA_H_ */
