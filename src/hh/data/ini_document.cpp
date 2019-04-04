///
///
/// @see https://en.wikipedia.org/wiki/INI_file
///

#include "hh/data/ini_document.hpp"

#include <Windows.h>

namespace hh::data
{
	ini_document::ini_document()
	{
	}
	ini_document::~ini_document()
	{
	}
	int ini_document::load_form_file(const std::string & filename)
	{
		auto path = std::filesystem::path(filename);
		return load_from_file(path);
	}
	int ini_document::load_from_file(const std::wstring & filename)
	{
		auto path = std::filesystem::path(filename);
		return load_from_file(path);
	}
	int ini_document::load_from_file(const std::filesystem::path & path)
	{
		if (!std::filesystem::exists(path))
		{
			return 2;	// ERROR_FILE_NOT_FOUND
		}
		auto filesize = std::filesystem::file_size(path);
		if (0 == filesize)
		{
			return 232;	// ERROR_NO_DATA
		}
		auto buffer = std::make_unique<char[]>(filesize);
		if (!buffer)
		{
			return 82;	// ERROR_CANNOT_MAKE
		}
		std::ifstream f;
		f.open(path, std::ios::in | std::ios::binary);
		if (!f.is_open())
		{
			return 110;	// ERROR_OPEN_FAILED
		}
		if (!f.read(buffer.get(), filesize))
		{
			return 30;	// ERROR_READ_FAULT
		}
		f.close();
		return load_from_buffer(buffer.get(), filesize);
	}
	int ini_document::load_from_buffer(const void * data, size_t size)
	{
		if ((size >= 3) && (memcmp(data, "\xEF\xBB\xBF", 3) == 0))
		{
			const char * pchar = (const char *)data;
			pchar += 3;
			size -= 3;
			return load_utf8(pchar, size);
		}
		return load_ansi((const char *)data, size);
	}
	int ini_document::load_utf8(const char * data, size_t size)
	{
		return 0;
	}
	int ini_document::load_ansi(const char * data, size_t size)
	{
		auto ir = ::MultiByteToWideChar(CP_ACP, MB_COMPOSITE, data, size, nullptr, 0);
		if (ir == 0)
		{
			return GetLastError();
		}
		DWORD bufsize = ir + 1;
		auto buf = std::make_unique<wchar_t[]>(bufsize);
		ir = ::MultiByteToWideChar(CP_ACP, MB_COMPOSITE, data, size, buf.get(), bufsize);
		if (ir == 0)
		{
			return GetLastError();
		}
		buf.get()[bufsize - 1] = 0;
		return load_unicode(buf.get(), bufsize);
	}
	int ini_document::load_unicode(const wchar_t * data, size_t size)
	{
		return 0;
	}
	int ini_document::read(const wchar_t * data, size_t size)
	{
		if (size == 0)
		{
			return 0;
		}
		auto pend = data + size;
		auto pcur = data;
		size_t len = 0;
		while (pcur < pend)
		{
			if ((*pcur == '\r') && (len < size - 1) && (pcur[1]=='\n'))
			{
				parse(data, len);
				size -= (len + 2);
				data += (len + 2);
			}
			if (*pcur == '\n')
			{
				parse(data, len);
				size -= (len + 1);
				data += (len + 1);
			}
			len++;
			if (len == size)
			{
				parse(data, len);
				return 0;
			}
			return read(data, size);
		}
		return 0;
	}
	void ini_document::parse(const wchar_t * data, size_t size)
	{
		if (size == 0) { return; }
		if (*data == ';')
		{
			parse_comment(std::wstring_view(++data, size-1));
		}
		if (*data == '[')
		{
			if (size < 3) { return; }
			for (size_t i = 2; i < size; i++)
			{
				if (data[i] == ']')
				{
					parse_section(std::wstring_view(++data, i - 1));
				}
			}
		}
		if (*data == '=')
		{
			return;
		}
		for (size_t i = 1; i < size; i++)
		{
			if (data[i] == '=')
			{
				parse_element(std::wstring_view(data, i), std::wstring(data + i + 1, size - i - 1));
			}
		}
		// invalid
	}
	void ini_document::parse_comment(const std::wstring_view& data)
	{
		m_temp_comment.push_back(std::move(std::wstring(data)));
	}
	void ini_document::parse_section(const std::wstring_view& data)
	{
	}
	void ini_document::parse_element(const std::wstring_view& key, const std::wstring_view& value)
	{
	}
	void ini_document::parse_blankline()
	{
	}
}
