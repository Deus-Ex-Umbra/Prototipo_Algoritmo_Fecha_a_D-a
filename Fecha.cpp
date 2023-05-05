#include<iostream>
#include"Fecha_a_Dia.h"
#include<string>
using namespace std;
int main(int argv, char** argc) {
	string fecha;
	Fecha_a_Dia fecha_i;
	cout << "----------------------------------------------------\n";
	cout << "La fecha actual es: " << fecha_i.get_fecha_actual() << "\n";
	cout << "----------------------------------------------------\n";
	cout << "Ingrese una fecha: "; getline(cin, fecha);
	cout << "----------------------------------------------------\n";
	while (!fecha_i.fecha_correcta(fecha)) {
		cout << "Ingrese una fecha correcta: "; cin.ignore();  getline(cin, fecha);
	}
	fecha_i.set_fecha_ingresada(fecha);
	return 0;
}