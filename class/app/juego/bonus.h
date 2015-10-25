#ifndef BONUS_H
#define BONUS_H

#include "actor.h"
#include "../interfaces/representable.h"
#include "../interfaces/objeto_juego.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"
#include "../definiciones/animaciones.h"

namespace App_Juego
{

class Bonus:
	public App_Interfaces::Objeto_juego,
	public Actor, 
	public App_Interfaces::Representable
{
	////////////////////////
	// Interfaz pública...
	public:

	enum class tipos {pequeno, mediano, grande, disparos};

						Bonus(float x, float y, tipos);
	bool					es_disparos() const {return tipo==tipos::disparos;}
	bool					es_puntos() const {return tipo!=tipos::disparos;}
	int					acc_puntos() const
	{
		switch(tipo)
		{
			case tipos::pequeno: return 100; break;
			case tipos::mediano: return 500; break;
			case tipos::grande: return 1000; break;
			default:
			case tipos::disparos: return 0; break;
		}
		
	}

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return es_borrar();}

	/////////////////////////
	// Internas....
	private:

	static const int 			W=16;
	static const int 			H=16;
	tipos					tipo;
};

}
#endif
