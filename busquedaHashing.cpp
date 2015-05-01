/*
 * =====================================================================================
 *
 *       Filename:  codigotarea.cpp
 *
 *    Description:  editando
 *
 *        Version:  1.0
 *        Created:  11/03/2013 05:27:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


// CÃ³digo para el tercer examen parcial de Estructuras de Datos, semestre AD12, elaborado por RMM
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
#define TAM 10 //Tamaño de la tabla Hash

//ImplementaciÃ³n del nivel fÃ­sico de un ABB
template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		void inserta (T dato);
		void despliega() { inorden(raiz); }
		int cuenta () { return contar(raiz); }
		int altura () { return niveles(raiz); }
		bool existe(T dato);
		~ABB() { libera(raiz); }
};

template <class T>
void libera (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void inorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		inorden(raiz->izq);
		cout << raiz->info <<" ";
		inorden(raiz->der);
	}
}

template <class T>
int contar (NodoArbol<T>* raiz)
{
	if (raiz == NULL)
		return 0;
	return(1+contar(raiz->izq)+contar(raiz->der));
}

template <class T>x|
int niveles (NodoArbol<T>* raiz)
{
	int altizq, altder;
	if (raiz == NULL)
		return 0;
	altizq = niveles(raiz->izq);
	altder = niveles(raiz->der);
	return(1+ (altizq>altder? altizq : altder));
}

template <class T>
void ABB<T>::inserta (T valor)
{
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		actual=(actual->info>valor? actual->izq: actual->der);
	}
	if (anterior==NULL)
		raiz = NuevoNodo;
	else
		if (anterior->info > valor)
			anterior->izq = NuevoNodo;
		else
			anterior->der = NuevoNodo;
}

template <class T>
bool ABB<T>::existe(T dato)
{
	NodoArbol<T> *aux = raiz;
	int comparaciones = 1;
	while (aux != NULL && aux->info != dato){
		aux = (dato < aux->info? aux->izq : aux->der);
		comparaciones++;
	}
	if(aux==NULL){
		cout<<comparaciones<<" comparaciones para saber que no existe en el arbol."<<endl;
	}else{
		cout<<comparaciones<<" comparaciones para encontrar el dato en el arbol."<<endl;
	}
	return !(aux == NULL);
}
// ImplementaciÃ³n del nivel fÃ­sico de una Tabla de Hash

template <class T>
class tablaHash
{
private:
	ABB<T> tabla[TAM];
	int cantidad;
	
public:
	tablaHash() {cantidad = 0;}
	void inserta (T dato);
	void inserta2 (T dato);
	bool buscarDato (T dato);
	bool buscarDato2 (T dato);
	void despliega ();
	double tamanioPromedioBuckets ();
	double alturaPromedioBuckets ();
};

template <class T>
void tablaHash<T>::inserta (T dato)
{
	int posicion = dato / 100 % TAM;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
void tablaHash<T>::inserta2 (T dato)
{
	int posicion = dato % TAM;
	posicion = pow(posicion,2);
	posicion%=TAM;
	cout<<"Se inserta el dato "<<dato<<" en la posicion: "<<posicion<<endl;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
void tablaHash<T>::despliega()
{
	cout << "Cantidad de datos: "<<cantidad<<"\n";
	for (int i = 0; i < TAM; i++)
	{
		cout << "Posicion "<<i<<": "<<tabla[i].cuenta()<<" datos en "<<tabla[i].altura()<<" niveles ";
		tabla[i].despliega();
		cout << "\n";
	}
}

template <class T>
double tablaHash<T>::tamanioPromedioBuckets()
{
	int suma = 0, bucketsLlenos = 0;
	for (int i = 0; i < TAM; i++)
	{
		int nodosBucket = tabla[i].cuenta();
		if (nodosBucket!=0) {
			suma += nodosBucket;
			bucketsLlenos++;
		}
	}
	return ((suma*1.0)/bucketsLlenos);
}

template <class T>
double tablaHash<T>::alturaPromedioBuckets()
{
	int suma = 0, bucketsLlenos = 0;
	for (int i = 0; i < TAM; i++)
	{
		int alturaBucket = tabla[i].altura();
		if (alturaBucket!=0) {
			suma += alturaBucket;
			bucketsLlenos++;
		}
	}
	return ((suma*1.0)/bucketsLlenos);
}

template <class T>
bool tablaHash<T>::buscarDato (T dato){
	int datoTemp = dato;
	int indice = datoTemp / 100 % TAM;
	cout<<"Este es el indice donde esta el dato "<<dato<<": "<<indice<<endl;
	return tabla[indice].existe(dato);
}

template <class T>
bool tablaHash<T>::buscarDato2 (T dato){
	int datoTemp = dato;
	int indice = datoTemp % TAM;
	indice = pow(indice,2);
	indice%=TAM;

	cout<<"Este es el indice donde esta el dato "<<dato<<": "<<indice<<endl;
	return tabla[indice].existe(dato);
}
// ImplementaciÃ³n del programa de aplicaciÃ³n
int main()
{
    tablaHash<int> hashing;
    tablaHash<int> hashing2;
	ifstream arch;
	string nomarch;
	int dato;

	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;

	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		hashing.inserta(dato);
		hashing2.inserta2(dato);
	}
	arch.close();

	cout<<"HASH TABLE 1"<<endl;
	hashing.despliega();	
	cout<<endl;

	cout<<"HASH TABLE 2"<<endl;
	hashing2.despliega();	
	cout<<endl;

	cout<<"HASH TABLE 1, OPERACIONES"<<endl;

	cout<<"Buscando el dato 785958"<<endl;
	hashing.buscarDato(785958);	
	
	cout<<"Buscando el dato 143012"<<endl;
	hashing.buscarDato(143012);	
	
	cout<<"Tamanio promedio de los buckets: "<<hashing.tamanioPromedioBuckets()<<endl;
	cout<<"Altura promedio de los buckets: "<<hashing.alturaPromedioBuckets()<<endl;
	cout<<endl;

	cout<<"HASH TABLE 2, OPERACIONES"<<endl;

	cout<<"Buscando el dato 785958"<<endl;
	hashing2.buscarDato2(785958);	
	
	cout<<"Buscando el dato 143012"<<endl;
	hashing2.buscarDato2(143012);	
	
	cout<<"Tamanio promedio de los buckets: "<<hashing2.tamanioPromedioBuckets()<<endl;
	cout<<"Altura promedio de los buckets: "<<hashing2.alturaPromedioBuckets()<<endl;

	return 0;
}

