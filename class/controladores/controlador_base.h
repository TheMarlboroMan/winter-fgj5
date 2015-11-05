#ifndef CONTROLADOR_BASE
#define CONTROLADOR_BASE

#include "../framework/interface_controlador.h"
#include "director_estados.h"
#include "../framework/derivada/localizador.h"
#include "../framework/base/configuracion_base.h"
#include <capa_compatibilidad_representaciones_libdansdl2.h>

class Controlador_base:public Interface_controlador
{
	public:

	Controlador_base(Director_estados &d, Localizador& loc, Configuracion_base& config)
		:DI(d), loc(loc), configuracion(config),
		abandonar(false), romper(false)
	{

	}

	void solicitar_cambio_estado(Director_estados::t_estados v) 
	{
		DI.solicitar_cambio_estado(v);
	}

	bool 				es_abandonar_aplicacion() const {return abandonar;}
	bool 				es_romper_loop() const {return romper;}

	void 				abandonar_aplicacion() {abandonar=true;}
	void 				romper_loop() {romper=true;}

	std::string			texto_localizado(int indice) {return loc.obtener(indice);}
	Configuracion_base& 		acc_configuracion() {return configuracion;}

	private:

	Director_estados& 		DI;
	Localizador			loc;
	Configuracion_base& 		configuracion;

	bool 				abandonar;
	bool 				romper;
};

#endif
