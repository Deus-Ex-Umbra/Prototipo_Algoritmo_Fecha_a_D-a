#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<string>
using namespace std;
class Fecha_a_Dia
{
private:
	string fecha_actual, fecha_in, dia_a, mes_a, anio_a, dia, mes, anio, hora_a, minuto_a, segundo_a;
	int cantidad_de_dias;
	void set_fecha_actual() {
		time_t f;
		struct tm fa = {0};
		errno_t e = time(&f);
		localtime_s(&fa, &f);
		anio_a = to_string(fa.tm_year + 1900); mes_a = to_string(fa.tm_mon + 1); dia_a = to_string(fa.tm_mday); hora_a = to_string(fa.tm_hour); minuto_a = to_string(fa.tm_min); segundo_a = to_string(fa.tm_sec);
		anio_a = (stoi(anio_a) < 10) ? "000" + anio_a : ((stoi(anio_a) < 100) ? "00" + anio_a : ((stoi(anio_a) < 1000) ? "0" + anio_a : anio_a));
		mes_a = (stoi(mes_a) < 10) ? "0" + mes_a : mes_a;
		dia_a = (stoi(dia_a) < 10) ? "0" + dia_a : dia_a;
		hora_a = (stoi(hora_a) < 10) ? "0" + hora_a : hora_a;
		minuto_a = (stoi(minuto_a) < 10) ? "0" + minuto_a : minuto_a;
		segundo_a = (stoi(segundo_a) < 10) ? "0" + segundo_a : segundo_a;
		fecha_actual = dia_a + "/" + mes_a + "/" + anio_a + "[" + hora_a + ":" + minuto_a + ":" + segundo_a + "]";
	}
	void set_dia_mes_anio(string _fecha_c) {
		if (!es_un_numero(_fecha_c))
		{
			int pos_no_digit1 = _fecha_c.find_first_not_of("0123456789");
			int pos_digit1 = _fecha_c.find_first_of("0123456789", pos_no_digit1 + 1);
			int pos_no_digit2 = _fecha_c.find_first_not_of("0123456789", pos_digit1 + 1);
			int pos_digit2 = _fecha_c.find_first_of("0123456789", pos_no_digit2 + 1);
			dia = _fecha_c.substr(0, pos_no_digit1);
			mes = _fecha_c.substr(pos_digit1, pos_no_digit2 - pos_digit1);
			anio = _fecha_c.substr(pos_digit2);
		}else {
			dia = _fecha_c.substr(0, 2);
			mes = _fecha_c.substr(2, 2);
			anio = _fecha_c.substr(4);
		}
		dia = (stoi(dia) < 10 && dia.length() == 1) ? "0" + dia : dia;
		mes = (stoi(mes) < 10 && mes.length() == 1) ? "0" + mes : mes;
		anio = (stoi(anio) < 10 && anio.length() == 1) ? "0" + anio :((stoi(anio) < 100 && anio.length() == 2) ? "00" + anio : ((stoi(anio) < 1000 && anio.length() == 3) ? "000" + anio : anio));
	}
	bool es_un_numero(string _fecha_c) {
		for (char _fecha : _fecha_c) {
			if (!isdigit(_fecha)) { return false; }
		}
		return true;
	}
	bool anio_bisiesto(string _anio_c) {
		return (stoi(_anio_c) % 100 == 0) ? (stoi(_anio_c) % 400 == 0) : (stoi(_anio_c) % 4 == 0);
	}
	int get_cantidad_anio_bisiesto(int anio) {
		return (anio / 4 - anio / 100 + anio / 400);
	}
	int suma_meses(vector <int> _meses, int _cantidad_mes) {
		int suma = 0;
		int index = 0;
		for (int indice : _meses) {
			suma += indice; index++; if (index >= _cantidad_mes) { break; }
		}
		cout << suma << "\n";
		return suma;
	}
public:
	Fecha_a_Dia() : cantidad_de_dias(0){
		set_fecha_actual();
	}
	bool fecha_correcta(string _fecha_c) {
		try {
			set_dia_mes_anio(_fecha_c);
			if ((stoi(dia) <= 0) || (stoi(dia) >= 31)) { tipo_error = DIA; return false; }
			if ((stoi(mes) <= 0) || stoi(mes) > 12) { tipo_error = MES; return false; }
			if (stoi(anio) < 0) { tipo_error = ANIO; return false; }
			if (((stoi(dia) > 30) && (stoi(mes) == 4)) || ((stoi(dia) > 30) && (stoi(mes) == 6)) || ((stoi(dia) > 30) && (stoi(mes) == 9)) || ((stoi(dia) > 30) && (stoi(mes) == 11))) { tipo_error = DIA_30; return false; }
			if ((anio_bisiesto(anio) && stoi(dia) > 29) || (!anio_bisiesto(anio) && stoi(dia) > 28)) { tipo_error = DIA_BIS; return false; }
			if (stoi(anio) > stoi(anio_a)) { tipo_error = ANIO_M; return false; }
			return true;
		} catch (const exception& e) {
			cout << "Error: Usted ha ingresado una fecha en un formato no aceptable. " << e.what() << "\n"; return false;
		}
	}
	void set_fecha_ingresada(string _fecha_ingresar) {
		set_dia_mes_anio(_fecha_ingresar);
		cout << "La fecha es correcta.\n";
		fecha_in = dia + "/" + mes + "/" + anio;
		cout << "La fecha es: " << fecha_in << "\n";
	}
	string get_dia_ingresado() { return dia; }
	string get_mes_ingresado() { return mes; }
	string get_anio_ingresado() { return anio; }
	string get_fecha_ingresada() { return fecha_in; }
	string get_fecha_actual() { return fecha_actual; }
	int get_cantidad_de_dias() {
		vector <int> meses = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int dias_a = stoi(dia_a) + suma_meses(meses, stoi(mes_a)) + stoi(anio_a) * 365 + get_cantidad_anio_bisiesto(stoi(anio_a));
		int dias = stoi(dia) + suma_meses(meses, stoi(mes)) + stoi(anio) * 365 + get_cantidad_anio_bisiesto(stoi(anio));
		cantidad_de_dias = dias_a - dias;
		return cantidad_de_dias;
	}
	enum error { NINGUNO, DIA, MES, ANIO, DIA_30, DIA_BIS, ANIO_M };
	error tipo_error = NINGUNO;
	int get_tipo_error() { return tipo_error; }
};

