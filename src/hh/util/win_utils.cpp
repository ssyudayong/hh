

#include "hh/util/win_utils.hpp"

//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif 
#include <Windows.h>
//#include <powerbase.h>
#include <Shlwapi.h>

#include <mutex>
#include <memory>
#include <exception>

namespace hh::util
{

	struct win_utils::data
	{
		typedef NTSTATUS (NTAPI *sRtlGetVersion)(PRTL_OSVERSIONINFOW lpVersionInformation);
		typedef ULONG(NTAPI *sRtlNtStatusToDosError)(NTSTATUS Status);

		HMODULE ntdll_module;
		HMODULE powrprof_module;
		HMODULE user32_module;
		HMODULE kernel32_module;
		//
		sRtlGetVersion pRtlGetVersion;
		sRtlNtStatusToDosError pRtlNtStatusToDosError;
		//
		data();
		~data();
		static data& instance();
	};
	win_utils::data::data()
	{
		ntdll_module = GetModuleHandle(L"ntdll.dll");
		if (!ntdll_module) { throw std::exception(" GetModuleHandle ntdll.dll fail."); }
		pRtlGetVersion = (sRtlGetVersion)GetProcAddress(ntdll_module, "RtlGetVersion");
		pRtlNtStatusToDosError = (sRtlNtStatusToDosError)GetProcAddress(ntdll_module, "RtlNtStatusToDosError");
		if (pRtlNtStatusToDosError == NULL)
		{
			throw std::exception("GetProcAddress RtlNtStatusToDosError fail.");
		}
	}
	win_utils::data::~data()
	{
		
	}
	win_utils::data & win_utils::data::instance()
	{
		static std::unique_ptr<win_utils::data> _o;
		if (!_o)
		{
			static std::mutex _m;
			auto _lock = std::lock_guard(_m);
			if (!_o)
			{
				_o = std::make_unique<win_utils::data>();
			}
		}
		if (_o)
		{
			return _o.operator*();
		}
		throw std::exception("create win_utils instance fail.");
	}
	long win_utils::get_version(os_version_info_t & verinfo)
	{
		auto &dll = data::instance();
		ZeroMemory(&verinfo, sizeof(verinfo));
		verinfo.dwOSVersionInfoSize = sizeof(verinfo);
		return dll.pRtlNtStatusToDosError(dll.pRtlGetVersion((PRTL_OSVERSIONINFOW)&verinfo));
	}
	uint64_t win_utils::get_tickcount()
	{
		return ::GetTickCount64();
	}
}
