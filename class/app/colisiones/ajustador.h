#ifndef AJUSTADOR_H
#define AJUSTADOR_H

#include <vector>
#include "../juego/actor_movil.h"

namespace App_Colisiones
{

class Ajustador
{
	public:
	void		ajustar_colisiones_eje_y_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const;
	void		ajustar_colisiones_eje_x_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const;
};
}

#endif
