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
		switch (fecha_i.get_tipo_error()) {
		case Fecha_a_Dia::error::DIA:
			cout << "Error: D�a fuera de rango.\n"; break;
		case Fecha_a_Dia::error::MES:
			cout << "Error: Mes fuera de rango.\n"; break;
		case Fecha_a_Dia::error::ANIO:
			cout << "Error: A�o fuera de rango.\n"; break;
		case Fecha_a_Dia::error::DIA_30:
			cout << "Error: D�a de " << fecha_i.get_mes_ingresado() << " es mayor a 30 d�as.\n"; break;
		case Fecha_a_Dia::error::DIA_BIS:
			cout << "Error: D�a de " << fecha_i.get_mes_ingresado() << " es mayor a 28 o 29 d�as.\n"; break;
		case Fecha_a_Dia::error::ANIO_M:
			cout << "Error: A�o ingresado es mayor a a�o actual.\n"; break;
		}
		cout << "Ingrese una fecha correcta: "; getline(cin, fecha);
	}
	fecha_i.set_fecha_ingresada(fecha);
	cout << "La fecha ingresada de la fecha actual se separa por " << fecha_i.get_cantidad_de_dias() << " d�as.\n";
	system("pause");
	return 0;
}