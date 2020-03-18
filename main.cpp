

//***************************************************************************************
//ZUDOKU                 Rigoberto Canseco                                   2013
//**************************************************************************************
#include "Zudoku.h"
#include <iostream>
using namespace std;

int main()
{	
	Codigo ok ;//para guardar el el zudoku en un .txt
	int num;
	Zudoku z;
	z.crea_Zudoku(); 
	z.guardar_zudoku("zudoku1.txt",ok);
	z.imprime_numeros();
	cout << "ingresa los numeros a ocultar:  ";
	cin >> num;
	z.ocultar_numeros(num);
	z.imprime_numeros();
	while( !key[KEY_ESC] )
	{
		z.resolver();
		z.imprime_numeros();

	}
	return 0;//sale
}