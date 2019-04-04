

#include "hh/locked_long.hpp"

#include <Windows.h>

namespace hh
{
	locked_long::locked_long(long defaultvalue)
		: m_value(defaultvalue)
	{
	}
	long locked_long::operator++()
	{
		return InterlockedIncrement(&m_value);
	}
	long locked_long::operator--()
	{
		return InterlockedDecrement(&m_value);
	}
}
