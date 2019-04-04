

#include "hh/exception.hpp"

namespace hh
{
	exception::exception(const error_code& ec, const char * funcname, const char * filename, size_t line)
		: m_funcname(funcname)
		, m_filename(filename)
		, m_line(line)
		, m_ec(ec)
	{
	}
	exception::exception(int errorid, const error_category & ec, const char * funcname, const char * filename, size_t line)
		: m_funcname(funcname)
		, m_filename(filename)
		, m_line(line)
		, m_ec(errorid,ec)
	{
	}
	exception::~exception()
	{
	}
}
