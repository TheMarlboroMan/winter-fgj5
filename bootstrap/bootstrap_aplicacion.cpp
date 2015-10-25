#include "bootstrap_aplicacion.h"

#include "../class/controladores/controlador_juego.h"
#include "../class/controladores/controlador_intro.h"
#include "../class/controladores/controlador_game_over.h"
#include "../class/app/niveles/parser_salas.h"

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	kernel.mut_mostrar_fps(false);
	//Declaraciones de herramientas externas.
	
	Localizador loc("data/loc/loc");
	loc.inicializar(1);

	std::vector<App_Niveles::Sala> salas;

	const int max_niveles=8;
	int indice_nivel=0;

	std::stringstream ss;

	while(indice_nivel <= max_niveles)
	{
		App_Niveles::Parser_salas parser;
		
		ss.str("");
		ss<<"data/niveles/nivel"<<indice_nivel<<".dat";
		LOG<<"Cargando "<<ss.str()<<std::endl;
		parser.parsear_fichero(ss.str());
		salas.push_back(std::move(parser.acc_sala()));
		++indice_nivel;
	}

	App_Graficos::Animaciones animaciones;
	animaciones.cargar();

	//Controladores e interfaces.
	Director_estados DI;
	Controlador_juego C_J(DI, loc, salas, animaciones);
	Controlador_intro C_I(DI, loc);
	Controlador_game_over C_GO(DI, loc);
	Interface_controlador * IC=&C_I;

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::intro: //Del estado intro sólo podemos salir en dirección al juego, que lo resetea.
					C_J.reiniciar_estado_inicial();
				break;
				case Director_estados::t_estados::juego: 
					C_J.restaurar_estado_visual();
					Audio::detener_musica();
				break;
				case Director_estados::t_estados::game_over: 
				case Director_estados::t_estados::the_end: 
				break;
			}

			switch(DI.acc_estado_deseado())
			{
				case Director_estados::t_estados::intro: IC=&C_I; break;
				case Director_estados::t_estados::juego: 
					Audio::reproducir_musica(
						DLibA::Gestor_recursos_audio::obtener_musica(App::Recursos_audio::rm_ballade));
					IC=&C_J; 
				break;
				case Director_estados::t_estados::game_over: 
					C_GO.desactivar_texto();
					IC=&C_GO;
				break;
				case Director_estados::t_estados::the_end: 
					IC=&C_GO; 
					C_GO.activar_texto();
				break;				
			}

			DI.confirmar_cambio_estado();
		}
	};
}
