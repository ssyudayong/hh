

#pragma once

#include <string>

#pragma comment(lib, "Rpcrt4.lib")

namespace hh
{
	std::wstring a2w(const std::string & src);
	std::wstring a2w(const char * src);
	std::wstring a2w(const char * src, size_t size);
	std::wstring utf8tow(const std::string & src);
	std::wstring utf8tow(const char * src);
	std::wstring utf8tow(const char * src, size_t size);
	std::string w2a(const std::wstring& src);
	std::string w2a(const wchar_t * src);
	std::string w2a(const wchar_t * src, size_t size);
	std::string wtoutf8(const std::wstring& src);
	std::string wtoutf8(const wchar_t * src);
	std::string wtoutf8(const wchar_t * src, size_t size);
	std::string& lower(std::string& src);
	std::wstring& lower(std::wstring& src);
	std::string& upper(std::string& src);
	std::wstring& upper(std::wstring& src);
	void hex(char c, char * pc);
	void hex(char c, wchar_t * pc);
	std::string to_string(double value, const char * formatstr);
	std::wstring to_string(double value, const wchar_t * formatstr);
	bool string_to(const std::wstring & src, long long & value);
	bool string_to(const std::wstring & src, unsigned long long & value);
	bool string_to(const std::wstring & src, int & value);
	bool string_to(const std::wstring & src, unsigned long & value);
	bool string_to(const std::wstring & src, double & value);
	bool string_to(const std::wstring & src, unsigned short & value);
	bool is_digit(const std::wstring & value);
	bool is_digit(const std::string & value);
	size_t findcount(const std::string & str, char c);
	size_t findcount(const std::wstring & str, wchar_t c);
	size_t replace_all(std::wstring & src, const std::wstring & sub, const std::wstring & rs);
	size_t replace_all(std::string & src, const std::string & sub, const std::string & rs);
	std::wstring new_guid();
	void new_guid(std::wstring & value);
	void new_guid(std::string & value);
	#ifdef GUID_DEFINED
	void new_guid(GUID * value);
	#endif
	std::wstring string_format(const wchar_t * fmt, ...);
	std::wstring string_format(size_t bufsize, const wchar_t * fmt, ...);
	std::string string_format(const char * fmt, ...);
	std::string string_format(size_t bufsize, const char * fmt, ...);
	template<typename T>
	T* find(const T* src, size_t size, const T* fs, size_t fssize)
	{
		if (size < fssize) { return nullptr; }
		size_t len = size - fssize;
		T * pba = src;
		T * pbb = fs;
		for (size_t i = 0; i < len; i++)
		{
			size_t j = 0;
			for (j = 0; j < fssize; j++)
			{
				if (pba[j] != pbb[j]) { break; }
			}
			if (j == fssize) { return pba; }
			pba += (j + 1);
		}
		return nullptr;
	}
}
