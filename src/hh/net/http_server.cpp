

#include "hh/net/http_server.hpp"

namespace hh::net
{
	http_server::http_server(http_server_params & params)
		: tcp_server(params)
	{
	}
	http_server::~http_server()
	{
	}
}
