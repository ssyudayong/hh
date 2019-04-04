

#include "hh/datetime.hpp"
#include "hh/string.hpp"

#include <Windows.h>

namespace hh
{
	filetime_t filetime_t::to_local()
	{
		filetime_t ft;
		::FileTimeToLocalFileTime((LPFILETIME)this, (LPFILETIME)&ft);
		return ft;
	}
	filetime_t filetime_t::to_system()
	{
		filetime_t ft;
		::FileTimeToLocalFileTime((LPFILETIME)this, (LPFILETIME)&ft);
		return ft;
	}
	int filetime_t::get_filetime(file_handle_t file, filetime_t * lpcreateiontime, filetime_t * lplastaccesstime, filetime_t * lplastwritetime)
	{
		auto B = ::GetFileTime((HANDLE)file, (LPFILETIME)lpcreateiontime, (LPFILETIME)lplastaccesstime, (LPFILETIME)lplastwritetime);
		return B ? 0 : GetLastError();
	}
	//------------------------------------------------------------------------------------
	datetime::datetime()
		: m_data({0})
		, m_mode(system_mode)
	{
	}
	datetime::datetime(const filetime_t& ft, mode_t m)
		: m_mode(m)
	{
		::FileTimeToSystemTime((LPFILETIME)&ft, (LPSYSTEMTIME)&m_data);
	}
	datetime::~datetime()
	{
	}
	datetime datetime::system_now()
	{
		datetime dt;
		::GetSystemTime((LPSYSTEMTIME)&dt.m_data);
		dt.m_mode = system_mode;
		return dt;
	}
	datetime datetime::local_now()
	{
		datetime dt;
		::GetLocalTime((LPSYSTEMTIME)&dt.m_data);
		dt.m_mode = local_mode;
		return dt;
	}
	filetime_t datetime::to_filetime()
	{
		filetime_t ft;
		::SystemTimeToFileTime((LPSYSTEMTIME)&m_data, (LPFILETIME)&ft);
		return ft;
	}

	std::wstring datetime::to_iso8601() const
	{
		std::wstring send;
		if (m_mode == system_mode)
		{
			TIME_ZONE_INFORMATION tzi;
			GetTimeZoneInformation(&tzi);
			auto h = tzi.Bias / 60;
			auto m = tzi.Bias % 60;
			auto c = h >= 0 ? L"-" : L"+";
			h = abs(h);
			send = hh::string_format(L"%s%02d:%02d", c, h, m);
		}
		else
		{
			send = L"Z";
		}
		return hh::string_format(L"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s",
			m_data.wYear, m_data.wMonth, m_data.wDay,
			m_data.wHour, m_data.wMinute, m_data.wSecond, m_data.wMilliseconds,
			send.c_str());
	}
	
}
