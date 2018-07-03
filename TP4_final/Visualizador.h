#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
//#include "Arbol.h"
/**@class Visualizador
*Clase que implementa las funciones necesarias para graficar un árbol binario equilibrado rojo-negro en formato de archivo SVG.
*/
template<class K, class V>
class Arbol;
template<class K>
class Nodo;
template<class K, class V>
class Visualizador
{
	private:
	
		/**Entero que guarda el número de paso actual, para crear archivos de salida distintos.*/
		int paso;
		/**Radio establecido para los círculos. También para el lado de los cuadrados.*/
		const int RADIO = 40;
		/**Iterador del árbol que se está dibujando.*/
		typename Arbol<K, V>::Iterator iterador;
		/**Puntero al árbol que se va a dibujar con este visualizador.*/
		Arbol<K, V> *arbol;
		/**Archivo de salida para el gráfico SVG.*/
		std::fstream dibujo;
		/**Cantidad de nodos del árbol, que cambia para cada dibujo generado.*/
		int cantNodos;
		/**Vector que contiene los nombres de los dibujos creados en las inserciones del árbol, para juntarlos en el HTML.*/
		std::vector<std::string> dibujos;
		/**Función simple que dibuja un círculo rojo con un círculo inscrito si el nodo es un nodo rojo, o un círculo de borde negro sin fondo si
		*es un nodo negro.
		*@param cx Coordenada del centro en el eje x.
		*@param cy Coordenada del centro en el eje y.
		*@param c Color del círculo.
		*/
		void dibujarCirculo(int cx, int cy, char c);
		/**Función simple que dibuja un rectángulo, para representar nodos hoja.
		*@param x Coordenada de la esquina superior izquierda en el eje x.
		*@param y Coordenada de la esquina superior derecha en el eje y.
		*/
		void dibujarRectangulo(int x, int y, char color);
		/**Función simple que traza una línea, dados sus puntos de inicio y final.
		*@param x1 Coordenada de inicio en el eje x.
		*@param y1 Coordenada de inicio en el eje y.
		*@param x2 Coordenada de fin en el eje x.
		*@param y2 Coordenada de fin en el eje y.
		*/
		void dibujarLinea(int x1, int y1, int x2, int y2);
		/**Función simple que inserta el texto que representa la llave y/o el valor de un nodo, en el centro de un círculo o un cuadrado.
		*@param x Coordenada x del texto (alineado al centro).
		*@param y Coordenada y del texto.
		*@param nodo Puntero al nodo, para extraer su llave/valor e insertarlo en el círculo o cuadrado.
		*/
		void dibujarTexto(int x, int y, Nodo<K> *nodo);
		/**Función que imprime en formato de texto SVG las instrucciones necesarias para construir el árbol tal y como se muestra en la visualización.
		*@param instrucciones Vector de instrucciones que serán impresas en la esquina superior izquierda del archivo svg, una por línea.
		*/
		void imprimirInstrucciones(std::vector<std::string> instrucciones);
		/**Función recursiva que dibuja un subárbol a la vez, donde un subárbol se entiende como un único nodo padre y sus dos hijos.
		*Si el hijo de la izquierda del nodo actual no es una hoja, se llama para dibujar ese subárbol. Lo mismo para el hijo derecho. En cada iteración, incrementa el iterador para avanzar en el árbol.
		*@param x Coordenada x donde se centrará el círculo o el cuadrado que representa el nodo en cuestión.
		*@param y Coordenada y donde se centrará el círculo o el cuadrado que representa el nodo en cuestión.
		*/
		void dibujarSubArbol(int x, int y);
		
	public:
	
		/**Constructor.
		*@param arbol Arbol que se va a graficar.
		*/
		Visualizador(Arbol<K, V> *arbol);
		/**Función principal que realiza el gráfico completo del árbol y crea el archivo en el formato .svg.
		*También calcula las dimensiones del lienzo de dibujo, según la cantidad de nodos que tenga el árbol.
		*@param instrucciones Vector de instrucciones para incluírlas en la visualización.
		*/
		void dibujar(std::vector<std::string> instrucciones);
		/**Función que genera un archivo final HTML para visualizar todas las imágenes de los pasos en SVG.
		*@param salida Nombre del archivo de salida dado por los argumentos de línea de comandos.
		*/
		void generarHTML(char *salida);
};
#endif