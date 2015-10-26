#include "controlador_game_over.h"

Controlador_game_over::Controlador_game_over(Director_estados& d, Localizador& loc, Configuracion_base& config)
	:Controlador_base(d, loc, config),
	rep_game_over(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_game_over)),
	rep_the_end(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_the_end)),
	tiempo(0.0f), alpha(0), alpha_the_end(0)
{
	rep_game_over.ir_a(300, 120);
	rep_the_end.ir_a(230, 320);

	rep_game_over.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
	rep_the_end.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
}

void Controlador_game_over::preloop(Input_base& input, float delta)
{

}


void Controlador_game_over::postloop(Input_base& input, float delta)
{

}

void Controlador_game_over::loop(Input_base& input, float delta)
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

		alpha_the_end=(tiempo * 255) / 5.0f;
		if(alpha_the_end > 255) alpha_the_end=255;

		rep_game_over.establecer_alpha(alpha);
		rep_the_end.establecer_alpha(alpha_the_end);

		if(input.hay_eventos_teclado_down() && alpha > 200)
		{
			solicitar_cambio_estado(Director_estados::t_estados::intro);
		}
	}
}

void Controlador_game_over::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);
	rep_game_over.volcar(pantalla);
	rep_the_end.volcar(pantalla);
}
