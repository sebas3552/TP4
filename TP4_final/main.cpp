#include "Visualizador.h"
#include "Arbol.h"
#include "Cargador.h"
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	
	if(!strncmp(argv[1], "-i", 2)){
		fstream archivo(argv[2], ios::in);
		if(!archivo){
			cout << "No se encontró el archivo \"" << argv[2] << "\"!";
			exit(1);
		}
		string tipoLlave;
		string tipoValor;
		int cantElementos = 0;
		try{
			archivo >> tipoLlave >> tipoValor >> cantElementos;
			Cargador *cargador = new Cargador(tipoLlave, tipoValor, cantElementos);
			cargador->generarArbol(archivo, argv[4]);
			delete cargador;
		}catch(exception &e){
			cerr << e.what() << endl;
		}
	}else{
		cerr << "Argumentos invalidos!" << endl;
		exit(1);
	}
	return 0;
}