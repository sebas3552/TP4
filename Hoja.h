#ifndef HOJA_H
#define HOJA_H
#include "Nodo.h"
#include "Arbol.h"
template <class K, class V>
class Hoja : public Nodo<K>
{
	public:
		V value;
		Hoja(K k, V v, char c, Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: Nodo<K>(k, c, izq, der), value(v) { }
		virtual std::ostream &imprimir(std::ostream &salida) { salida << "(K: " << this->key << " V: " << value << ") "; return salida; }	
};
#endif