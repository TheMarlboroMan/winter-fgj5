#ifndef ACTOR_H
#define ACTOR_H

#include "../interfaces/espaciable.h"

/*El actor es algo que existe en el espacio de juego.
Podemos encontrar con controladores que hacen cosas y que da igual su punto
en el espacio, pero bueno, no es importante.

Básicamente es el siguiente paso en el "espaciable", concretándulo en una
caja real.
*/

namespace App_Juego
{

class Actor:
	public App_Interfaces::Espaciable
{
	////////////////////////
	// Propiedades.

	private:

	Espaciable::t_caja caja;


	///////////////////////
	// Implementación de espaciable

	public:

	virtual Espaciable::t_caja copia_caja() const {return caja;}
	virtual void mut_x_caja(float v) {caja.origen.x=v;}
	virtual void mut_y_caja(float v) {caja.origen.y=v;}
	virtual void mut_w_caja(unsigned int v) {caja.w=v;}
	virtual void mut_h_caja(unsigned int v) {caja.h=v;}
	virtual void desplazar_caja(float x, float y) {caja.origen.x+=x; caja.origen.y+=y;}

	///////////////////////
	// Interfaz pública.

	public:

	Actor();
	Actor(float x, float y, unsigned int w, unsigned int h);

	void establecer_caja(float x, float y, unsigned int w, unsigned int h);
};

}
#endif
