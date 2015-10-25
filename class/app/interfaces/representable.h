#ifndef REPRESENTABLE_H
#define REPRESENTABLE_H

#include <libDan2.h>
#include "../graficos/bloque_transformacion_representable.h"

extern DLibH::Log_base LOG;
/*
namespace App_Graficos
{
class Bloque_transformacion_representable;
}
*/

namespace App_Interfaces
{
/*Todos los elementos que vayan a ser representados como parte de un nivel
deben implementar la interface "representable". Uno de los métodos de la
misma consiste en recibir un Bloque_transformacion_representable y modificarlo
para luego pasarlo al representador.

El Bloque_transformacion_representable es una entidad que existe sólo una vez
para todas las cosas que se representan: es la alternativa a que cada entidad
representable tenga una copia de su representación.

El método "es_representable_borrar" está ahí para saber si el objeto debe
ser borrado de un hipotético vector de "representables". La implementación 
dependerá de la clase derivada.
*/

class Representable
{
	public:

	virtual 				~Representable() {}
	virtual unsigned short int 		obtener_profundidad_ordenacion()const=0;
	virtual unsigned int			obtener_ciclos_representable()const=0;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;
	virtual bool				es_representable_borrar()const=0;


};

class Ordenador_representables
{
	public: 

	bool operator()(const Representable* a, const Representable* b) const
	{
		return a->obtener_profundidad_ordenacion() < b->obtener_profundidad_ordenacion();
	}
};

}
#endif
