

#pragma once

#include "hh/net/ssl_params.hpp"


namespace hh::net
{
	class tcp_server_params
	{
	public:
		using port_t = unsigned short;
		
	public:
		tcp_server_params();
		virtual ~tcp_server_params();
	public:
		void port(port_t value);
		port_t port() const;
		bool have_ssl() const;
		void set_ssl(ssl_params::unique_ptr&& sslparams);
	private:
		port_t m_port;							///< 服务端口
		size_t m_max_thread_count;				///< 最大线程数量
		size_t m_max_acceptor_count;			///< 最大同时投递数量
		size_t m_max_dispatch_queue_count;		///< 最大调度队列大小
		//size_t m_max_client_count;				///< 最大客户链接数量
		size_t m_max_session_count;				///< 最大同时连接数
		ssl_params::unique_ptr m_ssl_params;	///< SSL参数
	};

	
}