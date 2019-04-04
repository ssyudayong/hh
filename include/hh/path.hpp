

#pragma once

#include <string>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Mincore.lib")

namespace hh
{
	class path
	{
	public:
		using ulong = unsigned long;
		using fixed_file_info = struct 
		{
			ulong dwSignature;
			ulong dwStrucVersion;
			ulong dwFileVersionMS;
			ulong dwFileVersionLS;
			ulong dwProductVersionMS;
			ulong dwProductVersionLS;
			ulong dwFileFlagsMask;
			ulong dwFileFlags;
			ulong dwFileOS;
			ulong dwFileType;
			ulong dwFileSubtype;
			ulong dwFileDateMS;
			ulong dwFileDateLS;
		};
	public:
		/// current directory.(have '\' char)
		static std::wstring current_path();
		/// process file full name.
		static const std::wstring& execute_fullname();
		/// directory for process file.(have '\' char)
		static const std::wstring& execute_path();
		static std::wstring remove_file_externsion(const std::wstring & filename);
		static std::string remove_file_externsion(const std::string & filename);
		static std::wstring find_file_externsion(const std::wstring & filename);
		static std::string find_file_externsion(const std::string & filename);
		static bool file_exist(const std::wstring & filename);
		static bool file_exist(const std::string & filename);
		static int  file_version(const std::wstring & filename, fixed_file_info & version);
	};
}
