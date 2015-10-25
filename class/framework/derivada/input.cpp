#include "input.h"

void Input::configurar()
{
	//El input I_ESCAPE es la tecla SDLK_ESCAPE. Simple.
	mapa_teclado.insert(std::make_pair(I_ESCAPE, SDL_SCANCODE_ESCAPE));
	mapa_teclado.insert(std::make_pair(I_SALTO, SDL_SCANCODE_SPACE));
	mapa_teclado.insert(std::make_pair(I_DISPARO, SDL_SCANCODE_LCTRL));

	mapa_teclado.insert(std::make_pair(I_IZQUIERDA, SDL_SCANCODE_LEFT));
	mapa_teclado.insert(std::make_pair(I_DERECHA, SDL_SCANCODE_RIGHT));
}
