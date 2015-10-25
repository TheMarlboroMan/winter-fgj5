#include "jugador.h"

using namespace App_Juego;

const float Jugador::ACELERACION_HORIZONTAL_SEGUNDO=300.0;
const float Jugador::DECELERACION_HORIZONTAL_SEGUNDO=250.0;
const float Jugador::MAXIMA_VELOCIDAD_HORIZONTAL=200.0;
const float Jugador::MAXIMA_VELOCIDAD_CAIDA=600.0;
const float Jugador::VALOR_GRAVEDAD=1.0f;
const float Jugador::VECTOR_SALTO=-350.0f;
const float Jugador::VECTOR_PERDER_VIDA=-200.0f;
const float Jugador::PESO=600.0;
const float Jugador::DURACION_DISPARO=0.55f;

Jugador::Jugador(float x, float y)
	:Actor_movil(x, y, W, H),
	estado(estados::suelo),
	direccion(App_Definiciones::direcciones::derecha),
	posicion_anterior(copia_caja()),
	tiempo_disparando(0.0f)
{

}

Jugador::~Jugador()
{

}

/**
* Callback de ajuste para actor móvil.
*/

void Jugador::callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo)
{
	switch(tipo)
	{
		case Actor_movil::posiciones_ajuste::arriba:
			establecer_vector(0.0, Movil::t_vector::V_Y);
		break;
		case Actor_movil::posiciones_ajuste::abajo:
			establecer_vector(0.0, Movil::t_vector::V_Y);
			estado=estados::suelo;
		break;
		break;
		case Actor_movil::posiciones_ajuste::izquierda:
		case Actor_movil::posiciones_ajuste::derecha:
			establecer_vector(0.0, Movil::t_vector::V_X);
		break;
		case Actor_movil::posiciones_ajuste::nada:
			//Noop.
		break;
	}
}

unsigned int Jugador::obtener_ciclos_representable()const
{
	return 1;
}

unsigned short int Jugador::obtener_profundidad_ordenacion() const
{
	return 40;
}

void Jugador::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Definiciones;
//	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::jugador, 0);

	size_t indice_animacion=0;
	const auto& v=acc_vector();

	float parcial=App_Graficos::Animaciones::obtener_tiempo();

	if(estado==estados::perder_vida)
	{
		indice_animacion=animaciones_sprites::jugador_morir;
	}
	else if(tiempo_disparando)
	{
		parcial=tiempo_disparando;
		indice_animacion=animaciones_sprites::jugador_disparar;
	}
	else switch(estado)
	{
		case estados::suelo:
			if(v.x) indice_animacion=animaciones_sprites::jugador_correr;
			else indice_animacion=animaciones_sprites::jugador_quieto;
		break;
		default:
			indice_animacion=animaciones_sprites::jugador_salto;
		break;
	}

	const auto& a=b.obtener_animacion(animaciones::sprites, indice_animacion);
	const auto& f=a.obtener_para_tiempo_animacion(parcial, a.acc_duracion_total()).frame;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_sprites);

	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);

/*	b.establecer_mod_color(mod_color.r, mod_color.g, mod_color.b);
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_primitiva_caja);
	b.establecer_alpha(255);
	b.color_caja(255, 255, 255);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
*/
}

void Jugador::turno(float delta)
{
	using namespace App_Input;

	posicion_anterior=copia_caja();

	accion_gravedad(delta, VALOR_GRAVEDAD);

	//Frenada o aceleración.
	if(input.mov_horizontal)
	{
		float v=acc_vector_x();
		//Controlar el "contravolante...".
		float extra=(input.mov_horizontal > 0 && v > 0.0f) 
			|| (input.mov_horizontal < 0 && v < 0.0f) 
			? 1.0f : 2.5f; 

		v+=(delta * ACELERACION_HORIZONTAL_SEGUNDO * extra) * input.mov_horizontal;
		if(v > MAXIMA_VELOCIDAD_HORIZONTAL) v=MAXIMA_VELOCIDAD_HORIZONTAL;
		else if(v < -MAXIMA_VELOCIDAD_HORIZONTAL) v=-MAXIMA_VELOCIDAD_HORIZONTAL;

		establecer_vector(v, Movil::t_vector::V_X);
		if(input.mov_horizontal < 0) direccion=App_Definiciones::direcciones::izquierda;
		else direccion=App_Definiciones::direcciones::derecha;
	}
	else
	{
		float v=abs(acc_vector_x());
		v-=(delta * ACELERACION_HORIZONTAL_SEGUNDO);
		if(v < 0.0) v=0;
			//Aproximarse al cero.
		float vr=acc_vector_x();
		if(vr > 0.0) establecer_vector(v, Movil::t_vector::V_X);
		else if(vr < 0.0) establecer_vector(-v, Movil::t_vector::V_X);	
	}

	/////
	
	if(tiempo_disparando)
	{
		tiempo_disparando+=delta;
		if(tiempo_disparando >= DURACION_DISPARO) tiempo_disparando=0.0f;
	}
}

void Jugador::saltar()
{
	establecer_vector(VECTOR_SALTO, Movil::t_vector::V_Y);
	estado=estados::salto_control;
}

void Jugador::cancelar_control_salto()
{
	auto v=acc_vector();
	if(v.y <= 0.0f) establecer_vector(v.y / 2.0f, Movil::t_vector::V_Y);
	estado=estados::salto_no_control;
}

void Jugador::perder_vida()
{
	establecer_vector(VECTOR_PERDER_VIDA, Movil::t_vector::V_Y);
	estado=estados::perder_vida;
}

void Jugador::restaurar_a_inicio_nivel(float x, float y)
{
	establecer_posicion(x, y);
	establecer_vector(DLibH::Vector_2d(0.f, 0.f));
	estado=estados::suelo;
}

App_Interfaces::Espaciable::t_caja Jugador::caja_comprobar_caida() const
{
	auto res=copia_caja();
	++res.origen.y;
	return res;
}

void Jugador::iniciar_disparo()
{
	tiempo_disparando=0.01f;
}
