#ifndef BLOQUE_TRANSFORMACION_REPRESENTABLE_H
#define BLOQUE_TRANSFORMACION_REPRESENTABLE_H

#include <libDan2.h>
#include "animaciones.h"

namespace App_Graficos
{

struct Bloque_transformacion_representable
{
	///////////////////////////////////
	// Definiciones...

	enum class tipos{
		tr_bitmap=1,
		tr_grupo_dinamico=2,
		tr_grupo_estatico=3,
		tr_primitiva_puntos=4,
		tr_primitiva_caja=5,
		tr_externa=6
	};

	///////////////////////////////////
	// Interfaz pública

	public:

								Bloque_transformacion_representable(const Animaciones&);
								~Bloque_transformacion_representable();

	int							acc_ciclo() const {return ciclo;}
	Bloque_transformacion_representable&			mut_ciclo(int v) {ciclo=v; return *this;}
	const Herramientas_proyecto::Tabla_animaciones&		obtener_tabla_animaciones(size_t v) const;
	const Herramientas_proyecto::Animacion&			obtener_animacion(size_t tabla, size_t animacion) const;
	const Herramientas_proyecto::Frame_sprites&		obtener_frame(size_t tabla, size_t animacion, size_t frame) const;
	bool 							es_visible() const;
	void 							establecer_recorte(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	void 							establecer_posicion(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	SDL_Rect 						acc_posicion() const;
	void 							establecer_tipo(tipos t);
	void 							ocultar();
	void 							establecer_alpha(unsigned int v);
	void 							establecer_blend(unsigned int v);
	void 							establecer_mod_color(unsigned int r, unsigned int g, unsigned int b);
	void							establecer_externa(DLibV::Representacion& rep);
	void							establecer_externa(DLibV::Representacion * rep);

	///////////////////
	// Metodos para manipular el grupo de representaciones...

	void 							insertar_en_grupo(DLibV::Representacion * r);

	////////////////////
	//Métodos para manipular la representación de puntos.

	void 							color_puntos(int r, int g, int b);
	void 							insertar_punto(int x, int y);

	////////////////////
	//Métodos para manipular la representación de caja.

	void 							color_caja(int r, int g, int b);
	void 							posicion_caja(int x, int y, int w, int h);

	///////////////////
	// Métodos para manipular la representación de bitmap...

	void 							invertir_horizontal(bool v);
	void 							invertir_vertical(bool v);
	void 							rotar(float v);
	void 							especificar_centro_rotacion(float x, float y);
	void 							establecer_recurso(unsigned int i);
	void 							establecer_textura_manual(DLibV::Textura * r);

	friend class Representador;

	///////////////////////////////////
	// Propiedades

	private:

	const Animaciones&				animaciones;
	DLibV::Representacion_bitmap_dinamica 		rep_bmp;
	DLibV::Representacion_agrupada_dinamica 	rep_agr_din;
	DLibV::Representacion_agrupada_estatica 	rep_agr_est;
	DLibV::Representacion_primitiva_puntos_dinamica rep_prim_punt;
	DLibV::Representacion_primitiva_caja_dinamica 	rep_prim_caja;
	DLibV::Representacion * 			rep;
	tipos 						tipo_actual;
	bool 						visible;
	int						ciclo;
};

}

#endif
