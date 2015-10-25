#include "tabla_sprites.h"

Tabla_sprites::Tabla_sprites(const std::string& ruta)
{
	cargar(ruta);
}

Tabla_sprites::Tabla_sprites()
{

}

const Frame_sprites& Tabla_sprites::obtener(unsigned int indice) const
{
	return mapa.at(indice);
}

Frame_sprites Tabla_sprites::obtener(unsigned int indice)
{
	if(mapa.count(indice)) return mapa[indice];
	else return Frame_sprites();
}

void Tabla_sprites::cargar(const std::string& ruta)
{
	DLibH::Lector_txt L(ruta, '#');

	if(!L)	
	{
		LOG<<"ERROR: Para Tabla_sprites no se ha podido abrir el archivo "<<ruta<<std::endl;
	}
	else
	{
		std::string linea;
		const char separador='\t';
		
		while(true)
		{
			linea=L.leer_linea();
			if(!L) break;

			std::vector<std::string> valores=DLibH::Herramientas::explotar(linea, separador);
			if(valores.size()==7)
			{
				Frame_sprites f;
				unsigned int indice=std::atoi(valores[0].c_str());
				f.x=std::atoi(valores[1].c_str());
				f.y=std::atoi(valores[2].c_str());
				f.w=std::atoi(valores[3].c_str());
				f.h=std::atoi(valores[4].c_str());
				f.desp_x=std::atoi(valores[5].c_str());
				f.desp_y=std::atoi(valores[6].c_str());
				mapa[indice]=f;
			}
			else
			{
				LOG<<"ERROR: En tabla sprites, la línea "<<L.obtener_numero_linea()<<" no está bien formada. Ignorando"<<std::endl;
			}
		}
	}
}

