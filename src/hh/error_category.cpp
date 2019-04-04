

#include "hh/error_category.hpp"

#include <memory>

namespace hh
{
	namespace implementation
	{
		class system_category : public hh::error_category
		{
		public:
			virtual const char * msg_c(int errorid, int languageid) const;
			virtual const wchar_t * msg_w(int errorid, int languageid) const;
			virtual const char * msg_c(int errorid) const;
			virtual const wchar_t * msg_w(int errorid) const;
		};
		const char * system_category::msg_c(int errorid, int languageid) const
		{
			return "unknown error id.";
		}
		const wchar_t * system_category::msg_w(int errorid, int languageid) const
		{
			return L"unknown error id.";
		}
		const char * system_category::msg_c(int errorid) const
		{
			return "unknown error id.";
		}
		const wchar_t * system_category::msg_w(int errorid) const
		{
			return L"unknown error id.";
		}
		system_category system_category_instance;
	}
	const error_category & system_category()
	{
		return implementation::system_category_instance;
	}
}
