#include "humo.h"

using namespace App_Juego;

const float Humo::TIEMPO=1.0f;

Humo::Humo(float x, float y, const DLibH::Vector_2d& v):
	Objeto_juego(),
	Actor_movil(x, y, 1, 1),
	tiempo(0.0f), w(0.0f), h(0.0f)
{
	establecer_vector(v);
}

void Humo::turno(float delta)
{
	accion_gravedad(delta, 1.0f);

	const auto& v=acc_vector();
	desplazar_caja(v.x * delta, v.y * delta);

	tiempo+=delta;
	if(tiempo >= TIEMPO) mut_borrar(true);
}

unsigned int Humo::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Humo::obtener_profundidad_ordenacion() const
{
	return 90;
}

void Humo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& f=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::humo).obtener_para_tiempo_animacion(tiempo, TIEMPO).frame;

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(127);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);
	b.establecer_recorte(f.x, f.y, f.w, f.h);

	//Centramos la posición según el ancho del frame anterior.
	float pos_x=acc_espaciable_x()-(w / 2);
	float pos_y=acc_espaciable_y()-(h / 2);

	w=f.w;
	h=f.h;

	b.establecer_posicion(pos_x, pos_y, w, h);
}
