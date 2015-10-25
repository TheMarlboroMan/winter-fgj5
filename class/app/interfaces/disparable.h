#ifndef DISPARABLE_H
#define DISPARABLE_H

#include "espaciable.h"

namespace App_Interfaces
{

class Disparable
{
	public:

	virtual int		acc_puntos() const=0;
	virtual void 		recibir_disparo(int)=0;
	virtual bool		es_colision_proyectil(const Espaciable&)const=0;
	virtual bool		es_disparable_borrar() const=0;
	virtual Espaciable::t_caja	caja_disparable() const=0;
};

}

#endif
