#include "rompible.h"

using namespace App_Juego;

Rompible::Rompible(float x, float y)
	:Actor(x, y, W, H)
{

}

unsigned int Rompible::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Rompible::obtener_profundidad_ordenacion() const
{
	return 30;
}

void Rompible::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::rompible);
	const auto& f=a.obtener_para_tiempo_animacion(App_Graficos::Animaciones::obtener_tiempo(), a.acc_duracion_total()).frame;

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
}

void Rompible::recibir_disparo(int v)
{
	mut_borrar(true);
}
