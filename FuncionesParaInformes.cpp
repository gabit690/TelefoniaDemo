/*
 * FuncionesParaInformes.cpp
 *
 *  Created on: 10 de jun. de 2016
 *      Author: lnx
 */

#include "FuncionesParaInformes.h"
using namespace std;





unsigned int elegirPrimerCelular(Lista<Celular*>& listaCelulares){
	unsigned int eleccionDelUsuario;
	bool validezDeLaEleccion = false;

	do{
		mostrarCelularesDelSistema(listaCelulares);
		cout << ">>> Ingrese el codigo que corresponde al PRIMER numero de celular que quiere procesar." << endl;
		cout << "Su respuesta: ";
		cin  >> eleccionDelUsuario;
		cin.ignore(256,'\n');
		if((eleccionDelUsuario!=0)&&(eleccionDelUsuario<=listaCelulares.obtenerTamanio())){
			validezDeLaEleccion = true;
		}
		else{
			cout << "!!! Su eleccion ha sido incorrecta !!!" << endl << endl;
		}
		cout << "Presione la tecla ENTER para continuar...";
		cin.get();
	}while(!validezDeLaEleccion);
	return eleccionDelUsuario;
}

unsigned int elegirSegundoCelular(Lista<Celular*>& listaCelulares, unsigned int primerCelularElegido){
	unsigned int eleccionDelUsuario;
	bool validezDeLaEleccion = false;
	do{
		mostrarCelularesDelSistema(listaCelulares);
		cout << ">>> Ingrese el codigo que corresponde al SEGUNDO numero de celular que quiere procesar." << endl;
		cout << "Su respuesta: ";
		cin  >> eleccionDelUsuario;
		cin.ignore(256,'\n');
		if((eleccionDelUsuario!=0)&&(eleccionDelUsuario<=listaCelulares.obtenerTamanio())){
			if(eleccionDelUsuario!=primerCelularElegido){
				validezDeLaEleccion = true;
			}
			else{
				cout << "!!! Debe ingresar un numero de codigo diferente al PRIMERO !!!." << endl;
			}
		}
		else{
			cout << "!!! Su eleccion ha sido incorrecta !!!" << endl << endl;
		}
		cout << "Presione la tecla ENTER para continuar...";
		cin.get();
	}while(!validezDeLaEleccion);
	return eleccionDelUsuario;
}

Celular* buscarCelularPorCodigo(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares){
	Celular* celularBuscado = 0;
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	while(cursorEnListaDeCelulares->obtenerDato()->obtenerCodigo()!=codigoDeCelular){
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	celularBuscado = cursorEnListaDeCelulares->obtenerDato();
	return celularBuscado;
}

void procesarLlamadasEntreLosCelulares(Celular* eleccion1, Celular* eleccion2, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, unsigned int& numeroDeVecesOcupado, Lista<std::string*>* antenasUtilizadas){

	recorrerListaDeLlamadasRealizadasPorElPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeRealizadas(), eleccion2->obtenerNumero(), numeroDeLlamadas, tiempoHablado, antenasUtilizadas);
	recorrerListaDeLlamadasRecibidasPorElPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeRecibidas(), eleccion2->obtenerNumero(), numeroDeLlamadas, tiempoHablado, antenasUtilizadas);
	recorrerListaDeLlamadasRealizadasOcupadasDelPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeNumerosQueDieronOcupadoEnRealizadas(), eleccion2->obtenerNumero(), numeroDeVecesOcupado);
	recorrerListaDeLlamadasRecibidasOcupadasDelPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas(), eleccion2->obtenerNumero(), numeroDeVecesOcupado);
}

void recorrerListaDeLlamadasRealizadasPorElPrimerCelularYobtenerDatos(Lista<RegistroLlamada*>* listaDeRealizadas, unsigned int numeroCelularAComparar, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, Lista<std::string*>* antenasUtilizadas){
	Nodo<RegistroLlamada*>* cursorEnListaDeRealizadas = listaDeRealizadas->obtenerPrimerNodo();
	while(cursorEnListaDeRealizadas!=0){
		if(cursorEnListaDeRealizadas->obtenerDato()->obtenerCelularInvolucrado()==numeroCelularAComparar){
			numeroDeLlamadas++;
			tiempoHablado+=(cursorEnListaDeRealizadas->obtenerDato()->obtenerTiempoDeFinalizacion()-cursorEnListaDeRealizadas->obtenerDato()->obtenerTiempoDeInicio());
			Lista<std::string*>* listaDeNombresDeAntenasQueIntervinieron = cursorEnListaDeRealizadas->obtenerDato()->obtenerListadoDeAntenas();
			chequearAntenasInvolucradas( listaDeNombresDeAntenasQueIntervinieron, antenasUtilizadas);
		}
		cursorEnListaDeRealizadas = cursorEnListaDeRealizadas->obtenerNodoSiguiente();
	}
}

void chequearAntenasInvolucradas(Lista<std::string*>* listaDeAntenasDelRegistro, Lista<std::string*>* antenasUtilizadas){
	Nodo<string*>* cursorEnListaDeAntenasInvolucradasEnElRegistro = listaDeAntenasDelRegistro->obtenerPrimerNodo();
	while(cursorEnListaDeAntenasInvolucradasEnElRegistro!=0){
		if(!antenaInvolucradaYaFueAcumulada(*cursorEnListaDeAntenasInvolucradasEnElRegistro->obtenerDato(), antenasUtilizadas)){
			string* nombreDeAntenaAagregar = new string;
			*nombreDeAntenaAagregar = *cursorEnListaDeAntenasInvolucradasEnElRegistro->obtenerDato();
			antenasUtilizadas->agregarElemento(nombreDeAntenaAagregar);
		}
		cursorEnListaDeAntenasInvolucradasEnElRegistro = cursorEnListaDeAntenasInvolucradasEnElRegistro->obtenerNodoSiguiente();
	}
}

bool antenaInvolucradaYaFueAcumulada(string nombreDeLaAntenaAbuscar,Lista<std::string*>* antenasUtilizadas){
	Nodo<string*>* cursorEnListaDeAntenasInvolucradas = antenasUtilizadas->obtenerPrimerNodo();
	bool antenaEncontrada = false;
	while(cursorEnListaDeAntenasInvolucradas!=0){
		if(*cursorEnListaDeAntenasInvolucradas->obtenerDato()==nombreDeLaAntenaAbuscar){
			antenaEncontrada = true;
			break;
		}
		cursorEnListaDeAntenasInvolucradas = cursorEnListaDeAntenasInvolucradas->obtenerNodoSiguiente();
	}
	return antenaEncontrada;
}

void recorrerListaDeLlamadasRecibidasPorElPrimerCelularYobtenerDatos(Lista<RegistroLlamada*>* listaDeRecibidas, unsigned int numeroCelularAComparar, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, Lista<std::string*>* antenasUtilizadas){
	Nodo<RegistroLlamada*>* cursorEnListaDeRecibidas = listaDeRecibidas->obtenerPrimerNodo();
	while(cursorEnListaDeRecibidas!=0){
		if(cursorEnListaDeRecibidas->obtenerDato()->obtenerCelularInvolucrado()==numeroCelularAComparar){
			numeroDeLlamadas++;
			tiempoHablado+=(cursorEnListaDeRecibidas->obtenerDato()->obtenerTiempoDeFinalizacion()-cursorEnListaDeRecibidas->obtenerDato()->obtenerTiempoDeInicio());
			Lista<std::string*>* listaDeNombresDeAntenasQueIntervinieron = cursorEnListaDeRecibidas->obtenerDato()->obtenerListadoDeAntenas();
			chequearAntenasInvolucradas( listaDeNombresDeAntenasQueIntervinieron, antenasUtilizadas);
		}
		cursorEnListaDeRecibidas = cursorEnListaDeRecibidas->obtenerNodoSiguiente();
	}
}

void recorrerListaDeLlamadasRealizadasOcupadasDelPrimerCelularYobtenerDatos(Lista<unsigned int*>* listaDeOcupadasRealizadas, unsigned int numeroCelularAcomparar, unsigned int& cantidadDeVecesOcupado){
	Nodo<unsigned int*>* cursorEnListaDeRealizadasOcupadas = listaDeOcupadasRealizadas->obtenerPrimerNodo();
	while(cursorEnListaDeRealizadasOcupadas!=0){
		if(*cursorEnListaDeRealizadasOcupadas->obtenerDato()==numeroCelularAcomparar){
			cantidadDeVecesOcupado++;
		}
		cursorEnListaDeRealizadasOcupadas = cursorEnListaDeRealizadasOcupadas->obtenerNodoSiguiente();
	}
}

void recorrerListaDeLlamadasRecibidasOcupadasDelPrimerCelularYobtenerDatos(Lista<unsigned int*>* listaDeOcupadasRecibidas, unsigned int numeroCelularAcomparar, unsigned int& cantidadDeVecesOcupado){
	Nodo<unsigned int*>* cursorEnListaDeRecibidasOcupadas = listaDeOcupadasRecibidas->obtenerPrimerNodo();
	while(cursorEnListaDeRecibidasOcupadas!=0){
		if(*cursorEnListaDeRecibidasOcupadas->obtenerDato()==numeroCelularAcomparar){
			cantidadDeVecesOcupado++;
		}
		cursorEnListaDeRecibidasOcupadas = cursorEnListaDeRecibidasOcupadas->obtenerNodoSiguiente();
	}
}

void celularQueMasHablo(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeDuracionEnLlamadasRealizadasPorAlgunCelular = numeroMaximoDeDuracionEnLlamadasRealizadasEnListaDeCelulares(listaCelulares);
	imprimirCelularesQueMasHablaronEnElSistema(listaCelulares, numeroMaximoDeDuracionEnLlamadasRealizadasPorAlgunCelular);

	imprimirCelularesQueMasHablaronEnCadaAntena(listaAntenas);
}

unsigned int numeroMaximoDeDuracionEnLlamadasRealizadasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeDuracionEnLlamadasRealizadas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRealizadas()>cantidadMaximaDeDuracionEnLlamadasRealizadas){
			cantidadMaximaDeDuracionEnLlamadasRealizadas = cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRealizadas();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRealizadas;
}

void imprimirCelularesQueMasHablaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDuracionMaximaEnRealizadas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad maxima de duracion total en llamadas Realizadas: " << cantidadDuracionMaximaEnRealizadas << endl;
	cout << "***** CELULAR QUE MAS HABLO EN TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRealizadas()==cantidadDuracionMaximaEnRealizadas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesQueMasHablaronEnCadaAntena(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULAR QUE MAS HABLO EN CADA ANTENA *****" << endl << endl;
	cout << "ANTENA " << " CELULAR " << "  DURACION DE REALIZADAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMaximaDeDuracionEnLlamadasRealizadas = numeroDeDuracionEnLlamadasRealizadasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMaximaDeDuracionEnLlamadasRealizadas!=0){
			imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRealizadasEsLaMayor(cursorEnListaDeAntenas->obtenerDato(), cantidadMaximaDeDuracionEnLlamadasRealizadas);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int numeroDeDuracionEnLlamadasRealizadasEnActividadAntena(Antena* antenaAtratar){
	unsigned int cantidadMaximaDeDuracionEnLlamadasRealizadas = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerTiempoRealizadas() > cantidadMaximaDeDuracionEnLlamadasRealizadas){
			cantidadMaximaDeDuracionEnLlamadasRealizadas = cursorActividadEnAntena->obtenerDato()->obtenerTiempoRealizadas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRealizadas;
}

void imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRealizadasEsLaMayor(Antena* antenaAtratar, unsigned int duracionEnLlamadasRealizadas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerTiempoRealizadas() == duracionEnLlamadasRealizadas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "   ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "               ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerTiempoRealizadas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void celularQueMasLlamo(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeLlamadasRealizadasPorAlgunCelular = numeroMaximoDeLlamadasRealizadasEnListaDeCelulares(listaCelulares);
	imprimirCelularesQueMasLlamaronEnElSistema(listaCelulares, numeroMaximoDeLlamadasRealizadasPorAlgunCelular);

	imprimirCelularesQueMasLlamaronEnCadaAntena(listaAntenas);
}

unsigned int numeroMaximoDeLlamadasRealizadasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeDuracionEnLlamadasRealizadas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRealizadas()>cantidadMaximaDeDuracionEnLlamadasRealizadas){
			cantidadMaximaDeDuracionEnLlamadasRealizadas = cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRealizadas();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRealizadas;
}

void imprimirCelularesQueMasLlamaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDeLlamadasRealizadas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad maxima de llamadas Realizadas: " << cantidadDeLlamadasRealizadas << endl;
	cout << "***** CELULARES QUE MAS LLAMARON EN TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRealizadas()==cantidadDeLlamadasRealizadas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesQueMasLlamaronEnCadaAntena(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULARES QUE MAS LLAMARON EN CADA ANTENA *****" << endl << endl;
	cout << "ANTENA " << " CELULAR " << " CANTIDAD DE REALIZADAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMaximaDeDuracionEnLlamadasRealizadas = cantidadDeLlamadasRealizadasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMaximaDeDuracionEnLlamadasRealizadas!=0){
			imprimirActividadEnAntenaConMayorCantidadDeLlamadasRealizadas(cursorEnListaDeAntenas->obtenerDato(), cantidadMaximaDeDuracionEnLlamadasRealizadas);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int cantidadDeLlamadasRealizadasEnActividadAntena(Antena* antenaAtratar){
	unsigned int cantidadDeLlamadasRealizadas = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadas() > cantidadDeLlamadasRealizadas){
			cantidadDeLlamadasRealizadas = cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return cantidadDeLlamadasRealizadas;
}

void imprimirActividadEnAntenaConMayorCantidadDeLlamadasRealizadas(Antena* antenaAtratar, unsigned int cantidadDeLlamadasRealizadas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadas() == cantidadDeLlamadasRealizadas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "   ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "            ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void celularQueMasLeDioOcupadoSusLlamadasRealizadas(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeLlamadasOcupadasRealizadasEnAlgunCelular = numeroMaximoDeLlamadasRealizadasOcupadasEnListaDeCelulares(listaCelulares);
	imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadas(listaCelulares, numeroMaximoDeLlamadasOcupadasRealizadasEnAlgunCelular);

	imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadasEnAntenas(listaAntenas);
}

unsigned int numeroMaximoDeLlamadasRealizadasOcupadasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeOcupadas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRealizadas()->obtenerTamanio()>cantidadMaximaDeOcupadas){
			cantidadMaximaDeOcupadas = cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRealizadas()->obtenerTamanio();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeOcupadas;
}

void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadas(Lista<Celular*>& listaCelulares, unsigned int cantidadMaximaDeOcupadas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad Maxima De Llamadas Recibidas Ocupadas: " << cantidadMaximaDeOcupadas << endl;
	cout << "***** CELULAR AL QUE MAS LE DIERON OCUPADAS SUS LLAMADAS EN TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas()->obtenerTamanio()==cantidadMaximaDeOcupadas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRealizadasEnAntenas(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULAR QUE MAS LE DIO OCUPADO SUS LLAMADAS EN TODO EL SISTEMA *****" << endl;
	cout << "ANTENA " << " CELULAR " << "  CANTIDAD DE OCUPADAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMayorDeLlamadasOcupadasEnAntena = numeroMaximoDeOcupadasRealizadasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMayorDeLlamadasOcupadasEnAntena!=0){
			imprimirActividadEnAntenaConMayorCantidadDeLlamadasRecibidas(cursorEnListaDeAntenas->obtenerDato(), cantidadMayorDeLlamadasOcupadasEnAntena);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int numeroMaximoDeOcupadasRealizadasEnActividadAntena(Antena* antenaAtratar){
	unsigned int maximoDeOcupadasEnActividadAntena = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadasOcupadas() > maximoDeOcupadasEnActividadAntena){
			maximoDeOcupadasEnActividadAntena = cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadasOcupadas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return maximoDeOcupadasEnActividadAntena;
}

void imprimirActividadEnAntenaQueTieneMaximoDeOcupadasRealizadas(Antena* antenaAtratar, unsigned int cantidadMaximaDeOcupadas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadasOcupadas() == cantidadMaximaDeOcupadas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "  ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "            ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerCantidadRealizadasOcupadas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void celularAlQueMasLlamaron(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeLlamadasRecibidasPorAlgunCelular = numeroMaximoDeLlamadasRecibidasEnListaDeCelulares(listaCelulares);
	imprimirCelularesAlQueMasLlamaronEnElSistema(listaCelulares, numeroMaximoDeLlamadasRecibidasPorAlgunCelular);

	imprimirCelularesAlQueMasLlamaronEnCadaAntena(listaAntenas);
}

unsigned int numeroMaximoDeLlamadasRecibidasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeDuracionEnLlamadasRecibidas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRecibidas()>cantidadMaximaDeDuracionEnLlamadasRecibidas){
			cantidadMaximaDeDuracionEnLlamadasRecibidas = cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRecibidas();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRecibidas;
}

void imprimirCelularesAlQueMasLlamaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDeLlamadasRecibidas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad maxima de llamadas Recibidas: " << cantidadDeLlamadasRecibidas << endl;
	cout << "***** CELULAR AL QUE MAS LE LLAMARON EN TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerCantidadRecibidas()==cantidadDeLlamadasRecibidas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesAlQueMasLlamaronEnCadaAntena(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULAR AL QUE MAS LLAMARON EN CADA ANTENA *****" << endl << endl;
	cout << "ANTENA " << "CELULAR  " << "  CANTIDAD DE RECIBIDAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMaximaDeDuracionEnLlamadasRecibidas = cantidadDeLlamadasRecibidasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMaximaDeDuracionEnLlamadasRecibidas!=0){
			imprimirActividadEnAntenaConMayorCantidadDeLlamadasRecibidas(cursorEnListaDeAntenas->obtenerDato(), cantidadMaximaDeDuracionEnLlamadasRecibidas);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int cantidadDeLlamadasRecibidasEnActividadAntena(Antena* antenaAtratar){
	unsigned int cantidadDeLlamadasRecibidas = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidas() > cantidadDeLlamadasRecibidas){
			cantidadDeLlamadasRecibidas = cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return cantidadDeLlamadasRecibidas;
}

void imprimirActividadEnAntenaConMayorCantidadDeLlamadasRecibidas(Antena* antenaAtratar, unsigned int cantidadDeLlamadasRecibidas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidas() == cantidadDeLlamadasRecibidas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "  ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "            ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void celularAlQueMasLeHablaron(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeDuracionEnLlamadasRecibidasPorAlgunCelular = numeroMaximoDeDuracionEnLlamadasRecibidasEnListaDeCelulares(listaCelulares);
	imprimirCelularesAlosQueMasLeHablaronEnElSistema(listaCelulares, numeroMaximoDeDuracionEnLlamadasRecibidasPorAlgunCelular);

	imprimirCelularesAlosQueMasLeHablaronEnCadaAntena(listaAntenas);
}

unsigned int numeroMaximoDeDuracionEnLlamadasRecibidasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeDuracionEnLlamadasRecibidas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRecibidas()>cantidadMaximaDeDuracionEnLlamadasRecibidas){
			cantidadMaximaDeDuracionEnLlamadasRecibidas = cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRecibidas();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRecibidas;
}

void imprimirCelularesAlosQueMasLeHablaronEnElSistema(Lista<Celular*>& listaCelulares, unsigned int cantidadDuracionMaximaEnRecibidas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad maxima de duracion total en llamadas Recibidas: " << cantidadDuracionMaximaEnRecibidas << endl;
	cout << "***** CELULAR AL QUE MAS LE HABLARON EN TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerActividad()->obtenerTiempoRecibidas()==cantidadDuracionMaximaEnRecibidas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesAlosQueMasLeHablaronEnCadaAntena(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULAR AL QUE MAS LE HABLARON EN CADA ANTENA *****" << endl << endl;
	cout << "ANTENA " << "CELULAR  " << "  DURACION DE RECIBIDAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMaximaDeDuracionEnLlamadasRecibidas = numeroDeDuracionEnLlamadasRecibidasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMaximaDeDuracionEnLlamadasRecibidas!=0){
			imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRecibidaEsLaMayor(cursorEnListaDeAntenas->obtenerDato(), cantidadMaximaDeDuracionEnLlamadasRecibidas);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int numeroDeDuracionEnLlamadasRecibidasEnActividadAntena(Antena* antenaAtratar){
	unsigned int cantidadMaximaDeDuracionEnLlamadasRecibidas = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerTiempoRecibidas() > cantidadMaximaDeDuracionEnLlamadasRecibidas){
			cantidadMaximaDeDuracionEnLlamadasRecibidas = cursorActividadEnAntena->obtenerDato()->obtenerTiempoRecibidas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeDuracionEnLlamadasRecibidas;
}

void imprimirActividadEnAntenaCuyaDuracionEnUnaLlamadaRecibidaEsLaMayor(Antena* antenaAtratar, unsigned int duracionEnLlamadasRecibidas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerTiempoRecibidas() == duracionEnLlamadasRecibidas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "  ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "            ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerTiempoRecibidas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void celularQueMasDioOcupado(Lista<Celular*>& listaCelulares, Lista<Antena*>& listaAntenas){
	unsigned int numeroMaximoDeLlamadasOcupadasRecibidasEnAlgunCelular = numeroMaximoDeLlamadasRecibidasOcupadasEnListaDeCelulares(listaCelulares);
	imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidas(listaCelulares, numeroMaximoDeLlamadasOcupadasRecibidasEnAlgunCelular);

	imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidasEnAntenas(listaAntenas);
}

unsigned int numeroMaximoDeLlamadasRecibidasOcupadasEnListaDeCelulares(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	unsigned int cantidadMaximaDeOcupadas = 0;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas()->obtenerTamanio()>cantidadMaximaDeOcupadas){
			cantidadMaximaDeOcupadas = cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas()->obtenerTamanio();
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
	return cantidadMaximaDeOcupadas;
}

void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidas(Lista<Celular*>& listaCelulares, unsigned int cantidadMaximaDeOcupadas){
	Nodo<Celular*>* cursorEnListaDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "Cantidad Maxima De Llamadas Recibidas Ocupadas: " << cantidadMaximaDeOcupadas << endl;
	cout << "***** CELULAR QUE MAS DIO OCUPADO DE TODO EL SISTEMA *****" << endl;
	while(cursorEnListaDeCelulares!=0){
		if(cursorEnListaDeCelulares->obtenerDato()->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas()->obtenerTamanio()==cantidadMaximaDeOcupadas){
			cout << "  ";
			cout << cursorEnListaDeCelulares->obtenerDato()->obtenerNumero() << endl;
		}
		cursorEnListaDeCelulares = cursorEnListaDeCelulares->obtenerNodoSiguiente();
	}
}

void imprimirCelularesConLaCantidadMaximaDeLlamadasOcupadasRecibidasEnAntenas(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursorEnListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** CELULAR QUE MAS DIO OCUPADO EN CADA ANTENA *****" << endl << endl;
	cout << "ANTENA " << "CELULAR  " << "  CANTIDAD DE OCUPADAS" << endl;
	while(cursorEnListaDeAntenas!=0){
		unsigned int cantidadMaxDeOcupadasEnActividad = numeroMaximoDeOcupadasRecibidasEnActividadAntena(cursorEnListaDeAntenas->obtenerDato());
		if(cantidadMaxDeOcupadasEnActividad!=0){
			imprimirActividadEnAntenaQueTieneMaximoDeOcupadasRecibidas(cursorEnListaDeAntenas->obtenerDato(), cantidadMaxDeOcupadasEnActividad);
		}
		cursorEnListaDeAntenas = cursorEnListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

unsigned int numeroMaximoDeOcupadasRecibidasEnActividadAntena(Antena* antenaAtratar){
	unsigned int maximoDeOcupadasEnActividadAntena = 0;
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidasOcupadas() > maximoDeOcupadasEnActividadAntena){
			maximoDeOcupadasEnActividadAntena = cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidasOcupadas();
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
	return maximoDeOcupadasEnActividadAntena;
}

void imprimirActividadEnAntenaQueTieneMaximoDeOcupadasRecibidas(Antena* antenaAtratar, unsigned int cantidadMaximaDeOcupadas){
	Nodo<RegistroActividadCelular*>* cursorActividadEnAntena = antenaAtratar->obtenerListaDeActividadRegistrada()->obtenerPrimerNodo();
	while(cursorActividadEnAntena!=0){
		if(cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidasOcupadas() == cantidadMaximaDeOcupadas){
			cout << "  ";
			cout << antenaAtratar->obtenerNombreDeAntena();
			cout << "  ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerNumeroDeCelular();
			cout << "            ";
			cout << cursorActividadEnAntena->obtenerDato()->obtenerCantidadRecibidasOcupadas() << endl;
		}
		cursorActividadEnAntena = cursorActividadEnAntena->obtenerNodoSiguiente();
	}
}

void detalleDellamdadasEmitidas(Lista<Celular*>& listaCelulares){
	unsigned int codigoDeCelularElegido = 0;
	bool codigoCorrecto = false;
	while(!codigoCorrecto){
		mostrarCelularesDelSistema(listaCelulares);
		cout << ">>> Ingrese el codigo del celular que quiere procesar." << endl;
		cout << "Su respuesta: ";
		cin >> codigoDeCelularElegido;
		cin.ignore(256,'\n');
		cout << endl;
		if((codigoDeCelularElegido>0)&&(codigoDeCelularElegido<=listaCelulares.obtenerTamanio())){
			codigoCorrecto = true;
		}
		else{
			cout << "la respuesta ingresada no corresponde a un celular existente" << endl;
			cout << "Presione la Tecla ENTER para continuar...";
			cin.get();
		}
	}
	imprimirLlamadasRealizadasDeCelular(codigoDeCelularElegido, listaCelulares);
}

void imprimirLlamadasRealizadasDeCelular(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorDeCelulares = listaCelulares.obtenerPrimerNodo();
	while(cursorDeCelulares->obtenerDato()->obtenerCodigo()!=codigoDeCelular){
		cursorDeCelulares = cursorDeCelulares->obtenerNodoSiguiente();
	}
	Nodo<RegistroLlamada*>* cursorDeListaDeLlamadas = cursorDeCelulares->obtenerDato()->obtenerListaDeRealizadas()->obtenerPrimerNodo();
	cout << "***** LLAMADAS REALIZADAS POR EL CELULAR " << cursorDeCelulares->obtenerDato()->obtenerNumero() << "*****" << endl;
	cout << "RECEPTOR " << " ANTENAS " << " INICIO " << " FIN " << endl;
	if(cursorDeListaDeLlamadas!=0){
		while(cursorDeListaDeLlamadas!=0){
			imprimirRegistroDeLlamada(cursorDeListaDeLlamadas->obtenerDato());
			cursorDeListaDeLlamadas = cursorDeListaDeLlamadas->obtenerNodoSiguiente();
		}
	}
	else{
		cout << "El Celular no concreto llamadas realizadas" << endl;
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

void detalleDellamdadasRecibidas(Lista<Celular*>& listaCelulares){
	unsigned int codigoDeCelularElegido = 0;
	bool codigoCorrecto = false;
	while(!codigoCorrecto){
		mostrarCelularesDelSistema(listaCelulares);
		cout << ">>> Ingrese el codigo del celular que quiere procesar." << endl;
		cout << "Su respuesta: ";
		cin >> codigoDeCelularElegido;
		cin.ignore(256,'\n');
		cout << endl;
		if((codigoDeCelularElegido>0)&&(codigoDeCelularElegido<=listaCelulares.obtenerTamanio())){
			codigoCorrecto = true;
		}
		else{
			cout << "la respuesta ingresada no corresponde a un celular existente" << endl;
			cout << "Presione la Tecla ENTER para continuar...";
			cin.get();
		}
	}
	imprimirLlamadasRecibidasDeCelular(codigoDeCelularElegido, listaCelulares);
}

void mostrarCelularesDelSistema(Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorDeCelulares = listaCelulares.obtenerPrimerNodo();
	cout << "***** CELULARES EXISTENTES. *****" << endl;
	cout << "CODIGO  " << "  NUMERO DE CELULAR" << endl;
	while(cursorDeCelulares!=0){
		cout << "  ";
		cout << cursorDeCelulares->obtenerDato()->obtenerCodigo() ;
		cout << "         ";
		cout << cursorDeCelulares->obtenerDato()->obtenerNumero() ;
		cout << endl;
		cursorDeCelulares = cursorDeCelulares->obtenerNodoSiguiente();
	}
	cout << endl;
}

void imprimirLlamadasRecibidasDeCelular(unsigned int codigoDeCelular, Lista<Celular*>& listaCelulares){
	Nodo<Celular*>* cursorDeCelulares = listaCelulares.obtenerPrimerNodo();
	while(cursorDeCelulares->obtenerDato()->obtenerCodigo()!=codigoDeCelular){
		cursorDeCelulares = cursorDeCelulares->obtenerNodoSiguiente();
	}
	Nodo<RegistroLlamada*>* cursorDeListaDeLlamadas = cursorDeCelulares->obtenerDato()->obtenerListaDeRecibidas()->obtenerPrimerNodo();
	cout << "***** LLAMADAS RECIBIDAS POR EL CELULAR " << cursorDeCelulares->obtenerDato()->obtenerNumero() << "*****" << endl;
	cout << "EMISOR " << " ANTENAS " << " INICIO " << " FIN " << endl;
	if(cursorDeListaDeLlamadas!=0){
		while(cursorDeListaDeLlamadas!=0){
			imprimirRegistroDeLlamada(cursorDeListaDeLlamadas->obtenerDato());
			cursorDeListaDeLlamadas = cursorDeListaDeLlamadas->obtenerNodoSiguiente();
		}
	}
	else{
		cout << "El Celular no concreto llamadas recibidas" << endl;
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

void imprimirRegistroDeLlamada(RegistroLlamada* registroAimprimir){
	cout << "  ";
	cout << registroAimprimir->obtenerCelularInvolucrado();
	cout << "  ";
	Nodo<string*>* cursorDeAntenasInvolucradas = registroAimprimir->obtenerListadoDeAntenas()->obtenerPrimerNodo();
	while(cursorDeAntenasInvolucradas!=0){
		cout << *cursorDeAntenasInvolucradas->obtenerDato();
		cout << "  ";
		cursorDeAntenasInvolucradas = cursorDeAntenasInvolucradas->obtenerNodoSiguiente();
	}
	cout << "  ";
	cout << registroAimprimir->obtenerTiempoDeInicio();
	cout << "  ";
	cout << registroAimprimir->obtenerTiempoDeFinalizacion() << endl;
}

void cantidadMaximaDeOperacionesEstablecidasConcurrentementePorAntena(Lista<Antena*>& listaAntenas){
	Nodo<Antena*>* cursosrDeListaDeAntenas = listaAntenas.obtenerPrimerNodo();
	cout << "***** COMUNICACIONES MAXIMAS ESTABLECIDAS POR ANTENA *****" << endl << endl;
	cout << "ANTENA  " << "  COMUNICACIONES ESTABLECIDAS" << endl;
	while(cursosrDeListaDeAntenas!=0){
		cout << "  ";
		cout << cursosrDeListaDeAntenas->obtenerDato()->obtenerNombreDeAntena();
		cout << "              ";
		cout << cursosrDeListaDeAntenas->obtenerDato()->obtenerCantidadDeComunicacionesEstablecidas() << endl;
		cursosrDeListaDeAntenas = cursosrDeListaDeAntenas->obtenerNodoSiguiente();
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

void detalleDellamadasRecibidasDeUnCelularEntreDosAelegir(Lista<Celular*>& listaCelulares){
	unsigned int primerCelularElegido = elegirPrimerCelular(listaCelulares);
	unsigned int segundoCelularElegido = elegirSegundoCelular(listaCelulares, primerCelularElegido);
	Celular* primeraEleccion = buscarCelularPorCodigo(primerCelularElegido, listaCelulares);
	Celular* segundaEleccion = buscarCelularPorCodigo(segundoCelularElegido, listaCelulares);

	unsigned int numeroDeLlamadas = 0;
	Lista<string*>* antenasUtilizadas = new Lista<string*>;
	unsigned int tiempoHablado = 0;
	unsigned int numeroDeVecesOcupado = 0;

	procesarLlamadasRecibidasPorElPrimerCelularElegido(primeraEleccion, segundaEleccion, numeroDeLlamadas, tiempoHablado, numeroDeVecesOcupado, antenasUtilizadas);

	cout << "DETALLE DE LLAMADAS RECIBIDAS POR EL CELULAR " << primeraEleccion->obtenerNumero();
	cout << " REALIZADAS POR EL CELULAR " << segundaEleccion->obtenerNumero() << endl << endl;
	cout << "Cantidad de llamadas: " << numeroDeLlamadas << endl;
	cout << "Antenas involucradas: ";
	Nodo<string*>* cursorAntenasUtilizadas = antenasUtilizadas->obtenerPrimerNodo();
	while(cursorAntenasUtilizadas!=0){
		cout << *cursorAntenasUtilizadas->obtenerDato() << "  ";
		cursorAntenasUtilizadas = cursorAntenasUtilizadas->obtenerNodoSiguiente();
	}
	cout << endl;
	cout << "Cantidad de tiempo hablado: " << tiempoHablado << endl;
	cout << "Cantidad de veces ocupado: " << numeroDeVecesOcupado << endl << endl;
	delete antenasUtilizadas;
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}

void procesarLlamadasRecibidasPorElPrimerCelularElegido(Celular* eleccion1, Celular* eleccion2, unsigned int& numeroDeLlamadas, unsigned int& tiempoHablado, unsigned int& numeroDeVecesOcupado, Lista<std::string*>* antenasUtilizadas){
	recorrerListaDeLlamadasRecibidasPorElPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeRecibidas(), eleccion2->obtenerNumero(), numeroDeLlamadas, tiempoHablado, antenasUtilizadas);
	recorrerListaDeLlamadasRecibidasOcupadasDelPrimerCelularYobtenerDatos(eleccion1->obtenerListaDeNumerosQueDieronOcupadoEnRecibidas(), eleccion2->obtenerNumero(), numeroDeVecesOcupado);
}

void cantidadDeAnuladasPorFaltaDeCapacidadPorAntena(Lista<Antena*>& listaAntenas){
	unsigned int cantidadMaxDeOperacionesAnuladasDelSistema = buscarCantidadMaxDeOperacionesAnuladasEnElSistema(listaAntenas);
	cout << "***** LLAMADAS ANULADAS POR ANTENA *****" << endl << endl;
	cout << "ANTENA  " << "  CANTIDAD DE ANULADAS" << endl;
	if(cantidadMaxDeOperacionesAnuladasDelSistema!=0){
		for(unsigned int numeroDeAnuladas = cantidadMaxDeOperacionesAnuladasDelSistema; numeroDeAnuladas>0; numeroDeAnuladas--){
				recorrerListaDeAntenasBuscansdoAnuladas(listaAntenas, numeroDeAnuladas);
			}
	}
	else{
		cout << "No se anulo ninguna operacion en todo el sistema." << endl;
	}
	cout << "Presione la tecla ENTER para continuar...";
	cin.get();
}



