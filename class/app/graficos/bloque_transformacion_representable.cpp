#include "bloque_transformacion_representable.h"

using namespace App_Graficos;

Bloque_transformacion_representable::Bloque_transformacion_representable(const Animaciones& animaciones)
	:
	animaciones(animaciones),
	rep_bmp(), 
	rep_agr_din(true),
	rep_agr_est(true),
	rep_prim_punt(0, 0, 0),
	rep_prim_caja(DLibH::Herramientas_SDL::nuevo_sdl_rect(0,0,0,0), 0, 0, 0),
	rep(&rep_bmp),
	tipo_actual(tipos::tr_bitmap),
	visible(true)
{
	rep_agr_din.imponer_alpha();
	rep_agr_din.imponer_modo_blend();
	rep_agr_est.imponer_alpha();
	rep_agr_est.imponer_modo_blend();
}

Bloque_transformacion_representable::~Bloque_transformacion_representable()
{
	rep_agr_din.vaciar_grupo();
	rep_agr_est.vaciar_grupo();
}

const Herramientas_proyecto::Tabla_animaciones&	Bloque_transformacion_representable::obtener_tabla_animaciones(size_t v) const
{
	return animaciones.obtener(v);
}

const Herramientas_proyecto::Animacion&	Bloque_transformacion_representable::obtener_animacion(size_t tabla, size_t animacion) const
{
	return animaciones.obtener(tabla).obtener(animacion);
}

const Herramientas_proyecto::Frame_sprites& Bloque_transformacion_representable::obtener_frame(size_t tabla, size_t animacion, size_t frame) const
{
	return animaciones.obtener(tabla).obtener(animacion).obtener(frame).frame;
}

bool Bloque_transformacion_representable::es_visible() const 
{
	return visible;
}

void Bloque_transformacion_representable::establecer_recorte(unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
{
	rep->establecer_recorte(x, y, w, h);	
}

void Bloque_transformacion_representable::establecer_posicion(unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
{
	rep->establecer_posicion(x, y, w, h);
}

SDL_Rect Bloque_transformacion_representable::acc_posicion() const 
{
	return rep->acc_posicion();
}

void Bloque_transformacion_representable::establecer_tipo(tipos t)
{
	tipo_actual=t;

	switch(t)
	{
		case tipos::tr_bitmap: 
			rep_bmp.reiniciar_transformacion();
//				rep_bmp.establecer_mod_color(255,255,255);
			rep=&rep_bmp;
		break;

		case tipos::tr_grupo_dinamico:
			rep_agr_din.vaciar_grupo();
			rep=&rep_agr_din;
		break;

		case tipos::tr_grupo_estatico:
			rep_agr_est.vaciar_grupo();
			rep=&rep_agr_est;
		break;

		case tipos::tr_primitiva_puntos:
			rep_prim_punt.limpiar_puntos();
			rep=&rep_prim_punt;
		break;

		case tipos::tr_primitiva_caja:
			rep=&rep_prim_caja;
		break;

		case tipos::tr_externa:
			rep=nullptr;
		break;
	}

	establecer_alpha(255);
	establecer_blend(DLibV::Representacion::BLEND_ALPHA);
	establecer_mod_color(255, 255, 255);
	visible=true;
}

void Bloque_transformacion_representable::ocultar()
{
	visible=false;
}

void Bloque_transformacion_representable::establecer_alpha(unsigned int v) 
{
	if(v > 255) v=255;
	rep->establecer_alpha(v);
}

void Bloque_transformacion_representable::establecer_blend(unsigned int v) 
{
	rep->establecer_modo_blend(v);
}

void Bloque_transformacion_representable::establecer_mod_color(unsigned int r, unsigned int g, unsigned int b) 
{
	rep->establecer_mod_color(r, g, b);
}

///////////////////
// Metodos para manipular el grupo de representaciones...

void Bloque_transformacion_representable::insertar_en_grupo(DLibV::Representacion * r) 
{
	switch(tipo_actual)
	{
		case tipos::tr_bitmap:
		case tipos::tr_primitiva_puntos:
		case tipos::tr_primitiva_caja:
		case tipos::tr_externa: break;
		case tipos::tr_grupo_dinamico:	rep_agr_din.insertar_representacion(r);	break;
		case tipos::tr_grupo_estatico:	rep_agr_est.insertar_representacion(r);	break;

	}
}

////////////////////
//Métodos para manipular la representación de puntos.

void Bloque_transformacion_representable::color_puntos(int r, int g, int b)
{
	rep_prim_punt.mut_rgb(r, g, b);
}

void Bloque_transformacion_representable::insertar_punto(int x, int y)
{
	rep_prim_punt.insertar(x, y);
}

/////////////////////
// Métodos para manipular la representación de caja...

void Bloque_transformacion_representable::color_caja(int r, int g, int b)
{
	rep_prim_caja.mut_rgb(r, g, b);
}

void Bloque_transformacion_representable::posicion_caja(int x, int y, int w, int h)
{
	rep_prim_caja.establecer_posicion(x, y, w, h);
}

///////////////////
// Métodos para manipular la representación de bitmap...

void Bloque_transformacion_representable::invertir_horizontal(bool v) 
{
	rep_bmp.transformar_invertir_horizontal(v);
}

void Bloque_transformacion_representable::invertir_vertical(bool v) 
{
	rep_bmp.transformar_invertir_vertical(v);
}

void Bloque_transformacion_representable::rotar(float v) 
{
	rep_bmp.transformar_rotar(v);
}

void Bloque_transformacion_representable::especificar_centro_rotacion(float x, float y) 
{
	rep_bmp.transformar_centro_rotacion(x, y);
}

void Bloque_transformacion_representable::establecer_recurso(unsigned int i) //Por defecto establece el recorte al tamaño del recurso.
{
	if(!DLibV::Gestor_texturas::comprobar(i)) LOG<<"SOLICITADO RECURSO "<<i<<", NO EXISTENTE"<<std::endl;
	else rep_bmp.establecer_textura(DLibV::Gestor_texturas::obtener(i));
}

//Establece un recurso que no tiene porqué estar en el gestor.	
void Bloque_transformacion_representable::establecer_textura_manual(DLibV::Textura * r) 
{
	rep_bmp.establecer_textura(r);
}

/**
* Establece el puntero a una representación que no es una de las que provee
* el bloque de transformación representable. Si luego no existe o falla no es
* problema de esta clase.
*/

void Bloque_transformacion_representable::establecer_externa(DLibV::Representacion * p_rep)
{
	establecer_externa(*p_rep);
}

void Bloque_transformacion_representable::establecer_externa(DLibV::Representacion& p_rep)
{
	tipo_actual=tipos::tr_externa;
	rep=&p_rep;
}
