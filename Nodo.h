#ifndef NODO_H
#define NODO_H
#include <iostream>
#include "Arbol.h"
template <class K>
class Nodo
{
	public:
		K key;
		char color;
		Nodo<K> *derecho;
		Nodo<K> *izquierdo;
		Nodo(K k, char c,  Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: key(k), color(c), izquierdo(izq), derecho(der) { }
		~Nodo() { derecho = izquierdo = nullptr; };
		std::ostream &operator<<(std::ostream &salida) { return imprimir(salida); }
		virtual std::ostream &imprimir(std::ostream &) = 0;
		virtual bool operator<=(Nodo<K> *otro) const { return this->key <= otro->key; }
		virtual bool operator<(Nodo<K> *otro) const { return this->key < otro->key; }
		virtual bool operator>(Nodo<K> *otro) const { return this->key > otro->key; }
		virtual bool operator==(Nodo<K> *otro) const { return this->key == otro->key; }
		virtual bool operator!=(Nodo<K> *otro) const { return !(this == otro); }
		
};
#endif