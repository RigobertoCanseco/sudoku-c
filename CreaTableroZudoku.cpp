#include "CreaTableroZudoku.h"
#include <time.h>

CreaTableroZudoku::CreaTableroZudoku(void)
{
}
CreaTableroZudoku::~CreaTableroZudoku(void)
{
}
void CreaTableroZudoku::insertarNumero( int num, int fila, int columna, Matriz & numeros )
{
	numeros[fila][columna] = num;
}
int CreaTableroZudoku::elementoArreglo(int fila, int columna, Matriz numeros )
{
	return numeros[fila][columna];
}
//retorna false si no hay un numero repetido en los cuadrantes
bool CreaTableroZudoku::numero_rep_cuadrante(int numero, int fila, int columna, Matriz numeros)
{
		bool repetido=false;
		for( int h = int(fila/3)*3; h <= fila; h++ )//recore el cuadrante 
			for( int k = int(columna/3)*3; k <= ( (int(columna/3)*3) + 2 ); k++ )
					if(numeros[ h ][ k ] == numero) repetido = true;
		if( repetido == true)return true; 
		else return false;
}
//retorna false si no hay un numero repetido en la fila 
bool CreaTableroZudoku::numero_rep_fila(int numero, int fila, int columna, Matriz numeros)
	{
		bool repetido=false;
		for( int h=fila ; h>=0; --h)
			if( numeros[ h ][ columna ] == numero)
				repetido = true;	
		if( repetido == true)return true; 
		else return false;
	}
//retorna false si no hay un numero repetido en la columna
bool CreaTableroZudoku::numero_rep_columna(int numero, int fila, int columna, Matriz numeros)
	{
		bool repetido=false;
		for( int k=columna; k>=0; --k )
			if( numeros[ fila ][ k ] == numero)
				repetido = true;
		if( repetido == true)return true; 
		else return false;
	}
//retorna false si no hay numero repetido
bool CreaTableroZudoku::numero_repetido(int numero,int fila,int columna, Matriz numeros)
	{
		if( numero_rep_columna(numero, fila, columna, numeros )||
			numero_rep_fila(numero, fila, columna, numeros)||
			numero_rep_cuadrante(numero, fila, columna, numeros ) == true)
			return true;
		else 
			return false;
	}
void CreaTableroZudoku::creaTablero( Matriz &numeros )//mejorar con listas ligadas
{
	
	srand(time(0));
	int columna=0, fila=0;
	int numero,iteraciones=0;
	int error=0;
	while( fila<9)
	{
		if(error>30)
		{
			if(columna==0)
			{
				fila--;
			}
			for(int k=columna; k >= 0; k--)
			{
				numeros[ fila ] [ columna ] = 0;
			}
			columna =0;
			error = 0;
		}
		numero=rand()%9+1;
		if( numero_repetido( numero, fila, columna, numeros) == false )
		{
			insertarNumero( numero, fila, columna, numeros );
			if( columna<8 )columna++;
			else{
				fila++;
				columna=0;
			}
			error=0;
		}
		else error++;
		iteraciones++;
	}
	cout<<"numero de iteraciones:   " <<iteraciones<<endl;
	
}