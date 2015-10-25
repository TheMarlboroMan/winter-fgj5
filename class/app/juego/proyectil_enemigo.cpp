#include "proyectil_enemigo.h"

using namespace App_Juego;

const float Proyectil_enemigo::MAXIMA_VELOCIDAD_CAIDA=1000.0f;

Proyectil_enemigo::Proyectil_enemigo(float x, float y, const DLibH::Vector_2d& v, float peso)
	:Objeto_juego(),
	Actor_movil(x, y, W, H),
	peso(peso)
{
	establecer_vector(v);
}

void Proyectil_enemigo::turno(float delta)
{
	accion_gravedad(delta, 1.0f);
}

unsigned int Proyectil_enemigo::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Proyectil_enemigo::obtener_profundidad_ordenacion() const
{
	return 80;
}

void Proyectil_enemigo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& f=b.obtener_frame(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::disparo_enemigo, 0);

	float angulo=acc_vector().angulo_grados();

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.rotar(angulo);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
}
