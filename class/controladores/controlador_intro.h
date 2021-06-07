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

	void 			loop_fadein(Input_base& input, float delta);
	void 			loop_fadeout(Input_base& input, float delta);
	void 			loop_title(Input_base& input, float delta);
	void 			loop_to_credits(Input_base& input, float delta);
	void 			loop_credits(Input_base& input, float delta);
	void 			loop_to_title(Input_base& input, float delta);


	DLibV::Representacion_bitmap_estatica rep_fondo,
										rep_credits;

	enum class states{fadein, title, to_credits, credits, to_title, fadeout};
	states state{states::fadein};

	float 				tiempo{0.f};
	int				alpha{0};
};

#endif
