#ifndef ARBOL_H
#define ARBOL_H
#include "Nodo_Arbol.h"

template < typename TIPONODO > class Arbol
{
public:
	Arbol();
	void insertarNodo( TIPONODO & ) ;
	int numero_elementos();
	bool buscar_elemento( TIPONODO & );
	void recorridoPreOrden() ;
	void recorridoInOrden() ;
	void recorridoPostOrden() ;
	void recorridoDecOrden() ;
	void vaciar_arbol();
	~Arbol();
private:
	NodoArbol < TIPONODO > *raizPtr;
	int numeroelem;
	//funciones utilitarias
	bool ayudanteBuscarElemento( NodoArbol <TIPONODO> **,TIPONODO & );
	void ayudanteInsertarNodo( NodoArbol < TIPONODO > **, TIPONODO & );
	void ayudantePreOrden( NodoArbol < TIPONODO > * ) ;
	void ayudanteDecOrden( NodoArbol < TIPONODO > * ) ;
	void ayudanteInOrden( NodoArbol < TIPONODO > * ) ;
	void ayudantePostOrden( NodoArbol < TIPONODO > * ) ;
};

template < typename TIPONODO >
Arbol< TIPONODO >::Arbol()
{
	raizPtr = 0;
	numeroelem=0;
}

//insertar el nodo en el arbol
template < typename TIPONODO >
void Arbol< TIPONODO >::insertarNodo(  TIPONODO &valor ) 
{
	ayudanteInsertarNodo( &raizPtr, valor);
}

template < typename TIPONODO >
void Arbol< TIPONODO >::ayudanteInsertarNodo( NodoArbol< TIPONODO > **ptr, TIPONODO &valor )
{
	//el subarbol esta vacio, crea nuevo NodoArbol 
	if( *ptr == 0){
		*ptr = new NodoArbol< TIPONODO >(valor);
		numeroelem++;
	}
	else{
		
		//los datos a insertar son menores que los datos en el nodo actual
		if( valor < (*ptr)->datos ){
			ayudanteInsertarNodo( &((*ptr) -> izquierdoPtr), valor);
		}
		else{
			//los datos a insertar son mayores que los datos en el nodo actual
			if( valor > (*ptr)->datos ){
				ayudanteInsertarNodo( &((*ptr) -> derechoPtr), valor);
			}
			//else{//se ignora el valor de datos duplicados
				//cout << valor << " duplicado " << endl;
			//}
		}

	}
}

//buscar elemento
template < typename TIPONODO >
bool Arbol< TIPONODO >::buscar_elemento(  TIPONODO &valor ) 
{
	if( ayudanteBuscarElemento( &raizPtr, valor)==true )
		return true;
	else return false;

}
template < typename TIPONODO >
bool Arbol< TIPONODO >::ayudanteBuscarElemento( NodoArbol< TIPONODO > **ptr, TIPONODO &valor )
{
	//el subarbol esta vacio, crea nuevo NodoArbol 
	if( *ptr != 0){
		//los datos a insertar son menores que los datos en el nodo actual
		if( valor < (*ptr)->datos ){
			ayudanteBuscarElemento( &((*ptr) -> izquierdoPtr), valor);
		}
		else if( valor > (*ptr)->datos ){
				ayudanteBuscarElemento( &((*ptr) -> derechoPtr), valor);
			}
		else if( valor == (*ptr)->datos ){
			return true;
			//cout << valor << " encontrado " << endl;
		}
		else if( valor != (*ptr)->datos ){
			return false;
		}
	}

}

template< typename TIPONODO >
void Arbol< TIPONODO >::recorridoPreOrden()
{
	ayudantePreOrden( raizPtr );
}
template< typename TIPONODO >
void Arbol< TIPONODO >::ayudantePreOrden( NodoArbol < TIPONODO > *ptr )
{
	if( ptr != 0 ){
		cout << ptr->datos <<' ';//procesa el nodo
		ayudantePreOrden( ptr->izquierdoPtr );
		ayudantePreOrden( ptr->derechoPtr );
	}
}

//recorrido inorden
template< typename TIPONODO >
void Arbol< TIPONODO >::recorridoInOrden() 
{
	ayudanteInOrden( raizPtr );
}

template< typename TIPONODO >
void Arbol< TIPONODO >::ayudanteInOrden( NodoArbol < TIPONODO > *ptr )
{
	if( ptr != 0 ){
		
		ayudanteInOrden( ptr->izquierdoPtr );
		//cout << ptr->datos <<' ';//procesa el nodo
		ayudanteInOrden( ptr->derechoPtr );
		
	}
}

//recorrido decreciente
template< typename TIPONODO >
void Arbol< TIPONODO >::recorridoDecOrden() 
{
	ayudanteDecOrden( raizPtr );
}

template< typename TIPONODO >
void Arbol< TIPONODO >::ayudanteDecOrden( NodoArbol < TIPONODO > *ptr )
{
	if( ptr != 0 ){
		
		ayudanteDecOrden( ptr->derechoPtr );
		cout << ptr->datos <<' ';//procesa el nodo
		ayudanteDecOrden( ptr->izquierdoPtr );
		
	}
}

//recorrido postorden
template< typename TIPONODO >
void Arbol< TIPONODO >::recorridoPostOrden()
{
	ayudantePostOrden( raizPtr );
}

template< typename TIPONODO >
void Arbol< TIPONODO >::ayudantePostOrden( NodoArbol < TIPONODO > *ptr )
{
	if( ptr != 0 ){
		ayudantePostOrden( ptr->izquierdoPtr );
		ayudantePostOrden( ptr->derechoPtr );
		cout << ptr->datos <<' ';//procesa el nodo
		
	}
}
template< typename TIPONODO >
int Arbol< TIPONODO >::numero_elementos( )
{
	return numeroelem;
}
template< typename TIPONODO >
void Arbol< TIPONODO >::vaciar_arbol()
{
	delete[] raizPtr;
	raizPtr=0;
	numeroelem=0;

}
template < typename TIPONODO >
Arbol< TIPONODO >::~Arbol()
{
	delete [] raizPtr;
}


#endif
