

#include "hh/error_code.hpp"

#include <Windows.h>

namespace hh
{
	error_code::error_code() noexcept
		: m_value(::GetLastError())
		, m_category_ptr(&system_category())
	{
	}
	error_code::error_code(int errorid, const error_category & ecat) noexcept
		: m_value(errorid)
		, m_category_ptr(&ecat)
	{
	}
	error_code::~error_code()
	{
	}
	void error_code::clear()
	{
		m_value = 0;
		m_category_ptr = &system_category();
	}
	void error_code::reset(int errorid, const error_category & ecat) noexcept
	{
		m_value = errorid;
		m_category_ptr = &ecat;
	}
	void error_code::reset_os_last_error()
	{
		m_value = GetLastError();
		m_category_ptr = &system_category();
	}
	error_code::operator bool() const
	{
		return value() != 0;
	}
	int error_code::value() const
	{
		return m_value;
	}
	const error_category& error_code::category() const
	{
		return *m_category_ptr;
	}
	const char * error_code::msg_c() const
	{
		return m_category_ptr->msg_c(value());
	}
}
