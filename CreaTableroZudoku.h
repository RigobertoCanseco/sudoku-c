#ifndef CREARZUDOKU_h
#define CREARZUDOKU_h
#include <iostream>
#include <array>
using namespace std;
using namespace std::tr1 ;
typedef array<int, 9> Fila ;
typedef array<Fila, 9> Matriz ;

class CreaTableroZudoku
{

public:
	CreaTableroZudoku(void);
	~CreaTableroZudoku(void);
	//mejorar con listas ligadas
	void creaTablero( Matriz &numeros );//metodo para crear el sudoku en un arreglo de 9X9
	int elementoArreglo(int fila, int columna, Matriz numeros );
	void insertarNumero( int num, int fila, int columna, Matriz &numeros );
private:
	bool numero_rep_cuadrante(int numero, int fila, int columna, Matriz numeros);
	bool numero_rep_fila(int numero, int fila, int columna, Matriz numeros);
	bool numero_rep_columna(int numero, int fila, int columna, Matriz numeros);
	bool numero_repetido(int numero,int fila,int columna, Matriz numeros);

};
#endif

