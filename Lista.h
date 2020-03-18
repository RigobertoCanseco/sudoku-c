#pragma once
#define LISTA_EXITO 0
#define LISTA_LLENA 1
#define LISTA_VACIA 2

template < typename NODO > class LISTA
{
	NODO * Inicio;	//Nodo de inicio
	NODO * Final;	//Nodo de fin
	NODO * Actual;	//Nodo actual
	NODO * Cabeza;	//Nodo cabeza de lista
	int		  iCodError;
public:
	LISTA(void);
	void Insertar(NODO dato);
	NODO Muestra(void);
	void InsertarCabeza(NODO dato);
	NODO Siguiente(void);
	NODO VeCabeza(void);
	NODO Anterior(void);
	NODO VeInicio(void);
	NODO VeFinal(void);
	NODO Borrar(void);
	~LISTA(void);
};

