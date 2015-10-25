#ifndef CELDA_H
#define CELDA_H

#include "../interfaces/espaciable.h"
#include "../graficos/representador.h"
#include "celda_base.h"

namespace App_Niveles
{

class Celda:
	public Celda_base,
	public App_Interfaces::Espaciable
{
	//////////
	//Definiciones...
	public:
	enum class tipo_celda {solida, plataforma, letal, bloqueo_enemigo};

	///////////
	// Interface pública

	public:

						Celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, tipo_celda pt);
	bool 					es_solida_solo_arriba() const {return tipo==tipo_celda::plataforma;}
	bool					es_bloqueo_enemigo() const {return tipo==tipo_celda::bloqueo_enemigo || tipo==tipo_celda::solida || tipo==tipo_celda::letal;}
	bool					es_letal() const {return tipo==tipo_celda::letal;}
	bool					es_bloqueo_proyectil(const App_Interfaces::Espaciable::t_caja& caja) const 
	{
		return tipo==tipo_celda::solida || tipo==tipo_celda::letal;
	}

	bool					es_jugador_ignora() const {return tipo==tipo_celda::bloqueo_enemigo;}

/*
	bool					es_bloquea_a_jugador(const App_Interfaces::Espaciable::t_caja& caja) const 
	{
		return tipo==tipo_celda::letal || tipo==tipo_celda::solida ||
		(tipo==tipo_celda::plataforma && App_Interfaces::Espaciable::es_sobre(caja, copia_caja()));
	}
	*/

	//////////////////////////////
	//Implementación de Espaciable
	public:

	bool					es_plataforma() const {return tipo==tipo_celda::plataforma;}
	virtual Espaciable::t_caja 		copia_caja() const;

	//Ninguna de estas funciones hace nada porque la celda es inamovible.
	virtual void 				mut_x_caja(float) {}
	virtual void 				mut_y_caja(float) {}
	virtual void 				desplazar_caja(float, float) {}
	virtual void 				mut_w_caja(unsigned int) {}
	virtual void 				mut_h_caja(unsigned int) {}

	//////////
	// Propiedades
	private:

	tipo_celda 				tipo;
};

}

#endif
