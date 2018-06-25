#ifndef INTERMEDIO_H
#define INTERMEDIO_H
#include "Nodo.h"
#include "Arbol.h"
template <class K>
class Intermedio : public Nodo<K>
{
	//friend class Arbol;
	public:
		virtual std::ostream &imprimir(std::ostream &salida) { salida << "(K: " << this->key << ") "; return salida; }
		
	//public:
		Intermedio(K k, char c,  Nodo<K> *p = nullptr, Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: Nodo<K>(k, c, p, izq, der) { } 
		
};
#endif