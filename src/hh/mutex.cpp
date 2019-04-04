


#include "hh/mutex.hpp"

#include <Windows.h>

namespace hh
{
	mutex::mutex()
	{
		InitializeCriticalSection((LPCRITICAL_SECTION)data);
	}
	mutex::~mutex()
	{
		DeleteCriticalSection((LPCRITICAL_SECTION)data);
	}
	void mutex::lock()
	{
		EnterCriticalSection((LPCRITICAL_SECTION)data);
	}
	void mutex::unlock()
	{
		LeaveCriticalSection((LPCRITICAL_SECTION)data);
	}
	bool mutex::try_lock()
	{
		return TryEnterCriticalSection((LPCRITICAL_SECTION)data) ? true : false;
	}
	lock_guard::lock_guard(mutex & m)
		: m_mutex(m)
	{
		m_mutex.lock();
	}
	lock_guard::~lock_guard()
	{
		m_mutex.unlock();
	}
}
