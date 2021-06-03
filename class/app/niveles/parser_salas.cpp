#include "parser_salas.h"
#include <class/lector_txt.h>
//#include "../lectores/info_obstaculos_genericos.h"

using namespace App_Niveles;

const std::string Parser_salas::TIPO_ESTRUCTURA="[ESTRUCTURA]";
const std::string Parser_salas::TIPO_FIN_ESTRUCTURA="[/ESTRUCTURA]";
const std::string Parser_salas::TIPO_INFO="[INFO]";
const std::string Parser_salas::TIPO_META="[META]";
const std::string Parser_salas::TIPO_FIN_META="[/META]";
const std::string Parser_salas::TIPO_REJILLA="[REJILLA]";
const std::string Parser_salas::TIPO_CELDAS="[CELDAS]";
const std::string Parser_salas::TIPO_CAMARA="[CAMARA]";
const std::string Parser_salas::TIPO_LOGICA="[LOGICA]";
const std::string Parser_salas::TIPO_OBJETOS="[OBJETOS]";
		

Parser_salas::Parser_salas()
	:d_celdas(destino_celdas::nada), estado(t_estados::nada),
	sala(0,0)
{

}

void Parser_salas::parsear_fichero(const std::string& ruta)
{
	Herramientas_proyecto::Lector_txt L(ruta, '#');

	if(!L)
	{
		LOG<<"ERROR: Imposible localizar nivel en fichero "<<ruta<<std::endl;
		throw std::runtime_error("Imposible localizar nivel en fichero");
	}
	else
	{	
		std::string linea;

		while(true)
		{
			linea=L.leer_linea();
			if(!L) break;

			if(interpretar_estado(linea))
			{
				switch(estado)
				{
					case t_estados::nada: 
					case t_estados::estructura: 
					case t_estados::info: 
					case t_estados::logica: 
					case t_estados::fin: 
					break;
					case t_estados::meta: interpretar_linea_como_meta(linea); break;
					case t_estados::rejilla: interpretar_linea_como_rejilla(linea); break;
					case t_estados::celdas: interpretar_linea_como_celdas(linea); break;
					case t_estados::objetos: interpretar_linea_como_objeto(linea); break;
				}
			}
		}


		//TODO: Al finalizar, implantar los objetos en la sala...
	}
}

bool Parser_salas::interpretar_estado(const std::string& linea)
{
	if(linea==TIPO_ESTRUCTURA) estado=t_estados::estructura;
	else if(linea==TIPO_INFO) estado=t_estados::info;
	else if(linea==TIPO_META) estado=t_estados::meta;
	else if(linea==TIPO_REJILLA) estado=t_estados::rejilla;
	else if(linea==TIPO_CELDAS) 
	{
		//Cada vez que encuentre una, aumentamos el destino.
		switch(d_celdas)
		{
			case destino_celdas::nada: 	d_celdas=destino_celdas::logica; break;
			case destino_celdas::logica: 	d_celdas=destino_celdas::decoracion; break;
			case destino_celdas::decoracion: throw std::runtime_error("Demasiadas secciones de celda en sala."); break;
		}

		estado=t_estados::celdas;
	}	
	else if(linea==TIPO_LOGICA) estado=t_estados::logica;
	else if(linea==TIPO_OBJETOS)  estado=t_estados::objetos;
	else if(linea==TIPO_FIN_ESTRUCTURA) 
	{
		estado=t_estados::fin;
		return true; //Hay que ejecutar una acción al cerrar la estructura.
	}
	else return true;

	return false;
}

void Parser_salas::interpretar_linea_como_rejilla(const std::string& linea)
{
	std::vector<std::string> valores=Herramientas::explotar(linea, ',');

	if(valores.size() < 2)
	{
		throw std::runtime_error("ERROR: Al interpretar línea como rejilla hay menos de 2 parámetros");
	}

	const auto w=toi(valores[0]), h=toi(valores[1]);
	sala.modificar_dimensiones(w, h);
}

void Parser_salas::interpretar_linea_como_celdas(const std::string& linea)
{
	std::vector<std::string> valores=Herramientas::explotar(linea, ' ');

	for(const auto& v : valores)
	{
		const auto& partes=Herramientas::explotar(v, ',');

		if(partes.size() != 3)
		{
			throw std::runtime_error("ERROR: Al interpretar línea "+v+" como celda hay debe haber 3 parámetros.");
		}

		const int x=toi(partes[0]), y=toi(partes[1]), tipo=toi(partes[2]);

		switch(d_celdas)
		{
			case destino_celdas::nada: break;
			case destino_celdas::logica:
			{
				App_Niveles::Celda::tipo_celda t=App_Niveles::Celda::tipo_celda::solida;
		
				switch(tipo)
				{
					case 1: t=App_Niveles::Celda::tipo_celda::solida; break;
					case 2: t=App_Niveles::Celda::tipo_celda::plataforma; break;
					case 3: t=App_Niveles::Celda::tipo_celda::letal; break;
					case 4: t=App_Niveles::Celda::tipo_celda::bloqueo_enemigo; break;
				}

				sala.insertar_celda(x, y, t);
			}
			break;
			case destino_celdas::decoracion: 
				sala.insertar_celda_decorativa(x, y, toi(partes[2]));
			break;
		}
	}
}

void Parser_salas::interpretar_linea_como_objeto(const std::string& linea)
{
	std::vector<std::string> valores=Herramientas::explotar(linea, ',');
	const auto tipo=toi(valores[0]);

	switch(tipo)
	{
		case 1: interpretar_como_rompible(valores); break;
		case 2: interpretar_como_bonus(valores); break;
		case 3: interpretar_como_enemigo_patrulla(valores); break;
		case 4: interpretar_como_enemigo_disparador(valores); break;
		case 5: interpretar_como_enemigo_canon(valores); break;
		case 10: interpretar_como_plataforma(valores); break;
		case 100: interpretar_como_entrada(valores); break;
		case 101: interpretar_como_salida(valores); break;
		default: throw std::runtime_error("ERROR: Tipo desconocido importando como objeto."); break;
	}
}

void Parser_salas::interpretar_como_entrada(const std::vector<std::string>& valores)
{
	if(valores.size() != 3)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como entrada.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]);
	sala.asignar_entrada(App_Juego::Entrada(x, y));
}

void Parser_salas::interpretar_como_salida(const std::vector<std::string>& valores)
{
	if(valores.size() != 5)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como salida.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]), indice=toi(valores[3]);
	bool bloqueable=toi(valores[4]);
	sala.insertar_objeto(App_Juego::Salida(x, y, indice, bloqueable));
}

void Parser_salas::interpretar_como_rompible(const std::vector<std::string>& valores)
{
	if(valores.size() != 3)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como rompible.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]);
	sala.insertar_objeto(App_Juego::Rompible(x, y));
}

void Parser_salas::interpretar_como_bonus(const std::vector<std::string>& valores)
{
	if(valores.size() != 4)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como bonus.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]), tipo=toi(valores[3]);

	App_Juego::Bonus::tipos t=App_Juego::Bonus::tipos::pequeno;

	switch(tipo)
	{
		case 1: t=App_Juego::Bonus::tipos::pequeno; break;
		case 2: t=App_Juego::Bonus::tipos::mediano; break;
		case 3: t=App_Juego::Bonus::tipos::grande; break;
		case 4: t=App_Juego::Bonus::tipos::disparos; break;
	}

	sala.insertar_objeto(App_Juego::Bonus(x, y, t));
}

void Parser_salas::interpretar_como_enemigo_patrulla(const std::vector<std::string>& valores)
{
	if(valores.size() != 5)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como enemigo patrulla.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]), vector_x=toi(valores[3]), salud=toi(valores[4]);
	sala.insertar_objeto(App_Juego::Enemigo_patrulla(x, y, vector_x, salud));
}

void Parser_salas::interpretar_como_enemigo_disparador(const std::vector<std::string>& valores)
{
	if(valores.size() != 5)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como enemigo disparador.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]), salud=toi(valores[4]);
	float tiempo=toi(valores[3]) / 1000.f; 
	sala.insertar_objeto(App_Juego::Enemigo_disparador(x, y, tiempo, salud));
}

void Parser_salas::interpretar_como_enemigo_canon(const std::vector<std::string>& valores)
{
	if(valores.size() != 6)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como enemigo cañón.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]);
	float tiempo=toi(valores[3]) / 1000.f, angulo=toi(valores[4]), velocidad=toi(valores[5]);
	sala.insertar_objeto(App_Juego::Enemigo_canon(x, y, tiempo, angulo, velocidad));
}

void Parser_salas::interpretar_como_plataforma(const std::vector<std::string>& valores)
{
	if(valores.size() != 6)
	{
		throw std::runtime_error("ERROR: Parámetros incorrectos al interpretar línea como plataforma.");
	}

	const auto x=toi(valores[1]), y=toi(valores[2]);
	float tiempo_on=toi(valores[3]) / 1000.f, tiempo_off=toi(valores[4]) / 1000.f;
	bool on=toi(valores[5]);
	sala.insertar_objeto(App_Juego::Plataforma(x, y, tiempo_on, tiempo_off, on));
}

void Parser_salas::interpretar_linea_como_meta(
	const std::string& _line
) {

	if(_line==TIPO_FIN_META) {

		estado=t_estados::nada;
		return;
	}

	std::cout<<"meta line" <<_line<<std::endl;

	std::vector<std::string> pieces=Herramientas::explotar(_line, ':', 2);
	if(2!=pieces.size()) {

		throw std::runtime_error("ERROR: invalid meta line");
	}

	if(pieces[0]=="title") {

		sala.set_name_index(toi(pieces[1]));
	}
	else {

		throw std::runtime_error("ERROR: invalid meta property");
	}

}
