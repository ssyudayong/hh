

#include "hh/net/socket.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
/// Socket 2
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <mswsock.h>

namespace hh::net
{
	socket::socket()
		: m_handle((handle_t)INVALID_SOCKET)
	{
	}
	socket::socket(handle_t s)
		: socket()
	{
		m_handle = s;
	}
	socket::socket(address_family_t af, socket_type_t st, protocol_t p)
		: socket()
	{
		m_handle = WSASocket(af, st, p, NULL, 0, WSA_FLAG_OVERLAPPED);
	}
	socket::~socket()
	{
		if ((handle_t)(~0) != m_handle)
		{
			::closesocket(m_handle);
			m_handle = (handle_t)(~0);
		}
	}
	socket::handle_t socket::accept(socket_address & addr)
	{
		sockaddr_storage buffer;
		struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(&buffer);
		int ilen = sizeof(buffer);
		auto s = ::accept(m_handle, pSA, &ilen);
		if (s == (handle_t)(~0))
		{
			throw;
		}
		addr.parse(pSA, ilen);
		return s;
	}
	int socket::connect(const socket_address & addr)
	{
		return ::connect(m_handle, addr.data<const sockaddr>(), addr.size());
	}
	int socket::bind(const socket_address & addr)
	{
		return 0;
	}
	int socket::listen(int backlog)
	{
		return ::listen(m_handle, backlog);
	}
	int socket::shutdown(int how)
	{
		return ::shutdown(m_handle, how);
	}
	void socket::close()
	{
		if (m_handle != (handle_t)(~0))
		{
			::closesocket(m_handle);
			m_handle = (handle_t)(~0);
		}
	}
	int socket::ioctl(long cmd, ioctl_arg_ptr argp)
	{
		return ::ioctlsocket(m_handle, cmd, argp);
	}
	int socket::available()
	{
		ioctl_arg_t i = 0;
		ioctl(FIONREAD, &i);
		return i;
	}
	socket_address socket::address()
	{
		sockaddr_storage buffer;
		struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(&buffer);
		int ilen = sizeof(buffer);
		auto ir = ::getsockname(m_handle, pSA, &ilen);
		if (ir == 0)
		{
			return std::move(socket_address(pSA, ilen));
		}
		return socket_address();
	}
	socket_address socket::peer_address()
	{
		sockaddr_storage buffer;
		struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(&buffer);
		int ilen = sizeof(buffer);
		auto ir = ::getpeername(m_handle, pSA, &ilen);
		if (ir == 0)
		{
			return std::move(socket_address(pSA, ilen));
		}
		return socket_address();
	}
	int socket::set_option(int level, int option, const void * value, int length)
	{
		return ::setsockopt(m_handle, level, option, (const char *)value, length);
	}
	int socket::get_option(int level, int option, void * value, int & length)
	{
		return ::getsockopt(m_handle, level, option, (char *)value, &length);
	}
	void socket::set_no_delay(bool flag)
	{
		int value = flag ? 1 : 0;
		set_option(IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
	}
	bool socket::get_no_delay()
	{
		int value = 0;
		int len = sizeof(value);
		get_option(IPPROTO_TCP, TCP_NODELAY, &value, len);
		return value != 0;
	}
	void socket::set_keepalive(bool flag)
	{
		int value = flag ? 1 : 0;
		set_option(SOL_SOCKET, SO_KEEPALIVE, &value, sizeof(value));
	}
	bool socket::get_keepalive()
	{
		int value = 0;
		int len = sizeof(value);
		get_option(SOL_SOCKET, SO_KEEPALIVE, &value, len);
		return value != 0;
	}
	void socket::set_reuse_address(bool flag)
	{
		int value = flag ? 1 : 0;
		set_option(SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	}
	bool socket::get_reuse_address()
	{
		int value = 0;
		int len = sizeof(value);
		get_option(SOL_SOCKET, SO_REUSEADDR, &value, len);
		return value != 0;
	}
	int socket::error()
	{
		int i = 0;
		int ilen = sizeof(i);
		get_option(SOL_SOCKET, SO_ERROR, &i, ilen);
		return i;
	}
	socket::handle_t socket::handle() const
	{
		return m_handle;
	}
}
