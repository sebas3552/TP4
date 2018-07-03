#ifndef HOJA_H
#define HOJA_H
#include "Nodo.h"
#include "Arbol.h"
/**@class Hoja
*Clase concreta que hereda de Nodo, para representar nodos tipo Hoja.
*Añade a la definición abstracta de nodo su valor de tipo genérico V, y su forma de imprimirse en un flujo de salida.
*/
template <class K, class V>
class Hoja : public Nodo<K>
{
	public:
		/**Valor de tipo genérico.*/
		V value;
		/**Constructor.
		*@param k Tipo genérico de llave.
		*@param v Tipo genérico de valor.
		*@param izq Puntero al hijo izquierdo del nodo, si se conoce de antemano.
		*@param der Puntero al hijo derecho del nodo, si se conoce de antemano.
		*/
		Hoja(K k, V v, Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: Nodo<K>(k, Nodo<K>::NEGRO, izq, der), value(v) { }
		/**Función para imprimir la llave y el valor en un flujo de salida.*/
		virtual std::ostream &imprimir(std::ostream &salida) { salida << "(K: " << this->key << " V: " << value << ") "; return salida; }	
};
#endif