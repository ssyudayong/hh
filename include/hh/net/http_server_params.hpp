


#pragma once

#include "hh/net/tcp_server_params.hpp"

namespace hh::net
{
	class http_server_params : public tcp_server_params
	{
	public:
		http_server_params();
		virtual ~http_server_params();
	};
}
