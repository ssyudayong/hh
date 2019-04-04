

#pragma once

#include <string>
#include <cstdint>

namespace hh::util
{
	class win_utils
	{
	public:
		using ushort_t = unsigned short;
		using ulong_t  = unsigned long;
		using uchar_t  = unsigned char;
		//
		using os_version_info_t = struct 
		{
			ulong_t  dwOSVersionInfoSize;
			ulong_t  dwMajorVersion;
			ulong_t  dwMinorVersion;
			ulong_t  dwBuildNumber;
			ulong_t  dwPlatformId;
			wchar_t  szCSDVersion[128];
			ushort_t wServicePackMajor;
			ushort_t wServicePackMinor;
			ushort_t wSuiteMask;
			uchar_t  wProductType;
			uchar_t  wReserved;
		};
	public:
		static long get_version(os_version_info_t& verinfo);
		static uint64_t get_tickcount();
	private:
		struct data;
	};
}
