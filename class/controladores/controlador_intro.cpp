#include "controlador_intro.h"

Controlador_intro::Controlador_intro(Director_estados& d, Localizador& loc, Configuracion_base& config)
	:Controlador_base(d, loc, config),
	rep_fondo(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_intro)),
	rep_credits(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_credits))
{
	rep_fondo.establecer_posicion(0, 0, 800, 600);
	rep_fondo.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);

	rep_credits.establecer_posicion(0, 0, 800, 600);
	rep_credits.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
	rep_credits.establecer_alpha(0);
}

void Controlador_intro::reset() {

	tiempo=0.f;
	alpha=0;
	state=states::fadein;
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
		switch(state) {

			case states::fadein:
				loop_fadein(input, delta);
			break;
			case states::fadeout:
				loop_fadeout(input, delta);
			break;
			case states::title:
				loop_title(input, delta);
			break;
			case states::to_credits:
				loop_to_credits(input, delta);
			break;
			case states::credits:
				loop_credits(input, delta);
			break;
			case states::to_title:
				loop_to_title(input, delta);
			break;
		}
	}
}

void Controlador_intro::loop_fadein(
	Input_base& input,
	float delta
) {

	tiempo+=delta;
	alpha=(tiempo * 255) / 2.0f;
	if(alpha >= 255) {

		tiempo=0.f;
		alpha=255;
		state=states::title;
	}

	rep_fondo.establecer_alpha(alpha);
	rep_credits.establecer_alpha(0);
}

void Controlador_intro::loop_fadeout(
	Input_base& input,
	float delta
) {

	tiempo+=delta;
	alpha=(tiempo * 255) / 2.0f;
	if(alpha >= 255) {

		tiempo=0.f;
		alpha=255;
		state=states::fadein;
		solicitar_cambio_estado(Director_estados::t_estados::juego);
	}

	rep_fondo.establecer_alpha(255-alpha);
	rep_credits.establecer_alpha(0);
}

void Controlador_intro::loop_title(
	Input_base& input,
	float delta
) {

	if(input.es_input_down(Input::I_HELP)) {

		state=states::to_credits;
		Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_wind))));
	}
	else if(input.hay_eventos_teclado_down()) {

		state=states::fadeout;
	}
}

void Controlador_intro::loop_credits(
	Input_base& input,
	float delta
) {

	if(input.hay_eventos_teclado_down() && alpha==255)
	{
		Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_wind))));
		state=states::to_title;
	}
}

void Controlador_intro::loop_to_credits(
	Input_base& input,
	float delta
) {

	tiempo+=delta;
	alpha=(tiempo * 255) / 2.0f;
	if(alpha > 255) {

		tiempo=0.f;
		alpha=255;
		state=states::credits;
	}

	rep_credits.establecer_alpha(alpha);
	rep_fondo.establecer_alpha(255-alpha);
}

void Controlador_intro::loop_to_title(
	Input_base& input,
	float delta
) {

	tiempo+=delta;
	alpha=(tiempo * 255) / 2.0f;
	if(alpha > 255) {

		tiempo=0.f;
		alpha=255;
		state=states::title;
	}

	rep_fondo.establecer_alpha(alpha);
	rep_credits.establecer_alpha(255-alpha);
}

void Controlador_intro::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);
	rep_fondo.volcar(pantalla);
	rep_credits.volcar(pantalla);
}
