#include "Visualizador.h"
#include <vector>
#include <utility>
#include <string>
using namespace std;

int main()
{
	vector<pair<int, char>> hojas;
	int num = 0;
	char c = 'a';
	cout << "Inserte elementos o digite -1 para terminar" << endl;
	while(cin >> num && num != -1){
		hojas.push_back(make_pair(num, c++));
	}
	Arbol<int, char> *a = new Arbol<int, char>();	
	Visualizador<int, char> *v = new Visualizador<int, char>(a);
	for(int i = 0; i < hojas.size(); i++)
	{
		v->dibujar(a->agregar(hojas[i].first, hojas[i].second));
	}
	delete v;
	delete a;
	return 0;
}