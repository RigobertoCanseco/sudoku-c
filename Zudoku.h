
#ifndef ZUDOKU_h
#define ZUDOKU_h
#include <iostream>
#include "CreaTableroZudoku.h"
#include "ResuelveZudoku.h"
#include "Archivo.h"
class Zudoku:private CreaTableroZudoku, ResuelveZudoku,public Archivo
{
public:
	Zudoku(void);
	~Zudoku(void);
	void crea_Zudoku();
	void guardar_zudoku(const char* nombre, Codigo& ok);
	void imprime_numeros();//**
	void ocultar_numeros(int limite );
	void resolver();
private:
	Matriz Numeros;
};
#endif
