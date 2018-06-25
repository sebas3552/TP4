#include "Arbol.h"
#include "Intermedio.h"
#include "Hoja.h"

using namespace std;

template <class K, class V>
Arbol<K, V>::Iterator::Iterator(Nodo<K> *nodo)
: actual(nodo)
{
	
}

template <class K, class V>
void Arbol<K, V>::Iterator::recorrerEnOrden(Nodo<K> **&raiz)
{
	if(!(*raiz))
		return;
	recorrerEnOrden((*raiz)->izquierdo);
	arbolPlano.push_back(*raiz);
	recorrerEnOrden((*raiz)->derecho);
}

template<class K, class V>
Arbol<K, V>::~Arbol<K, V>()
{
	if(!Iterator::arbolPlano.empty()){
		for(int i = 0; i < Iterator::arbolPlano.size(); i++)
			delete Iterator::arbolPlano[i];
	}
	delete *raiz;
	
}

template <class K, class V>
void Arbol<K, V>::insertar(K k, V v, Nodo<K> **&raiz)
{
	if(!raiz){
		*raiz = new Hoja<K, V>(k, v, NEGRO);
	}
	else{
		//si es hoja
		if(dynamic_cast<Hoja<K,  V> *>(*raiz)){
			Intermedio<K> *intermedio = new Intermedio<K>((*raiz)->key, ROJO, (*raiz)->padre );
			/*Establece el hijo izquierdo como la hoja ya existente.*/
			intermedio->izquierdo = *raiz;
			/*Establece el hijo derecho como la hoja a insertar, y al padre de esa hoja como al nuevo intermedio.*/
			intermedio->derecho = new Hoja<K, V>(k, v, NEGRO, intermedio);
			/*Asigna el padre de la hoja ya existente al nuevo nodo intermedio.*/
			(*raiz)->padre = intermedio;
			/*Reasigna el hijo del nodo padre, para que apunte al nuevo nodo rojo intermedio*/
			if(intermedio->padre){
				if(intermedio->padre->izquierdo == *raiz)
					intermedio->padre->izquierdo = intermedio;
				else
					intermedio->padre->derecho = intermedio;
			}
		}
		//si no es una hoja, insertar recursivamente en orden
		else{
			if(k <= (*raiz)->key){
				insertar(k, v, (*raiz)->izquierdo);
			}else{
				insertar(k, v, (*raiz)->derecho);
			}
		}
	}
}

template <class K, class V>
Arbol<K, V> &Arbol<K, V>::agregar(K key, V value)
{
	insertar(key, value, this->raiz);
	return *this;
}

template <class K, class V>
ostream &Arbol<K, V>::imprimir(ostream &salida, Nodo<K> **&raiz) const
{
	if(!(*raiz))
		return salida;
	imprimir(salida, (*raiz)->izquierdo);
	salida << (**raiz) << " ";
	imprimir(salida, (*raiz)->derecho);
	return salida;
}

template <class K, class V>
ostream &Arbol<K, V>::operator<<(ostream &salida)
{
	return imprimir(salida, this->raiz);
}