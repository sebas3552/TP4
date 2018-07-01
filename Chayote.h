#ifndef CHAYOTE_H
#define CHAYOTE_H
#include <iostream>
#include <string>
class Chayote
{
	private:
		double peso;
		std::string fechaCaducidad;
		
	public:
	
		Chayote(double p) : peso(p) { }
		bool operator==(const Chayote &otro){ return peso == otro.peso; }
		bool operator!=(const Chayote &otro){ return peso != otro.peso; }
		bool operator<(const Chayote &otro){ return peso < otro.peso; }
		bool operator<=(const Chayote &otro){ return peso <= otro.peso; }
		bool operator>(const Chayote &otro){ return peso > otro.peso; }
		bool operator>=(const Chayote &otro){ return peso >= otro.peso; }
		friend std::ostream &operator<<(std::ostream &salida, Chayote &chayote){ salida << chayote.peso; return salida; }
};
#endif