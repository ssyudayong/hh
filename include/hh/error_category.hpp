

#pragma once

namespace hh
{
	class error_category
	{
	public:
		virtual const char * msg_c(int errorid, int languageid) const = 0;
		virtual const wchar_t * msg_w(int errorid, int languageid) const = 0;
		virtual const char * msg_c(int errorid) const = 0;
		virtual const wchar_t * msg_w(int errorid) const = 0;
	};
	const error_category & system_category();
}
