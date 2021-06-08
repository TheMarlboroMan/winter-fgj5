#include "controlador_juego.h"

Controlador_juego::Controlador_juego(Director_estados &DI, Localizador& loc, Configuracion_base& config,const std::vector<App_Niveles::Sala>& salas, App_Graficos::Animaciones& anim)
	:Controlador_base(DI, loc, config),
	estado(estados::normal),
	estado_dinamicas(config.acc_volumen_musica()),
	camara(0, 0, App_Definiciones::definiciones::w_vista, App_Definiciones::definiciones::h_vista),
	representador(anim),
	jugador(200, 200),
	salas(salas),
	sala_actual(salas.at(0)),
	indice_sala(0), siguiente_sala(0), sala_finalizada(0)
{

}

void Controlador_juego::reiniciar_estado_inicial()
{
	//Reiniciar parámetros...
	estado_dinamicas=App_Definiciones::Estado_dinamicas(acc_configuracion().acc_volumen_musica());
	datos_juego=App_Definiciones::Datos_juego();
	indice_sala=0;
	siguiente_sala=0;
	sala_finalizada=0;

	representador.resetar_animaciones();
	Audio::establecer_volumen_musica(acc_configuracion().acc_volumen_musica());

	//Reiniciar estado de salas...
	estados_salas.clear();
	estados_salas.insert(std::begin(estados_salas), salas.size(), false);

	//Cargar la sala 0.
	cargar_sala(INDICE_SALA_HUB, true);
}

void Controlador_juego::procesar_cambio_presentacion()
{
	switch(datos_juego.cambios_efectuados)
	{
		case 0:
			LOG<<"Cambio presentación sin efecto"<<std::endl;
		break;
		case 1: //Primer cambio... Se cae el fondo.
			LOG<<"Cambio caida fondo inicado"<<std::endl;
			estado=estados::animacion;
		break;
		case 2: //Segundo cambio... Se cambia la presentación...
			LOG<<"Cambio color inicado"<<std::endl;
			estado=estados::animacion;
		break;
		case 3: //Tercer cambio... Cambia la música...
			LOG<<"Cambio música inicado"<<std::endl;
			estado=estados::animacion;
		break;
	}
}

void Controlador_juego::cargar_sala(
	size_t s,
	bool _is_new_entry
) {

	is_new_room=_is_new_entry;

	if(s==INDICE_SALA_HUB) 	{

		procesar_cambio_presentacion();
	}

	sala_finalizada=indice_sala;
	indice_sala=s;
	sala_actual=salas.at(indice_sala);

	humos.clear();
	proyectiles.clear();
	proyectiles_enemigos.clear();

	ajustar_camara_a_sala(sala_actual);

	//Bloquear las entradas que ya han sido accedidas.
	auto &salidas=sala_actual.ref_salidas();
	for(auto& s: salidas)
	{
		size_t indice=s.acc_indice_sala();
		if(estados_salas[indice]) s.bloquear();
	}

	//Limpiar cosas según dinámicas...
	if(!estado_dinamicas.con_disparo)
	{
		sala_actual.eliminar_dinamica_disparos();
	}

	if(!estado_dinamicas.con_bonus)
	{
		sala_actual.eliminar_dinamica_bonus();
	}

	const auto& entrada=sala_actual.acc_entrada();
	jugador.restaurar_a_inicio_nivel(entrada.acc_espaciable_cx() - (entrada.acc_espaciable_w() / 2), entrada.acc_espaciable_fy()-jugador.acc_espaciable_h()-1);
	evaluar_enfoque_camara();

	//Cuando no quedan dinámicas de juego podemos insertar la última salida a pelo, que lleva al final del juego...
	if(!estado_dinamicas.con_bonus && !estado_dinamicas.con_disparo && !estado_dinamicas.con_vidas)
	{
		App_Juego::Salida salida(369, 512, 9999, false);
		sala_actual.insertar_objeto(salida);
	}

	//The last check is the special case for the hub, in which the animation
	//has priority over the title, which always plays later.
	if(is_new_room && 0!=sala_actual.get_name_index() && estado!=estados::animacion) {

		show_title();
	}
}

void Controlador_juego::preloop(Input_base& input, float delta)
{

}

void Controlador_juego::postloop(Input_base& input, float delta)
{

}

void Controlador_juego::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
	}
	else
	{
		App_Graficos::Animaciones::turno(delta);
		Audio::procesar_cola_sonido();
		using namespace App_Input;

		if(input.es_input_down(Input::I_ESCAPE))
		{
			estado=estados::normal;
			solicitar_cambio_estado(Director_estados::t_estados::intro);
		}
		else switch(estado)
		{
			case estados::normal:
			{
				Recogedor_input ri;
				Input_usuario iu=ri.recoger_input_usuario(input);
				procesar_jugador(jugador, delta, iu);
				procesar_proyectiles(delta);
				procesar_mundo(delta);
				procesar_borrados();
			}
			break;
			case estados::animacion_muerte:
				procesar_animacion_muerte(delta, jugador);
			break;
			case estados::animacion:
				switch(datos_juego.cambios_efectuados)
				{
					case 1: procesar_animacion_caida_fondo(delta, input); break;
					case 2: procesar_animacion_cambio_color(delta, input); break;
					case 3: procesar_animacion_cambio_musica(delta, input); break;
					default: break;
				}
			break;
			case estados::show_title:

				if(representador.is_show_title_done()) {

					estado=estados::normal;
				}
				else {

					representador.tick_show_title(delta);
				}

			break;
		};
	}
}

void Controlador_juego::procesar_animacion_muerte(float delta, App_Juego::Jugador& jugador)
{
	auto v=jugador.acc_vector();
	jugador.desplazar_caja(0.0, v.y * delta);
	jugador.accion_gravedad(delta, 1.0f);

	if(jugador.acc_espaciable_y() > camara.acc_y()+(camara.acc_caja_pos().h*1.5f))
	{
		if(estado_dinamicas.con_vidas) --datos_juego.vidas;

		if(!datos_juego.vidas)
		{
			estado=estados::normal;
			solicitar_cambio_estado(Director_estados::t_estados::game_over);
		}
		else
		{
			estado=estados::normal;
			cargar_sala(indice_sala, false);
			datos_juego.disparos=App_Definiciones::Datos_juego::DISPAROS_DEFECTO;
		}
	}
}

void Controlador_juego::procesar_animacion_caida_fondo(float delta, Input_base& input)
{
	if(!representador.es_animacion_fondo_finalizada())
	{
		representador.procesar_animacion_fondo(delta);
	}
	else
	{
		if(input.hay_eventos_teclado_down())
		{
			show_title();
		}
	}
}

void Controlador_juego::procesar_animacion_cambio_color(float delta, Input_base& input)
{
	//Recibir señales flicker del representador.

	if(!representador.es_animacion_color_finalizada())
	{
		representador.procesar_animacion_color(delta);

		if(representador.es_flicker_animacion_color())
		{
			estado_dinamicas.colores_originales=!estado_dinamicas.colores_originales;
			DLibV::Gestor_texturas::swap(App::Recursos_graficos::rt_celdas, App::Recursos_graficos::rt_celdas_bn);
			DLibV::Gestor_texturas::swap(App::Recursos_graficos::rt_sprites, App::Recursos_graficos::rt_sprites_bn);
		}
	}
	else
	{
		if(input.hay_eventos_teclado_down())
		{
			show_title();
		}
	}
}

void Controlador_juego::procesar_animacion_cambio_musica(float delta, Input_base& input)
{
	if(!estado_dinamicas.volumen_musica && input.hay_eventos_teclado_down())
	{
		Audio::detener_musica();
		show_title();
	}
	else
	{
		estado_dinamicas.volumen_musica-=delta * 20.f;
		if(estado_dinamicas.volumen_musica < 0.f) estado_dinamicas.volumen_musica=0.f;
		Audio::establecer_volumen_musica(estado_dinamicas.volumen_musica);
	}
}

void Controlador_juego::procesar_mundo(float delta)
{
	struct Obtener_bloqueos_enemigo
	{
		void operator()(std::vector<const App_Niveles::Celda *>& resultado)
		{
			auto comprobar=[](const App_Niveles::Celda * cel) ->bool {return !cel->es_bloqueo_enemigo();};
			std::vector<const App_Niveles::Celda *>::iterator fin=std::remove_if(resultado.begin(), resultado.end(), comprobar);
			resultado.erase(fin, resultado.end());
		};
	}obtener_bloqueos_enemigo;

	using namespace App_Colisiones;

	auto con_turno=sala_actual.acc_con_turno();
	for(auto &cp: con_turno)
	{
		Calculador_colisiones CC;
		auto colisiones=CC.solidos_en_caja_sala(cp->copia_caja_con_turno(), sala_actual, obtener_bloqueos_enemigo);

		cp->turno(delta, jugador, colisiones);
		if(cp->es_disparar()) crear_proyectil_enemigo(cp->obtener_estructura_disparo(jugador));
	}

	for(auto &h : humos)
	{
		h.turno(delta);
	}

}

void Controlador_juego::procesar_proyectiles(float delta)
{
	struct Bloqueos_proyectil
	{
		Bloqueos_proyectil(const App_Interfaces::Espaciable::t_caja& c):caja(c) {}
		const App_Interfaces::Espaciable::t_caja& caja;
		void operator()(std::vector<const App_Niveles::Celda *>& resultado)
		{
			auto comprobar=[this](const App_Niveles::Celda * cel) ->bool {return !cel->es_bloqueo_proyectil(caja);};
			std::vector<const App_Niveles::Celda *>::iterator fin=std::remove_if(resultado.begin(), resultado.end(), comprobar);
			resultado.erase(fin, resultado.end());
		};
	};

	for(auto &p: proyectiles)
	{
		//Movimiento.
		const auto& v=p.acc_vector();
		p.turno(delta);
		p.desplazar_caja(v.x * delta, v.y * delta);

		auto disparables=sala_actual.acc_disparables();
		for(auto &d : disparables)
		{
			if(d->es_colision_proyectil(p))
			{
				p.mut_borrar(true);
				d->recibir_disparo(p.acc_potencia());
				if(d->es_disparable_borrar())
				{
					datos_juego.puntuacion+=d->acc_puntos();
					generar_humo(*d);
					Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_destruir))));
				}
				continue;
			}
		}

		//Si colisiona con una celda, fuera...
		auto caja=p.copia_caja();
		auto bp=Bloqueos_proyectil(caja);
		App_Colisiones::Calculador_colisiones CC;
		auto coli=CC.celdas_en_caja(caja, sala_actual, bp); //Comprobamos sólo colisones con celdas.
		if(coli.size())
		{
			p.mut_borrar(true);
			continue;
		}
	}

	for(auto &p: proyectiles_enemigos)
	{
		//Movimiento.
		const auto& v=p.acc_vector();
		p.turno(delta);
		p.desplazar_caja(v.x * delta, v.y * delta);

		//Si colisiona con una celda, fuera...
		auto caja=p.copia_caja();
		auto bp=Bloqueos_proyectil(caja);
		App_Colisiones::Calculador_colisiones CC;
		auto coli=CC.celdas_en_caja(caja, sala_actual, bp); //Comprobamos sólo colisones con celdas.
		if(coli.size()) p.mut_borrar(true);
	}
}

void Controlador_juego::procesar_borrados()
{
	//Eliminar los proyectiles marcados para borrar.

	{
	auto 	ini=std::begin(proyectiles);
	while(ini < std::end(proyectiles))
	{
		if(ini->es_borrar()) ini=proyectiles.erase(ini);
		else ++ini;
	}
	}

	{
	auto 	ini=std::begin(proyectiles_enemigos);
	while(ini < std::end(proyectiles_enemigos))
	{
		if(ini->es_borrar()) ini=proyectiles_enemigos.erase(ini);
		else ++ini;
	}
	}

	{
	auto 	ini=std::begin(humos);
	while(ini < std::end(humos))
	{
		if(ini->es_borrar()) ini=humos.erase(ini);
		else ++ini;
	}
	}

	sala_actual.actualizar_borrados();
}

void Controlador_juego::dibujar(DLibV::Pantalla& pantalla)
{
	DLibH::Caja<float, int> caja_fondo(camara.acc_caja_pos().x, camara.acc_caja_pos().y, camara.acc_caja_pos().w, camara.acc_caja_pos().h);

	representador.generar_fondo(pantalla, caja_fondo, camara.acc_x(), camara.acc_y(), sala_actual.acc_w() * App_Definiciones::definiciones::dim_celda, sala_actual.acc_h() * App_Definiciones::definiciones::dim_celda);

	std::vector<const App_Interfaces::Representable *> vr=sala_actual.obtener_vector_representables();
	for(const auto &p : humos) vr.push_back(&p);
	for(const auto &p : proyectiles) vr.push_back(&p);
	for(const auto &p : proyectiles_enemigos) vr.push_back(&p);
	vr.push_back(&jugador);

	struct Ordenador_representables
	{
		public:

		bool operator()(const App_Interfaces::Representable* a, const App_Interfaces::Representable* b) const
		{
			return a->obtener_profundidad_ordenacion() < b->obtener_profundidad_ordenacion();
		}
	}ord;

	std::sort(std::begin(vr), std::end(vr), ord);

	//Generar vista.
	if(estado==estados::normal) evaluar_enfoque_camara();

	representador.generar_vista(pantalla, camara, vr);
	representador.generar_hud(pantalla, estado_dinamicas, datos_juego);

	//Generar mensaje, si procede...
	if(estado==estados::animacion)
	{
		std::string txt("");
		switch(sala_finalizada)
		{
			case INDICE_SALA_FIN_DISPARO: txt=texto_localizado(App_Definiciones::definiciones_loc::txt_disparo); break;
			case INDICE_SALA_FIN_BONUS: txt=texto_localizado(App_Definiciones::definiciones_loc::txt_bonus); break;
			case INDICE_SALA_FIN_VIDAS: txt=texto_localizado(App_Definiciones::definiciones_loc::txt_vidas); break;
		}

		representador.generar_mensaje(pantalla, txt);
	}

	if(estado==estados::show_title) {

		int index=sala_actual.get_name_index();

		//especial hub...
		if(index==100) {

			switch(datos_juego.cambios_efectuados) {

				case 0: index=26; break;
				case 1: index=27; break;
				case 2: index=28; break;
				case 3: index=29; break;
			}
		}

		representador.show_title(pantalla, index);
	}
}

void Controlador_juego::procesar_jugador(App_Juego::Jugador& j, float delta, App_Input::Input_usuario iu)
{
	using namespace App_Colisiones;
	auto pos_anterior=jugador.acc_posicion_anterior();

	//Functor para detectar si colisionamos con alguna celda letal.
	struct Hay_celda_letal_y_trunca_no_celdas
	{
		int es_letal;

		void operator()(std::vector<const App_Niveles::Celda *>& resultado)
		{
			//Mirar si hay alguna letal.
			bool hay_letal=std::count_if(std::begin(resultado), std::end(resultado), [](const App_Niveles::Celda * cel) ->bool {return cel->es_letal();});

			//Truncar aquellas que no sean sólidas, letales o plataformas.
			std::vector<const App_Niveles::Celda *>::iterator fin=std::remove_if(resultado.begin(), resultado.end(), [](const App_Niveles::Celda * cel) {return cel->es_jugador_ignora();});
			resultado.erase(fin, resultado.end());

			//Letal es cuando no hay contacto con otra cosa que algo letal.
			es_letal=resultado.size() && hay_letal==resultado.size();
		};
	}hay_celda_letal_y_trunca_no_celdas;

	//////
	//Inicio.

	j.recoger_input(iu);

	//Comprobar si el jugador está cayendo...
	if(jugador.es_en_suelo())
	{
		Calculador_colisiones CC;
		auto colisiones_caida=CC.solidos_en_caja_sala(jugador.caja_comprobar_caida(), sala_actual);
		if(!colisiones_caida.size())
		{
			jugador.establecer_en_caida();
		}
	}

	//Intentar saltar...
	if(iu.salto==App_Input::Input_usuario::t_estados::down && jugador.puede_saltar())
	{
		jugador.saltar();
		Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_salto))));

	}
	//Añadir control de altura del salto: si está saltando y se suelta el botón...
	else if(iu.salto==App_Input::Input_usuario::t_estados::nada && jugador.es_saltando_control())
	{
		jugador.cancelar_control_salto();
	}

	//Intentar disparar.
	if(estado_dinamicas.con_disparo && iu.disparo==App_Input::Input_usuario::t_estados::down && datos_juego.disparos && jugador.puede_disparar())
	{
		jugador.iniciar_disparo();
		crear_proyectil_jugador(jugador);
		Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_disparo))));
		--datos_juego.disparos;
	}

	//Interpretar input.
	j.turno(delta);

	//Procesar movimiento tras turno. Se comprueban las colisiones con las celdas
	//y con los objetos de juego sólidos. Por cada parte se comprobará también
	//si ha colisionado con celdas letales.
	bool celda_letal=false;
	auto v=j.acc_vector();
	if(v.y)
	{
		jugador.desplazar_caja(0.0, v.y * delta);
		Calculador_colisiones CC;
		Ajustador AJ;
		auto colisiones=CC.solidos_en_caja_sala(jugador.copia_caja(), sala_actual, hay_celda_letal_y_trunca_no_celdas);

		//Eliminar todos aquellos que sean "es_plataforma" que estén por debajo del jugador".
		//ojo: !es_sobre != es_bajo...
		//Otra forma de decirlo: para tener en cuenta a una plataforma, la posición anterior tiene que haber estado "encima".
		auto fin=std::remove_if(colisiones.begin(), colisiones.end(), [&pos_anterior](const App_Interfaces::Espaciable* e)
		{
			return e->es_plataforma() && !App_Interfaces::Espaciable::es_sobre(pos_anterior, e->copia_caja());
		});
		colisiones.erase(fin, colisiones.end());
		if(colisiones.size()) AJ.ajustar_colisiones_eje_y_actor_movil_con_espaciables(jugador, colisiones);
		celda_letal=celda_letal || hay_celda_letal_y_trunca_no_celdas.es_letal;
	}

	if(v.x)
	{
		jugador.desplazar_caja(v.x * delta, 0.0);
		Calculador_colisiones CC;
		Ajustador AJ;
		auto colisiones=CC.solidos_en_caja_sala(jugador.copia_caja(), sala_actual, hay_celda_letal_y_trunca_no_celdas);

		//Eliminar todos aquellos que sean "es_plataforma" que estén por debajo del jugador".
		auto fin=std::remove_if(colisiones.begin(), colisiones.end(), [&pos_anterior](const App_Interfaces::Espaciable* e)
		{
			return e->es_plataforma() && !App_Interfaces::Espaciable::es_sobre(pos_anterior, e->copia_caja());
		});
		colisiones.erase(fin, colisiones.end());
		if(colisiones.size()) AJ.ajustar_colisiones_eje_x_actor_movil_con_espaciables(jugador, colisiones);
		celda_letal=celda_letal || hay_celda_letal_y_trunca_no_celdas.es_letal;
	}

	//Las colisiones con objetos de juego se evaluan en la posición final.
	auto &bonus=sala_actual.ref_bonus();
	for(auto &b : bonus)
	{
		if(b.en_colision_con(jugador)) recoger_bonus(b);
	}

	//Comprobar colisiones con objetos letales... Con las celdas ya está calculado.
	if(celda_letal)
	{
		perder_vida();
	}
	else
	{
		//Son espaciables...
		const auto& letales=sala_actual.acc_objetos_letales();
		for(auto &l: letales)
		{
			if(l->en_colision_con(jugador))
			{
				perder_vida();
				return;
			}
		}

		//Aquí los proyectiles enemigos.-
		for(auto &l: proyectiles_enemigos)
		{
			if(l.en_colision_con(jugador))
			{
				perder_vida();
				return;
			}
		}
	}

	//Y ahora las salidas de las salas...
	const auto &salidas=sala_actual.acc_salidas();
	for(const auto& s: salidas)
	{
		if(jugador.es_dentro_de(s))
		{
			if(s.es_bloqueada()) continue;

			size_t indice=s.acc_indice_sala();

			if(indice==9999)	//Lool... Hack.
			{
				finalizar_juego();
				return;
			}
			else
			{
				//Marcar la sala como finalizada: para que las puertas
				//a esa sala ya no sean accesibles. La salida en si
				//tendrá una propiedad "bloqueable" que se establece en
				//el editor que actúa como "override".

				estados_salas[indice_sala]=true;
				evaluar_fin_sala(indice_sala);

				siguiente_sala=indice;
				cargar_sala(siguiente_sala, true);
				return;
			}
		}
	}
}

void Controlador_juego::perder_vida()
{
	Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_perder_vida))));
	jugador.perder_vida();
	estado=estados::animacion_muerte;
}

void Controlador_juego::evaluar_enfoque_camara()
{
	const auto& c_foco=camara.acc_caja_foco();
	int x=jugador.acc_espaciable_x()-(c_foco.w / 2 );
	int y=jugador.acc_espaciable_y()-(c_foco.h / 2);
	camara.enfocar_a(x, y);
}

/**
* Establece los límites de la cámara según la sala. Adicionalmente puede cambiar
* el tamaño y la posición de la cámara para salas más pequeñas que la misma.
*/

void Controlador_juego::ajustar_camara_a_sala(const App_Niveles::Sala& s)
{
	using namespace App_Definiciones;
	const int w_sala=sala_actual.acc_w()*definiciones::dim_celda;
	const int h_sala=sala_actual.acc_h()*definiciones::dim_celda;

	camara.establecer_limites(0, 0, w_sala, h_sala);

	//TODO: Todo esto de la cámara es una mierda. Mejorar la librería.
	int w_pos=definiciones::w_vista, h_pos=definiciones::h_vista, x_pos=0, y_pos=0;

	if(w_sala < definiciones::w_vista || h_sala < definiciones::h_vista)
	{
		if(w_sala < definiciones::w_vista)
		{
			w_pos=w_sala;
			x_pos=(definiciones::w_vista - w_sala) / 2;
		}

		if(h_sala < definiciones::h_vista)
		{
			h_pos=h_sala;
			y_pos=(definiciones::h_vista - h_sala) / 2;
		}

	}

	camara.mut_w_pos(w_pos);
	camara.mut_h_pos(h_pos);
	camara.mut_pos_x(x_pos);
	camara.mut_pos_y(y_pos);

	camara.restaurar_enfoque();
}

void Controlador_juego::crear_proyectil_jugador(const App_Juego::Jugador& j)
{
	float vx=j.es_encarando_direccion(App_Definiciones::direcciones::derecha) ? 1.0f : -1.0f;
	proyectiles.push_back(App_Juego::Proyectil(j.acc_espaciable_cx(), j.acc_espaciable_cy(), vx));
}

void Controlador_juego::crear_proyectil_enemigo(const App_Interfaces::Con_turno::Estructura_disparo& ed)
{
	proyectiles_enemigos.push_back(App_Juego::Proyectil_enemigo(ed.x, ed.y, ed.v, ed.peso));
}

/**
* Evalúa las dinámicas que se eliminarán al finalizar una sala en concreto.
*/

void Controlador_juego::evaluar_fin_sala(size_t indice)
{
	Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_nivel_finalizado))));

	switch(indice)
	{
		case INDICE_SALA_FIN_DISPARO:
			estado_dinamicas.con_disparo=false;
			++datos_juego.cambios_efectuados;
		break;

		case INDICE_SALA_FIN_BONUS:
			estado_dinamicas.con_bonus=false;
			++datos_juego.cambios_efectuados;
		break;

		case INDICE_SALA_FIN_VIDAS:
			estado_dinamicas.con_vidas=false;
			++datos_juego.cambios_efectuados;
		break;
	}
}

void Controlador_juego::recoger_bonus(App_Juego::Bonus& b)
{
	if(b.es_disparos())
	{
		datos_juego.disparos+=3;
		if(datos_juego.disparos > App_Definiciones::Datos_juego::MAX_DISPAROS) datos_juego.disparos=App_Definiciones::Datos_juego::MAX_DISPAROS;
	}
	else if(b.es_puntos())
	{
		datos_juego.puntuacion+=b.acc_puntos();
	}

	Audio::insertar_sonido(DLibA::Estructura_sonido((DLibA::Gestor_recursos_audio::obtener_sonido(App::Recursos_audio::rs_item))));
	b.mut_borrar(true);
}

void Controlador_juego::generar_humo(const App_Interfaces::Disparable& d)
{
	const auto caja=d.caja_disparable();
	float cx=caja.origen.x+(caja.w/2), cy=caja.origen.y+(caja.h/2);
	humos.push_back(App_Juego::Humo(cx, cy, DLibH::Vector_2d(-100.f, -100.f)));
	humos.push_back(App_Juego::Humo(cx, cy, DLibH::Vector_2d(100.f, -100.f)));
	humos.push_back(App_Juego::Humo(cx, cy, DLibH::Vector_2d(-100.f, 100.f)));
	humos.push_back(App_Juego::Humo(cx, cy, DLibH::Vector_2d(100.f, 100.f)));
}

void Controlador_juego::restaurar_estado_visual()
{
	if(!estado_dinamicas.colores_originales)
	{
		DLibV::Gestor_texturas::swap(App::Recursos_graficos::rt_celdas, App::Recursos_graficos::rt_celdas_bn);
		DLibV::Gestor_texturas::swap(App::Recursos_graficos::rt_sprites, App::Recursos_graficos::rt_sprites_bn);
	}
}

void Controlador_juego::finalizar_juego()
{
	estado=estados::normal;
	solicitar_cambio_estado(Director_estados::t_estados::the_end);
}

void Controlador_juego::show_title() {

	representador.reset_show_title();
	estado=estados::show_title;
}
