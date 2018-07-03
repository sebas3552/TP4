#ifndef ARBOL_R_N
#define ARBOL_R_N
#include <vector>
#include <string>
#include <cstring>
#include <initializer_list>
#include <algorithm>
#include <sstream>
#include "Intermedio.h"
#include "Hoja.h"
#include "Visualizador.cpp"
/**@class Arbol
*Clase mediante la cual se construye la estructura del árbol binario ordenado equilibrado rojo-negro.
*Cuenta con la clase anidada de acceso público Iterator, para realizar operaciones de recorrido y sustitución de nodos 
*en el árbol. El árbol se recorre en preorden por el iterador.
*/
template <class K, class V>
class Arbol
{	
	public:
		/**Declaración de la clase Iterator.*/
		class Iterator;
		/**Declaración friend de la clase emplantillada Visualizador.*/
		template <class S, class T>
		friend class Visualizador;
	
	private:
		/**Puntero al nodo raíz del árbol.*/
		Nodo<K> *raiz;
		/**Constante para representar el color negro de un nodo.*/
		static const char NEGRO = 'n';
		/**Constante para representar el color rojo de un nodo.*/
		static const char ROJO = 'r';
		/**Vector de instrucciones para imprimir en el archivo svg.*/
		std::vector<std::string> instrucciones;
		/**Visualizador emplantillado para representar el árbol, cuya funcionalidad es llamada al insertar un par al árbol.*/
		Visualizador<K, V> *visualizador;
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
		/**Función que realiza el procedimiento del cambio de color a la raíz, cuando se identifique el caso.*/
		void cambioColorRaiz()
		{
			if(this->raiz){
				if(this->raiz->color == ROJO){
					this->raiz->color = NEGRO;
					instrucciones.push_back("Cambio color raíz");
				}
			}
		}
		/**Función que realiza el color flip, que invierte los colores cuando un nodo es negro y sus dos hijos son rojos
		*@param padre Nodo padre al que se le invertirá el color junto con sus hijos, en caso de cumplir las condiciones.
		*/
		void colorFlip(Nodo<K> *padre)
		{
			/*Omite las hojas, ya que siempre son negras.*/
			if(dynamic_cast<Hoja<K, V> *>(padre))
				return;
			if(padre->izquierdo->color == ROJO && padre->derecho->color == ROJO){
				padre->izquierdo->color = padre->derecho->color = NEGRO;
				padre->color = ROJO;
				instrucciones.push_back("Color flip");
			}
		}
		/**Función que realiza el recoloreo después de una rotación, para mantener las leyes de los árboles rojo-negro.
		*@param padre Nodo padre que representa el subárbol que se necesita recolorear.
		*/
		void recolorear(Nodo<K> *padre)
		{
			if(padre->color == ROJO){
				/*Si los hijos no son hojas y sus colores son distintos, se colorean ambos rojos y el padre de color negro.*/
				if(padre->izquierdo->color != padre->derecho->color){
					if(!dynamic_cast<Hoja<K, V> *>(padre->izquierdo))
						padre->izquierdo->color = ROJO;
					if(!dynamic_cast<Hoja<K, V> *>(padre->derecho))
						padre->derecho->color = ROJO;
						padre->color = NEGRO;
					instrucciones.push_back("Recoloreo");
				}
			}
		}
		/**Función que realiza una rotación doble hacia la derecha, siendo ésta una simple izquierda (modificada) y 
		*una simple derecha. Toma el puntero a la raiz por referencia, para modificarla directamente cuando es la raíz absoluta del árbol.
		*@param raiz Nodo raiz donde se identificó el problema (hijo derecho e hijo izquierdo del hijo derecho rojos).
		*@param i Iterador que apunta al nodo raiz, para no perder su referencia al hacer modificaciones a los punteros, y para poder reasignar 
		*el subárbol como hijo del nodo abuelo cuando sea necesario.
		*/
		void rotacionDobleDerecha( Nodo<K> *&raiz, Iterator & i ){
			Nodo<K> *huerfano = raiz->izquierdo->derecho->izquierdo;
			Nodo<K> *nuevoPadre = raiz->izquierdo->derecho;
			nuevoPadre->izquierdo = raiz->izquierdo;
			nuevoPadre->izquierdo->derecho = huerfano;
			raiz->izquierdo = nuevoPadre;
			rotacionSimpleDerecha( raiz, i );
			std::string vieja = "Rotación simple derecha";
			std::string nueva = "Rotación doble derecha";
			/*Se sustituye la instrucción de rotación simple derecha porque está contemplada dentro de la rotación doble derecha.*/
			std::replace(instrucciones.begin(), instrucciones.end(), vieja, nueva);
		}
		/**Función que realiza una rotación doble hacia la izquierda, siendo ésta una simple derecha (modificada) y 
		*una simple izquierda. Toma el puntero a la raiz por referencia, para modificarla directamente cuando es la raíz absoluta del árbol.
		*@param raiz Nodo raiz donde se identificó el problema (hijo izquierdo e hijo derecho del hijo izquierdo rojos).
		*@param i Iterador que apunta al nodo raiz, para no perder su referencia al hacer modificaciones a los punteros, y para poder reasignar 
		*el subárbol como hijo del nodo abuelo cuando sea necesario.
		*/
		void rotacionDobleIzquierda( Nodo<K> *&raiz, Iterator & i ){
			Nodo<K> * huerfano = raiz->derecho->izquierdo->derecho;
			Nodo<K> *nuevoPadre = raiz->derecho->izquierdo;
			nuevoPadre->derecho = raiz->derecho;
			nuevoPadre->derecho->izquierdo = huerfano;
			raiz->derecho = nuevoPadre;
			rotacionSimpleIzquierda( raiz, i );
			std::string vieja = "Rotación simple izquierda";
			std::string nueva = "Rotación doble izquierda";
			/*Se sustituye la instrucción de rotación simple izquierda porque está contemplada dentro de la rotación doble izquierda.*/
			std::replace(instrucciones.begin(), instrucciones.end(), vieja, nueva);
		}
		/**Función que realiza una rotación simple hacia la derecha. Toma el puntero a la raiz por referencia, para modificarla directamente 
		*cuando es la raíz absoluta del árbol.
		*@param raiz Nodo raiz donde se identificó el problema (hijo izquierdo e hijo izquierdo del hijo izquierdo rojos).
		*@param i Iterador que apunta al nodo raiz, para no perder su referencia al hacer modificaciones a los punteros, y para poder reasignar 
		*el subárbol como hijo del nodo abuelo cuando sea necesario.
		*/
		void rotacionSimpleDerecha( Nodo<K> *&raiz, Iterator & i ){
			Nodo<K> * huerfano = raiz->izquierdo->derecho;
			Nodo<K> *nuevoPadre = raiz->izquierdo;
			raiz->izquierdo = huerfano;
			nuevoPadre->derecho = raiz;
			if((*(--i))->izquierdo == raiz){
				(*(--i))->izquierdo = nuevoPadre;
			}else{
				if((*(--i))->derecho == raiz){
				(*(--i))->derecho = nuevoPadre;
				}else{
					raiz = nuevoPadre;
				}
			}
			instrucciones.push_back("Rotación simple derecha");
			recolorear( nuevoPadre );
		}
		/**Función que realiza una rotación simple hacia la izquierda. Toma el puntero a la raiz por referencia, para modificarla directamente 
		*cuando es la raíz absoluta del árbol.
		*@param raiz Nodo raiz donde se identificó el problema (hijo derecho e hijo derecho del hijo derecho rojos).
		*@param i Iterador que apunta al nodo raiz, para no perder su referencia al hacer modificaciones a los punteros, y para poder reasignar 
		*el subárbol como hijo del nodo abuelo cuando sea necesario.
		*/
		void rotacionSimpleIzquierda( Nodo<K> *& raiz, Iterator & i ){
			Nodo<K> *huerfano = raiz->derecho->izquierdo;
			Nodo<K> *nuevoPadre = raiz->derecho;
			raiz->derecho = huerfano;
			nuevoPadre->izquierdo = raiz;
			if((*(--i))->derecho == raiz){
				(*(--i))->derecho = nuevoPadre;
			}else{
				if((*(--i))->izquierdo == raiz){
				(*(--i))->izquierdo = nuevoPadre;
				}else{
					raiz = nuevoPadre;
				}
			}
			instrucciones.push_back("Rotación simple izquierda");
			recolorear( nuevoPadre );		
		}
		
		/**Función que verifica las condiciones donde se dan los casos de: color flip, rotación simple izquierda, rotación simple derecha, rotación doble
		izquierda, rotación doble derecha, y llama a la función correspondiente para arreglar ese problema, verificando los nodos en el orden el que se 
		insertará el próximo nuevo elemento. Se toma el nodo raíz por referencia para poder pasarlo así a las funciones que necesiten modificarlo.*/
		void verificarCamino(Nodo<K> *&raiz, K key)
		{
			if(!raiz){
				return;
			}
			else{
				if(raiz->color == NEGRO && dynamic_cast<Intermedio<K> *>(raiz)){
					colorFlip(raiz); //color flip verifica si las condiciones se cumplen para hacer el procedimiento
					Iterator i(this, raiz);
					if(raiz->izquierdo->color == ROJO && raiz->izquierdo->izquierdo->color == ROJO){			
						rotacionSimpleDerecha(raiz, i);
						return;
					}
					if(raiz->izquierdo->color == ROJO && raiz->izquierdo->derecho->color == ROJO){
						rotacionDobleDerecha(raiz, i);
						return;
					}
					if(raiz->derecho->color == ROJO && raiz->derecho->derecho->color == ROJO){
						rotacionSimpleIzquierda(raiz, i);
						return;
					}
					if(raiz->derecho->color == ROJO && raiz->derecho->izquierdo->color == ROJO){
						rotacionDobleIzquierda(raiz, i);
						return;
					}
					if(!dynamic_cast<Hoja<K, V> *>(raiz) && key <= raiz->key){	
						verificarCamino(raiz->izquierdo, key);
					}else{
						if(!dynamic_cast<Hoja<K, V> *>(raiz))
							verificarCamino(raiz->derecho, key);
					}
				}
				else{
					if(key <= raiz->key){	
						verificarCamino(raiz->izquierdo, key);
					}else{
						verificarCamino(raiz->derecho, key);
					}
				}
			}
		}
		
	public:
		/**Cantidad de nodos del árbol, útil para cálculo de dimensiones del gráfico SVG.*/
		int cantidadNodos;
		/**Vector que contiene los nodos del árbol, para poder recorrerlos fácilmente.*/
		std::vector<Nodo<K> *> arbolPlano;
		char *nombreArchivoSalida;
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
				K value_type;
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
				Nodo<K>* operator=(Nodo<K> *nodo)
				{
					/*Víctima es el nodo al que apunta actualmente el iterador, que será reemplazado por el nuevo nodo.*/
					Nodo<K> *victima = this->operator*();
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
					/*Sustituye el puntero eliminado en el vector de punteros.*/
					nodos->operator[](dirVictima) = nodo;
					/*Restablece el puntero actual para que quede apuntando al nuevo nodo.*/
					++(*this);
					return victima;
				}
		};
		/**Iterador que apunta a la raiz del árbol.*/
		Iterator begin()
		{
			if(!empty()){
				Iterator nuevo(this);
				nuevo.actual = this->arbolPlano[nuevo.nodoActual];
				return nuevo;
			}else{
				return end();
			}
		}
		
		/**Iterador que apunta al elemento después del último elemento del árbol (siempre nulo).*/
		Iterator end()
		{
			return Iterator(this, nullptr);
		}
		/**Constructor por omisión.*/
		Arbol() : cantidadNodos(0), raiz(nullptr) {
			visualizador = new Visualizador<K, V>(this);
			//nombreArchivoSalida = "salida.html";
		}
		/**Constructor con lista inicializadora. Debe ser una lista de punteros a Hoja.*/
		Arbol(std::initializer_list<Hoja<K, V> *> lista): cantidadNodos(0), raiz(nullptr)
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
			/**Genera archivo HTML al final de la ejecución del programa, donde están todas las imágenes de los pasos de inserción de nodos del árbol.*/
			visualizador->generarHTML(nombreArchivoSalida);
			delete visualizador;
		}
		/**Función recursiva para insertar ordenadamente nodos hoja en el árbol. Al final de la inserción arregla los errores que 
		pudo haber dejado en su camino, para que el árbol siga siendo un árbol rojo-negro. Crea nodos intermedios rojos que tienen únicamente 
		*la llave menor entre la hoja que se está insertando y la hoja existente a la cual se le está agregando el nodo en orden.
		*@param k Tipo genérico k para crear la hoja con esa llave.
		*@param v Tipo genérico v para crear la hoja con ese valor.
		*/
		void insertar(K k, V v, Nodo<K> *&raiz)
		{		
			if(!raiz){
				raiz = new Hoja<K, V>(k, v);
			}
			else{
				//si es hoja
				if(dynamic_cast<Hoja<K,  V> *>(raiz)){
					/*Crea un nuevo nodo rojo intermedio con la llave menor entre el existente y el nuevo.*/
					Intermedio<K> *intermedio = new Intermedio<K>((raiz->key <= k? raiz->key : k), ROJO);
					/*Crea una nueva hoja para el elemento que se va a agregar.*/
					Hoja<K, V> *nueva = new Hoja<K, V>(k, v);
					/*A la izquierda del nuevo intermedio agrega el elemento más pequeño.*/
					intermedio->izquierdo = (raiz->key <= nueva->key ? raiz : nueva);
					/*A la derecha, el más grande.*/
					intermedio->derecho = (raiz->key > nueva->key ? raiz : nueva);
					/*Sustituye la hoja vieja por el nuevo nodo intermedio.*/
					raiz = intermedio;
				}
				/*Si no es una hoja, insertar recursivamente en orden*/
				else{
					if(k <= raiz->key){
						insertar(k, v, raiz->izquierdo);
					}else{
						insertar(k, v, raiz->derecho);
					}
				}
			}
			/*Verifica y corrige los errores que violan las normas de un árbol rojo-negro, para que quede bien al imprimirse.*/
			verificarCamino(this->raiz, k);
		}
		/**Función para agregar un par (llave, valor) al árbol, que involucra otras funciones además de la inserción.
		*@param key Llave del nuevo par a insertar.
		*@param value Valor del nuevo par a insertar.
		*@return vector de strings que contiene en cada celda una instrucción individual dada por las funciones que se hayan llamado para 
		*corregir el árbol, para que puedan imprimirse en el archivo svg.
		*/
		std::vector<std::string> agregar(K key, V value)
		{
			/*Inserta un nodo y actualiza el vector de nodos del iterador.*/
			instrucciones.clear();
			/*Se utiliza stringstream para insertar en un flujo de caracteres cualquier cosa representada por los parámetros de plantilla.*/
			std::stringstream sstr;
			sstr << "Insertando ( " << key << ", " << value << " )";
			std::string instruccion = sstr.str();
			sstr.clear();
			instrucciones.push_back(instruccion);
			cambioColorRaiz();			
			insertar(key, value, (this->raiz));				
			this->arbolPlano.clear();
			this->recorrerEnPreorden((this->raiz));
			cantidadNodos = arbolPlano.size();
			instrucciones.push_back("Inserción hoja");			
			return instrucciones;
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
		std::ostream &operator<<(std::ostream &salida) const
		{
			imprimir(salida, this->raiz);
			salida << std::endl << "cantidad de nodos: " << size() << std::endl; 
			return salida;
		}
		/**Función predicado que revisa si el árbol está vacío.
		*@return true si el árbol está vacío, false en caso contrario.
		*/
		bool empty() const
		{
			return (raiz == nullptr? true : false);
		}
		/**Función predicado que retorna la cantidad de nodos del árbol, para realizar cálculos en el dibujo svg.
		*@return Cantidad de nodos en el árbol.
		*/
		int size() const
		{
			return cantidadNodos;
		}
		/**Función de uso externo para insertar un par al árbol, que a su vez crea la visualización para esa inserción.
		*@param k tipo parametrizado para la llave.
		*@param v tipo parametrizado para el valor.
		*/
		void push_back(K k, V v)
		{
			visualizador->dibujar(agregar(k, v));
		}
		/**Función utilitaria para pasarle al visualizador el nombre del archivo html donde se presentarán todos los pasos creados en archivos svg.
		*@param nombre Nombre del archivo de salida introducido por el usuario en los argumentos de línea de comandos.
		*/
		void setNombreArchivoSalida(char *nombre)
		{
			nombreArchivoSalida = nombre;
		}	
};
#endif