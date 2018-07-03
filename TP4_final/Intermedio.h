#ifndef INTERMEDIO_H
#define INTERMEDIO_H
#include "Nodo.h"
#include "Arbol.h"
/**@class Intermedio
*Clase concreta que hereda de Nodo, para representar nodos tipo Intermedio.
*Añade a la definición abstracta de nodo su forma de imprimirse en un flujo de salida.
*/
template <class K>
class Intermedio : public Nodo<K>
{
	public:
		/**Constructor.
		*@param k Tipo genérico de llave.
		*@param v Tipo genérico de valor.
		*@param c Color del nodo.
		*@param izq Puntero al hijo izquierdo del nodo, si se conoce de antemano.
		*@param der Puntero al hijo derecho del nodo, si se conoce de antemano.
		*/
		Intermedio(K k, char c = 'r', Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: Nodo<K>(k, c, izq, der) { } 
		/**Función para imprimir la llave en un flujo de salida.*/
		virtual std::ostream &imprimir(std::ostream &salida) { salida << "(K: " << this->key << ") "; return salida; }		
};
#endif