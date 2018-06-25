#ifndef NODO_H
#define NODO_H
#include <iostream>
#include "Arbol.h"
template <class K>
class Nodo
{
	//friend class Arbol;
	public:
		K key;
		char color;
		Nodo<K> *derecho;
		Nodo<K> *izquierdo;
		Nodo<K> *padre;
		virtual std::ostream &imprimir(std::ostream &) = 0;
		
	//public:
		Nodo(K k, char c,  Nodo<K> *p = nullptr, Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: key(k), color(c), padre(p), izquierdo(izq), derecho(der) { }
		virtual ~Nodo() { derecho = izquierdo = padre = nullptr; };
		Nodo *abuelo() const {  if(padre) return padre->padre; }
		Nodo *tio() const { if(padre){ if(padre->padre) return (padre->padre->izquierdo != this->padre? padre->padre->izquierdo : padre->padre->derecho); }}
		void setColor(char c) { color = c; }
		bool operator<=(Nodo<K> &otro) const { return this->key <= otro.key; }
		bool operator<(Nodo<K> &otro) const { return this->key < otro.key; }
		bool operator>(Nodo<K> &otro) const { return !(*this) < otro; }
		std::ostream &operator<<(std::ostream &salida) { return imprimir(salida); }
};
#endif