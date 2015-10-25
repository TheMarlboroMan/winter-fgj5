#ifndef ROMPIBLE_H
#define ROMPIBLE_H

#include "actor.h"
#include "../interfaces/representable.h"
#include "../interfaces/disparable.h"
#include "../interfaces/objeto_juego.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"


namespace App_Juego
{

class Rompible:
	public App_Interfaces::Objeto_juego,
	public Actor, 
	public App_Interfaces::Representable,
	public App_Interfaces::Disparable
{
	////////////////////////
	// Interfaz pública...
	public:
						Rompible(float x, float y);

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return es_borrar();}
	virtual App_Interfaces::Espaciable::t_caja	caja_disparable() const {return copia_caja();}

	///////////////////////
	// Implementación de Disparable
	virtual int				acc_puntos() const {return 0;}
	virtual void 				recibir_disparo(int);
	virtual bool				es_colision_proyectil(const Espaciable& e)const {return en_colision_con(e);}
	virtual bool				es_disparable_borrar() const {return es_borrar();}

	/////////////////////////
	// Internas....
	private:

	static const int 			W=32;
	static const int 			H=32;
};

}
#endif
