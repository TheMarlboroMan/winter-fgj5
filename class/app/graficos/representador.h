#ifndef REPRESENTADOR_H
#define REPRESENTADOR_H

#include <iomanip>

#include "bloque_transformacion_representable.h"
#include "../definiciones/definiciones.h"
#include "../interfaces/representable.h"
//#include "barra_indicadora.h"

/*El representador funciona de la siguiente forma: desde el controlador
generamos un array de punteros a "Representables". Se le pasa el array al
representador que primero lo ordena por profundidad y luego genera un bloque de
transformación que pasa y procesa para cada uno de ellos.

El representador, por supuesto, sólo funciona con aquellas entidades que sean
"Representable", esto es, para todo aquello que forme parte del mundo. HUDS,
mensajes y otras cosas irían representadas de otro modo.
*/

namespace App_Graficos
{

class Representador
{
	/////////////////////////
	// Interface pública

	public:

						Representador(const Animaciones&);
	unsigned int 				generar_vista(DLibV::Pantalla&, DLibV::Camara&, const std::vector<const App_Interfaces::Representable *>&);
	unsigned int 				generar_vista(DLibV::Pantalla&, const std::vector<const App_Interfaces::Representable *>&);
	void 					generar_hud(DLibV::Pantalla& pantalla, const App_Definiciones::Estado_dinamicas&, const App_Definiciones::Datos_juego&);
	void					generar_fondo(DLibV::Pantalla& pantalla, const DLibH::Caja<float, int>& caja, int x, int y, int w, int h);
	void					generar_mensaje(DLibV::Pantalla& pantalla, const std::string& txt);

	void 					resetar_animaciones();
	void 					procesar_animacion_fondo(float delta);
	void 					procesar_animacion_color(float delta);
	void					reset_show_title();
	void					tick_show_title(float);
	bool					is_show_title_done() const;
	void					show_title(DLibV::Pantalla&, int);
	bool					es_animacion_color_finalizada() const {return animacion_cambio_color.finalizada;}
	bool					es_animacion_fondo_finalizada() const {return animacion_caida_fondo.finalizada;}
	bool					es_flicker_animacion_color();

	private:

	static const int				INDICE_HUD_MARCO_PUNTOS=1;
	static const int				INDICE_HUD_MARCO_DISPAROS=2;
	static const int				INDICE_HUD_MARCO_VIDA=3;
	static const int				INDICE_HUD_DISPARO=4;
	static const int				INDICE_HUD_VIDA=5;
	static const int				INDICE_HUD_MARCO_TEXTO=6;

	static const int				ORIGEN_HUD_X=20;
	static const int				ORIGEN_HUD_Y=20;
	static const int				DESP_MARCO_PUNTOS_X=0;
	static const int				DESP_MARCO_PUNTOS_Y=0;
	static const int				DESP_PUNTOS_X=4;
	static const int				DESP_PUNTOS_Y=4;
	static const int				DESP_MARCO_DISPAROS_X=0;
	static const int				DESP_MARCO_DISPAROS_Y=32;
	static const int				DESP_DISPAROS_X=8;
	static const int				DESP_DISPAROS_Y=36;
	static const int				DESP_MARCO_VIDA_X=32;
	static const int				DESP_MARCO_VIDA_Y=32;
	static const int				DESP_VIDA_X=40;
	static const int				DESP_VIDA_Y=41;
	static const int				SEPARACION_DISPAROS=16;
	static const int				SEPARACION_VIDA=18;
	static const int				MARCO_TEXTO_X=340;
	static const int				MARCO_TEXTO_Y=200;
	static const int				TEXTO_X=346;
	static const int				TEXTO_Y=206;

	Bloque_transformacion_representable 		bloque_transformacion;
	Herramientas_proyecto::Tabla_sprites	hoja;

	struct Animacion_caida_fondo
	{
		float		tiempo;
		float 		pos_fondo_x;
		float 		pos_fondo_y;
		float		angulo_rotacion;
		float		velocidad_caida;
		float		velocidad_horizontal;
		float		acel_angulo;
		bool		finalizada=false;

		Animacion_caida_fondo()
			:tiempo(0.0f), pos_fondo_x(0.0f), pos_fondo_y(0.f),
			angulo_rotacion(0.f), velocidad_caida(0.f), velocidad_horizontal(0.f),
			acel_angulo(1.f)
		{}

	}animacion_caida_fondo;

	struct Animacion_cambio_color
	{
		float		tiempo;
		int		cambios=0;
		bool		finalizada=false;
		Animacion_cambio_color()
			:tiempo(0.0f)
		{}
	}animacion_cambio_color;

	struct title_transition_out {

		float time{0.f};
		int alpha{255};

		void reset() {

			time=0.f;
			alpha=255;
		}

		void tick(float _delta) {

			time+=_delta;
			if(time > 4.f) {

				alpha=255 - (( (time-4.f) * 255) / 3.0f);
			}

			if(alpha < 0) {

				alpha=0;
			}
		}

		bool is_done() const {

			return time > 7.0f;
		}

	} title_transition_out;

};
}
#endif
