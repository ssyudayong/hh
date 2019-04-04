


#pragma once

/// link windows sdk static library
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

namespace hh::net
{
	struct address_family
	{
		typedef enum : int
		{
			unspecified = 0,
			ipv4        = 2,
			ipx         = 6,
			appletalk   = 16,
			netbios     = 17,
			ipv6        = 23,
			irda        = 26,
			bluetooth   = 32
		} value;
	};
	using address_family_t = address_family::value;
	struct socket_type
	{
		typedef enum : int
		{
			stream    = 1,
			datagrams = 2,
			raw       = 3,
			rdm       = 4,
			seqpacket = 5
		} value;
	};
	using socket_type_t = socket_type::value;
	struct protocol
	{
		typedef enum : int
		{
			icmp   = 1,
			igmp   = 2,
			rfcomm = 3,
			tcp    = 6,
			udp    = 17,
			icmpv6 = 58,
			rm     = 113
		} value;
	};
	using protocol_t = protocol::value;

	class environment
	{
	public:
		using socket_t       = size_t;
		using length_t       = unsigned long;
		using overlapped_ptr = void *;
		using sockaddr_ptr   = void *;
		using length_ptr     = int *;
	public:
		static environment& instance();
		static void release();
		int acceptex(
			socket_t       sListenSocket,
			socket_t       sAcceptSocket,
			void*        lpOutputBuffer,
			length_t        dwReceiveDataLength,
			length_t        dwLocalAddressLength,
			length_t        dwRemoteAddressLength,
			length_t*      lpdwBytesReceived,
			overlapped_ptr lpOverlapped
		);
		void get_acceptex_sockaddrs(
			void*    lpOutputBuffer,
			length_t    dwReceiveDataLength,
			length_t    dwLocalAddressLength,
			length_t    dwRemoteAddressLength,
			sockaddr_ptr*LocalSockaddr,
			length_ptr    LocalSockaddrLength,
			sockaddr_ptr*RemoteSockaddr,
			length_ptr    RemoteSockaddrLength
		);
		int connectex(
			socket_t s,
			const sockaddr_ptr name,
			int namelen,
			void* lpSendBuffer,
			length_t dwSendDataLength,
			length_t* lpdwBytesSent,
			overlapped_ptr lpOverlapped
		);
		int disconnectex(
			socket_t s,
			overlapped_ptr lpOverlapped,
			length_t  dwFlags,
			length_t  dwReserved = 0
		);
	private:
		environment();
		~environment();
		static environment* s_instance;
	private:
		struct data;
	};

	inline environment& env()
	{
		return environment::instance();
	}
}
