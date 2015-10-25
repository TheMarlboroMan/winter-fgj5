#include "definiciones.h"
#include <stdexcept>


using namespace App_Definiciones;

App_Definiciones::direcciones App_Definiciones::obtener_direccion_contraria(App_Definiciones::direcciones s)
{
	switch(s)
	{
		case App_Definiciones::direcciones::arriba: return App_Definiciones::direcciones::abajo; break;
		case App_Definiciones::direcciones::abajo: return App_Definiciones::direcciones::arriba; break;
		case App_Definiciones::direcciones::derecha: return App_Definiciones::direcciones::izquierda; break;
		case App_Definiciones::direcciones::izquierda: return App_Definiciones::direcciones::derecha; break;
		default: return App_Definiciones::direcciones::nada; break;
	}
}

App_Definiciones::direcciones App_Definiciones::operator|(App_Definiciones::direcciones a, App_Definiciones::direcciones b)
{
	return static_cast<App_Definiciones::direcciones>(static_cast<int>(a) | static_cast<int>(b));
}

App_Definiciones::direcciones App_Definiciones::operator&(App_Definiciones::direcciones a, App_Definiciones::direcciones b)
{
	return static_cast<App_Definiciones::direcciones>(static_cast<int>(a) & static_cast<int>(b));
}

bool App_Definiciones::es_direccion_pura(App_Definiciones::direcciones dir)
{
	switch(dir)
	{
		case App_Definiciones::direcciones::arriba:
		case App_Definiciones::direcciones::abajo:
		case App_Definiciones::direcciones::derecha:
		case App_Definiciones::direcciones::izquierda:
			return true;
		break;
		case App_Definiciones::direcciones::nada:
		default:
			return false;
		break;
	}
}

App_Definiciones::direcciones App_Definiciones::convertir_en_direccion(int v)
{
	if(v < 0 && v > 15)
/*		(direcciones::arriba | 
		direcciones::derecha |
		direcciones::abajo |
		direcciones::izquierda))*/
	{
		throw std::runtime_error("Casting inválido de enter a App_Definiciones::direcciones");
	}

	return static_cast<App_Definiciones::direcciones>(v);
/*
	switch(v)
	{
		case 1: return direcciones::arriba; break;
		case 2: return direcciones::derecha; break;
		case 4: return direcciones::abajo; break;
		case 8: return direcciones::izquierda; break;
		default: return direcciones::nada; break;
	}
*/
}
