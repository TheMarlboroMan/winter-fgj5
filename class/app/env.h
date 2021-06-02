#pragma once

#include <string>

namespace App {

struct env {

	static std::string data_path;
	static std::string usr_path;
	static std::string make_data_path(const std::string& _path) {return data_path+_path;}
};

struct version {

	static const int major{1};
	static const int minor{1};
	static const int patch{0};
};

}//end App namespace
