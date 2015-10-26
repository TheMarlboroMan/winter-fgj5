#ifndef CONTROLADOR_GAME_OVER_H
#define CONTROLADOR_GAME_OVER_H

#include "controlador_base.h"
#include "../app/recursos.h"
#include "../app/definiciones/loc.h"

class Controlador_game_over:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
					Controlador_game_over(Director_estados& d, Localizador& loc, Configuracion_base& config);

	virtual void 			preloop(Input_base& input, float delta);
	virtual void 			postloop(Input_base& input, float delta);
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);

	void				activar_texto() {rep_the_end.cambiar_visibilidad(true);}
	void				desactivar_texto() {rep_the_end.cambiar_visibilidad(false);}

	private:

	DLibV::Representacion_bitmap_estatica 	rep_game_over;
	DLibV::Representacion_bitmap_estatica 	rep_the_end;
	float 					tiempo;
	int 					alpha, alpha_the_end;
};

#endif
