#ifndef RESUELVE_H
#define RESUELVE_H
#define EXTER_NUM -1
#include <iostream>
#include <array>
#include <stack>
#include "Arbol.h"
using namespace std;
using namespace std::tr1 ;
typedef array<int, 9> Fila ;
typedef array<Fila, 9> Matriz ;
typedef std::stack<int> Stack_Int ;
class ResuelveZudoku: private Arbol<int>
{
public:
	ResuelveZudoku(void);
	void resolver_zudoku(Matriz &Numeros);//detalles para poder resolver
	~ResuelveZudoku(void);
private:
	Stack_Int NumerosPosibles;
	Stack_Int NumerosInvalidos;
	void vaciarPila( Stack_Int &Pila);
	void busquedaPorCasilla( Matriz &Numeros, int fila, int columna);
	void busquedaGeneral( Matriz &Numeros, int numero);//mejorar listas ligadas
	void almacenaNumFila( Matriz &Numeros, int fila);
	void almacenaNumColumna( Matriz &Numeros, int columna);
	void almacenaNumCuadricula( Matriz &Numeros,int fila, int columna);
	void numerosPosibles(Stack_Int &NumerosPosibles, Stack_Int &NumerosInvalidos);
	void insertarNumero( int num, int fila, int columna, Matriz & Numeros );
	int CuadriculasVacias(Matriz &Numeros,int posyCuad, int posxCuad);
	void limpiaNumeros(Matriz &Numeros);
};
#endif

