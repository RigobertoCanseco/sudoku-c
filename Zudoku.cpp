#include "Zudoku.h"
#include <time.h>

Zudoku::Zudoku()
{
	
}
Zudoku::~Zudoku(void)
{
}
void Zudoku::imprime_numeros()
{
}
void Zudoku::ocultar_numeros(int limite )
{
	int columna, fila;
	int contador=0;

	while( contador!= limite ){
		fila = rand()%9;
		columna = rand()%9;
		if( Numeros[fila][columna] != 0 ){
			Numeros[fila][columna] = 0 ;
		    contador++;
		}
	}

}
void Zudoku::crea_Zudoku()
{
	creaTablero( Numeros );//crea zudoku en un arreglo de 9x9
}
void  Zudoku::resolver()
{
	 resolver_zudoku( Numeros );
}
void Zudoku::guardar_zudoku(const char *nombre, Codigo& ok)
{
	escribir_fich(nombre, ok, Numeros);
}