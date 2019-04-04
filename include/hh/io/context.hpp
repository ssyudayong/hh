

#pragma once

#include "hh/error_code.hpp"

namespace hh::io
{
	class context
	{
	public:
		using handle_t = void *;	//< windows platform handle type
		using transfer_size_t = unsigned long;
		using complete_key_t = size_t;
		using overlapped_ptr = void *;
		using timeout_t = unsigned long;
	public:
		context(handle_t h);
		virtual ~context();
		handle_t handle() const;
		void register_handle(handle_t h, complete_key_t key, transfer_size_t count, hh::error_code& ec);
		void post_status(transfer_size_t size, complete_key_t key, overlapped_ptr ovlpd, hh::error_code& ec);
		void get_status(complete_key_t &key, overlapped_ptr &ovlpd, transfer_size_t &size, timeout_t timeout, hh::error_code& ec);
	protected:
		void set_handle(handle_t h);
	private:
		handle_t m_handle;
	};
}
