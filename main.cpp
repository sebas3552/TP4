#include "arbolCopia2.h"
using namespace std;

int main()
{
	Arbol<int, const char *> *a = new Arbol<int, const char *>();
	a->agregar(5, "cinco");
	a->agregar(6, "seis");
	a->agregar(4, "cuatro");
	a->agregar(2, "dos");
	a->agregar(1, "uno");
	a->agregar(7, "siete");
	a->agregar(8, "ocho");
	a->agregar(9, "nueve");
	a->agregar(3, "tres");
	a->agregar(-2, "menos dos");
	//a->operator<<(cout);
	Arbol<int, const char *>::Iterator i = a->begin();
	for(i; *i != nullptr ; ++i){
		(*i)->imprimir(cout) << endl;
	}
	i = a->begin();
	Arbol<int, const char*>::Iterator j(i);
	for(int l = 0; l < 3; l++)
		++j;
	Intermedio<int> *intermedio = new Intermedio<int>(-4);
	/*cambia el nodo 2 por el nuevo nodo -4*/
	j = intermedio;
	cout << "despues del cambio, imprimiendo con i: " << endl;
	for(i; i != a->end() ; ++i){
		(*i)->imprimir(cout) << endl;
	}
	cout << "imprimiendo con j: " << endl;
	for(j = a->begin(); j != a->end() ; ++j){
		(*j)->imprimir(cout) << endl;
	}
	delete a;
	return 0;
}