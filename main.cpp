#include <libDan2.h>
#include <defDanSDL.h>
#include "class/framework/derivada/kernel.h"
#include "bootstrap/bootstrap_aplicacion.h"
#include "class/app/env.h"

#ifdef WINCOMPIL

	#include <libloaderapi.h>
	#include <fileapi.h>

#else
	#include <unistd.h>
	#include <sys/stat.h>

#endif


//Declaración del log del motor en espacio global.
DLibH::Log_base LOG;
std::string App::env::data_path="";
std::string App::env::usr_path="";

void ready_system();
void dump_file(const std::string&, const std::string&);

int main(int argc, char ** argv)
{
	ready_system();

	if(DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK))
	{
		//Inicializar control de logs.
		std::string info_log_path=App::env::usr_path+"logs/info.log";

		LOG.inicializar(info_log_path.c_str());
		LOG.activar();

		std::string dlib_log_path=App::env::usr_path+"logs/log_motor.log";
		DLibH::Log_motor::arrancar(dlib_log_path.c_str());

		//Inicializar control de argumentos.
		Herramientas_proyecto::Controlador_argumentos CARG(argc, argv);

		try
		{
			Kernel_app kernel(CARG);
			kernel.inicializar();

			//Función en el espacio de nombres "App", definida en "include_controladores.h"
			using namespace App;
			loop_aplicacion(kernel);
		}
		catch(std::runtime_error &e)
		{
			std::cout<<e.what()<<std::endl;
		}
	}

	DLibH::Log_motor::finalizar();
	DLibH::Herramientas_SDL::apagar_SDL();

	return 0;
}

void dump_file(
	const std::string& _in,
	const std::string& _out
) {

	std::string res, lin;
	std::ifstream f{_in};
	std::ofstream out{_out};

	while(true) {
		std::getline(f, lin);
		if(f.eof()) {
			break;
		}
		out<<lin<<std::endl;
	}
}

#ifdef WINCOMPIL

void ready_system() {

	std::array<char, 1024> buff;
	int bytes=GetModuleFileNameA(nullptr, buff.data(), 1024);

	std::string executable_path=std::string{std::begin(buff), std::begin(buff)+bytes};

	auto last_slash=executable_path.find_last_of("\\");
	std::string executable_dir=executable_path.substr(0, last_slash)+"\\";

	App::env::data_path=executable_dir;
	App::env::usr_path=executable_dir+"user\\";

	std::string logs_path=App::env::usr_path+"\\logs\\";
	CreateDirectoryA(logs_path.c_str(), nullptr);
	CreateDirectoryA(App::env::usr_path.c_str(), nullptr);

	dump_file(
		App::env::make_data_path("data/config/configuracion.dat"),
		App::env::usr_path+"/configuracion.dat"
	);
}

#else

void ready_system() {

	std::string executable_path, executable_dir;
	std::array<char, 1024> buff;

	int bytes=readlink("/proc/self/exe", buff.data(), 1024);
	if(-1==bytes) {

		std::cerr<<"could not locate proc/self/exe, error "<<errno<<std::endl;
		throw std::runtime_error("could not locate proc/self/exe");
	}

	executable_path=std::string{std::begin(buff), std::begin(buff)+bytes};
	auto last_slash=executable_path.find_last_of("/");
	executable_dir=executable_path.substr(0, last_slash)+"/";

	App::env::data_path=executable_dir+"/";
	App::env::usr_path=std::string{getenv("HOME")}+"/.winter-fgj5/";

#ifdef AS_APPIMAGE
	#pragma message ("Building as AppImage!!")
	App::env::data_path=executable_dir+"/../share/";
#else
	#pragma message ("Building as regular app!!")
#endif

	struct stat st={0};
	if(stat(App::env::usr_path.c_str(), &st) == -1) {

		mkdir(App::env::usr_path.c_str(), 0700);

		std::string logs_path=App::env::usr_path+"logs";
		mkdir(logs_path.c_str(), 0700);

		dump_file(
			App::env::make_data_path("data/config/configuracion.dat"),
			App::env::usr_path+"/configuracion.dat"
		);
	}
}
#endif
