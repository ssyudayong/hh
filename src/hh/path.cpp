

#include "hh/path.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 
#include <Windows.h>

#include <Shlwapi.h>

#include <string>
#include <memory>
#include <cassert>
#include <mutex>
#include <map>
#include <vector>

namespace hh
{
	std::wstring path::current_path()
	{
		wchar_t wbuf[8192] = { 0 };
		::GetCurrentDirectory(8192, wbuf);
		::PathAddBackslash(wbuf);
		wchar_t wd[8192] = { 0 };
		::PathCanonicalize(wd, wbuf);
		return std::wstring(wd);
	}
	const std::wstring & path::execute_fullname()
	{
		static std::wstring data;
		if (data.empty())
		{
			static std::mutex m;
			std::lock_guard<std::mutex> lock(m);
			if (data.empty())
			{
				wchar_t wc[8192];
				auto dw = ::GetModuleFileName(NULL, wc, 8192);
				UNREFERENCED_PARAMETER(dw);
				assert(dw <= 8192);
				wchar_t wd[8192] = { 0 };
				::PathCanonicalize(wd, wc);
				data = std::wstring(wd);
			}
		}
		return data;
	}
	const std::wstring & path::execute_path()
	{
		static std::wstring data;
		if (data.empty())
		{
			static std::mutex m;
			std::lock_guard<std::mutex> lock(m);

			if (data.empty()) 
			{ 
				wchar_t wc[8192];
				auto dw = ::GetModuleFileName(NULL, wc, 8192);
				UNREFERENCED_PARAMETER(dw);
				assert(dw <= 8192);
				auto b = ::PathRemoveFileSpec(wc);
				UNREFERENCED_PARAMETER(b);
				assert(b == TRUE);
				::PathAddBackslash(wc);
				wchar_t wd[8192];
				::PathCanonicalize(wd, wc);
				data = std::wstring(wd);
			}
		}
		return data;
	}
	std::wstring path::remove_file_externsion(const std::wstring & filename)
	{
		wchar_t wt[8192] = { 0 };
		wcscpy_s(wt, 8192, filename.c_str());
		PathRemoveExtension(wt);
		return std::wstring(wt);
	}
	std::string path::remove_file_externsion(const std::string & filename)
	{
		char wt[8192] = { 0 };
		strcpy_s(wt, 8192, filename.c_str());
		PathRemoveExtensionA(wt);
		return std::string(wt);
	}
	std::wstring path::find_file_externsion(const std::wstring & filename)
	{
		auto pext = ::PathFindExtension(filename.c_str());
		return std::wstring(pext);
	}
	std::string path::find_file_externsion(const std::string & filename)
	{
		auto pext = ::PathFindExtensionA(filename.c_str());
		return std::string(pext);
	}
	bool path::file_exist(const std::wstring & filename)
	{
		auto B = ::PathFileExists(filename.c_str());
		return B == TRUE ? true : false;
	}
	bool path::file_exist(const std::string & filename)
	{
		auto B = ::PathFileExistsA(filename.c_str());
		return B == TRUE ? true : false;
	}
	int path::file_version(const std::wstring & filename, fixed_file_info & version)
	{
		if (!file_exist(filename))
		{
			return ERROR_FILE_NOT_FOUND;
		}
		DWORD dwhandle = 0;
		DWORD dwsize = 0;
		dwsize = GetFileVersionInfoSize(filename.c_str(), &dwhandle);
		if (dwsize == 0)
		{
			auto err = GetLastError();
			return err;
		}
		auto pdata = std::make_unique<unsigned char[]>(dwsize);
		auto B = GetFileVersionInfo(filename.c_str(), 0, dwsize, pdata.get());
		if (!B)
		{
			auto err = GetLastError();
			return err;
		}
		VS_FIXEDFILEINFO * pinfo = nullptr;
		UINT dwsubsize = 0;
		B = VerQueryValue(pdata.get(), L"\\", (LPVOID*)&pinfo, &dwsubsize);
		if (!B)
		{
			auto err = GetLastError();
			return err;
		}
		if (dwsubsize == sizeof(fixed_file_info))
		{
			version = *(fixed_file_info*)pinfo;
			return 0;
		}
		return ERROR_INVALID_DATA;
	}
}
