#include "salida.h"

using namespace App_Juego;

Salida::Salida(float x, float y, size_t i, bool bloqueable):
	Actor(x, y, W, H), indice_sala(i), accesible(true), bloqueable(bloqueable)
{

}

void Salida::bloquear()
{
	if(bloqueable) 
	{	
		accesible=false;
	}
}

unsigned int Salida::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Salida::obtener_profundidad_ordenacion() const
{
	return 10;
}

void Salida::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	if(accesible)
	{
		const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::puerta_abierta);
		const auto& f=a.obtener(0).frame;
		b.establecer_recorte(f.x, f.y, f.w, f.h);
		b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
	}
	else
	{
		const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::puerta_cerrada);
		const auto& f=a.obtener(0).frame;
		b.establecer_recorte(f.x, f.y, f.w, f.h);
		b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
	}
}
