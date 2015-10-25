#include "enemigo_patrulla.h"

using namespace App_Juego;

Enemigo_patrulla::Enemigo_patrulla(float x, float y, float vx, int sal):
	Objeto_juego(),
	Actor_movil(x, y, W, H),
	salud(sal)
{
	establecer_vector(DLibH::Vector_2d(vx, 0.0f));
}

void Enemigo_patrulla::turno(float delta, const Espaciable& jugador, const std::vector<const Espaciable *>& bloqueos)
{
	//Movimiento.
	const auto& v=acc_vector();
	desplazar_caja(v.x * delta, v.y * delta);


	//Invertir sentido.
	if(bloqueos.size()) 
	{
		App_Colisiones::Ajustador AJ;
		AJ.ajustar_colisiones_eje_x_actor_movil_con_espaciables(*this, bloqueos);
		establecer_vector(-v.x, App_Interfaces::Movil::t_vector::V_X);
	}
}

unsigned int Enemigo_patrulla::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Enemigo_patrulla::obtener_profundidad_ordenacion() const
{
	return 30;
}

void Enemigo_patrulla::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	const auto& a=b.obtener_animacion(App_Definiciones::animaciones::sprites, App_Definiciones::animaciones_sprites::enemigo_patrulla);
	const auto& f=a.obtener_para_tiempo_animacion(App_Graficos::Animaciones::obtener_tiempo(), a.acc_duracion_total()).frame;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
	b.invertir_horizontal(acc_vector().x < 0.0f);
}

void Enemigo_patrulla::recibir_disparo(int v)
{
	salud-=v;
	if(salud <= 0) mut_borrar(true);
}
