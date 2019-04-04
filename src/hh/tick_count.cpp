

#include "hh/tick_count.hpp"

#include <Windows.h>

namespace hh
{
	tick_count::tick_count()
	{
		m_begin = ::GetTickCount64();
	}
	tick_count::~tick_count()
	{
	}
	unsigned long long tick_count::now()
	{
		return GetTickCount64();
	}
	unsigned long long tick_count::interval() const
	{
		return GetTickCount64() - m_begin;
	}
	void tick_count::reset()
	{
		m_begin = GetTickCount64();
	}
}
