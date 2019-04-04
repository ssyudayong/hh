

#include "hh/net/socket_address.hpp"

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
	socket_address::socket_address()
		: m_size(0)
	{
		ZeroMemory(m_data, sizeof(m_data));
	}
	socket_address::socket_address(address_family_t af)
	{
		if (af == address_family::ipv4)
		{
			init_ipv4();
		}
		else if (af == address_family::ipv6)
		{
			init_ipv6();
		}
		else
		{

		}
	}
	socket_address::socket_address(void * data, size_t size)
		: socket_address()
	{
		if ((size == ipv4_length) || (size == ipv6_length))
		{
			memcpy_s(m_data, ipv6_length, data, size);
			m_size = size;
		}
	}
	int socket_address::parse(void * data, size_t size)
	{
		return 0;
	}
	size_t socket_address::size() const
	{
		return m_size;
	}
	bool socket_address::is_ipv4() const
	{
		return m_size == ipv4_length;
	}
	bool socket_address::is_ipv6() const
	{
		return m_size == ipv6_length;
	}
	bool socket_address::empty() const
	{
		return m_size == 0;
	}
	address_family_t socket_address::af() const
	{
		sockaddr_in * psi = (sockaddr_in *)m_data;
		return (address_family_t)psi->sin_family;
	}
	socket_address::port_t socket_address::port() const
	{
		sockaddr_in * psi = (sockaddr_in *)m_data;
		return psi->sin_port;
	}
	void socket_address::port(port_t value)
	{
		sockaddr_in * psi = (sockaddr_in *)m_data;
		psi->sin_port = value;
	}
	socket_address::operator bool() const
	{
		return (m_size == ipv4_length) || (m_size == ipv6_length);
	}
	void socket_address::clear()
	{
		memset(m_data, 0, sizeof(m_data));
		m_size = 0;
	}
	void socket_address::init_ipv4()
	{
		memset(m_data, 0, sizeof(m_data));
		m_size = ipv4_length;
	}
	void socket_address::init_ipv6()
	{
		memset(m_data, 0, sizeof(m_data));
		m_size = ipv6_length;
	}
	/// 将字符串转换成四个字节。
	/// 参考libuv的inet.c中uv_inet_pton函数。
	/// 格式位xxx.xxx.xxx.xxx
	int socket_address::inet_stouc4(const char * str, unsigned char * puc)
	{
		static auto snum = "0123456789";
		unsigned char temp[4] = { 0 };
		auto saw_digit = false;
		auto octets = 0;
		auto p = temp;
		while (*str != NULL)
		{
			auto pch = strchr(snum, *str);
			if (pch != NULL)
			{
				auto pi = *p * 10 + (pch - snum);
				if ((saw_digit && (*p == 0)) || (pi > 255))
				{
					return ERROR_INVALID_DATA;
				}
				*p = static_cast<unsigned char>(pi);
				if (!saw_digit) { saw_digit = true; }
			}
			else if ((*str == '.') && saw_digit)
			{
				//if (!saw_digit) { return ERROR_INVALID_DATA; }
				octets++;
				if (octets == 4) { return ERROR_INVALID_DATA; }
				p++;
				saw_digit = false;
			}
			else
			{
				return ERROR_INVALID_DATA;
			}
			str++;
		}
		if ((octets != 3)|| (!saw_digit)) { return ERROR_INVALID_DATA; }
		if (puc)
		{
			memcpy_s(puc, 4, temp, 4);
		}
		return 0;
	}
	int socket_address::inet_stouc4(const char * str, size_t size, unsigned char * puc)
	{
		static auto snum = "0123456789";
		unsigned char temp[4] = { 0 };
		auto saw_digit = false;
		auto octets = 0;
		auto p = temp;
		while (size > 0)
		{
			auto pch = strchr(snum, *str);
			if (pch != NULL)
			{
				auto pi = *p * 10 + (pch - snum);
				if ((saw_digit && (*p == 0)) || (pi > 255))
				{
					return ERROR_INVALID_DATA;
				}
				*p = static_cast<unsigned char>(pi);
				if (!saw_digit) { saw_digit = true; }
			}
			else if ((*str == '.') && saw_digit)
			{
				//if (!saw_digit) { return ERROR_INVALID_DATA; }
				octets++;
				if (octets == 4) { return ERROR_INVALID_DATA; }
				p++;
				saw_digit = false;
			}
			else
			{
				return ERROR_INVALID_DATA;
			}
			str++;
			size--;
		}
		if ((octets != 3) || (!saw_digit)) { return ERROR_INVALID_DATA; }
		if (puc)
		{
			memcpy_s(puc, 4, temp, 4);
		}
		return 0;
	}
	int socket_address::inet_stouc4(const wchar_t * str, unsigned char * puc)
	{
		static auto snum = L"0123456789";
		unsigned char temp[4] = { 0 };
		auto saw_digit = false;
		auto octets = 0;
		auto p = temp;
		while (*str != NULL)
		{
			auto pch = wcschr(snum, *str);
			if (pch != NULL)
			{
				auto pi = *p * 10 + (pch - snum);
				if ((saw_digit && (*p == 0)) || (pi > 255))
				{
					return ERROR_INVALID_DATA;
				}
				*p = static_cast<unsigned char>(pi);
				if (!saw_digit) { saw_digit = true; }
			}
			else if ((*str == '.') && saw_digit)
			{
				//if (!saw_digit) { return ERROR_INVALID_DATA; }
				octets++;
				if (octets == 4) { return ERROR_INVALID_DATA; }
				p++;
				saw_digit = false;
			}
			else
			{
				return ERROR_INVALID_DATA;
			}
			str++;
		}
		if ((octets != 3) || (!saw_digit)) { return ERROR_INVALID_DATA; }
		if (puc)
		{
			memcpy_s(puc, 4, temp, 4);
		}
		return 0;
	}
	int socket_address::inet_stouc4(const wchar_t * str, size_t size, unsigned char * puc)
	{
		static auto snum = L"0123456789";
		unsigned char temp[4] = { 0 };
		auto saw_digit = false;
		auto octets = 0;
		auto p = temp;
		while (size > 0)
		{
			auto pch = wcschr(snum, *str);
			if (pch != NULL)
			{
				auto pi = *p * 10 + (pch - snum);
				if ((saw_digit && (*p == 0)) || (pi > 255))
				{
					return ERROR_INVALID_DATA;
				}
				*p = static_cast<unsigned char>(pi);
				if (!saw_digit) { saw_digit = true; }
			}
			else if ((*str == '.') && saw_digit)
			{
				//if (!saw_digit) { return ERROR_INVALID_DATA; }
				octets++;
				if (octets == 4) { return ERROR_INVALID_DATA; }
				p++;
				saw_digit = false;
			}
			else
			{
				return ERROR_INVALID_DATA;
			}
			str++;
			size--;
		}
		if ((octets != 3) || (!saw_digit)) { return ERROR_INVALID_DATA; }
		if (puc)
		{
			memcpy_s(puc, 4, temp, 4);
		}
		return 0;
	}
}
