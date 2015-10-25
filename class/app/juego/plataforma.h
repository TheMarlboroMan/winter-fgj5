#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "actor.h"
#include "../interfaces/representable.h"
#include "../interfaces/objeto_juego.h"
#include "../interfaces/con_turno.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"

namespace App_Juego
{

class Plataforma:
	public App_Interfaces::Objeto_juego,
	public Actor, 
	public App_Interfaces::Representable,
	public App_Interfaces::Con_turno
{
	////////////////////////
	// Interfaz pública...
	public:
						Plataforma(float x, float y, float t_on, float t_off, bool on);
	void					turno(float delta);
	bool					es_on() const {return on;}

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return es_borrar();}

	/////////////////////////
	// Implementación de Con_turno
	virtual void			turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos);
	virtual Espaciable::t_caja 	copia_caja_con_turno() const {return copia_caja();}
	virtual bool			es_disparar() const {return false;}
	virtual App_Interfaces::Con_turno::Estructura_disparo	obtener_estructura_disparo(const App_Interfaces::Espaciable&) {return App_Interfaces::Con_turno::Estructura_disparo();}

	//////////////////////////////
	//Implementación de Espaciable
	public:

	bool					es_plataforma() const {return true;}

	/////////////////////////
	// Internas....
	private:

	static const int 			W=32;
	static const int 			H=4;

	float 					tiempo_on_inicial, tiempo_off_inicial, tiempo_on, tiempo_off;
	bool					on;
};

}
#endif
