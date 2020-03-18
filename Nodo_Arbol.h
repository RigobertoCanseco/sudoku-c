#ifndef NODOARBOL_H
#define NODOARBOL_H

template< typename TIPONODO > class Arbol;
template< typename TIPONODO >
class NodoArbol
{
	friend class Arbol < TIPONODO >;
public:
	NodoArbol(const TIPONODO &d)
		:izquierdoPtr( 0 ),
		datos( d ),
		derechoPtr( 0 )
	{
	}
	//devuelve una copia de los datos del nodo
	TIPONODO obtenerDatos() const
	{
		return datos;
	}
private:
	NodoArbol< TIPONODO > *izquierdoPtr;//apuntador al subarbol izquierdo
	TIPONODO datos;
	NodoArbol< TIPONODO > *derechoPtr;//apuntador al subarbol derecho
};

#endif 