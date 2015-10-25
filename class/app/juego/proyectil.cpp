#include "proyectil.h"

using namespace App_Juego;

const float Proyectil::MAXIMA_VELOCIDAD_CAIDA=1000.0f;
const float Proyectil::VECTOR_X=370.0f;
const float Proyectil::VECTOR_Y=-100.0f;
const float Proyectil::PESO=350.0f;

Proyectil::Proyectil(float x, float y, float vx):
	Objeto_juego(),
	Actor_movil(x, y, W, H),
	tiempo(0.0f)
{
	establecer_vector(DLibH::Vector_2d(VECTOR_X * vx, VECTOR_Y));
}

void Proyectil::turno(float delta)
{
	accion_gravedad(delta, 1.0f);
	tiempo+=delta;
}

unsigned int Proyectil::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Proyectil::obtener_profundidad_ordenacion() const
{
	return 80;
}

void Proyectil::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& f=b.obtener_frame(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::disparo, 0);

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.rotar(fmod(tiempo*1000.0, 360));
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
}
