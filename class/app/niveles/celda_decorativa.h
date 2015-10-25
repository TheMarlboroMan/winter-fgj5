#ifndef CELDA_DECORATIVA_H
#define CELDA_DECORATIVA_H

#include "celda_base.h"
#include "../interfaces/representable.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"
#include "../recursos.h"

namespace App_Niveles
{

class Celda_decorativa:
	public Celda_base,
	public App_Interfaces::Representable
{
	///////////
	// Interface pública

	public:

						Celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim p_indice);

	//////////////////////////////
	//Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const {return 1;}
	virtual unsigned short int 		obtener_profundidad_ordenacion()const {return 0;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

	//////////
	// Propiedades
	private:

	App_Definiciones::t_dim	indice;

};

}

#endif
