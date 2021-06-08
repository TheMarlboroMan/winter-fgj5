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
		rt_credits=10,
		rt_title_cycle_1_1=20,
		rt_title_cycle_1_2=21,
		rt_title_cycle_2_1=22,
		rt_title_cycle_2_2=23,
		rt_title_cycle_2_3=24,
		rt_title_cycle_3=25,
		rt_title_hub_1=26,
		rt_title_hub_2=27,
		rt_title_hub_3=28,
		rt_title_hub_4=29
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
		rs_perder_vida=6,
		rs_wind=7
	};
};

}

#endif
