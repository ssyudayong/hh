

#include "hh/net/tcp_server_params.hpp"

namespace hh::net
{
	tcp_server_params::tcp_server_params()
	{
	}
	tcp_server_params::~tcp_server_params()
	{
	}
	void tcp_server_params::port(port_t value)
	{
	}
	tcp_server_params::port_t tcp_server_params::port() const
	{
		return port_t();
	}
	bool tcp_server_params::have_ssl() const
	{
		return m_ssl_params ? true : false;
	}
	void tcp_server_params::set_ssl(ssl_params::unique_ptr && sslparams)
	{
		m_ssl_params = std::move(sslparams);
	}
}
