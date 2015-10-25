#ifndef ENTRADA_H
#define ENTRADA_H

#include "actor.h"

namespace App_Juego
{

class Entrada:
	public Actor
{
	////////////////////////
	// Interfaz pública...
	public:
						Entrada(float x, float y);

	/////////////////////////
	// Internas....
	private:

	static const int 			W=32;
	static const int 			H=32;
};

}
#endif
