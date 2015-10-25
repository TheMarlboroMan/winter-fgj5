#include "espaciable.h"

using namespace App_Interfaces;

Espaciable::Espaciable()
{

}

Espaciable::~Espaciable()
{

}

bool Espaciable::en_colision_con(const Espaciable& e, bool roce_es_colision) const
{
	return copia_caja().es_en_colision_con(e.copia_caja(), roce_es_colision);
}

Espaciable::t_caja Espaciable::copia_caja_desplazada(float x, float y) const
{
	auto c=copia_caja();
	c.origen.x+=x;
	c.origen.y+=y;
	return c;
}

void Espaciable::establecer_posicion(const Espaciable& e)
{
	mut_x_caja(e.acc_espaciable_x());	
	mut_y_caja(e.acc_espaciable_y());
}

void Espaciable::establecer_posicion(float x, float y)
{
	mut_x_caja(x);	
	mut_y_caja(y);
}

DLibH::Vector_2d_pantalla Espaciable::obtener_vector_pantalla_para(const Espaciable& a, const Espaciable& b) const
{
	float ax=a.acc_espaciable_cx();
	float ay=a.acc_espaciable_cy();
	float bx=b.acc_espaciable_cx();
	float by=b.acc_espaciable_cy();

	return Vector_2d::obtener_para_puntos_pantalla(bx, by, ax, ay);
}

float Espaciable::obtener_angulo_pantalla_para(const Espaciable& a, const Espaciable& b) const
{
	return obtener_vector_pantalla_para(a, b).angulo_grados();
}

DLibH::Vector_2d_cartesiano Espaciable::obtener_vector_cartesiano_para(const Espaciable& a, const Espaciable& b) const
{
	float ax=a.acc_espaciable_cx();
	float ay=a.acc_espaciable_cy();
	float bx=b.acc_espaciable_cx();
	float by=b.acc_espaciable_cy();

	return Vector_2d::obtener_para_puntos_cartesiano(bx, by, ax, ay);
}

float Espaciable::obtener_angulo_cartesiano_para(const Espaciable& a, const Espaciable& b) const
{
	return obtener_vector_cartesiano_para(a, b).angulo_grados();
}
