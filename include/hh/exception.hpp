

#pragma once

#include "hh/error_code.hpp"

#include <exception>
#include <memory>

namespace hh
{
	class exception
	{
	public:
		exception(const error_code& ec, const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
		exception(int errorid, const error_category& ec, const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
		virtual ~exception();
	private:
		error_code m_ec;
		const char * m_funcname;
		const char * m_filename;
		size_t m_line;
	};
}

#define HH_SYS_EXP(x) hh::exception(x,hh::system_category(),__FUNCSIG__)
