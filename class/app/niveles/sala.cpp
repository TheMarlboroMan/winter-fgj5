#include "sala.h"
#include <algorithm>

using namespace App_Niveles;
using namespace Herramientas_proyecto;

/**
* @param t_dim pw 
* @param t_dim ph
* @param t_dim px
* @param t_dim py
*/

Sala::Sala(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph)
	:w(pw), h(ph), 
	//TODO: Esconder estas dos detrás de una clase más...
	celdas(pw, ph), celdas_decorativas(pw, ph), entrada(0.f, 0.f)
{

}

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
* @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada.
*/

void Sala::insertar_celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Celda::tipo_celda pt)
{
	celdas(px, py, Celda(px, py, pt));
}

void Sala::insertar_celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim pi)
{
	celdas_decorativas(px, py, Celda_decorativa(px, py, pi));
}

/**
* @return std::vector<const Representable *>
* Devuelve un vector con punteros a los objetos representables que contiene representables.
*/

std::vector<const App_Interfaces::Representable *> Sala::obtener_vector_representables() const
{
	using namespace App_Interfaces;

	typedef std::vector<const App_Interfaces::Representable *> t_res;
	t_res resultado;

	struct obtener
	{		
		obtener(t_res& res):r(res) {}
		t_res& r;
		void operator()(const Celda_decorativa& c) {r.push_back(&c);}
	}obt(resultado);

	//Recolectar las celdas.
	celdas_decorativas.aplicar(obt);

	for(auto& o : salidas) resultado.push_back(&o);
	for(auto& o : rompibles) resultado.push_back(&o);
	for(auto& o : bonus) resultado.push_back(&o);
	for(auto& o : enemigos_patrulla) resultado.push_back(&o);
	for(auto& o : enemigos_disparador) resultado.push_back(&o);
	for(auto& o : plataformas) if(o.es_on()) resultado.push_back(&o);

	return resultado;
}

void Sala::modificar_dimensiones(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph)
{
	w=pw;
	h=ph;
	//TODO: Esconder estas dos detrás de una clase más...
	celdas=celdas.copiar_con_dimensiones(w, h);
	celdas_decorativas=celdas_decorativas.copiar_con_dimensiones(w, h);
}

void Sala::actualizar_borrados()
{
	//TODO... Template, please.

	{
	auto it=std::remove_if(std::begin(rompibles), std::end(rompibles), [](const App_Juego::Rompible& e) {return e.es_borrar();});
	rompibles.erase(it, std::end(rompibles));
	}

	{
	auto it=std::remove_if(std::begin(bonus), std::end(bonus), [](const App_Juego::Bonus& e) {return e.es_borrar();});
	bonus.erase(it, std::end(bonus));
	}

	{
	auto it=std::remove_if(std::begin(enemigos_patrulla), std::end(enemigos_patrulla), [](const App_Juego::Enemigo_patrulla& e) {return e.es_borrar();});
	enemigos_patrulla.erase(it, std::end(enemigos_patrulla));
	}

	{
	auto it=std::remove_if(std::begin(enemigos_disparador), std::end(enemigos_disparador), [](const App_Juego::Enemigo_disparador& e) {return e.es_borrar();});
	enemigos_disparador.erase(it, std::end(enemigos_disparador));
	}

	{
	auto it=std::remove_if(std::begin(enemigos_canon), std::end(enemigos_canon), [](const App_Juego::Enemigo_canon& e) {return e.es_borrar();});
	enemigos_canon.erase(it, std::end(enemigos_canon));
	}

	//Las plataformas no se borran.
}

std::vector<App_Interfaces::Disparable*> Sala::acc_disparables()
{
	std::vector<App_Interfaces::Disparable*> res;

	for(auto& o : rompibles) res.push_back(&o);
	for(auto& o : enemigos_patrulla) res.push_back(&o);
	for(auto& o : enemigos_disparador) res.push_back(&o);

	return res;
}

const std::vector<const App_Interfaces::Espaciable*> Sala::acc_objetos_letales() const
{
	std::vector<const App_Interfaces::Espaciable*> res;

	for(const auto& o : enemigos_patrulla) res.push_back(&o);
	for(const auto& o : enemigos_disparador) res.push_back(&o);

	return res;
}

const std::vector<const App_Interfaces::Espaciable*> Sala::acc_objetos_solidos() const
{
	std::vector<const App_Interfaces::Espaciable*> res;
	for(const auto& o : rompibles) res.push_back(&o);
	for(const auto& o : plataformas) if(o.es_on()) res.push_back(&o);
	return res;
}

std::vector<App_Interfaces::Con_turno*> Sala::acc_con_turno()
{
	std::vector<App_Interfaces::Con_turno*> res;

	for(auto& o : enemigos_patrulla) res.push_back(&o);
	for(auto& o : enemigos_disparador) res.push_back(&o);
	for(auto& o : enemigos_canon) res.push_back(&o);
	for(auto& o : plataformas) res.push_back(&o);

	return res;
}

void Sala::eliminar_dinamica_disparos()
{
	enemigos_patrulla.clear();
	enemigos_disparador.clear();

	//Eliminar bonus disparos...
	auto it=std::remove_if(std::begin(bonus), std::end(bonus), [](const App_Juego::Bonus& b) {return b.es_disparos();});
	bonus.erase(it, std::end(bonus));
}

void Sala::eliminar_dinamica_bonus()
{
	//Eliminar bonus puntos...
	auto it=std::remove_if(std::begin(bonus), std::end(bonus), [](const App_Juego::Bonus& b) {return b.es_puntos();});
	bonus.erase(it, std::end(bonus));
}
