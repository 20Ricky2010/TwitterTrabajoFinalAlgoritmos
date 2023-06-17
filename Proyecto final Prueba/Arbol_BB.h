#pragma once
#pragma once
#include <functional>
#include <iostream>

using namespace std;
using namespace System;


//USAREMOS ID COMO KEY

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp; //Lambda

	Nodo<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparación



public:
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		//this->comparar = [](T a, T b)->int {return a - b; };
		this->comparar = [](string a, string b)->int {
			return a.compare(b);	//0: Iguales, <0: a<b, >0: a>b
		};
		raiz = nullptr;
	}
	Nodo<T>* getRaiz() { return raiz; }

	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	Nodo<T>* Obtener(T e)
	{
		return _obtener(raiz, e);
	}

	// Propuesto 1: Elaborar un algoritmo para obtener el nodo cuyo valor es el mínimo del árbol.
	T Minimo() {
		return _minimo(raiz);
	}

	// Propuesto 2: Elaborar un algoritmo para obtener el nodo cuyo valor es el  máximo del árbol.
	T Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
private:
	bool _buscar(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) {
				return nodo;
			}
			else if (r < 0) {
				return _obtener(nodo->der, e);
			}
			else {
				return _obtener(nodo->izq, e);
			}
		}
	}
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false;
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo<T>* nodo) {	//Izq => Raiz => Der
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo<T>* nodo) {	//Raiz => Izq => Der
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {	//Izq => Der => Raiz
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
	int _altura(Nodo<T>* nodo) {
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario

		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}






	//Utiles para una mejor busqueda 
	void rotar_Derecha(Nodo<T>*& nodo) { //RECIBE EL NODO
		cout << "ROTAR DERECHA" << nodo->elemento << endl;
		Nodo<T>* p = nodo->izq; //Nodo auxiliar a moverse 
		nodo->izq = p->der;
		p->der = nodo;
		nodo = p;
		cout << "ROTAR DERECHA [fin]" << nodo->elemento << endl;
	}


	void rotar_Izq(Nodo<T>*& nodo) { //RECIBE EL NODO
		cout << "ROTAR DERECHA" << nodo->elemento << endl;
		Nodo<T>* p = nodo->der; //Nodo auxiliar a moverse (OPUESTO AL QUE SE ROTA)
		nodo->der = p->izq;
		p->izq = nodo;
		nodo = p;
		cout << "ROTAR DERECHA [fin]" << nodo->elemento << endl;
	}

	void _balanceo(Nodo<T>*& nodo) { //AQUI IDENTIFICA EL FACTOR DE BALANACE ( cumple 1>k )
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;
		//int fb = hizq - hder; [Opcion2]

		//[Opcion2]if (fb < -1) { //rotar a la izq [hizq < hder]
		if (fb > 1) { //rotar a la izq [hizq < hder]
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotaciÃ³n RDI
				rotar_Derecha(nodo->der);	// RSD
			}

			rotar_Izq(nodo);	// RSI

		}
		//[Opcion2]else if (fb > 1) { //rotar a la der [hizq > hder]
		else if (fb < -1) { //rotar a la der [hizq > hder]
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) { //verificar si aplica doble rotaciÃ³n RDD
				rotar_Izq(nodo->izq);	// ROTACION SIMPLE IZQUIERDA
			}
			rotar_Derecha(nodo);	// ROTACION SIMPLE DERECHA
		}

	};

	/*void _imprimir_A(Nodo<T>* nodo, S indent, B last) {
		if (nodo != nullptr) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "    ";

			}
			else
			{
				cout << "L----";
				indent += "    ";
			}
		}
	}*/

};