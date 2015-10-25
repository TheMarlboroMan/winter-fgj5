#ifndef INPUT_USUARIO_H
#define INPUT_USUARIO_H

namespace App_Input
{

struct Input_usuario
{
	enum class t_estados {nada, down, pulsado};

	short int mov_horizontal;
	t_estados salto;
	t_estados disparo;

	Input_usuario():mov_horizontal(0), salto(t_estados::nada), disparo(t_estados::nada)
	{}
};

}
#endif
