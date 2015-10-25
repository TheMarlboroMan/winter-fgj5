#ifndef ACTOR_MOVIL_H
#define ACTOR_MOVIL_H

#include "actor.h"
#include "../interfaces/movil.h"

namespace App_Juego
{

class Actor_movil:public Actor, public App_Interfaces::Movil
{
	/////////////////
	// Definiciones

	public:

	enum class posiciones_ajuste {nada, arriba, abajo, izquierda, derecha};

	/////////////////
	//Interface pública

	public:

	Actor_movil(float x, float y, unsigned int w, unsigned int h)
		:Actor(x, y, w, h)
	{}

	void ajustar(float pos, posiciones_ajuste tipo);
	void ajustar(const Espaciable& e, posiciones_ajuste tipo);
	void desplazar(float delta);
	void frenar(float delta, float factor);

	/////////////////
	//Implementación de Movil

	virtual float obtener_peso() const=0;
	virtual float obtener_max_velocidad_caida() const=0;

	/////////////////
	//A implementar, propio.
	virtual void callback_ajuste(float pos, posiciones_ajuste tipo)=0;
};

}

#endif
