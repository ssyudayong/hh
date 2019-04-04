

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
		port_t m_port;							///< ����˿�
		size_t m_max_thread_count;				///< ����߳�����
		size_t m_max_acceptor_count;			///< ���ͬʱͶ������
		size_t m_max_dispatch_queue_count;		///< �����ȶ��д�С
		//size_t m_max_client_count;				///< ���ͻ���������
		size_t m_max_session_count;				///< ���ͬʱ������
		ssl_params::unique_ptr m_ssl_params;	///< SSL����
	};

	
}