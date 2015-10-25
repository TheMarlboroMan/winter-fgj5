#ifndef JUGADOR_H
#define JUGADOR_H

#include <memory>
#include <map>
#include "actor_movil.h"
#include "../interfaces/representable.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../input/input_usuario.h"
#include "../definiciones/definiciones.h"

namespace App_Juego
{

class Jugador:
	public Actor_movil, 
	public App_Interfaces::Representable
{
	////////////////////////
	// Interfaz pública...
	public:
						Jugador(float x=0.0, float y=0.0);
						~Jugador();

	void 					recoger_input(App_Input::Input_usuario iu) {input=iu;}
	void 					turno(float delta);
	App_Interfaces::Espaciable::t_caja	acc_posicion_anterior() const {return posicion_anterior;}
	App_Interfaces::Espaciable::t_caja	caja_comprobar_caida() const;
	void					saltar();
	void					cancelar_control_salto();
	void					perder_vida();
	void					establecer_en_caida() {estado=estados::salto_no_control;}
	void					restaurar_a_inicio_nivel(float x, float y);
	void					iniciar_disparo();

	
	App_Definiciones::direcciones 		acc_direccion() const {return direccion;}
	bool 					es_encarando_direccion(App_Definiciones::direcciones dir) const {return direccion==dir;}
	bool					es_saltando_control() const {return estado==estados::salto_control;}
	bool					puede_saltar() const {return estado!=estados::salto_control && estado!=estados::salto_no_control;}
	bool					puede_disparar() const {return !tiempo_disparando;}
	bool					es_en_suelo() const {return estado==estados::suelo;}

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return PESO;}
	virtual float 				obtener_max_velocidad_caida() const {return MAXIMA_VELOCIDAD_CAIDA;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo);

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

	enum class estados {suelo, salto_control, salto_no_control, perder_vida} estado;

	static const int 			W=14;
	static const int 			H=30;

	static const float 			ACELERACION_HORIZONTAL_SEGUNDO;
	static const float 			DECELERACION_HORIZONTAL_SEGUNDO;
	static const float 			MAXIMA_VELOCIDAD_HORIZONTAL;
	static const float 			MAXIMA_VELOCIDAD_CAIDA;
	static const float 			VALOR_GRAVEDAD;
	static const float 			VECTOR_SALTO;
	static const float 			VECTOR_PERDER_VIDA;
	static const float			PESO;
	static const float			DURACION_DISPARO;

	App_Input::Input_usuario 		input;
	App_Definiciones::direcciones 		direccion;
	App_Interfaces::Espaciable::t_caja	posicion_anterior;
	float					tiempo_disparando;

};

}
#endif
