#include "representador.h"
#include "../recursos.h"
#include "../env.h"

#include <sstream>

using namespace App_Graficos;
using namespace App_Interfaces;

Representador::Representador(const Animaciones& animaciones)
	:bloque_transformacion(animaciones), hoja(App::env::make_data_path("data/recursos/hud.dat"))
{

}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	DLibV::Camara& camara, 
	const std::vector<const Representable *>& v)
{
	unsigned int total=0;

	for(const Representable * r : v)
	{
		int ciclos=r->obtener_ciclos_representable(), c=1;
		while(c <= ciclos)
		{
			r->transformar_bloque(bloque_transformacion.mut_ciclo(c++));
			if(bloque_transformacion.rep->volcar(pantalla, camara)) ++total;
		}
		
	}

	return total;
}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	const std::vector<const Representable *>& v)
{
	unsigned int total=0;

	for(const Representable * r : v)
	{
		int ciclos=r->obtener_ciclos_representable(), c=1;
		while(c <= ciclos)
		{
			r->transformar_bloque(bloque_transformacion.mut_ciclo(c++));
			if(bloque_transformacion.rep->volcar(pantalla)) ++total;
		}
	}

	return total;
}


void Representador::generar_hud(DLibV::Pantalla& pantalla, const App_Definiciones::Estado_dinamicas& ed, const App_Definiciones::Datos_juego& dj)
{
	if(ed.con_disparo)
	{
		const auto& f=hoja.obtener(INDICE_HUD_MARCO_DISPAROS);
		bloque_transformacion.establecer_recurso(App::Recursos_graficos::rt_hud);
		bloque_transformacion.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
		bloque_transformacion.establecer_alpha(255);
		bloque_transformacion.establecer_recorte(f.x, f.y, f.w, f.h);
		bloque_transformacion.establecer_posicion(ORIGEN_HUD_X+DESP_MARCO_DISPAROS_X, ORIGEN_HUD_Y+DESP_MARCO_DISPAROS_Y, f.w, f.h);
		bloque_transformacion.rep->volcar(pantalla);

		//Y ahora cada disparo...
		int i=0;
		int y=DESP_DISPAROS_Y;
		while(i< App_Definiciones::Datos_juego::MAX_DISPAROS)
		{
			const auto& f2=hoja.obtener(INDICE_HUD_DISPARO);
			bloque_transformacion.establecer_recorte(f2.x, f2.y, f2.w, f2.h);
			bloque_transformacion.establecer_posicion(ORIGEN_HUD_X+DESP_DISPAROS_X, ORIGEN_HUD_Y+y, f2.w, f2.h);
			bloque_transformacion.establecer_alpha(dj.disparos > i ? 255 : 64);
			bloque_transformacion.rep->volcar(pantalla);

			++i;
			y+=SEPARACION_DISPAROS;
		}		
	}

	if(ed.con_bonus)
	{
		const auto& f=hoja.obtener(INDICE_HUD_MARCO_PUNTOS);
		bloque_transformacion.establecer_alpha(255);
		bloque_transformacion.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
		bloque_transformacion.establecer_recurso(App::Recursos_graficos::rt_hud);
		bloque_transformacion.establecer_recorte(f.x, f.y, f.w, f.h);
		bloque_transformacion.establecer_posicion(ORIGEN_HUD_X+DESP_MARCO_PUNTOS_X, ORIGEN_HUD_Y+DESP_MARCO_PUNTOS_Y, f.w, f.h);
		bloque_transformacion.rep->volcar(pantalla);

		std::stringstream ss;
		ss<<std::setw(8)<<std::setfill('0')<<dj.puntuacion;
		DLibV::Representacion_texto_auto_estatica rep_hud(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_gra), ss.str());
		rep_hud.establecer_posicion(ORIGEN_HUD_X+DESP_PUNTOS_X, ORIGEN_HUD_Y+DESP_PUNTOS_Y);
		rep_hud.volcar(pantalla);
	}

	if(ed.con_vidas)
	{
		const auto& f=hoja.obtener(INDICE_HUD_MARCO_VIDA);
		bloque_transformacion.establecer_recurso(App::Recursos_graficos::rt_hud);
		bloque_transformacion.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
		bloque_transformacion.establecer_alpha(255);
		bloque_transformacion.establecer_recorte(f.x, f.y, f.w, f.h);
		bloque_transformacion.establecer_posicion(ORIGEN_HUD_X+DESP_MARCO_VIDA_X, ORIGEN_HUD_Y+DESP_MARCO_VIDA_Y, f.w, f.h);
		bloque_transformacion.rep->volcar(pantalla);

		//Y ahora cada disparo...
		int i=0;
		int x=ORIGEN_HUD_X+DESP_VIDA_X;
		while(i< App_Definiciones::Datos_juego::VIDAS_DEFECTO)
		{
			const auto& f2=hoja.obtener(INDICE_HUD_VIDA);
			bloque_transformacion.establecer_recorte(f2.x, f2.y, f2.w, f2.h);
			bloque_transformacion.establecer_posicion(x, ORIGEN_HUD_Y+DESP_VIDA_Y, f2.w, f2.h);
			bloque_transformacion.establecer_alpha(dj.vidas > i ? 255 : 64);
			bloque_transformacion.rep->volcar(pantalla);

			++i;
			x+=SEPARACION_VIDA;
		}	
	}
}

/**
*  X e Y es adonde apunta la cámara. W y H son las dimensiones del nivel.
* Caja es el tamaño de la cámara.
*/

void Representador::generar_fondo(DLibV::Pantalla& pantalla, const DLibH::Caja<float, int>& caja, int x, int y, int w, int h)
{
	pantalla.limpiar(200, 203, 220, 255);

	if(!animacion_caida_fondo.finalizada)
	{
		int max_pos_x_cam=w > caja.w ? w - caja.w : 0;
		int max_pos_y_cam=h > caja.h ? h - caja.h : 0;

		int rx=max_pos_x_cam ? (x * 100) / max_pos_x_cam : 0;
		int ry=max_pos_y_cam ? (y * 100) / max_pos_y_cam : 0;

		bloque_transformacion.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
		bloque_transformacion.establecer_recurso(App::Recursos_graficos::rt_fondo);
		bloque_transformacion.establecer_recorte(rx, ry, caja.w, caja.h);

		float pos_x=animacion_caida_fondo.tiempo ? animacion_caida_fondo.pos_fondo_x : caja.origen.x;
		float pos_y=animacion_caida_fondo.tiempo ? animacion_caida_fondo.pos_fondo_y : caja.origen.y;

		bloque_transformacion.establecer_posicion(pos_x, pos_y, caja.w, caja.h);	

		if(animacion_caida_fondo.angulo_rotacion)
		{
			bloque_transformacion.especificar_centro_rotacion(40.0f, 40.0f);
			bloque_transformacion.rotar(animacion_caida_fondo.angulo_rotacion);
		}
		else
		{

		}

		bloque_transformacion.rep->volcar(pantalla);
	}
}

void Representador::generar_mensaje(DLibV::Pantalla& pantalla, const std::string& txt)
{
	const auto& f=hoja.obtener(INDICE_HUD_MARCO_TEXTO);
	bloque_transformacion.establecer_alpha(255);
	bloque_transformacion.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	bloque_transformacion.establecer_recurso(App::Recursos_graficos::rt_hud);
	bloque_transformacion.establecer_recorte(f.x, f.y, f.w, f.h);
	bloque_transformacion.establecer_posicion(MARCO_TEXTO_X, MARCO_TEXTO_Y, f.w, f.h);
	bloque_transformacion.rep->volcar(pantalla);

	DLibV::Representacion_texto_auto_estatica rep_mensaje(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_peq), txt);
	rep_mensaje.establecer_posicion(TEXTO_X, TEXTO_Y);
	rep_mensaje.volcar(pantalla);
}

void Representador::resetar_animaciones()
{
	animacion_caida_fondo=Animacion_caida_fondo();
	animacion_cambio_color=Animacion_cambio_color();
}

void Representador::procesar_animacion_fondo(float delta)
{
	animacion_caida_fondo.tiempo+=delta;

	float t=animacion_caida_fondo.tiempo;

	if(t > 1.5f) //Pausa inicial...
	{
		if(animacion_caida_fondo.angulo_rotacion < 48.0f)
		{
			animacion_caida_fondo.acel_angulo+=delta * 10.f;
			animacion_caida_fondo.angulo_rotacion+=delta * (15.f + animacion_caida_fondo.acel_angulo);
		}
		else
		{
			animacion_caida_fondo.velocidad_caida+=delta * 1.f;
			animacion_caida_fondo.velocidad_horizontal+=delta * 0.25f;

			animacion_caida_fondo.pos_fondo_x+=animacion_caida_fondo.velocidad_horizontal;
			animacion_caida_fondo.pos_fondo_y+=animacion_caida_fondo.velocidad_caida;

			animacion_caida_fondo.finalizada=animacion_caida_fondo.pos_fondo_y >= App_Definiciones::definiciones::h_vista;
		}
	}
}

void Representador::procesar_animacion_color(float delta)
{
	animacion_cambio_color.tiempo+=delta;

	if(animacion_cambio_color.tiempo >= 0.5)
	{
		++animacion_cambio_color.cambios;
		animacion_cambio_color.tiempo=0.0;		
	}

	animacion_cambio_color.finalizada=animacion_cambio_color.cambios==7;
}

bool Representador::es_flicker_animacion_color()
{
	return animacion_cambio_color.cambios && !animacion_cambio_color.tiempo;
}

void Representador::tick_show_title(float) {

	//TODO:
}

bool Representador::is_show_title_done() const {

	return true;
}

void Representador::reset_show_title() {

	//TODO:
}

void Representador::show_title(
	DLibV::Pantalla&, 
	int
) {

	//TODO: Choose resource (100 is special, is the hub, can have 4 titles!!).
	//TODO: Center resoruce horizontally on the screen...
	//TODO: Display, I guess that also fade it out.
}
