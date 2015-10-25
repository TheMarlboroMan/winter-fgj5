#ifndef PARSER_SALAS_H
#define PARSER_SALAS_H

#include <string>
#include <vector>
#include "../definiciones/definiciones.h"
#include "../niveles/sala.h"
//#include "../juego/factorias/factoria_objetos_juego.h"

namespace App_Niveles
{

/**
* El parser de salas. 
*/

class Parser_salas
{
	//////////////////////
	//Interface pública

	public:

								Parser_salas();
	void 							parsear_fichero(const std::string& ruta);
	App_Niveles::Sala&					acc_sala() {return sala;}
	
	private:

	bool							interpretar_estado(const std::string& linea);
	void 							interpretar_linea_como_rejilla(const std::string& linea);
	void							interpretar_linea_como_celdas(const std::string& linea);
	void							interpretar_linea_como_objeto(const std::string& linea);
	int							toi(const std::string& s) {return std::atoi(s.c_str());};
	void							interpretar_como_entrada(const std::vector<std::string>&);
	void							interpretar_como_salida(const std::vector<std::string>&);
	void							interpretar_como_rompible(const std::vector<std::string>&);
	void							interpretar_como_bonus(const std::vector<std::string>&);
	void							interpretar_como_enemigo_patrulla(const std::vector<std::string>&);
	void							interpretar_como_enemigo_disparador(const std::vector<std::string>&);
	void							interpretar_como_enemigo_canon(const std::vector<std::string>&);
	void							interpretar_como_plataforma(const std::vector<std::string>&);


	enum class 						t_estados {nada, estructura, info, rejilla, celdas, logica, objetos, fin};
	
	enum class destino_celdas {nada, logica, decoracion};

	destino_celdas						d_celdas;
	t_estados 						estado;
	static const std::string 				TIPO_ESTRUCTURA;
	static const std::string 				TIPO_FIN_ESTRUCTURA;
	static const std::string 				TIPO_INFO;
	static const std::string 				TIPO_REJILLA;
	static const std::string 				TIPO_CELDAS;
	static const std::string 				TIPO_CAMARA;
	static const std::string 				TIPO_LOGICA;
	static const std::string 				TIPO_OBJETOS;

	App_Niveles::Sala 					sala;
};

}

#endif
