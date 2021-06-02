#ifndef PROYECTO_SDL2_DERIVADA_CARGADOR_RECURSOS_H
#define PROYECTO_SDL2_DERIVADA_CARGADOR_RECURSOS_H

#include "../base/cargador_recursos_base.h"
#include "../../app/env.h"

class Cargador_recursos:public Cargador_recursos_base
{
	protected: 

	std::vector<std::string> obtener_entradas_audio() const {return obtener_entradas_desde_ruta(App::env::make_data_path("data/recursos/audio.txt"));}
	std::vector<std::string> obtener_entradas_musica() const {return obtener_entradas_desde_ruta(App::env::make_data_path("data/recursos/musica.txt"));}
	std::vector<std::string> obtener_entradas_texturas() const {return obtener_entradas_desde_ruta(App::env::make_data_path("data/recursos/texturas.txt"));}
	std::vector<std::string> obtener_entradas_superficies() const {return obtener_entradas_desde_ruta(App::env::make_data_path("data/recursos/superficies.txt"));}

	public:

	Cargador_recursos():Cargador_recursos_base() {}
};

#endif
