


#pragma once

#include "hh/net/environment.hpp"

namespace hh::net
{
	class socket_address
	{
	public:
		enum
		{
			ipv4_length = 16,
			ipv6_length = 28
		};
		using port_t = unsigned short;
	public:
		socket_address();
		socket_address(address_family_t af);
		socket_address(void * data, size_t size);
		int parse(void * data, size_t size);
		template<typename T>
		T* data();
		template<typename T>
		T* const data() const;
		size_t size() const;
		bool is_ipv4() const;
		bool is_ipv6() const;
		bool empty() const;
		address_family_t af() const;
		port_t port() const;
		void port(port_t value);
		explicit operator bool() const;
		void clear();
		void init_ipv4();
		void init_ipv6();
		static int inet_stouc4(const char * str, unsigned char * puc);
		static int inet_stouc4(const char * str, size_t size, unsigned char * puc);
		static int inet_stouc4(const wchar_t * str, unsigned char * puc);
		static int inet_stouc4(const wchar_t * str, size_t size, unsigned char * puc);
	private:
		unsigned char m_data[ipv6_length];
		size_t m_size;
	};
	template<typename T>
	inline T * socket_address::data()
	{
		return (T*)(m_data);
	}
	template<typename T>
	inline T * const socket_address::data() const
	{
		return (T*)(m_data);
	}
}
