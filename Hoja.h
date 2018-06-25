#ifndef HOJA_H
#define HOJA_H
#include "Nodo.h"
#include "Arbol.h"
template <class K, class V>
class Hoja : public Nodo<K>
{
	//friend class Arbol;
	public:
		V value;
	
	//protected:
		virtual std::ostream &imprimir(std::ostream &salida) { salida << "(K: " << this->key << " V: " << value << ") "; return salida; }
	
	//public:
		Hoja(K k, V v, char c,  Nodo<K> *p = nullptr, Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: Nodo<K>(k, c, p, izq, der), value(v) { }
		
};
#endif