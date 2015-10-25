#ifndef CELDA_BASE_H
#define CELDA_BASE_H

#include "../definiciones/definiciones.h"

namespace App_Niveles
{

class Celda_base
{
	///////////
	// Interface pública

	public:

						Celda_base(App_Definiciones::t_dim px, App_Definiciones::t_dim py);

	//////////
	// Propiedades
	protected:

	App_Definiciones::t_dim	x, y;
};

}

#endif
