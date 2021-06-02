#ifndef CAMARA_H
#define CAMARA_H

#include <SDL2/SDL.h>
#include "../../herramientas/herramientas_sdl/herramientas_sdl.h"

namespace DLibV
{

class Camara
{
	private:

	//Propiedades...

	SDL_Rect caja_foco;			//La caja a la que se apunta en el "mundo", es decir, estamos apuntado al punto x, y, enfocando w y h del mundo. Si cambian estos w y h haríamos zoom.
	SDL_Rect caja_pos;		//La caja desplazada con pos_x y pos_y, guardada aquí para no crearla again and again. La cámara aparece en pantalla en x e y, con ancho y alto tal.
	unsigned int pos_x;		//La posición X e Y en la que aparece la cámara en pantalla.
	unsigned int pos_y;

//	bool con_clip;			//Indica si no puede dibujar nada fuera de pos_x, pos_y, caja.w y caja.h.

	bool limitada;
	Sint16 limite_min_x;		//Límites para el movimiento de la cámara.
	Sint16 limite_min_y;
	Sint16 limite_max_x;
	Sint16 limite_max_y;

	void sincronizar_cajas();
	
	public:

	//Interfaz pública.

	Camara(Sint16=0, Sint16=0, Uint16=800, Uint16=600, unsigned int=0, unsigned int=0);
	~Camara();

	const SDL_Rect& acc_caja_foco() const {return this->caja_foco;}
	const SDL_Rect& acc_caja_pos() const {return this->caja_pos;}

	SDL_Rect copia_caja_foco() const {return this->caja_foco;}
	SDL_Rect copia_caja_pos() const {return this->caja_pos;}

	unsigned int acc_pos_x() const {return this->pos_x;}
	unsigned int acc_pos_y() const {return this->pos_y;}
	Sint16 acc_x() const {return this->caja_foco.x;}
	Sint16 acc_y() const {return this->caja_foco.y;}

	void mut_pos_x(unsigned int p_valor) {this->pos_x=p_valor; sincronizar_cajas();}
	void mut_pos_y(unsigned int p_valor) {this->pos_y=p_valor; sincronizar_cajas();}
	void mut_x(Sint16 p_valor) {this->caja_foco.x=p_valor;}
	void mut_y(Sint16 p_valor) {this->caja_foco.y=p_valor;}
	void mut_enfoque(unsigned int w, unsigned int h) 
	{
		caja_foco.w=w; caja_foco.h=h;
		enfocar_a(caja_foco.x, caja_foco.y);
	}
	void mut_w_pos(unsigned int v) {caja_pos.w=v;}
	void mut_h_pos(unsigned int v) {caja_pos.h=v;}
	void mut_w_enfoque(unsigned int v) {caja_foco.w=v;}
	void mut_h_enfoque(unsigned int v) {caja_foco.h=v;}
	void restaurar_enfoque() 
	{
		caja_foco.w=caja_pos.w;
		caja_foco.h=caja_pos.h;
	}

	void enfocar_a(Sint16, Sint16);
	void movimiento_relativo(Sint16=0, Sint16=0);
	void establecer_limites(Sint16, Sint16, Sint16, Sint16);
	void limpiar_limite();

	void transformar_posicion_raton(int& x, int& y);
};

} //Fin namespace DLibV

#endif
