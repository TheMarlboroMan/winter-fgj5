#ifndef RECURSOS_PROYECTO_H
#define RECURSOS_PROYECTO_H

namespace App
{

class Recursos_graficos
{
	private:

	Recursos_graficos();

	public:

	enum superficies{
		rs_fuente_peq=1,
		rs_fuente_gra=2
	};

	enum texturas{
		rt_celdas=1,
		rt_celdas_bn=2,
		rt_sprites=3,
		rt_sprites_bn=4,
		rt_hud=5,
		rt_fondo=6,
		rt_intro=7,
		rt_game_over=8,
		rt_the_end=9,
//		rt_title_hub_round_0=10,
//		rt_title_hub_round_1=11,
//		rt_title_hub_round_2=12,
//s		rt_title_hub_round_3=13

	};
};

class Recursos_audio
{
	private:

	Recursos_audio();

	public:

	enum musicas{
		rm_ballade=1
	};

	enum sonidos{
		rs_destruir=1,
		rs_disparo=2,
		rs_item=3,
		rs_nivel_finalizado=4,
		rs_salto=5,
		rs_perder_vida=6
	};
};

}

#endif
