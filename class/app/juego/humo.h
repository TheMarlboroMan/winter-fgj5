#ifndef HUMO_H
#define HUMO_H

#include "actor_movil.h"
#include "../interfaces/representable.h"
#include "../interfaces/objeto_juego.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"

namespace App_Juego
{

class Humo:
	public App_Interfaces::Objeto_juego,
	public Actor_movil, 
	public App_Interfaces::Representable
{
	////////////////////////
	// Interfaz pública...
	public:
						Humo(float x, float y, const DLibH::Vector_2d&);
	void 					turno(float delta);

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return 300.0f;}
	virtual float 				obtener_max_velocidad_caida() const {return 1000.0f;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return es_borrar();}

	/////////////////////////
	// Internas....
	private:

	static const float			TIEMPO;

	float					tiempo;
	mutable float				w, h;
};

}

#endif
