


#pragma once

#include <memory>

namespace hh::net
{
	class ssl_params : public std::enable_shared_from_this<ssl_params>
	{
	public:
		using shared_ptr = std::shared_ptr<ssl_params>;
		using unique_ptr = std::unique_ptr<ssl_params>;
	};
}
