#ifndef ENEMIGO_CANON_H
#define ENEMIGO_CANON_H

#include "actor_movil.h"
#include "../interfaces/objeto_juego.h"
#include "../interfaces/con_turno.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../colisiones/ajustador.h"

namespace App_Juego
{

class Enemigo_canon:
	public App_Interfaces::Objeto_juego,
	public Actor, 
	public App_Interfaces::Con_turno
{
	////////////////////////
	// Interfaz pública...
	public:
						Enemigo_canon(float x, float y, float t, float a, float vel);

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return 0.0f;}
	virtual float 				obtener_max_velocidad_caida() const {return 0.0f;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	///////////////////////
	// Implementación de "Con turno"
	virtual void				turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos);
	virtual Espaciable::t_caja 		copia_caja_con_turno() const {return copia_caja();}
	virtual bool				es_disparar() const {return tiempo <= 0.0f;}
	virtual App_Interfaces::Con_turno::Estructura_disparo obtener_estructura_disparo(const App_Interfaces::Espaciable&);

	/////////////////////////
	// Internas....
	private:

	static const int 			W=6;
	static const int 			H=6;

	float 					tiempo_inicial, tiempo, angulo, velocidad;

};

}
#endif
