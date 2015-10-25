#ifndef PROYECTIL_ENEMIGO_H
#define PROYECTIL_ENEMIGO_H

#include "actor_movil.h"
#include "../interfaces/representable.h"
#include "../interfaces/objeto_juego.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"

namespace App_Juego
{

class Proyectil_enemigo:
	public App_Interfaces::Objeto_juego,
	public Actor_movil, 
	public App_Interfaces::Representable
{
	////////////////////////
	// Interfaz pública...
	public:
						Proyectil_enemigo(float x, float y, const DLibH::Vector_2d& v, float peso);
	//TODO: Con interface...
	void 					turno(float delta);

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return peso;}
	virtual float 				obtener_max_velocidad_caida() const {return MAXIMA_VELOCIDAD_CAIDA;}
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

	static const int 			W=6;
	static const int 			H=6;

	static const float 			VECTOR_X;
	static const float 			VECTOR_Y;
	static const float 			MAXIMA_VELOCIDAD_CAIDA;

	float					peso;
};

}
#endif
