#include "movil.h"

using namespace App_Interfaces;

Movil::Movil()
	:vector(0.0, 0.0)
{

}

Movil::~Movil()
{

}

float Movil::integrar_vector(float delta, float &vec, float factor)
{
	float copia_vector=vec;
	vec+=factor * delta;
	float val=copia_vector + vec;
	return val * 0.5 * delta;
}

void Movil::sumar_vector(float c, t_vector t)
{
	switch(t)
	{
		case t_vector::V_X: vector.x+=c; break;
		case t_vector::V_Y: vector.y+=c; break;
	}
}

void Movil::establecer_vector(float c, t_vector t)
{
	switch(t)
	{
		case t_vector::V_X: vector.x=c; break;
		case t_vector::V_Y: vector.y=c; break;
	}
}

void Movil::accion_gravedad(float delta, float valor_gravedad)
{
	integrar_vector(delta, vector.y, obtener_peso()*valor_gravedad);
	float max_v_c=obtener_max_velocidad_caida();
	if(vector.y > max_v_c) vector.y=max_v_c;
}

