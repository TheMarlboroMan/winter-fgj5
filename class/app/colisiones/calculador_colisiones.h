#ifndef CALCULADOR_COLISIONES_H
#define CALCULADOR_COLISIONES_H

#include "../niveles/sala.h"
#include "../juego/actor_movil.h"
#include "../definiciones/definiciones.h"
#include <algorithm>

namespace App_Colisiones
{

class Calculador_colisiones
{
	public:

	template <typename TipoFunc>
	std::vector<const App_Niveles::Celda *> 	celdas_en_caja(const App_Interfaces::Espaciable::t_caja& c, const App_Niveles::Sala& sala, TipoFunc& f) const
	{
		std::vector<const App_Niveles::Celda *> resultado=celdas_en_caja(c, sala);
		f(resultado);	
		return resultado;
	}

	std::vector<const App_Niveles::Celda *> 	celdas_en_caja(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;

	template <typename TipoFunc>
	std::vector<const App_Interfaces::Espaciable *> solidos_en_caja_sala(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala, TipoFunc& f) const
	{
		std::vector<const App_Interfaces::Espaciable *> res;
		auto c=celdas_en_caja(caja, sala, f);
		std::copy(std::begin(c), std::end(c), std::back_inserter(res));
		recolectar_solidos(caja, res, sala);
		return res;
	}

	std::vector<const App_Interfaces::Espaciable *> solidos_en_caja_sala(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;

	bool 						es_fuera_de_sala(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;

	private:

	void						recolectar_solidos(const App_Interfaces::Espaciable::t_caja& caja, std::vector<const App_Interfaces::Espaciable *>&, const App_Niveles::Sala& sala) const;
};

}

#endif
