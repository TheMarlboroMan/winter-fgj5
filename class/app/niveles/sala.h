#ifndef SALA_H
#define SALA_H

#include <memory>


#include <class/matriz2d.h>

#include "celda.h"
#include "celda_decorativa.h"
#include "../definiciones/definiciones.h"
#include "../juego/rompible.h"
#include "../juego/bonus.h"
#include "../juego/enemigo_patrulla.h"
#include "../juego/enemigo_disparador.h"
#include "../juego/enemigo_canon.h"
#include "../juego/entrada.h"
#include "../juego/salida.h"
#include "../juego/plataforma.h"

namespace App_Niveles
{

class Sala
{
	///////////
	// Interface pública.
	public:

	
								Sala(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph);

	App_Definiciones::t_dim 				acc_w() const {return w;}
	App_Definiciones::t_dim 				acc_h() const {return h;}
	void 							insertar_celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Celda::tipo_celda pt); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							insertar_celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim pi); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							modificar_posicion(App_Definiciones::t_dim px, App_Definiciones::t_dim py);
	void 							modificar_dimensiones(App_Definiciones::t_dim px, App_Definiciones::t_dim py);
	std::vector<const App_Interfaces::Representable *> 	obtener_vector_representables() const;
	void							actualizar_borrados();
	void							eliminar_dinamica_disparos();	
	void							eliminar_dinamica_bonus();
	const int						get_name_index() const {return name_index;}


	const Herramientas_proyecto::Matriz_2d<Celda>& 		acc_matriz() const {return celdas;}
	const std::vector<App_Juego::Bonus>&			acc_bonus() const  {return bonus;}

	const std::vector<App_Juego::Salida>&			acc_salidas() const {return salidas;}
	std::vector<App_Juego::Salida>&				ref_salidas() {return salidas;}
	const App_Juego::Entrada&				acc_entrada() const {return entrada;}

	const std::vector<const App_Interfaces::Espaciable*>	acc_objetos_letales() const;
	const std::vector<const App_Interfaces::Espaciable*>	acc_objetos_solidos() const;
	std::vector<App_Interfaces::Disparable*>		acc_disparables();
	std::vector<App_Interfaces::Con_turno*>			acc_con_turno();

	std::vector<App_Juego::Bonus>&				ref_bonus() {return bonus;}

	void							asignar_entrada(const App_Juego::Entrada& v) {entrada=v;}
	void							insertar_objeto(const App_Juego::Salida& v) {salidas.push_back(v);}
	void							insertar_objeto(const App_Juego::Rompible& v) {rompibles.push_back(v);}
	void							insertar_objeto(const App_Juego::Bonus& v) {bonus.push_back(v);}
	void							insertar_objeto(const App_Juego::Enemigo_patrulla& v) {enemigos_patrulla.push_back(v);}
	void							insertar_objeto(const App_Juego::Enemigo_disparador& v) {enemigos_disparador.push_back(v);}
	void							insertar_objeto(const App_Juego::Enemigo_canon& v) {enemigos_canon.push_back(v);}
	void							insertar_objeto(const App_Juego::Plataforma& v) {plataformas.push_back(v);}
	void							set_name_index(int _value) {name_index=_value;}

	///////////
	// Internas de la clase...

	private:

	App_Definiciones::t_dim 				w, h;		//Ancho y alto.
	Herramientas_proyecto::Matriz_2d<Celda> 		celdas;
	Herramientas_proyecto::Matriz_2d<Celda_decorativa> 	celdas_decorativas;
	App_Juego::Entrada					entrada;
	std::vector<App_Juego::Salida>				salidas;
	std::vector<App_Juego::Rompible>			rompibles;
	std::vector<App_Juego::Bonus>				bonus;
	std::vector<App_Juego::Enemigo_patrulla>		enemigos_patrulla;
	std::vector<App_Juego::Enemigo_disparador>		enemigos_disparador;
	std::vector<App_Juego::Enemigo_canon>			enemigos_canon;
	std::vector<App_Juego::Plataforma>			plataformas;
	int											name_index{0};
};
}
#endif
