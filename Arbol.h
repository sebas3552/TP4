#ifndef ARBOL_R_N
#define ARBOL_R_N
#include <vector>
#include <initializer_list>
#include "Intermedio.h"
#include "Hoja.h"
#include "Visualizador.h"
/**@class Arbol
*Clase mediante la cual se construye la estructura del árbol binario ordenado equilibrado rojo-negro.
*Cuenta con la clase anidada de acceso público Iterator, para realizar operaciones de recorrido y sustitución de nodos 
*en el árbol. El árbol se recorre en preorden por el iterador.
*/
template <class K, class V>
class Arbol
{
	/**Declaración friend de la clase emplantillada Visualizador.*/
	template <class S, class T>
	friend class Visualizador;
	private:
		/**Puntero al nodo raíz del árbol.*/
		Nodo<K> *raiz;
		/**Entero que guarda la profundidad del árbol (nodos negros).*/
		int profundidad;
		/**Constante para representar el color negro de un nodo.*/
		static const char NEGRO = 'n';
		/**Constante para representar el color rojo de un nodo.*/
		static const char ROJO = 'r';
		/**Cantidad de nodos del árbol, útil para cálculo de dimensiones del gráfico SVG.*/
		int cantidadNodos;
		/**Función que recorre el árbol en pre-orden (raiz - hijo izquierdo - hijo derecho) y va agregando los nodos
		al vector de punteros a Nodo para poder recorrerlos.*/
		void recorrerEnPreorden(Nodo<K> *raiz)
		{
			if(!(raiz))
				return;
			arbolPlano.push_back(raiz);
			recorrerEnPreorden((raiz)->izquierdo);
			recorrerEnPreorden((raiz)->derecho);
		}
		
	public:
		/**Vector que contiene los nodos del árbol, para poder recorrerlos fácilmente.*/
		std::vector<Nodo<K> *> arbolPlano;
		/**@class Iterator
		*Esta clase permite tener objetos para iterar un árbol, útil para operaciones de recorrido, inserción y reemplazo
		*de nodos en la estructura del árbol.
		*/
		class Iterator
		{
			friend class Arbol;
			private:
				/**Puntero a un vector de nodos.*/
				std::vector<Nodo<K> *> *nodos;
				/**Puntero al nodo actual al que apunta el iterador.*/
				Nodo<K> *actual;
				/**Puntero al Árbol en el que está contenido el iterador.*/
				Arbol<K,  V> *miArbol;
				/**Número de nodo por el cual está iterando actualmente el objeto.*/
				int nodoActual;
			public:
				/**Constructor.
				*@param padre Puntero al árbol que contiene este iterador.
				*@param nodo Nodo al que apuntará inicialmente el iterador.
				*/
				Iterator(Arbol<K, V> *padre, Nodo<K> *nodo = nullptr)
				: actual(nodo), nodoActual(0), miArbol(padre)
				{
					nodos = &(miArbol->arbolPlano);
				}
				/**Constructor de copia.
				*@param otro Iterador a partir del cual se construirá el nuevo, por copia.
				*/
				Iterator(const Iterator &otro)
				: actual(otro.actual) , nodoActual(otro.nodoActual), nodos(otro.nodos), miArbol(otro.miArbol)
				{
				}
				/**Función para retornar un puntero al nodo que apunta actualmente el iterador.*/
				Nodo<K> *operator*()
				{
					return actual;
				}
				/**Operador de preincremento; mueve el puntero nodo actual al siguiente, en el vector de punteros a Nodo.*/
				Iterator &operator++()
				{
					if(nodoActual < nodos->size()-1){
						actual = nodos->operator[](++nodoActual);		
					}
					else{
						actual = nullptr;
					}
					return *this;
				}
				/**Operador de igualdad.*/
				bool operator==(const Iterator &otro)
				{
					return (this->actual == otro.actual && otro.actual != nullptr? true : false);
				}
				/**Operador de diferencia (no igualdad).*/
				bool operator!=(const Iterator &otro)
				{
					return !(this->actual==otro.actual);
				}
				/**Operador de asignación.*/
				Iterator &operator=(const Iterator &otro)
				{
					this->miArbol = otro.miArbol;
					this->actual = otro.actual;
					this->nodoActual = otro.nodoActual;
					return *this;
				}
				/**Operador de predecremento.*/
				Iterator &operator--()
				{
					if(nodoActual -1 >= 0){
						nodoActual--;
						actual = nodos->operator[](nodoActual);
					}else{
						actual = nodos->operator[](0);
					}
					return *this;
				}
				/**Operador de asignación para utilizar como rvalue un puntero a Nodo. Útil para reemplazar el nodo al que 
				apunta el Iterador, en la estructura del árbol.*/
				void operator=(Nodo<K> *nodo)
				{
					/*Víctima es el nodo al que apunta actualmente el iterador, que será reemplazado por el nuevo nodo.*/
					Nodo<K> *victima = (this->operator*());
					int dirVictima = this->nodoActual;
					/*Se regresa al nodo padre de la víctima, para cambiar el puntero de la víctima hacia el nuevo.*/
					Iterator aux(--(*this));
					/*Se asignan los hijos de la víctima al nuevo, "los adopta".*/
					nodo->izquierdo = victima->izquierdo;
					nodo->derecho = victima->derecho;
					/*Verifica en el padre cual es el hijo victima, y lo reemplaza por el nuevo.*/
					if((*aux)->izquierdo == victima){
						(*aux)->izquierdo = nullptr;
						(*aux)->izquierdo = nodo;
					}else{
						(*aux)->derecho = nullptr;
						(*aux)->derecho = nodo;
					}
					/*Elimina la victima.*/
					delete victima;
					/*Sustituye el puntero eliminado en el vector de punteros.*/
					nodos->operator[](dirVictima) = nodo;
					/*Restablece el puntero actual para que quede apuntando al nuevo nodo.*/
					++(*this);
				}
		};
		/**Iterador que apunta a la raiz del árbol.*/
		Iterator begin()
		{
			Iterator nuevo(this);
			nuevo.actual = this->arbolPlano[nuevo.nodoActual];			
			return nuevo;
		}
		
		/**Iterador que apunta a nulo.*/
		Iterator end()
		{
			return Iterator(this, nullptr);
		}
		/**Constructor por omisión.*/
		Arbol() : profundidad(0), cantidadNodos(0), raiz(nullptr) { }
		/**Constructor con lista inicializadora. Debe ser una lista de punteros a Hoja.*/
		Arbol(std::initializer_list<Hoja<K, V> *> lista): profundidad(0), cantidadNodos(0), raiz(nullptr)
		{
			for(Hoja<K, V> *hoja : lista)
				agregar(hoja->key, hoja->value);
		} 
		/**Destructor.*/
		~Arbol()
		{
			/**Borra los nodos con ayuda del vector de punteros del iterador.*/
			if(!this->arbolPlano.empty()){
				for(int i = 0; i < this->arbolPlano.size(); i++){
					delete arbolPlano[i];
				}
			}
		}
		/**Función recursiva para insertar ordenadamente nodos hoja en el árbol.*/
		void insertar(K k, V v, Nodo<K> *&raiz)
		{
			if(!raiz){
				raiz = new Hoja<K, V>(k, v);
			}
			else{
				//si es hoja
				if(dynamic_cast<Hoja<K,  V> *>(raiz)){
					/*Crea un nuevo nodo rojo intermedio.*/
					Intermedio<K> *intermedio = new Intermedio<K>((raiz)->key, ROJO);
					/*Crea una nueva hoja para el elemento que se va a agregar.*/
					Hoja<K, V> *nueva = new Hoja<K, V>(k, v);
					Nodo<K>* menor = (raiz->operator<(dynamic_cast<Nodo<K>*>(nueva))? raiz : nueva);
					/*A la izquierda del nuevo intermedio, agrega el elemento más pequeño.*/
					intermedio->izquierdo = menor;
					/*A la derecha, el más grande.*/
					intermedio->derecho = (raiz->operator==(menor)? nueva : raiz);
					/*Sustituye la hoja vieja por el nuevo nodo intermedio.*/
					raiz = intermedio;
				}
				//si no es una hoja, insertar recursivamente en orden
				else{
					if(k <= raiz->key){
						insertar(k, v, raiz->izquierdo);
					}else{
						insertar(k, v, raiz->derecho);
					}
				}
			}
		}
		/**Función para agregar un par (llave, valor), para uso del cliente.*/
		Arbol &agregar(K key, V value)
		{
			/*Inserta un nodo y actualiza el vector de nodos del iterador.**/
			insertar(key, value, (this->raiz));		
			this->arbolPlano.clear();
			this->recorrerEnPreorden((this->raiz));
			cantidadNodos = arbolPlano.size();
			return *this;
		}
		/**Función recursiva que imprime el árbol en preorden en la salida estándar.*/
		void imprimir(std::ostream &salida, Nodo<K> *&raiz) const
		{
			/*Imprime en preorden, encerrando entre llaves a un nodo y sus correspondientes hijos.*/
			if(!(raiz))
				return;
			salida << "{ ";
			raiz->imprimir(salida);
			imprimir(salida, (raiz)->izquierdo);
			imprimir(salida, (raiz)->derecho);
			salida << " }";
			
		}
		/**Función que imprime el árbol en preorden en la salida estándar, para pruebas del programa.*/
		std::ostream &operator<<(std::ostream &salida)
		{
			imprimir(salida, this->raiz);
			salida << std::endl << "cantidad de nodos: " << this->arbolPlano.size() << std::endl; 
			return salida;
		}
};
#endif