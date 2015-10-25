#include "plataforma.h"

using namespace App_Juego;

	float 					tiempo_on_inicial, tiempo_off_inicial, tiempo_on, tiempo_off;
	bool					on;

Plataforma::Plataforma(float x, float y, float ton, float toff, bool on)
	:Actor(x, y, W, H), 
	tiempo_on_inicial(ton), tiempo_off_inicial(toff),
	tiempo_on(ton), tiempo_off(toff),
	on(on)
{

}

void Plataforma::turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos)
{
	if(on)
	{
		tiempo_on-=delta;
		if(tiempo_on <= 0.f)
		{
			tiempo_on=tiempo_on_inicial;
			on=false;
		}
	}
	else
	{
		tiempo_off-=delta;
		if(tiempo_off <= 0.f)
		{
			tiempo_off=tiempo_off_inicial;
			on=true;
		}
	}
}

unsigned int Plataforma::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Plataforma::obtener_profundidad_ordenacion() const
{
	return 35;
}

void Plataforma::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::plataforma);
	const auto& f=a.obtener(0).frame;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);


	float cuarto_tiempo=tiempo_on_inicial / 4.0;

	b.establecer_alpha(tiempo_on <= cuarto_tiempo ? (tiempo_on * 128.f) / cuarto_tiempo : 255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, f.w, f.h);
}
