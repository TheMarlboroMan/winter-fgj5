#ifndef DEFINICIONES_ANIMACIONES_H
#define DEFINICIONES_ANIMACIONES_H

namespace App_Definiciones
{

enum animaciones
{
	celdas,
	sprites
};

enum animaciones_sprites
{
	jugador_quieto=1,
	jugador_correr=2,
	jugador_salto=3,
	jugador_disparar=4,
	jugador_morir=5,
	disparo=6,
	disparo_enemigo=7,
	enemigo_patrulla=8,
	bonus_peq=9,
	bonus_med=10,
	bonus_gra=11,
	bonus_disp=12,
	plataforma=13,
	rompible=14,
  	puerta_abierta=15,
  	puerta_cerrada=16,
	enemigo_disparo_quieto=17,
	enemigo_disparo_dispara=18,
	enemigo_disparo_post=19,
	humo=20
};

enum animaciones_particulas
{

};
}

#endif
