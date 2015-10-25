#ifndef SALIDA_H
#define SALIDA_H

#include "actor.h"
#include "../interfaces/representable.h"
#include "../definiciones/animaciones.h"
#include "../recursos.h"

namespace App_Juego
{

class Salida:
	public Actor,
	public App_Interfaces::Representable
{
	////////////////////////
	// Interfaz pública...
	public:
						Salida(float x, float y, size_t, bool);
	size_t					acc_indice_sala() const {return indice_sala;}	
	bool					es_bloqueada() const {return !accesible;}
	void					bloquear();

	///////////////////////
	// Implementación de Representable.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

	/////////////////////////
	// Internas....
	private:

	static const int 			W=32;
	static const int 			H=32;
	
	size_t					indice_sala;
	bool					accesible,
						bloqueable;
};

}
#endif
