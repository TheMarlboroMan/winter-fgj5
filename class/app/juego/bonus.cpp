#include "bonus.h"

using namespace App_Juego;

Bonus::Bonus(float x, float y, tipos t)
	:Actor(x, y, W, H), tipo(t)
{

}

unsigned int Bonus::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Bonus::obtener_profundidad_ordenacion() const
{
	return 20;
}

void Bonus::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	size_t indice=App_Definiciones::animaciones_sprites::bonus_peq;

	switch(tipo)
	{
		case tipos::pequeno: indice=App_Definiciones::animaciones_sprites::bonus_peq; break;
		case tipos::mediano: indice=App_Definiciones::animaciones_sprites::bonus_med; break;
		case tipos::grande: indice=App_Definiciones::animaciones_sprites::bonus_gra; break;
		case tipos::disparos: indice=App_Definiciones::animaciones_sprites::bonus_disp; break;
	}

	const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, indice);
	const auto& f=a.obtener_para_tiempo_animacion(App_Graficos::Animaciones::obtener_tiempo(), a.acc_duracion_total()).frame;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
}

