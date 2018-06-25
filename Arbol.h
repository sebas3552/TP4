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
			public:
				explicit Iterator(Nodo<K> *nodo = nullptr)
				: actual(nodo){}
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
				//Iterator &operator++();
		};
		Iterator *i;
		Arbol() : profundidad(0), raiz(nullptr) { i = new Iterator(); }
		~Arbol()
		{
			if(!this->i->arbolPlano.empty()){
				std::cout << std::endl;
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
					Intermedio<K> *intermedio = new Intermedio<K>((raiz)->key, ROJO, (raiz)->padre );
					/*Crea una nueva hoja para el elemento que se va a agregar.*/
					Hoja<K, V> *nueva = new Hoja<K, V>(k, v, NEGRO, intermedio);
					/*A la izquierda del nuevo intermedio, agrega el elemento más pequeño.*/
					intermedio->izquierdo = std::min(raiz, dynamic_cast<Nodo<K> *>(nueva));
					/*A la derecha, el más grande.*/
					intermedio->derecho = std::max(raiz, dynamic_cast<Nodo<K> *>(nueva));
					/*Reasigna el antecesor de la hoja para que su hijo sea el nuevo intermedio.*/
					if(raiz->padre){
						if(raiz->padre->izquierdo == raiz)
							raiz->padre->izquierdo = intermedio;
						else
							raiz->padre->derecho = intermedio;
					}
					/*Reasigna el padre de la hoja para que apunte al nuevo intermedio.*/
					(raiz)->padre = intermedio;
					/*Sustituye la hoja vieja por el nuevo nodo intermedio.*/
					raiz = intermedio;
				}
				//si no es una hoja, insertar recursivamente en orden
				else{
					if(k <= (raiz)->key){
						insertar(k, v, (raiz)->izquierdo);
					}else{
						insertar(k, v, (raiz)->derecho);
					}
				}
			}
		}
		Arbol &agregar(K key, V value)
		{
			insertar(key, value, (this->raiz));		
			this->i->arbolPlano.clear();
			this->i->recorrerEnOrden((this->raiz));
			return *this;
		}
		void imprimir(std::ostream &salida, Nodo<K> *&raiz) const
		{
			if(!(raiz))
				return;
			imprimir(salida, (raiz)->izquierdo);
			raiz->imprimir(salida);
			imprimir(salida, (raiz)->derecho);
		}
		std::ostream &operator<<(std::ostream &salida)
		{
			imprimir(salida, this->raiz);
			return salida;
		}
};
#endif