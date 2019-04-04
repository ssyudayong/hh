

#pragma once

#include "hh/net/tcp_server_params.hpp"
#include "hh/net/socket_address.hpp"

namespace hh::net
{
	class tcp_server
	{
	public:
		class whitelist;
		class blacklist;
	public:
		tcp_server(tcp_server_params& params);
		virtual ~tcp_server();
	private:
		tcp_server_params& m_params;
	};

	class tcp_server::whitelist
	{
	public:
		virtual bool is_enable(const socket_address& addr) = 0;
	};

	class tcp_server::blacklist
	{
	public:
		virtual bool is_disable(const socket_address& addr) = 0;
	};
}
