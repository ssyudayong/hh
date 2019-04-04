

#pragma once

#include "hh/net/environment.hpp"
#include "hh/net/socket_address.hpp"

#include <memory>

namespace hh::net
{
	class socket : public std::enable_shared_from_this<socket>
	{
	public:
		using handle_t = size_t;
		using shared_ptr = std::shared_ptr<socket>;
		using ioctl_arg_t = unsigned long;
		using ioctl_arg_ptr = ioctl_arg_t * ;
	public:
		socket();
		socket(handle_t s);
		// 这个构造函数不使用socket函数，而是wsasocket函数。
		socket(address_family_t af, socket_type_t st, protocol_t p);
		virtual ~socket();
		handle_t accept(socket_address &addr);
		int connect(const socket_address& addr);
		int bind(const socket_address & addr);
		int listen(int backlog);
		int shutdown(int how);
		void close();
		int ioctl(long cmd, ioctl_arg_ptr argp);
		int available();
		socket_address address();
		socket_address peer_address();
		int set_option(int level, int option, const void * value, int length);
		int get_option(int level, int option, void * value, int &length);
		void set_no_delay(bool flag);
		bool get_no_delay();
		void set_keepalive(bool flag);
		bool get_keepalive();
		void set_reuse_address(bool flag);
		bool get_reuse_address();
		int error();
		handle_t handle() const;
		template<class T>
		static socket::shared_ptr socket_sp(std::shared_ptr<T> p);
		//virtual void on_receive(size_t size);
		//virtual void on_send(size_t size);
		//virtual void on_shutdown();
	private:
		handle_t m_handle;
	};
	template<class T>
	inline socket::shared_ptr socket::socket_sp(std::shared_ptr<T> p)
	{
		return std::dynamic_pointer_cast<socket, T>(p);
	}
}