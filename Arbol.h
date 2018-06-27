#ifndef ARBOL_R_N
#define ARBOL_R_N
#include <algorithm>
#include <vector>
#include "Intermedio.h"
#include "Hoja.h"
template <class K, class V>
class Arbol
{
	private:
		Nodo<K> *raiz;
		int profundidad;
		const char NEGRO = 'n';
		const char ROJO = 'r';
		
	public:
		class Iterator
		{
			friend class Arbol;
			private:
				Nodo<K> *actual;
				std::vector<Nodo<K> *> arbolPlano;
				int nodoActual;
			public:
				explicit Iterator(Nodo<K> *nodo = nullptr)
				: actual(nodo), nodoActual(0) {}
				Iterator(const Iterator &otro)
				: actual(otro.actual) , nodoActual(otro.nodoActual), arbolPlano(otro.arbolPlano)
				{
					arbolPlano = otro.arbolPlano;
				}
				void recorrerEnOrden(Nodo<K> *raiz)
				{
					if(!(raiz))
						return;
					recorrerEnOrden((raiz)->izquierdo);
					arbolPlano.push_back(raiz);
					recorrerEnOrden((raiz)->derecho);
				}
				Nodo<K> *operator*()
				{
					return actual;
				}
				Iterator &operator++()
				{
					if(nodoActual < arbolPlano.size()-1){
						actual = arbolPlano[++nodoActual];		
					}
					else{
						actual = nullptr;
					}
					return *this;
				}
				bool operator==(const Iterator &otro)
				{
					return (this->actual == otro.actual && otro.actual != nullptr? true : false);
				}
				
				bool operator!=(const Iterator &otro)
				{
					return !(this->actual==otro.actual);
				}
		};
		Iterator *i;
		/**Iterador que apunta a la raiz del árbol.*/
		Iterator begin()
		{
			Iterator nuevo(*this->i);
			nuevo.nodoActual = 0;
			nuevo.actual = nuevo.arbolPlano[nuevo.nodoActual];
			return nuevo;
		}
		
		/**Iterador que apunta a nulo.*/
		Iterator end()
		{
			return Iterator(nullptr);
		}
		
		Arbol() : profundidad(0), raiz(nullptr) { i = new Iterator(); }
		~Arbol()
		{
			/**Borra los nodos con ayuda del vector de punteros del iterador.*/
			if(!this->i->arbolPlano.empty()){
				for(int i = 0; i < this->i->arbolPlano.size(); i++){
					delete this->i->arbolPlano[i];
				}
			}
			delete this->i;
		}
		void insertar(K k, V v, Nodo<K> *&raiz)
		{
			if(!raiz){
				raiz = new Hoja<K, V>(k, v, NEGRO);
			}
			else{
				//si es hoja
				if(dynamic_cast<Hoja<K,  V> *>(raiz)){
					/*Crea un nuevo nodo rojo intermedio.*/
					Intermedio<K> *intermedio = new Intermedio<K>((raiz)->key, ROJO);
					/*Crea una nueva hoja para el elemento que se va a agregar.*/
					Hoja<K, V> *nueva = new Hoja<K, V>(k, v, NEGRO);
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
		Arbol &agregar(K key, V value)
		{
			/*Inserta un nodo y actualiza el vector de nodos del iterador.**/
			insertar(key, value, (this->raiz));		
			this->i->arbolPlano.clear();
			this->i->recorrerEnOrden((this->raiz));
			return *this;
		}
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
		std::ostream &operator<<(std::ostream &salida)
		{
			imprimir(salida, this->raiz);
			salida << std::endl << "cantidad de nodos: " << this->i->arbolPlano.size(); 
			return salida;
		}
};
#endif