

#include "hh/net/environment.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
/// Socket 2
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <mswsock.h>

#include <mutex>

namespace hh::net
{
	environment* environment::s_instance = nullptr;
	struct environment::data
	{
		static WSADATA					  wsadata;
		static LPFN_ACCEPTEX             fn_accept_ex;
		static LPFN_CONNECTEX            fn_connect_ex;
		static LPFN_DISCONNECTEX         fn_disconnect_ex;
		static LPFN_GETACCEPTEXSOCKADDRS fn_get_acceptex_sock_addrs;
	};
	WSADATA                   environment::data::wsadata = { 0 };
	LPFN_ACCEPTEX             environment::data::fn_accept_ex = nullptr;
	LPFN_CONNECTEX            environment::data::fn_connect_ex = nullptr;
	LPFN_DISCONNECTEX         environment::data::fn_disconnect_ex = nullptr;
	LPFN_GETACCEPTEXSOCKADDRS environment::data::fn_get_acceptex_sock_addrs = nullptr;
	environment & environment::instance()
	{
		if (nullptr == s_instance)
		{
			std::mutex _m;
			auto _lock = std::lock_guard(_m);
			if (nullptr == s_instance)
			{
				s_instance = new environment();
			}
		}
		return *s_instance;
	}
	void environment::release()
	{
		if (nullptr != s_instance)
		{
			std::mutex _m;
			auto _lock = std::lock_guard(_m);
			if (nullptr != s_instance)
			{
				delete s_instance;
				s_instance = nullptr;
			}
		}
	}
	int environment::acceptex(socket_t sListenSocket, socket_t sAcceptSocket, void * lpOutputBuffer, length_t dwReceiveDataLength, length_t dwLocalAddressLength, length_t dwRemoteAddressLength, length_t* lpdwBytesReceived, overlapped_ptr lpOverlapped)
	{
		return data::fn_accept_ex(
			sListenSocket, sAcceptSocket, lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength,
			dwRemoteAddressLength, lpdwBytesReceived, (LPOVERLAPPED)lpOverlapped);
	}
	void environment::get_acceptex_sockaddrs(void * lpOutputBuffer, length_t dwReceiveDataLength, length_t dwLocalAddressLength, length_t dwRemoteAddressLength, sockaddr_ptr * LocalSockaddr, length_ptr LocalSockaddrLength, sockaddr_ptr * RemoteSockaddr, length_ptr RemoteSockaddrLength)
	{
		data::fn_get_acceptex_sock_addrs(
			lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength,
			(sockaddr**)LocalSockaddr, LocalSockaddrLength, (sockaddr**)RemoteSockaddr, RemoteSockaddrLength
		);
	}
	int environment::connectex(socket_t s, const sockaddr_ptr name, int namelen, void * lpSendBuffer, length_t dwSendDataLength, length_t * lpdwBytesSent, overlapped_ptr lpOverlapped)
	{
		return data::fn_connect_ex(
			s, (const sockaddr *)name, namelen, lpSendBuffer, dwSendDataLength, lpdwBytesSent, (LPOVERLAPPED)lpOverlapped
		);
	}
	int environment::disconnectex(socket_t s, overlapped_ptr lpOverlapped, length_t dwFlags, length_t dwReserved)
	{
		return data::fn_disconnect_ex(s, (LPOVERLAPPED)lpOverlapped, dwFlags, dwReserved);
	}
	environment::environment()
	{
		auto nRet = ::WSAStartup(MAKEWORD(2, 2), &(data::wsadata));
		if (nRet != 0) { throw std::exception("WSAStartup Fail.",WSAGetLastError()); }

		auto sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		{
			GUID guidAcceptex = WSAID_ACCEPTEX;
			DWORD dwBytes = 0;
			WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptex, sizeof(guidAcceptex), &data::fn_accept_ex,
				sizeof(data::fn_accept_ex), &dwBytes, nullptr, nullptr);
		}
		{
			GUID guidAcceptex = WSAID_GETACCEPTEXSOCKADDRS;
			DWORD dwBytes = 0;
			WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptex, sizeof(guidAcceptex), &data::fn_get_acceptex_sock_addrs,
				sizeof(data::fn_get_acceptex_sock_addrs), &dwBytes, nullptr, nullptr);
		}
		{
			GUID guidAcceptex = WSAID_CONNECTEX;
			DWORD dwBytes = 0;
			WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptex, sizeof(guidAcceptex), &data::fn_connect_ex,
				sizeof(data::fn_connect_ex), &dwBytes, nullptr, nullptr);
		}
		{
			GUID guidAcceptex = WSAID_DISCONNECTEX;
			DWORD dwBytes = 0;
			WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptex, sizeof(guidAcceptex), &data::fn_disconnect_ex,
				sizeof(data::fn_disconnect_ex), &dwBytes, nullptr, nullptr);
		}
		::closesocket(sock);
	}
	environment::~environment()
	{
		WSACleanup();
	}
}
