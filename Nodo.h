/*
 * Nodo.h
 *
 *  Created on: 8 de may. de 2016
 *      Author: lnx
 */

#ifndef NODO_H_
#define NODO_H_

template <typename Dato>

/* Estructura usada para contener datos y vincularse con otros del mismo tipo.
 * El tipo de dato se define en tiempo de compilacion.
 * Cada nodo se une a otro nodo o a ningun otro tipo de elemento.
 */
class Nodo
{
private:
	Dato dato;
	Nodo<Dato>* siguienteElemento;
public:
	/* Pre: -
	 * Post: Crea un nodo con el dato iniciado en 0 que apunta a NULL.
	 */
	Nodo()
	{
		this->dato = 0;
		this->siguienteElemento = 0;
	}
	/* Pre: nodo creado.
	 * Post: Se obtine un nodo cuyo dato es el ingresado.
	 */
	void asignarDato(Dato datoIngresado)
	{
		this->dato = datoIngresado;
	}
	/* Pre: nodo creado.
	* Post: Devuelve el dato contenido en el nodo.
	*/
	Dato obtenerDato()
	{
		return this->dato;
	}
	/* Pre: nodo creado
	* Post: Establece una union del nodo con otroNodo.
	*/
	void conectarNodo(Nodo<Dato>* otroNodo)
	{
		this->siguienteElemento = otroNodo;
	}
	/* Pre: nodo creado.
	* Post: Establece una union del nodo con otroNodo.
	*/
	Nodo<Dato>* obtenerNodoSiguiente()
	{
		return this->siguienteElemento;
	}
};

#endif /* NODO_H_ */
