

#pragma once

#include "hh/error_category.hpp"

namespace hh
{
	class error_code
	{
	public:
		error_code() noexcept;
		error_code(int errorid, const error_category& ecat = system_category()) noexcept;
		virtual ~error_code();
		void clear();
		void reset(int errorid, const error_category& ecat = system_category()) noexcept;
		void reset_os_last_error();
		explicit operator bool() const;
		int value() const;
		const error_category& category() const;
		const char * msg_c() const;
		int m_value;
		const error_category* m_category_ptr;
	};
}
