#ifndef CONTROLADOR_INTRO_H
#define CONTROLADOR_INTRO_H

#include "controlador_base.h"
#include "../app/definiciones/loc.h"
#include "../app/recursos.h"

class Controlador_intro:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
					Controlador_intro(Director_estados& d, Localizador& loc, Configuracion_base& config);

	virtual void 			preloop(Input_base& input, float delta);
	virtual void 			postloop(Input_base& input, float delta);
	virtual void 			loop(Input_base& input, float delta);
	virtual void 			dibujar(DLibV::Pantalla& pantalla);
	void 					reset();

	private:

	DLibV::Representacion_bitmap_estatica rep_fondo;

	float 				tiempo{0.f};
	int				alpha{0};
};

#endif
