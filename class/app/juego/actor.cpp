#include "actor.h"

using namespace App_Juego;
using namespace App_Interfaces;

Actor::Actor()
	:caja(0.0, 0.0, 0, 0)
{
	
}

Actor::Actor(float x, float y, unsigned int w, unsigned int h)
	:caja(x, y, w, h)
{

}

void Actor::establecer_caja(float x, float y, unsigned int w, unsigned int h)
{
	caja.origen.x=x;
	caja.origen.y=y;
	caja.w=w;
	caja.h=h;
}
