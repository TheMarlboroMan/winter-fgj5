#ifndef ENEMIGO_PATRULLA_H
#define ENEMIGO_PATRULLA_H

#include "actor_movil.h"
#include "../interfaces/representable.h"
#include "../interfaces/disparable.h"
#include "../interfaces/objeto_juego.h"
#include "../interfaces/con_turno.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"
#include "../colisiones/ajustador.h"

namespace App_Juego
{

class Enemigo_patrulla:
	public App_Interfaces::Objeto_juego,
	public Actor_movil, 
	public App_Interfaces::Representable,
	public App_Interfaces::Disparable,
	public App_Interfaces::Con_turno
{
	////////////////////////
	// Interfaz pública...
	public:
						Enemigo_patrulla(float x, float y, float vx, int);

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return 0.0f;}
	virtual float 				obtener_max_velocidad_caida() const {return 0.0f;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return es_borrar();}

	///////////////////////
	// Implementación de Disparable
	virtual int				acc_puntos() const {return 150;}
	virtual void 				recibir_disparo(int);
	virtual bool				es_colision_proyectil(const Espaciable& e)const {return en_colision_con(e);}
	virtual bool				es_disparable_borrar() const {return es_borrar();}
	virtual App_Interfaces::Espaciable::t_caja	caja_disparable() const {return copia_caja();}

	///////////////////////
	// Implementación de "Con turno"
	virtual void				turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos);
	virtual Espaciable::t_caja 		copia_caja_con_turno() const {return copia_caja();}
	virtual bool				es_disparar() const {return false;}
	virtual App_Interfaces::Con_turno::Estructura_disparo obtener_estructura_disparo(const App_Interfaces::Espaciable&) {return App_Interfaces::Con_turno::Estructura_disparo();}

	/////////////////////////
	// Internas....
	private:

	static const int 			W=14;
	static const int 			H=30;

	int salud;
};

}
#endif
