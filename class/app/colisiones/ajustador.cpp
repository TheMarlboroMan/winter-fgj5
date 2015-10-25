#include "ajustador.h"

using namespace App_Colisiones;

void Ajustador::ajustar_colisiones_eje_y_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const
{
	//TODO: Seguramente podemos parametrizar estas dos funciones para que llamen a una sóla...

	auto vy=actor.acc_vector_y();

	if(vy < 0.0)
	{
		int fy=-1;
		for(const App_Interfaces::Espaciable * e: espaciables)
		{
			if(e->acc_espaciable_fy() >= fy)
			{
				fy=e->acc_espaciable_fy();
			}
		}
		if(fy != -1)
		{
			actor.ajustar(fy, App_Juego::Actor_movil::posiciones_ajuste::arriba);
		}
	}
	else if(vy > 0.0)
	{
		int fy=-1;
		for(const App_Interfaces::Espaciable * e: espaciables)
		{
			if(e->acc_espaciable_y() >= fy)
			{
				fy=e->acc_espaciable_y();
			}
		}
		if(fy != -1)
		{
			actor.ajustar(fy, App_Juego::Actor_movil::posiciones_ajuste::abajo);
		}
	}
}

void Ajustador::ajustar_colisiones_eje_x_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const
{
	auto vx=actor.acc_vector_x();

	if(vx < 0.0)
	{
		int fx=-1;
		for(const App_Interfaces::Espaciable * e: espaciables)
		{
			if(e->acc_espaciable_fx() >= fx)
			{
				fx=e->acc_espaciable_fx();
			}
		}
		if(fx != -1)
		{
			actor.ajustar(fx, App_Juego::Actor_movil::posiciones_ajuste::izquierda);
		}
	}
	else if(vx > 0.0)
	{
		int fx=-1;
		for(const App_Interfaces::Espaciable * e: espaciables)
		{
			if(e->acc_espaciable_x() >= fx)
			{
				fx=e->acc_espaciable_x();
			}
		}
		if(fx != -1)
		{
			actor.ajustar(fx, App_Juego::Actor_movil::posiciones_ajuste::derecha);
		}
	}
}
