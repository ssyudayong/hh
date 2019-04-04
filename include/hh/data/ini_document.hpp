


#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

namespace hh::data
{
	class ini_document
	{
	public:
		enum : int
		{
			element_section,
			element_comment,
			element_keyvalue
		};
		struct element
		{
			std::wstring key;
			std::wstring value;
			std::vector<std::wstring> comment;
		};
		struct section
		{
			std::wstring name;
			std::vector<std::wstring> comment;
			std::vector<element> elements;
		};
	public:
		ini_document();
		virtual ~ini_document();
		int load_form_file(const std::string& filename);
		int load_from_file(const std::wstring& filename);
		int load_from_file(const std::filesystem::path& path);
		int load_from_buffer(const void * data, size_t size);
		int load_utf8(const char * data, size_t size);
		int load_ansi(const char * data, size_t size);
		int load_unicode(const wchar_t * data, size_t size);
	private:
		int read(const wchar_t * data, size_t size);
		void parse(const wchar_t * data, size_t size);
		void parse_comment(const std::wstring_view& data);
		void parse_section(const std::wstring_view& data);
		void parse_element(const std::wstring_view& key, const std::wstring_view& value);
		void parse_blankline();
	private:
		std::vector<std::wstring> m_header;
		std::vector<section>      m_sections;
		std::vector<std::wstring> m_footer;
		std::vector<std::wstring> m_temp_comment;
	};

}
