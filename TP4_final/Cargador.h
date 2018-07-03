#ifndef Cargador_H
#define Cargador_H
#include "Arbol.h"
#include <string>
#include <fstream>
#include <iostream>
/**@class Cargador
*En esta clase se realiza la identificación de los tipos parametrizados para el árbol y sus elementos, los cuales fueron extraídos desde el archivo por el 
*main. Al identificar cada tipo, seguidamente carga los elementos desde el archivo hasta que se alcanza el número de pares que el mismo especifica.
*Se tuvo que implementar casi el mismo código en todos los casos if dado que se necesitan variables para extraer el flujo de datos con formato desde el archivo,
*para cargarlos como variables de tipo definido en el árbol.
*/
class Cargador
{
	private:
		/**String que representa el tipo integral de la llave.*/
		std::string tipoLlave;
		/**String que representa el tipo integral del valor.*/
		std::string tipoValor;
		/**Cantidad de pares especificados en el archivo.*/
		int cantElementos;
		/**Máximos caracteres permitidos para una cadena de caracteres, por ancho de figuras svg.*/
		const int MAX = 10; 
		
	public: 
		/**Constructor que requiere el tipo de la llave y valor de los elementos, así como la cantidad de elementos, leídos en el main.*/
		Cargador(std::string tipoLlave, std::string tipoValor, int cantElementos)
		: tipoLlave(tipoLlave), tipoValor(tipoValor), cantElementos(cantElementos) { }
		
		/**Función principal que identifica los tipos integrales especificados en el archivo para la creación de la especialización de plantilla del árbol.
		*También carga los elementos hasta alcanzar el número especificado por cantElementos.
		*@param entrada Archivo de entrada para leer los datos de los pares.
		*@param salida Nombre del archivo de salida para generar el html con los dibujos svg.
		*/
		void generarArbol(std::fstream &entrada, char *salida)
		{
			if(tipoLlave == "int" && tipoValor == "int"){
				Arbol<int, int> *arbol = new Arbol<int, int>();
				int key = 0;
				int value = 0;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "int" && tipoValor == "double"){
				Arbol<int, double> *arbol = new Arbol<int, double>();
				int key = 0;
				double value = 0;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "int" && tipoValor == "char"){
				Arbol<int, char> *arbol = new Arbol<int, char>();		
				int key;
				char value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "int" && tipoValor == "string"){
				Arbol<int, std::string> *arbol = new Arbol<int, std::string>();
				int key;
				std::string value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key;
					std::getline(entrada, value);
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "int" && tipoValor == "char*"){
				Arbol<int, const char *> *arbol = new Arbol<int, const char *>();
				int key;
				char *value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					value = new char[MAX+1];
					entrada >> key;
					entrada.ignore();
					entrada >> value;
					arbol->push_back(key,value);
				}
				delete arbol;
			}
			if(tipoLlave == "double" && tipoValor == "int"){
				Arbol<double, int> *arbol = new Arbol<double, int>();
				double key;
				int value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "double" && tipoValor == "double"){
				Arbol<double, double> *arbol = new Arbol<double, double>();
				double key;
				double value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "double" && tipoValor == "char"){
				Arbol<double, char> *arbol = new Arbol<double, char>();
				double key;
				char value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "double" && tipoValor == "string"){
				Arbol<double, std::string> *arbol = new Arbol<double, std::string>();
				double key;
				std::string value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key;
					std::getline(entrada, value);
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "double" && tipoValor == "char*"){
				Arbol<double, const char *> *arbol = new Arbol<double, const char *>();
				double key;
				char *value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					value = new char[MAX+1];
					entrada >> key;
					entrada.ignore();
					entrada >> value;
					arbol->push_back(key,value);
				}
				delete arbol;
			}
			if(tipoLlave == "char" && tipoValor == "int"){
				Arbol<char, int> *arbol = new Arbol<char, int>();
				char key;
				int value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char" && tipoValor == "double"){
				Arbol<char, double> *arbol = new Arbol<char, double>();
				char key;
				double value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char" && tipoValor == "char"){
				Arbol<char, char> *arbol = new Arbol<char, char>();
				char key;
				char value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char" && tipoValor == "string"){
				Arbol<char, std::string> *arbol = new Arbol<char, std::string>();
				char key;
				std::string value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key;
					std::getline(entrada, value);
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char" && tipoValor == "char*"){
				Arbol<char, const char *> *arbol = new Arbol<char, const char *>();
				char key;
				char *value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					value = new char[MAX+1];
					entrada >> key;
					entrada.ignore();
					entrada >> value;
					arbol->push_back(key,value);
				}
				delete arbol;
			}
			if(tipoLlave == "string" && tipoValor == "int"){
				Arbol<std::string, int> *arbol = new Arbol<std::string, int>();
				std::string key;
				int value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "string" && tipoValor == "double"){
				Arbol<std::string, double> *arbol = new Arbol<std::string, double>();
				std::string key;
				double value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "string" && tipoValor == "char"){
				Arbol<std::string, char> *arbol = new Arbol<std::string, char>();
				std::string key;
				char value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "string" && tipoValor == "string"){
				Arbol<std::string, std::string> *arbol = new Arbol<std::string, std::string>();
				std::string key;
				std::string value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					entrada >> key;
					std::getline(entrada, value);
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "string" && tipoValor == "char*"){
				Arbol<std::string, const char *> *arbol = new Arbol<std::string, const char *>();
				std::string key;
				char *value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					value = new char[MAX+1];
					entrada >> key;
					entrada.ignore();
					entrada >> value;
					arbol->push_back(key,value);
				}
				delete arbol;
			}
			if(tipoLlave == "char*" && tipoValor == "int"){
				Arbol<const char *, int> *arbol = new Arbol<const char *, int>();
				char *key;
				int value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					key = new char[MAX+1];
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char*" && tipoValor == "double"){
				Arbol<const char *, double> *arbol = new Arbol<const char *, double>();
				char *key;
				double value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					key = new char[MAX+1];
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char*" && tipoValor == "char"){
				Arbol<const char *, char> *arbol = new Arbol<const char *, char>();
				char *key;
				char value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					key = new char[MAX+1];
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char*" && tipoValor == "string"){
				Arbol<const char *, std::string> *arbol = new Arbol<const char *, std::string>();
				char *key;
				std::string value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					key = new char[MAX+1];
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
			if(tipoLlave == "char*" && tipoValor == "char*"){
				Arbol<const char *, const char *> *arbol = new Arbol<const char *, const char *>();
				char *key;
				char *value;
				arbol->setNombreArchivoSalida(salida);
				for(int i = 0; i < cantElementos; i++){
					key = new char[MAX+1];
					value = new char[MAX+1];
					entrada >> key >> value;
					arbol->push_back(key, value);
				}
				delete arbol;
			}
		}	
};
#endif