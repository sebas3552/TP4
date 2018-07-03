#include "Arbol.h"
#include "Visualizador.h"

template<class K, class V>
void Visualizador<K, V>::dibujarCirculo(int cx, int cy, char c)
{
	const char *color = (c == Arbol<K, V>::ROJO? "red" : "black");
	dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << (c == Arbol<K, V>::ROJO? color : "none") << "\" />\n";
	if(c == Arbol<K, V>::ROJO)
		dibujo << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << RADIO-10 << "\" stroke=\"black\" stroke-width=\"3\" fill=\"" << "none" << "\" />\n";
}

template<class K, class V>
void Visualizador<K, V>::dibujarRectangulo(int x, int y, char color)
{
	dibujo << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << RADIO*2 << "\" height=\"" << RADIO*2 << "\" style=\"fill:none; stroke:" << (color == Arbol<K, V>::NEGRO? "black" : "red") << "; stroke-width:3\"/>";
}

template<class K, class V>
void Visualizador<K, V>::dibujarLinea(int x1, int y1, int x2, int y2)
{
	dibujo << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n";
}

template<class K, class V>
void Visualizador<K, V>::dibujarTexto(int x, int y, Nodo<K> *nodo)
{
	if(dynamic_cast<Intermedio<K> *>(nodo)){
		dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y+5 << "\">" << (*iterador)->key << "</text>\n";
	}else{
		dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y-5 << "\">" << (*iterador)->key << "</text>\n";
		dibujo << "<text text-anchor=\"middle\" x=\"" << x << "\" y=\"" << y+10 << "\">" << (dynamic_cast<Hoja<K, V> *>(*iterador))->value << "</text>\n";
	}			
}

template<class K, class V>
void Visualizador<K, V>::imprimirInstrucciones(std::vector<std::string> instrucciones)
{
	dibujo << "<text text-anchor=\"start\" x=\"" << 10 << "\" y=\"" << 20 << "\">" << "Paso " << paso << ": " << "</text>";
	for(int i = 0; i < instrucciones.size(); i++)
		dibujo << "<text text-anchor=\"start\" x=\"" << 10 << "\" y=\"" << 40+30*i << "\">" << instrucciones[i] << "</text>";
}

template<class K, class V>
void Visualizador<K, V>::dibujarSubArbol(int x, int y) //posiciones absolutas para el centro del nodo padre
{
	int desplazamiento = 150 + ((*iterador) == arbol->raiz? 10*cantNodos : 0); //150px entre nivel de nodos, más si es el nodo raiz
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
		dibujarRectangulo(x-RADIO, y-RADIO, (*iterador)->color);
		dibujarTexto(x, y, *iterador);
		++iterador;
	}	
}

template<class K, class V>
inline Visualizador<K, V>::Visualizador(Arbol<K, V> *arbol) 
: arbol(arbol), paso(1), cantNodos(0), iterador(arbol->begin())
{	
}

template<class K, class V>
void Visualizador<K, V>::dibujar(std::vector<std::string> instrucciones)
{	
	cantNodos = arbol->size();
	iterador = arbol->begin();
	int width = 1350 + (cantNodos < 7? 0 : cantNodos*25);
	int height = 600 + (cantNodos < 7? 0 : cantNodos*25);
	std::string nombreArchivo = "dibujo";
	nombreArchivo += std::to_string(paso);
	nombreArchivo += ".svg";
	dibujo.open(nombreArchivo, std::ios::out);
	dibujo << "<?xml version='1.0' encoding='UTF-8' ?>\n<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='" << width << "' height='" << height << "px'>\n";
	dibujarSubArbol(width/2, 50);
	if(!instrucciones.empty())
		imprimirInstrucciones(instrucciones);
	dibujo << "</svg>";
	dibujo.close();
	dibujos.push_back(nombreArchivo);
	++paso;
}

template<class K, class V>
void Visualizador<K, V>::generarHTML(char *salida)
{
	strcat(salida, ".html");
	std::fstream archivo(salida, std::ios::out);
	archivo << "<!DOCTYPE html>\n<html>\n<body>\n";
	for(std::vector<std::string>::iterator i = dibujos.begin(); i != dibujos.end(); ++i){
		archivo << "<img src=\"" << (*i) << "\"></img>\n";
	}
	archivo << "</body>\n</html>";
	std::cout << "Arbol listo!\nAbra el archivo " << salida << std::endl; 
}