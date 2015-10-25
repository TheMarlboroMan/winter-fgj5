#include "enemigo_disparador.h"

using namespace App_Juego;

const float Enemigo_disparador::TIEMPO_PRE=1.2f;
const float Enemigo_disparador::TIEMPO_POST=0.2f;

Enemigo_disparador::Enemigo_disparador(float x, float y, float t, int sal):
	Objeto_juego(),
	Actor(x, y, W, H),
	direccion(App_Definiciones::direcciones::derecha),
	estado(estados::quieto),
	tiempo_inicial(t), tiempo(0.0f),
	salud(sal)
{

}

void Enemigo_disparador::turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos)
{
	direccion=jugador.es_a_la_izquierda_de(*this) ? App_Definiciones::direcciones::izquierda : App_Definiciones::direcciones::derecha; 
	tiempo-=delta;

	if(tiempo <= 0.f)
	{
		switch(estado)
		{
			case estados::quieto:
				estado=estados::pre;
				tiempo=TIEMPO_PRE;
			break;

			case estados::pre:
				estado=estados::disparo;
			break;
			case estados::disparo:
				estado=estados::post;
				tiempo=TIEMPO_POST;
			break;
			
			case estados::post:
				estado=estados::quieto;
				tiempo=tiempo_inicial;
			break;
		}
	}
}

App_Interfaces::Con_turno::Estructura_disparo Enemigo_disparador::obtener_estructura_disparo(const App_Interfaces::Espaciable& e)
{
	float vx=e.es_a_la_izquierda_de(*this) ? -100.f : 100.f;
	App_Interfaces::Con_turno::Estructura_disparo res{acc_espaciable_cx(), acc_espaciable_cy(), 400.f, DLibH::Vector_2d(vx, -100.f)};
	return res;
}

unsigned int Enemigo_disparador::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Enemigo_disparador::obtener_profundidad_ordenacion() const
{
	return 30;
}

void Enemigo_disparador::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	float parcial=App_Graficos::Animaciones::obtener_tiempo();
	size_t indice_animacion=App_Definiciones::animaciones_sprites::enemigo_disparo_quieto;

	switch(estado)
	{
		case estados::quieto:
			indice_animacion=App_Definiciones::animaciones_sprites::enemigo_disparo_quieto;
		break;
		case estados::pre:
			indice_animacion=App_Definiciones::animaciones_sprites::enemigo_disparo_dispara;
			parcial=TIEMPO_PRE-tiempo;
		break;
		case estados::disparo:
			indice_animacion=App_Definiciones::animaciones_sprites::enemigo_disparo_post;
		break;	
		case estados::post:
			indice_animacion=App_Definiciones::animaciones_sprites::enemigo_disparo_post;
		break;
	}

	const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, indice_animacion);
	const auto& f=a.obtener_para_tiempo_animacion(parcial, a.acc_duracion_total()).frame;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

void Enemigo_disparador::recibir_disparo(int v)
{
	salud-=v;
	if(salud <= 0) mut_borrar(true);
}
