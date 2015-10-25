#include "celda.h"

using namespace App_Niveles;

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
*/

Celda::Celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, tipo_celda pt)
		:Celda_base(px, py), tipo(pt)
{

}

App_Interfaces::Espaciable::t_caja Celda::copia_caja() const
{
	using namespace App_Definiciones;
	return App_Interfaces::Espaciable::t_caja(definiciones::dim_celda*x,definiciones::dim_celda*y,definiciones::dim_celda,definiciones::dim_celda);
}
