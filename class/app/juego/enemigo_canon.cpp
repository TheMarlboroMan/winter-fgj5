#include "enemigo_canon.h"

using namespace App_Juego;

Enemigo_canon::Enemigo_canon(float x, float y, float t, float angulo, float vel):
	Objeto_juego(),
	Actor(x, y, W, H),
	tiempo_inicial(t), tiempo(0.0f),
	angulo(angulo), velocidad(vel)
{

}

void Enemigo_canon::turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos)
{
	tiempo-=delta;
}

App_Interfaces::Con_turno::Estructura_disparo Enemigo_canon::obtener_estructura_disparo(const App_Interfaces::Espaciable& e)
{
	DLibH::Vector_2d_cartesiano vec=DLibH::Vector_2d::vector_unidad_para_angulo(angulo)*velocidad;
	tiempo=tiempo_inicial;
	App_Interfaces::Con_turno::Estructura_disparo res{acc_espaciable_x(), acc_espaciable_y(), 0.0f, vec};
	return res;
}
