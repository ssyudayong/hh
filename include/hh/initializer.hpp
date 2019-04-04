

#pragma once

#include "hh/error_code.hpp"

namespace hh
{
	class initializer
	{
	public:
		enum item_t
		{
			none         = 0,
			have_network = 1,
			have_all     = have_network
		};
	public:
		initializer(hh::error_code& ec, item_t items = none);
		virtual ~initializer();
		int last_error() const;
	};
}
