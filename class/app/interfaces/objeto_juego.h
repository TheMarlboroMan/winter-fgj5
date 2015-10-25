#ifndef OBJETO_JUEGO_H
#define OBJETO_JUEGO_H

#include <iostream>

/**
* Interface que define un objeto de juego. Su objetivo es definir una clase
* base en la que meter todos los objetos de juego que luego puedan
* separarse usando un visitante.
*/

namespace App_Interfaces
{
/**
* Interface en si.
*/

class Objeto_juego
{
	public:
					Objeto_juego();
	virtual 			~Objeto_juego() {}
	virtual bool			es_borrar()const {return borrar;}
	virtual void			mut_borrar(bool v) {borrar=v;}

	private:

	bool 				borrar;
};
}

#endif
