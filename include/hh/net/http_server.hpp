

#pragma once

#include "hh/net/http_server_params.hpp"
#include "hh/net/tcp_server.hpp"

namespace hh::net
{
	class http_server : public tcp_server
	{
	public:
		http_server(http_server_params& params);
		virtual ~http_server();
	};
}
