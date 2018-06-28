#include "Visualizador.h"
using namespace std;

int main()
{
	/*a->agregar(5, "cinco");
	a->agregar(6, "seis");
	a->agregar(4, "cuatro");
	a->agregar(2, "dos");
	a->agregar(1, "uno");
	a->agregar(7, "siete");
	a->agregar(8, "ocho");
	a->agregar(9, "nueve");
	a->agregar(3, "tres");
	a->agregar(-2, "menos dos");*/
	Hoja<int, const char *> *hoja1 = new Hoja<int, const char*>(5, "cinco");
	Hoja<int, const char *> *hoja2 = new Hoja<int, const char*>(6, "seis");
	Hoja<int, const char *> *hoja3 = new Hoja<int, const char*>(4, "cuatro");
	Hoja<int, const char *> *hoja4 = new Hoja<int, const char*>(2, "dos");
	Hoja<int, const char *> *hoja5 = new Hoja<int, const char*>(1, "uno");
	Hoja<int, const char *> *hoja6 = new Hoja<int, const char*>(7, "siete");
	Hoja<int, const char *> *hoja7 = new Hoja<int, const char*>(8, "ocho");
	Hoja<int, const char *> *hoja8 = new Hoja<int, const char*>(9, "nueve");
	Hoja<int, const char *> *hoja9 = new Hoja<int, const char*>(3, "tres");
	Hoja<int, const char *> *hoja10 = new Hoja<int, const char*>(-2, "menos dos");
	Hoja<int, const char *> *hoja11 = new Hoja<int, const char*>(20, "veinte");
	Hoja<int, const char *> *hoja12 = new Hoja<int, const char*>(21, "veintiuno");
	Arbol<int, const char *> a = {hoja1, hoja2, hoja3, hoja4, hoja5, hoja6, hoja7, hoja8, hoja9, hoja10, hoja11, hoja12};
	//a->operator<<(cout);	
	Arbol<int, const char *>::Iterator i = a.begin();
	Visualizador<int, const char *> *v = new Visualizador<int, const char *>(&a, i);
	v->dibujar();
	Arbol<int, const char*>::Iterator j(i);
	for(int l = 0; l < 19; l++)
		++j;
	Hoja<int, const char *> *intermedio = new Hoja<int, const char*>(-3, "menos tres");
	//cambia el nodo 2 por el nuevo nodo -4
	j = intermedio;
	i = a.begin();
	v->dibujar();
	delete v;
	delete hoja1;
	//delete a;
	return 0;
}