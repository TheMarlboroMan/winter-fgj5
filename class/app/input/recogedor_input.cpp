#include "recogedor_input.h"

using namespace App_Input;

Input_usuario Recogedor_input::recoger_input_usuario(Input_base& input) const
{
	auto proc=[&input](Input_usuario::t_estados& e, int t)
	{
		if(input.es_input_down(t)) 		e=Input_usuario::t_estados::down;
		else if(input.es_input_pulsado(t)) 	e=Input_usuario::t_estados::pulsado;
	};

	Input_usuario resultado;

	proc(resultado.salto, Input::I_SALTO);
	proc(resultado.disparo, Input::I_DISPARO);

	if(input.es_input_pulsado(Input::I_DERECHA)) resultado.mov_horizontal=1;
	else if(input.es_input_pulsado(Input::I_IZQUIERDA)) resultado.mov_horizontal=-1;

	return resultado;
}
