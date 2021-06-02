#include "representacion_primitiva_linea.h"

using namespace DLibV;



Representacion_primitiva_linea::Representacion_primitiva_linea(int px1, int py1, int px2, int py2, Uint8 pr, Uint8 pg, Uint8 pb)
	:Representacion_primitiva(pr, pg, pb), x1(px1), y1(py1), x2(px2), y2(py2)
{
	generar_posicion();
}

Representacion_primitiva_linea::Representacion_primitiva_linea(const Representacion_primitiva_linea& p_otra)
	:Representacion_primitiva(p_otra)
{

}

Representacion_primitiva_linea& Representacion_primitiva_linea::operator=(const Representacion_primitiva_linea& p_otro)
{
	Representacion_primitiva::operator=(p_otro);
	return *this;
}

Representacion_primitiva_linea::~Representacion_primitiva_linea()
{

}

void Representacion_primitiva_linea::establecer_puntos(int px1, int py1, int px2, int py2)
{
	x1=px1;
	y1=py1;
	x2=px2;
	y2=py2;
	generar_posicion();
}

void Representacion_primitiva_linea::generar_posicion()
{
	int x, y, w, h;

	auto f=[](int v1, int v2, int& pos, int& medida)
	{
		if(v1 > v2)
		{
			pos=v1;
			medida=v2-v1;
		}
		else
		{
			pos=v2;
			medida=v1-v2;
		}
	};

	f(x1, x2, x, w);
	f(y1, y2, y, h);

	establecer_posicion(x, y, w, h);
}

bool Representacion_primitiva_linea::volcado(SDL_Renderer * p_renderer)
{
	if(!es_visible()) return false;

	Uint8 alpha=acc_alpha();
	if(alpha) SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
	else SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(p_renderer, acc_r(), acc_g(), acc_b(), alpha);
	SDL_RenderSetClipRect(p_renderer, NULL);

	SDL_RenderDrawLine(p_renderer, x1, y1, x2, y2);

	return true;
}

bool Representacion_primitiva_linea::volcado(SDL_Renderer * p_renderer, const SDL_Rect& p_enfoque, const SDL_Rect& p_posicion)
{
	if(!es_visible()) return false;

	Uint8 alpha=acc_alpha();
	if(alpha) SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
	else SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(p_renderer, acc_r(), acc_g(), acc_b(), alpha);
	SDL_Rect pos=copia_posicion();
	SDL_Rect clip=p_posicion;

	if(this->es_estatica())
	{
		//Comprobar si, como estática, estaría dentro del enfoque de la cámara (básicamente 0,0 ancho y alto).
		SDL_Rect caja_cam=DLibH::Herramientas_SDL::nuevo_sdl_rect(0, 0, p_enfoque.w, p_enfoque.h);

		if(!DLibH::Herramientas_SDL::rectangulos_superpuestos(caja_cam, pos, true))
		{
			return false;
		}
		else
		{
			pos.x+=p_posicion.x;
			pos.y+=p_posicion.y;

			//Posición absoluta.
			SDL_RenderSetClipRect(p_renderer, &clip);

			//Proceso del zoom...					
			if(p_enfoque.w != p_posicion.w || p_enfoque.h != p_posicion.h)
			{
				procesar_zoom(pos, p_posicion, p_enfoque);
			}
			SDL_RenderDrawLine(p_renderer, x1, y1, x2, y2);
			return true;
		}
	}
	else
	{
		if(!DLibH::Herramientas_SDL::rectangulos_superpuestos(p_enfoque, pos, true))
		{
			return false;
		}
		else
		{
			//Calcular la nueva caja...
			pos.x+=p_posicion.x;
			pos.y+=p_posicion.y;

			pos.x-=p_enfoque.x;
			pos.y-=p_enfoque.y;

			SDL_RenderSetClipRect(p_renderer, &clip);

			//Proceso del zoom...
			if(p_enfoque.w != p_posicion.w || p_enfoque.h != p_posicion.h)
			{
				float fx=(float) p_posicion.w / (float) p_enfoque.w;
				float fy=(float) p_posicion.h / (float) p_enfoque.h;
				pos.w*=fx;
				pos.h*=fy;
				pos.x*=fx;
				pos.y*=fy;
			}


			//TODO... HOW?
			SDL_RenderDrawLine(p_renderer, x1, y1, x2, y2);	
			return true;
		}
	}
}

void Representacion_primitiva_linea::preparar_posicion()
{
	//No hace nada.
}	
