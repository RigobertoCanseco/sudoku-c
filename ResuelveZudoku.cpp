#include "ResuelveZudoku.h"


ResuelveZudoku::ResuelveZudoku(void)
{

}
void ResuelveZudoku::vaciarPila(Stack_Int &Pila)
{
	while (! Pila.empty()) {
		Pila.pop() ;
	}
}
void ResuelveZudoku::insertarNumero( int num, int fila, int columna, Matriz & Numeros )
{
	Numeros[fila][columna] = num;
}
void ResuelveZudoku::almacenaNumFila(Matriz &Numeros, int fila)
{
	for(int i=0;i<9;i++)
		insertarNodo( Numeros[fila][i] );
}
void ResuelveZudoku::almacenaNumColumna(Matriz &Numeros, int columna)
{
	for(int j=0;j<9;j++)
		insertarNodo( Numeros[j][columna]);
}
void ResuelveZudoku::almacenaNumCuadricula(Matriz &Numeros,int fila, int columna)
{
	for( int h = int(fila/3)*3; h <= ( (int(fila/3)*3)+2 ); h++ )//recore el cuadrante 
		for( int k = int(columna/3)*3; k <= ( (int(columna/3)*3) + 2 ); k++ )
			insertarNodo( Numeros[ h ][ k ] );
}
void ResuelveZudoku::numerosPosibles(Stack_Int &NumerosPosibles, Stack_Int &NumerosInvalidos)
{
	for(int num=1; num<10; num++)
	{
		if ( buscar_elemento( num ) == true ){//busca el numero dentro del arbol binario
			NumerosInvalidos.push( num );//almacena en una pila el numero repetido
		}
		else {
			NumerosPosibles.push( num );//alamcena en una pila los posibles numeros no repetidos
			//cout<< num << ", ";
		}
	}
}
int ResuelveZudoku::CuadriculasVacias(Matriz &Numeros,int posyCuad, int posxCuad)
{
	int casillas_vacias=0;
	for( int h = posyCuad*3 ; h <= (posyCuad*3) + 2; h++ ) //recore el cuadrante 
		for( int k = posxCuad*3 ; k <=  posxCuad*3 + 2 ; k++ )
			if(  Numeros[ h ][ k ] == 0 )
				casillas_vacias++;
	return casillas_vacias;
}
void ResuelveZudoku::limpiaNumeros(Matriz &Numeros)
{
	for(int j=0; j<9; j++)
		for(int i=0; i<9; i++)
			if(Numeros[j][i] == EXTER_NUM)
				insertarNumero( 0, j, i, Numeros );


}
void ResuelveZudoku::busquedaPorCasilla( Matriz &Numeros, int fila, int columna)
{
	
	if( Numeros[fila][columna] == 0 )//si esta vacia una casilla
	{
		vaciar_arbol();
		vaciarPila(NumerosPosibles);
		vaciarPila(NumerosInvalidos);
		//almacena todos los numeros de la fila en el arbol binario
		almacenaNumFila( Numeros, fila );
		//almacena todos los numeros de la columna en el arbol binario
		almacenaNumColumna( Numeros, columna );
		//almacena todos los numeros de la cuadricula en el arbol binario
		almacenaNumCuadricula( Numeros, fila, columna );
		//cout<<"en la posicion "<<"[ "<<fila<<", "<<columna<<" ]"<< "  posibles numero  ";
		numerosPosibles( NumerosPosibles, NumerosInvalidos);//encuentra los posibles numeros
		//cout<<endl;
		recorridoInOrden();//ordena los numeros
		if( NumerosPosibles.size()==1 )//si hay un solo posible numero entonces lo almacena
		{
			insertarNumero( NumerosPosibles.top(), fila, columna, Numeros );
			cout<<"en la posicion "<<"[ "<<fila<<", "<<columna<<" ]"<< " numero  ";
			cout<< Numeros[fila][columna] <<endl;
		}
	}
}
void ResuelveZudoku::busquedaGeneral( Matriz &Numeros, int numero)
{
	int numeroMap;
	vaciarPila(NumerosPosibles);
	vaciarPila(NumerosInvalidos);
	numeroMap = numero;
	//cout<< "numero a mapear  "<< numeroMap << endl;
	for(int fila=0; fila<9; fila++){
		for(int columna=0; columna<9; columna++)
		{
			if( Numeros[fila][columna] == numeroMap )
			{
				for( int h = int(fila/3)*3; h <= ( (int(fila/3)*3)+2 ); h++ )//recore el cuadrante 
					for( int k = int(columna/3)*3; k <= ( (int(columna/3)*3) + 2 ); k++ )
						if(  Numeros[ h ][ k ] == 0 )
							insertarNumero( EXTER_NUM, h, k, Numeros );
						
				for(int i=0; i<9; i++)
					if(  Numeros[ fila ][ i ] == 0 )
						insertarNumero( EXTER_NUM, fila, i, Numeros );
				for(int j=0; j<9; j++)
					if(  Numeros[ j ][columna ] == 0 )
						insertarNumero( EXTER_NUM, j, columna, Numeros );
			}
		}
	}
	for(int j=0; j<3; j++)
		for(int i=0; i<3; i++)
			if( CuadriculasVacias(Numeros,j,i)==1 )
				for( int h = j*3 ; h <= (j*3) + 2; h++ ) //recore el cuadrante 
					for( int k = i*3 ; k <=  i*3 + 2 ; k++ )
						if(  Numeros[ h ][ k ] == 0 ){
							cout<<"en la posicion "<<"[ "<<h<<", "<<k<<" ]"<< " numero  ";
							cout<< numeroMap <<endl;
							insertarNumero( numeroMap, h, k, Numeros );
						}
		limpiaNumeros(Numeros);
}
void ResuelveZudoku::resolver_zudoku( Matriz &Numeros )
{
	for(int fila=0;fila<9;fila++)
		for(int columna=0; columna<9; columna++)
			busquedaPorCasilla( Numeros, fila, columna );
	for(int numero=1;numero<=9;numero++)
		busquedaGeneral(Numeros, numero);
	

}
ResuelveZudoku::~ResuelveZudoku(void)
{
}