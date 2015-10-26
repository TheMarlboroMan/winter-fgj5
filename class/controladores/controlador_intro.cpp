#include "controlador_intro.h"

Controlador_intro::Controlador_intro(Director_estados& d, Localizador& loc, Configuracion_base& config)
	:Controlador_base(d, loc, config),
	rep_fondo(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_intro))
{
	rep_fondo.establecer_posicion(0, 0, 800, 600);
	rep_fondo.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
}

void Controlador_intro::preloop(Input_base& input, float delta)
{

}


void Controlador_intro::postloop(Input_base& input, float delta)
{

}

void Controlador_intro::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else
	{
		tiempo+=delta;
		alpha=(tiempo * 255) / 2.0f;
		if(alpha > 255) alpha=255;
		rep_fondo.establecer_alpha(alpha);

		if(input.hay_eventos_teclado_down() && alpha==255)
		{
			solicitar_cambio_estado(Director_estados::t_estados::juego);
		}
	}
}

void Controlador_intro::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);
	rep_fondo.volcar(pantalla);
} 
