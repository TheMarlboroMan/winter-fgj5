#include "representacion_grafica.h"

using namespace DLibV;

extern DLibH::Log_base LOG;

Representacion_grafica::Representacion_grafica()
	:Representacion(), textura(nullptr), preparada(false)
{
	this->reiniciar_posicion();
	this->reiniciar_recorte();
}

Representacion_grafica::Representacion_grafica(const Representacion_grafica& o)
	:Representacion(o) ,textura(o.textura), preparada(o.preparada)
{

}

Representacion_grafica& Representacion_grafica::operator=(const Representacion_grafica& o)
{
	Representacion::operator=(o);
	textura=o.textura;
	preparada=o.preparada;

	return *this;
}

Representacion_grafica::~Representacion_grafica()
{
	//OJO: No se borra el recurso gráfico porque se asume que lo hemos
	//obtenido de un gestor de recursos. Esta clase base NO gestiona los
	//recursos asignados. Una superior, en cambio, si podría.
}

void Representacion_grafica::recorte_a_medidas_textura()
{
	establecer_recorte(0,0, textura->acc_w(), textura->acc_h());
}

bool Representacion_grafica::realizar_render(SDL_Renderer * p_renderer, SDL_Rect& rec, SDL_Rect& pos)
{
	SDL_Texture * tex=ref_textura_sdl();
	SDL_SetTextureAlphaMod(tex, acc_alpha());

	switch(acc_modo_blend())
	{
		case BLEND_NADA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE); break;
		case BLEND_ALPHA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND); break;
		case BLEND_SUMA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD); break;
		case BLEND_MODULAR: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_MOD); break;
	};

	SDL_SetTextureColorMod(tex, acc_mod_color_r(), acc_mod_color_g(), acc_mod_color_b());

	if(!es_transformada())
	{
		return SDL_RenderCopy(p_renderer, tex, &rec,&pos) >= 0;
	}
	else
	{
		DLibV::Representacion_grafica_transformacion t=acc_transformacion();

		float angulo=t.obtener_angulo_rotacion();
		SDL_RendererFlip flip=t.obtener_flip();

		if(t.es_cambia_centro_rotacion())
		{
			SDL_Point centro=t.obtener_centro_rotacion();
			return SDL_RenderCopyEx(p_renderer, tex, &rec, &pos, angulo, &centro, flip) >= 0;
		}
		else
		{
			return SDL_RenderCopyEx(p_renderer, tex, &rec, &pos, angulo, NULL, flip) >= 0;
		}
	}
}

bool Representacion_grafica::volcado(SDL_Renderer * p_renderer)
{
	//Si no está en la pantalla no perdemos tiempo.
	if(!this->es_visible())
	{
		return false;
	}
	else
	{
		if(!this->es_preparada()) this->preparar(p_renderer);


		//Definimos aquí estas variables: puede que al "preparar" hayan cambiado los valores.
		SDL_Rect rec=acc_recorte();
		SDL_Rect pos=acc_posicion();
		SDL_Rect temp=DLibH::Herramientas_SDL::copiar_sdl_rect(pos, 0, 0);

		//Esto es especialmente útil para cuando vamos a hacer 
		//bitmaps en patrón... Para poco más, normalmente es la
		//posición de la representación.
		auto clip_rect=obtener_caja_clip();
		SDL_RenderSetClipRect(p_renderer, &clip_rect);

		return realizar_render(p_renderer, rec, temp);
	}
}

bool Representacion_grafica::volcado(SDL_Renderer * p_renderer, const SDL_Rect& p_foco, const SDL_Rect& p_pos)
{
	if(!this->es_visible())
	{
		return false;
	}
	else
	{	
		//Las representaciones estáticas están SIEMPRE en las mismas
		//posiciones para la cámara que la vea. Simplemente veremos
		//si está dentro de la caja de la cámara en 0,0.
		
		SDL_Rect pos=copia_posicion();
		bool en_toma=true;
		
		if(this->es_estatica())
		{
			SDL_Rect caja_cam=DLibH::Herramientas_SDL::nuevo_sdl_rect(0, 0, p_foco.w, p_foco.h);
			en_toma=DLibH::Herramientas_SDL::rectangulos_superpuestos(caja_cam, pos, false);
		}
		else
		{
			en_toma=DLibH::Herramientas_SDL::rectangulos_superpuestos(p_foco, pos, false);
		}

		if(!en_toma)
		{
			return false;
		}
		else
		{
			if(!this->es_preparada()) this->preparar(p_renderer);

			SDL_Rect rec=copia_recorte();
			pos=copia_posicion();	//Again, por si al preparar ha cambiado.
			SDL_Rect clip_rect=obtener_caja_clip();

			//Una representación estática aparecerá en la posición absoluta del objeto más la posición de la cámara.	
			pos.x+=p_pos.x;
			pos.y+=p_pos.y;
			clip_rect.x+=p_pos.x;
			clip_rect.y+=p_pos.y;

			//Una representación dinámica tiene un cálculo distinto, relativo a la cámara.
			if(!this->es_estatica())
			{
				pos.x-=p_foco.x;
				pos.y-=p_foco.y;
				clip_rect.x-=p_foco.x;
				clip_rect.y-=p_foco.y;
			}

			//Proceso del zoom...
			if(p_foco.w != p_pos.w || p_foco.h != p_pos.h)
			{
				procesar_zoom(pos, p_pos, p_foco);
			}

			//Si la caja de clip se sale por algún lado de la 
			//posición de la cámara vamos a ajustarla...
			DLibH::Herramientas_SDL::rectangulos_superpuestos(p_pos, clip_rect, clip_rect, false);

			SDL_RenderSetClipRect(p_renderer, &clip_rect);
			return realizar_render(p_renderer, rec, pos);
		}
	}
}


//Eso sólo deberíamos llamarlo en aquellas para las cuales hemos creado una
//textura que poseen. Si es parte de un recurso que no es de su propiedad
//te vas a encontrar con un problema.

void Representacion_grafica::liberar_textura()
{
	if(this->textura)
	{
		delete this->textura;
		this->textura=NULL;
	}
}

