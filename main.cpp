#include "Arbol.h"
using namespace std;

int main()
{
	Arbol<int, const char *> *a = new Arbol<int, const char *>();
	a->agregar(5, "cinco");
	a->agregar(3, "tres");
	a->agregar(8, "ocho");
	a->agregar(2, "dos");
	a->agregar(10, "diez");
	a->operator<<(cout);
	delete a;
	return 0;
}