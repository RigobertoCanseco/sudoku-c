#pragma once
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;
using namespace std::tr1 ;
typedef array<int, 9> Fila ;
typedef array<Fila, 9> Matriz ;
enum Codigo {
	OK, ERROR_APERTURA, ERROR_FORMATO
};
class Archivo
{
public:
	Archivo(void);
	~Archivo(void);
	void leer_fich(const string& nombre_fichero, Codigo& ok)
	{
		ifstream f_ent ;
		f_ent.open(nombre_fichero.c_str()) ;
		if (f_ent.fail()) {
			ok = ERROR_APERTURA ;
		} else {
			int numero ;
			f_ent >> numero ;
			while (! f_ent.fail()) {
				procesar(numero) ;
				f_ent >> numero ;
			}
			if (f_ent.eof()) {
				ok = OK ;
			} else {
				ok = ERROR_FORMATO ;
			}
			f_ent.close() ;
		}
	}
	void escribir_fich(const char *nombre, Codigo& ok,Matriz &num )
	{
		ofstream f_sal ;
		f_sal.open(nombre) ;
		if (f_sal.fail()) {
			ok = ERROR_APERTURA ;
		} else {
			for(int i=0;i<9;i++)
			{
				for(int j=0;j<9;j++)
				{
					f_sal<<num[i][j]<<"\t";
				}
				f_sal<<endl;
			}
			if ( ! f_sal.fail()) {
				ok = OK ;
			} else {
				ok = ERROR_FORMATO ;
			}
			f_sal.close() ;
		}
	}
private:
	void codigo_error(Codigo ok)
	{
		switch (ok) {
		case OK:
		cout << "Fichero procesado correctamente" << endl ;
		break ;
		case ERROR_APERTURA:
		cout << "Error en la apertura del fichero" << endl ;
		break ;
		case ERROR_FORMATO:
		cout << "Error de formato en la lectura del fichero" << endl ;
		break ;
		}
	}
	
	void procesar(int num)
	{
		cout << num << endl ;
	}
};

