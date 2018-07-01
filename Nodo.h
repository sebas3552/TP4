#ifndef NODO_H
#define NODO_H
#include <iostream>
#include "Arbol.h"
/**@class Nodo
*Clase abstracta Nodo que representa un Nodo genérico, de la que se derivan las clases concretas Intermedio y Hoja.
*Esta clase agrupa las funciones comunes entre los nodos del tipo Intermedio y Hoja, ya que la única diferencia entre 
*ellos es que la hoja tiene un valor del tipo genérico V, y que su color siempre será negro.
*/
template <class K>
class Nodo
{
	public:
		/**Constante para representar el color negro de un nodo.*/
		static const char NEGRO = 'n';
		/**Constante para representar el color rojo de un nodo.*/
		static const char ROJO = 'r';
		/**Tipo genérico de llave del nodo.*/
		K key;
		/**Color del nodo.*/
		char color;
		/**Puntero al hijo derecho.*/
		Nodo<K> *derecho;
		/**Puntero al hijo izquierdo.*/
		Nodo<K> *izquierdo;
		/**Constructor.
		*@param K Tipo genérico de llave.
		*@param c Color del nodo.
		*@param izq Puntero al hijo izquierdo del nodo, si se conoce de antemano.
		*@param der Puntero al hijo derecho del nodo, si se conoce de antemano.
		*/
		Nodo(K k, char c,  Nodo<K> *izq = nullptr, Nodo<K> *der = nullptr)
		: key(k), color(c), izquierdo(izq), derecho(der) { }
		/**Función para imprimir el nodo en un flujo de salida.*/
		std::ostream &operator<<(std::ostream &salida) { return imprimir(salida); }
		/**Función virtual pura para imprimir un Nodo; el Intermedio imprime su llave, el Hoja imprime su llave y su valor.*/
		virtual std::ostream &imprimir(std::ostream &) = 0;
		/**Funciones de comparación entre nodos, basándose en el elemento común entre ambos tipos: la llave.*/
		virtual bool operator<=(const Nodo<K> *otro){ return this->key <= otro->key; }
		virtual bool operator<(const Nodo<K> *otro){ return this->key < otro->key; }
		virtual bool operator>(const Nodo<K> *otro){ return this->key > otro->key; }
		virtual bool operator==(const Nodo<K> *otro){ return this->key == otro->key; }
		virtual bool operator!=(const Nodo<K> *otro){ return !(this == otro); }	
};
#endif