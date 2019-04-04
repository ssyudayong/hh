

#include "hh/tribool.hpp"

namespace hh
{
	tribool::tribool(value_t v)
		: m_value(v)
	{
	}
	void tribool::reset(value_t v)
	{
		m_value = v;
	}
	tribool::value_t tribool::value() const
	{
		return m_value;
	}
	void tribool::set(value_t v)
	{
		m_value = v;
	}
	tribool::operator bool() const
	{
		return m_value == true_value;
	}
}
