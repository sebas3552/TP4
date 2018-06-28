#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H
#include <fstream>
#include "Arbol.h"
template<class K, class V>
class Visualizador
{
	private:
		int paso;
		int cantNodos;
		const int RADIO = 40;
		typename Arbol<K, V>::Iterator iterador;
		std::fstream dibujo;
		
	public:
		Visualizador(Arbol<K, V> *arbol, typename Arbol<K, V>::Iterator i) 
		: paso(1), cantNodos(arbol->cantidadNodos), iterador(i)
		{
			dibujo.open("dibujo.svg", std::ios::out);
		}
		void dibujarCirculo(int cx, int cy, char c)
		{
			const char *color = (c == Arbol<K, V>::ROJO? "red" : "black");
			dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << (c == Arbol<K, V>::ROJO? color : "none") << "\" />\n";
			if(c == Arbol<K, V>::ROJO)
				dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO-10 << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << "none" << "\" />\n";
		}
		void dibujarRectangulo(int x, int y)
		{
			dibujo << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << RADIO*2 << "\" height=\"" << RADIO*2 << "\" style=\"fill:none; stroke:black; stroke-width:3\"/>";
		}
		void dibujarLinea(int x1, int y1, int x2, int y2)
		{
			dibujo << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n";
		}
		void dibujarTexto(int x, int y, Nodo<K> *nodo)
		{
			if(dynamic_cast<Intermedio<K> *>(nodo)){
				dibujo << "<text x=\"" << x-5 << "\" y=\"" << y+5 << "\">" << (*iterador)->key << "</text>\n";
			}else{
				dibujo << "<text x=\"" << x-5 << "\" y=\"" << y-5 << "\">" << (*iterador)->key << "</text>\n";
				dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y+10 << "\">" << (dynamic_cast<Hoja<K, V> *>(*iterador))->value << "</text>\n";
			}			
		}
		void dibujarSubArbol(int x, int y) //posiciones absolutas para el centro del nodo padre
		{
			int desplazamiento = 150; //150px entre nivel de nodos
			int lado = -1; //-1: rama izquierda, 1: rama derecha
			int ajusteD = 0; //factor de ajuste para las hojas, para que no se traslapen
			int ajusteI = 0;
			if(dynamic_cast<Intermedio<K> *>(*iterador)){ //si es un nodo intermedio
				ajusteI = ajusteD = 0;
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
		void dibujar()
		{
			int width = 1366 + (cantNodos%10)*200;
			int height = 768 + (cantNodos%10)*200;
			dibujo << "<?xml version='1.0' encoding='UTF-8' ?>\n<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='" << width << "' height='" << height << "px'>\n";
			dibujarSubArbol(width/2, 50);
			dibujo << "</svg>";
			dibujo.close();
		}
};
#endif