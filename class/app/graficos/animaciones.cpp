#include "animaciones.h"
#include "../env.h"

using namespace App_Graficos;

float Animaciones::contador=0.0f;
const float Animaciones::MAX_CONTADOR=30.0f;

const Herramientas_proyecto::Tabla_animaciones& Animaciones::obtener(size_t v) const
{
	return animaciones.at(v);
}

/**
* @throw std::runtime error por animaciones y frames si algo va mal...
*/

void Animaciones::cargar()
{	
	LOG<<"Iniciando registro de animaciones..."<<std::endl;

	//Cargar las tablas de sprites...
	auto f=[this](const std::string& ruta_frames, const std::string& ruta_animaciones, size_t indice)
	{
		LOG<<"Registrando animaciones "<<indice<<" -> "<<ruta_frames<<" -> "<<ruta_animaciones<<std::endl;
		Herramientas_proyecto::Tabla_sprites ts(ruta_frames);
		if(animaciones.count(indice)) throw std::runtime_error("Ya existe tabla de animaciones al cargar tablas!!");
		else animaciones.insert(std::make_pair(indice, Herramientas_proyecto::Tabla_animaciones(ts, ruta_animaciones)));
	};

	f(App::env::make_data_path("data/recursos/tiles.dat"), 
		App::env::make_data_path("data/recursos/animaciones_tiles.dat"), 
		App_Definiciones::animaciones::celdas
	);
	f(App::env::make_data_path("data/recursos/sprites.dat"), 
		App::env::make_data_path("data/recursos/animaciones_sprites.dat"), 
		App_Definiciones::animaciones::sprites
	);
}

void Animaciones::turno(float d)
{
	contador+=d;
	if(contador > MAX_CONTADOR) contador=0.0f;
}

/**
* Obtiene un parcial para el tiempo pasado según t, que es el máximo tiempo de
* animación.
*/

float Animaciones::obtener_tiempo()
{
	return contador;
}
