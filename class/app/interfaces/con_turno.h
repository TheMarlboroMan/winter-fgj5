#ifndef CON_TURNO_H
#define CON_TURNO_H

#include <herramientas/vector_2d/vector_2d.h>
#include <vector>
#include "espaciable.h"

namespace App_Interfaces
{

class Con_turno
{
	public:

	struct Estructura_disparo
	{
		float x, y, peso;
		DLibH::Vector_2d v;
	};

	virtual void			turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos)=0;
	virtual Espaciable::t_caja 	copia_caja_con_turno() const=0;
	virtual bool			es_disparar() const=0;
	virtual Estructura_disparo	obtener_estructura_disparo(const App_Interfaces::Espaciable&)=0;
};

}

#endif
