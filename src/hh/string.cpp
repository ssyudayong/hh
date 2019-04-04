

#include "hh/string.hpp"

#define NOMINMAX
#include <Windows.h>
#include <rpc.h>

#include <memory>
#include <cassert>
#include <cwctype>
#include <cctype>
#include <algorithm>

namespace hh
{
	std::wstring a2w(const std::string & src)
	{
		auto err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src.c_str(), -1, NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err);
		err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src.c_str(), -1, pw.get(), err);
		assert(err != 0);
		return std::wstring(pw.get());
	}
	std::wstring a2w(const char * src)
	{
		auto err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src, -1, NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err);
		err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src, -1, pw.get(), err);
		assert(err != 0);
		return std::wstring(pw.get());
	}
	std::wstring a2w(const char * src, size_t size)
	{
		auto err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src, static_cast<int>(size), NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err+1);
		err = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)src, static_cast<int>(size), pw.get(), err);
		assert(err != 0);
		pw.get()[err] = 0;
		return std::wstring(pw.get());
	}
	std::wstring utf8tow(const std::string & src)
	{
		auto err = ::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err);
		err = ::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, (LPWSTR)pw.get(), err);
		assert(err != 0);
		return  std::wstring(pw.get());
	}
	std::wstring utf8tow(const char * src)
	{
		auto err = ::MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err);
		err = ::MultiByteToWideChar(CP_UTF8, 0, src, -1, (LPWSTR)pw.get(), err);
		assert(err != 0);
		return  std::wstring(pw.get());
	}
	std::wstring utf8tow(const char * src, size_t size)
	{
		auto err = ::MultiByteToWideChar(CP_UTF8, 0, src, static_cast<int>(size), NULL, 0);
		assert(err != 0);
		auto pw = std::make_unique<wchar_t[]>(err + 1);
		err = ::MultiByteToWideChar(CP_UTF8, 0, src, static_cast<int>(size), (LPWSTR)pw.get(), err);
		assert(err != 0);
		pw.get()[err] = 0;
		return  std::wstring(pw.get());
	}
	std::string w2a(const std::wstring & src)
	{
		auto err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src.c_str(), -1, NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err);
		err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src.c_str(), -1, pc.get(), err, NULL, NULL);
		assert(err != 0);
		return std::string(pc.get());
	}
	std::string w2a(const wchar_t * src)
	{
		auto err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, -1, NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err);
		err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, -1, pc.get(), err, NULL, NULL);
		assert(err != 0);
		return std::string(pc.get());
	}
	std::string w2a(const wchar_t * src, size_t size)
	{
		auto err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, static_cast<int>(size), NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err+1);
		err = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, static_cast<int>(size), pc.get(), err, NULL, NULL);
		assert(err != 0);
		pc.get()[err] = 0;
		return std::string(pc.get());
	}
	std::string wtoutf8(const std::wstring & src)
	{
		auto err = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err);
		err = ::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, pc.get(), err, NULL, NULL);
		assert(err != 0);
		return std::string(pc.get());
	}
	std::string wtoutf8(const wchar_t * src)
	{
		auto err = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err);
		err = ::WideCharToMultiByte(CP_UTF8, 0, src, -1, pc.get(), err, NULL, NULL);
		assert(err != 0);
		return std::string(pc.get());
	}
	std::string wtoutf8(const wchar_t * src, size_t size)
	{
		auto err = WideCharToMultiByte(CP_UTF8, 0, src, static_cast<int>(size), NULL, 0, NULL, NULL);
		assert(err != 0);
		auto pc = std::make_unique<char[]>(err+1);
		err = ::WideCharToMultiByte(CP_UTF8, 0, src, static_cast<int>(size), pc.get(), err, NULL, NULL);
		assert(err != 0);
		pc.get()[err] = 0;
		return std::string(pc.get());
	}
	std::string & lower(std::string & src)
	{
		for (auto&c : src)
		{
			if ((c > 0x40) && (c < 0x5B))
			{
				c = c + ('a' - 'A');
			}
		}
		return src;
	}
	std::wstring & lower(std::wstring & src)
	{
		for (auto&c : src)
		{
			if ((c > 0x40) && (c < 0x5B))
			{
				c = c + ('a' - 'A');
			}
		}
		return src;
	}
	std::string & upper(std::string & src)
	{
		for (auto&c : src)
		{
			if ((c >= 'A') && (c <= 'Z'))
			{
				c = c - ('a' - 'A');
			}
		}
		return src;
	}
	std::wstring & upper(std::wstring & src)
	{
		for (auto&c : src)
		{
			if ((c >= 'A') && (c <= 'Z'))
			{
				c = c - ('a' - 'A');
			}
		}
		return src;
	}
	void hex(char c, char * pc)
	{
		static char hex[] = "0123456789ABCDEF";
		auto a = (BYTE)c >> 4;
		auto b = (BYTE)c & 0x0F;
		pc[0] = hex[a];
		pc[1] = hex[b];
	}
	void hex(char c, wchar_t * pc)
	{
		static wchar_t hex[] = L"0123456789ABCDEF";
		auto a = (BYTE)c >> 4;
		auto b = (BYTE)c & 0x0F;
		pc[0] = hex[a];
		pc[1] = hex[b];
	}
	std::string to_string(double value, const char * formatstr)
	{
		char tmp[96] = { 0 };
		sprintf_s(tmp, 96, formatstr, value);
		return std::string(tmp);
	}
	std::wstring to_string(double value, const wchar_t * formatstr)
	{
		wchar_t tmp[96] = { 0 };
		swprintf_s(tmp, 96, formatstr, value);
		return std::wstring(tmp);
	}
	bool string_to(const std::wstring & src, long long & value)
	{
		try
		{
			auto i = std::stoll(src);
			value = i;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool string_to(const std::wstring & src, unsigned long long & value)
	{
		try
		{
			auto i = std::stoull(src);
			value = i;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool string_to(const std::wstring & src, int & value)
	{
		try
		{
			auto i = std::stoi(src);
			value = i;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool string_to(const std::wstring & src, unsigned long & value)
	{
		try
		{
			auto sz = std::stoul(src);
			//auto max = std::numeric_limits<unsigned long>::max();
			//auto min = std::numeric_limits<unsigned long>::min();
			//if ((sz < min) || (sz > max)) { return false; }
			value = sz;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool string_to(const std::wstring & src, double & value)
	{
		try
		{
			auto d = std::stod(src);
			value = d;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool string_to(const std::wstring & src, unsigned short & value)
	{
		try
		{
			auto i = std::stoi(src);
			auto max = std::numeric_limits<unsigned short>::max();
			auto min = std::numeric_limits<unsigned short>::min();
			if ((i > max) || (i < min)) { return false; }
			value = static_cast<unsigned short>(i);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	bool is_digit(const std::wstring & value)
	{
		return !value.empty() && std::find_if(value.begin(),
			value.end(), [](wchar_t c) { return !std::iswdigit(c); }) == value.end();
	}
	bool is_digit(const std::string & value)
	{
		return !value.empty() && std::find_if(value.begin(),
			value.end(), [](char c) { return !std::isdigit(c); }) == value.end();
	}
	size_t findcount(const std::string & str, char c)
	{
		std::size_t count = 0;
		std::size_t size = str.size(); if (size == 0) { return count; }
		for (auto &v : str) { if (v == c) { count++; } }
		return count;
	}
	size_t findcount(const std::wstring & str, wchar_t c)
	{
		std::size_t count = 0;
		std::size_t size = str.size(); if (size == 0) { return count; }
		for (auto &v : str) { if (v == c) { count++; } }
		return count;
	}
	size_t replace_all(std::wstring & src, const std::wstring & sub, const std::wstring & rs)
	{
		size_t pos = 0;
		size_t subsize = sub.size();
		size_t rssize = rs.size();
		size_t count = 0;
		pos = src.find(sub, pos);
		while (pos != std::wstring::npos)
		{
			count++;
			src.replace(pos, subsize, rs);
			pos += rssize;
			pos = src.find(sub, pos);
		}
		return count;
	}
	size_t replace_all(std::string & src, const std::string & sub, const std::string & rs)
	{
		size_t pos = 0;
		size_t subsize = sub.size();
		size_t rssize = rs.size();
		size_t count = 0;
		pos = src.find(sub, pos);
		while (pos != std::wstring::npos)
		{
			count++;
			src.replace(pos, subsize, rs);
			pos += rssize;
			pos = src.find(sub, pos);
		}
		return count;
	}
	std::wstring new_guid()
	{
		UUID uid;
		auto r = ::UuidCreate(&uid);
		if (r != RPC_S_OK)
		{
			throw;
		}
		wchar_t buf[128] = { 0 };

		swprintf_s(buf, 128, L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			uid.Data1, uid.Data2, uid.Data3
			, uid.Data4[0], uid.Data4[1], uid.Data4[2], uid.Data4[3]
			, uid.Data4[4], uid.Data4[5], uid.Data4[6], uid.Data4[7]);

		return std::wstring(buf);
	}
	void new_guid(std::wstring & value)
	{
		UUID uid;
		auto r = UuidCreate(&uid);
		if (r != RPC_S_OK)
		{
			throw;
		}
		wchar_t buf[128] = { 0 };

		swprintf_s(buf, 128, L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			uid.Data1, uid.Data2, uid.Data3
			, uid.Data4[0], uid.Data4[1], uid.Data4[2], uid.Data4[3]
			, uid.Data4[4], uid.Data4[5], uid.Data4[6], uid.Data4[7]);

		value = buf;
	}
	void new_guid(std::string & value)
	{
		UUID uid;
		auto r = UuidCreate(&uid);
		if (r != RPC_S_OK)
		{
			throw;
		}
		//RPC_CSTR ws;
		//r = UuidToStringA(&uid, &ws);
		//if (r != RPC_S_OK)
		//{
		//	throw;
		//}
		//value = (char *)ws;
		//RpcStringFreeA(&ws);
		char buf[128] = { 0 };

		sprintf_s(buf, 128, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			uid.Data1, uid.Data2, uid.Data3
			, uid.Data4[0], uid.Data4[1], uid.Data4[2], uid.Data4[3]
			, uid.Data4[4], uid.Data4[5], uid.Data4[6], uid.Data4[7]);

		value = buf;
	}
#ifdef GUID_DEFINED
	void new_guid(GUID * value)
	{
		auto r = UuidCreate(value);
		if (r != RPC_S_OK)
		{
			throw;
		}
	}
#endif
	std::wstring string_format(const wchar_t * fmt, ...)
	{
		static const size_t bufsize = 1024;
		auto uc = std::make_unique<wchar_t[]>(bufsize);
		memset(uc.get(), 0, bufsize);
		va_list marker;
		va_start(marker, fmt);     /* Initialize variable arguments. */
		auto r = _vsnwprintf_s(uc.get(), bufsize, _TRUNCATE, fmt, marker);
		UNREFERENCED_PARAMETER(r);
		va_end(marker);              /* Reset variable argument list. */
		return std::wstring(uc.get());
	}
	std::wstring string_format(size_t bufsize, const wchar_t * fmt, ...)
	{
		auto uc = std::make_unique<wchar_t[]>(bufsize);
		memset(uc.get(), 0, bufsize);
		va_list marker;
		va_start(marker, fmt);     /* Initialize variable arguments. */
		auto r = _vsnwprintf_s(uc.get(), bufsize, _TRUNCATE, fmt, marker);
		UNREFERENCED_PARAMETER(r);
		va_end(marker);              /* Reset variable argument list. */
		return std::wstring(uc.get());
	}
	std::string string_format(const char * fmt, ...)
	{
		static const size_t st = 1024;
		auto uc = std::make_unique<char[]>(st);
		memset(uc.get(), 0, st);
		va_list marker;
		va_start(marker, fmt);     /* Initialize variable arguments. */
		auto r = vsnprintf_s(uc.get(), st, _TRUNCATE, fmt, marker);
		UNREFERENCED_PARAMETER(r);
		va_end(marker);              /* Reset variable argument list. */
		return std::string(uc.get());
	}
	std::string string_format(size_t bufsize, const char * fmt, ...)
	{
		int st = static_cast<int>(bufsize);
		auto uc = std::make_unique<char[]>(st);
		memset(uc.get(), 0, st);
		va_list marker;
		va_start(marker, fmt);     /* Initialize variable arguments. */
		auto r = vsnprintf_s(uc.get(), st, _TRUNCATE, fmt, marker);
		UNREFERENCED_PARAMETER(r);
		va_end(marker);              /* Reset variable argument list. */
		return std::string(uc.get());
	}
}
