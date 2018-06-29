#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Arbol.h"
/**@class Visualizador
*Clase que implementa las funciones necesarias para graficar un árbol binario equilibrado rojo-negro en formato de archivo SVG.
*/
template<class K, class V>
class Visualizador
{
	private:
	
		/**Entero que guarda el número de paso actual, para crear archivos de salida distintos.*/
		int paso;
		/**Cantidad de nodos del árbol, para ajustar el lienzo del gráfico SVG.*/
		int cantNodos;
		/**Radio establecido para los círculos. También para el lado de los cuadrados.*/
		const int RADIO = 40;
		/**Iterador del árbol que se está dibujando.*/
		typename Arbol<K, V>::Iterator iterador;
		Arbol<K, V> *arbol;
		/**Archivo de salida para el gráfico SVG.*/
		std::fstream dibujo;
		/**Función simple que dibuja un círculo rojo con un círculo inscrito si el nodo es un nodo rojo, o un círculo de borde negro sin fondo si
		*es un nodo negro.
		*@param cx Coordenada del centro en el eje x.
		*@param cy Coordenada del centro en el eje y.
		*@param c Color del círculo.
		*/
		void dibujarCirculo(int cx, int cy, char c)
		{
			const char *color = (c == Arbol<K, V>::ROJO? "red" : "black");
			dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << (c == Arbol<K, V>::ROJO? color : "none") << "\" />\n";
			if(c == Arbol<K, V>::ROJO)
				dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO-10 << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << "none" << "\" />\n";
		}
		/**Función simple que dibuja un rectángulo, para representar nodos hoja.
		*@param x Coordenada de la esquina superior izquierda en el eje x.
		*@param y Coordenada de la esquina superior derecha en el eje y.
		*/
		void dibujarRectangulo(int x, int y)
		{
			dibujo << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << RADIO*2 << "\" height=\"" << RADIO*2 << "\" style=\"fill:none; stroke:black; stroke-width:3\"/>";
		}
		/**Función simple que traza una línea, dados sus puntos de inicio y final.
		*@param x1 Coordenada de inicio en el eje x.
		*@param y1 Coordenada de inicio en el eje y.
		*@param x2 Coordenada de fin en el eje x.
		*@param y2 Coordenada de fin en el eje y.
		*/
		void dibujarLinea(int x1, int y1, int x2, int y2)
		{
			dibujo << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n";
		}
		/**Función simple que inserta el texto que representa la llave y/o el valor de un nodo, en el centro de un círculo o un cuadrado.
		*@param x Coordenada x del texto (alineado al centro).
		*@param y Coordenada y del texto.
		*@param nodo Puntero al nodo, para extraer su llave/valor e insertarlo en el círculo o cuadrado.
		*/
		void dibujarTexto(int x, int y, Nodo<K> *nodo)
		{
			if(dynamic_cast<Intermedio<K> *>(nodo)){
				dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y+5 << "\">" << (*iterador)->key << "</text>\n";
			}else{
				dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y-5 << "\">" << (*iterador)->key << "</text>\n";
				dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y+10 << "\">" << (dynamic_cast<Hoja<K, V> *>(*iterador))->value << "</text>\n";
			}			
		}
		/**Función recursiva que dibuja un subárbol a la vez, donde un subárbol se entiende como un único nodo padre y sus dos hijos.
		*Si el hijo de la izquierda del nodo actual no es una hoja, se llama para dibujar ese subárbol. Lo mismo para el hijo derecho. En cada iteración, incrementa el iterador para avanzar en el árbol.
		*@param x Coordenada x donde se centrará el círculo o el cuadrado que representa el nodo en cuestión.
		*@param y Coordenada y donde se centrará el círculo o el cuadrado que representa el nodo en cuestión.
		*/
		void dibujarSubArbol(int x, int y) //posiciones absolutas para el centro del nodo padre
		{
			int desplazamiento = 150; //150px entre nivel de nodos
			int lado = -1; //-1: rama izquierda, 1: rama derecha
			int ajusteD = 0; //factor de ajuste para las hojas, para que no se traslapen
			int ajusteI = 0;
			if(dynamic_cast<Intermedio<K> *>(*iterador)){ //si es un nodo intermedio
				/*Me dibujo yo*/
				dibujarCirculo(x, y, (*iterador)->color);
				dibujarTexto(x, y, *iterador);
				/*Si los hijos son hojas, establecer factor de ajuste para el correspondiente hijo hoja.*/
				if(dynamic_cast<Hoja<K, V> *>((*iterador)->izquierdo))
					ajusteI = 90;
				if(dynamic_cast<Hoja<K, V> *>((*iterador)->derecho))
					ajusteD = 90;
				/*Dibujo a mis hijos, proceso de dibujo del árbol en preorden*/
				++iterador;
				/*Subárbol izquierdo*/
				dibujarLinea(x, y+RADIO, x+(desplazamiento*lado)+ajusteI, (y+desplazamiento)-RADIO);
				dibujarSubArbol(x+desplazamiento*lado+ajusteI, y+desplazamiento);
				/*Subárbol derecho*/
				dibujarLinea(x, y+RADIO, x+(desplazamiento*lado*lado)-ajusteD, (y+desplazamiento)-RADIO);
				dibujarSubArbol(x+desplazamiento*lado*lado-ajusteD, y+desplazamiento);
			}else{ //si es una hoja
				dibujarRectangulo(x-RADIO, y-RADIO);
				dibujarTexto(x, y, *iterador);
				++iterador;
			}	
		}
		
		public:
		
		/**Constructor.
		*@param arbol Arbol que se va a graficar.
		*@param i Iterador del árbol, para recorrerlo y dibujarlo.
		*/
		Visualizador(Arbol<K, V> *arbol, typename Arbol<K, V>::Iterator i) 
		: arbol(arbol), paso(1), cantNodos(arbol->cantidadNodos), iterador(i)
		{	
		}
		/**Función principal que realiza el gráfico completo del árbol y crea el archivo en el formato .svg.
		*También calcula las dimensiones del lienzo de dibujo, según la cantidad de nodos que tenga el árbol.*/
		void dibujar()
		{	
			iterador = arbol->begin();
			int width = 1366 + (cantNodos%10)*200;
			int height = 768 + (cantNodos%10)*200;
			std::string nombreArchivo = "dibujo";
			nombreArchivo += std::to_string(paso);
			nombreArchivo += ".svg";
			dibujo.open(nombreArchivo, std::ios::out);
			dibujo << "<?xml version='1.0' encoding='UTF-8' ?>\n<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='" << width << "' height='" << height << "px'>\n";
			dibujarSubArbol(width/2, 50);
			dibujo << "</svg>";
			dibujo.close();
			++paso;
		}
};
#endif