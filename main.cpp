/*
 * main.cpp
 *
 *  Created on: 19 de may. de 2016
 *      Author: lnx
 */

#include "Funciones.h"
#include "FuncionesParaInformes.h"
#include <string>

using namespace std;

int main(){

	string respuesta;
	ifstream archivoAprocesar;

	respuesta = ingresarNombreDelArchivo(archivoAprocesar);

	Lista<Celular*> listaDeCelulares;
	Lista<Antena*> listaDeAntenas;

	procesarArchivo(archivoAprocesar, listaDeCelulares, listaDeAntenas);
	archivoAprocesar.close();

	char tareaElegida;
	do{
		tareaElegida = ingresarTarea();
		realizarTarea(tareaElegida, listaDeCelulares, listaDeAntenas);
	}while(tareaElegida!='o');

	return 0;
}
