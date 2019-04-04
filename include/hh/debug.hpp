

#pragma once

#include <iostream>
#include <mutex>

namespace hh
{
#ifdef _DEBUG
	inline void debug_message(const char * msg, const char * funcname, const char * filename = __FILE__, size_t line = __LINE__)
	{
		std::mutex _m;
		auto _lock = std::lock_guard(_m);
		std::cout << std::endl;
		std::cout << "[file] " << filename << std::endl;
		std::cout << "[line] " << line << std::endl;
		std::cout << "[func] " << funcname << std::endl;
		std::cout << "[ msg] " << msg << std::endl;
	}
#endif
}

#ifdef _DEBUG
	#define DEBUG_MSG(x) debug_message(x,__FUNCSIG__);
#else 
	#define DEBUG_MSG(x)
#endif
