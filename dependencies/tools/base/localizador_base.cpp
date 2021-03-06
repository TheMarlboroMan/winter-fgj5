#include "localizador_base.h"

#ifdef WINCOMPIL
/* Localización del parche mingw32... Esto debería estar en otro lado, supongo. */
#include <herramientas/herramientas/herramientas.h>
#endif

using namespace Herramientas_proyecto;

Localizador_base::Localizador_base(unsigned short int p_idioma)
{
	this->idioma=p_idioma;
}

Localizador_base::~Localizador_base()
{
	this->limpiar_cadenas();
}

void Localizador_base::limpiar_cadenas()
{
	this->cadenas.clear();
}

void Localizador_base::cambiar_idioma(unsigned short int p_idioma)
{
	this->idioma=p_idioma;
	this->inicializar();
}

void Localizador_base::insertar_cadena(unsigned int p_indice, t_cadena const& p_cadena)
{
	this->cadenas.insert(std::pair<unsigned int, t_cadena>(p_indice, p_cadena));
}

t_cadena Localizador_base::generar_nombre_archivo(t_cadena const& p_original)
{
#ifdef WINCOMPIL
	using namespace parche_mingw;
#else
	using namespace std;
#endif
	
	t_cadena nombre_archivo(p_original);

	nombre_archivo.append(".");
	nombre_archivo.append(to_string(this->idioma));
	nombre_archivo.append(".dat");

	return nombre_archivo;
}

void Localizador_base::inicializar()
{
	t_lista_nombres_archivo lista=this->obtener_lista_archivos();
	t_lista_nombres_archivo::iterator ini=lista.begin(), fin=lista.end();

	//Limpiar mapa e ir asignando.
	this->limpiar_cadenas();

	for(;ini<fin; ini++)
	{
		this->procesar_fichero(*ini);
	}

}

void Localizador_base::procesar_fichero(t_cadena const& nombre_archivo)
{
	const std::string ruta=generar_nombre_archivo(nombre_archivo);

	t_stream_in archivo(ruta.c_str(), std::ios::in | std::ios::binary);
	if(!archivo)
	{
		throw std::runtime_error("Imposible abrir fichero de localización "+ruta);
	}
	else
	{
		size_t indice=0; //, pos;
		size_t indice_aux=0;
		t_cadena_stream cadena, cadena_def;
		bool leyendo=false;

		//Leemos de línea en línea, 1024 como mucho. Por cada línea leida procesamos.
		while(true)
		{
			std::getline(archivo, cadena);
			if(archivo.eof()) 
			{
				break;
			}


			//La cadena esta vacia?	Si no estamos leyendo saltar al siguiente con "continue".
			if(!cadena.size() && !leyendo) 
			{
				continue;
			}
			else if(cadena[0]=='#') 
			{
				continue;	//Es un comentario????
			}

			//Delimitador de inicio encontrado?
		
			if(delimitador_inicio_en_cadena(cadena, indice_aux))
			{
				leyendo=true; //Marcar leyendo como true.
				indice=indice_aux; //Obtener índice.
				cadena=cadena.substr(3+digitos_en_entero(indice)); //Cortar delimitador inicio. + 3 por el < y el $>
			}

			//Delimitador de fin encontrado?
			if(this->delimitador_fin_en_cadena(cadena))
			{
				leyendo=false; //Marcar leyendo como false.
				cadena=cadena.substr(0, cadena.size()-3); //Cortar resto cadena. -3 es por <#>
				cadena_def.append(cadena);

				//Insertar en mapa.

				this->insertar_cadena(indice, cadena_def);
				cadena_def.clear();
				cadena.clear();
			}		

			//Estamos leyendo?
			if(leyendo)
			{
				cadena.append("\n"); //Insertar nueva línea.
				cadena_def.append(cadena); //Insertar en cadena actual.	
				cadena.clear();	//Limpiar buffer.
			}
		}	
	
		archivo.close();
	}

//	delete [] buffer;
}

/*
Busca <n#> al principio de la cadena donde n# es un número positivo. Si lo
encuentra devuelve n#. Si no devolverá -1.
*/
bool Localizador_base::delimitador_inicio_en_cadena(std::string const& p_cadena, size_t &indice)
{
	size_t pos=p_cadena.find("$>", 1);
	std::string cad_indice("");

	if(pos!=std::string::npos)
	{
		cad_indice.assign(p_cadena.substr(1, pos-1));
		indice=std::atoi(cad_indice.c_str());
		return true;
	}
	else 
	{
		return false;
	}
}

bool Localizador_base::delimitador_fin_en_cadena(std::string const& p_cadena)
{
	bool resultado=false;
	size_t pos;
	pos=p_cadena.find("<#>");

	if(pos!=std::string::npos)
	{
		resultado=true;
	}

	return resultado;
}

t_cadena const& Localizador_base::obtener(unsigned int p_indice) const
{
	if(!this->cadenas.size())
	{
		return this->cadena_no_cargado();
	}
	else
	{
		const auto it=this->cadenas.find(p_indice);

		if(it==this->cadenas.end())
		{
			return this->cadena_no_encontrado();
		}
		else
		{
			return it->second;
		}
	}
}
