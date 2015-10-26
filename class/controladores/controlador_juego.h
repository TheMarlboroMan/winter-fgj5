#ifndef CONTROLADOR_JUEGO
#define CONTROLADOR_JUEGO

#include <vector>

#include "controlador_base.h"

#include "../app/input/recogedor_input.h"
#include "../app/input/input_usuario.h"
#include "../app/juego/jugador.h"
#include "../app/juego/proyectil.h"
#include "../app/juego/proyectil_enemigo.h"
#include "../app/juego/humo.h"
#include "../app/juego/rompible.h"
#include "../app/juego/humo.h"
#include "../app/graficos/representador.h"
#include "../app/niveles/sala.h"
#include "../app/colisiones/calculador_colisiones.h"
#include "../app/colisiones/ajustador.h"
#include "../app/definiciones/loc.h"

class Controlador_juego:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
	
					Controlador_juego(Director_estados& d, Localizador& loc, Configuracion_base& config, const std::vector<App_Niveles::Sala>& salas, App_Graficos::Animaciones& anim);

	virtual void 			preloop(Input_base& input, float delta);
	virtual void 			postloop(Input_base& input, float delta);
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	void				reiniciar_estado_inicial();
	void				restaurar_estado_visual();

	//////////////
	//Internas...
	private:

	static const size_t		INDICE_SALA_HUB=0;
	static const size_t		INDICE_SALA_FIN_DISPARO=2;
	static const size_t		INDICE_SALA_FIN_BONUS=3;
	static const size_t		INDICE_SALA_FIN_VIDAS=8;

	void 				procesar_jugador(App_Juego::Jugador& j, float delta, App_Input::Input_usuario iu);
	void 				procesar_proyectiles(float delta);
	void 				procesar_borrados();
	void 				procesar_mundo(float delta);
	void 				crear_proyectil_jugador(const App_Juego::Jugador& j);
	void 				crear_proyectil_enemigo(const App_Interfaces::Con_turno::Estructura_disparo&);
	void				ajustar_camara_a_sala(const App_Niveles::Sala&);
	void				evaluar_enfoque_camara();
	void				evaluar_fin_sala(size_t);
	void				cargar_sala(size_t);
	void				procesar_animacion_muerte(float delta, App_Juego::Jugador& j);
	void				procesar_animacion_caida_fondo(float delta, Input_base& input);
	void				procesar_animacion_cambio_color(float delta, Input_base& input);
	void				procesar_animacion_cambio_musica(float delta, Input_base& input);
	void				perder_vida();
	void 				recoger_bonus(App_Juego::Bonus& b);
	void				generar_humo(const App_Interfaces::Disparable&);
	void				procesar_cambio_presentacion();
	void				finalizar_juego();

	enum class estados		{normal, animacion_muerte, animacion} estado;

	App_Definiciones::Estado_dinamicas estado_dinamicas;
	App_Definiciones::Datos_juego	datos_juego;

	DLibV::Camara 			camara;
	App_Graficos::Representador 	representador;
	App_Juego::Jugador		jugador;
	std::vector<App_Juego::Proyectil>	proyectiles;
	std::vector<App_Juego::Proyectil_enemigo>	proyectiles_enemigos;
	std::vector<App_Juego::Humo>	humos;

	const std::vector<App_Niveles::Sala>& salas; //Las salas son una referencia.
	std::vector<bool>		estados_salas;	//Indica si las salas están o no finalizadas.
	App_Niveles::Sala		sala_actual; //La sala actual es una copia de la referencia.
	size_t				indice_sala, siguiente_sala, sala_finalizada;
};

#endif
