

#include "hh/io/context.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace hh::io
{
	context::context(handle_t h)
		: m_handle(h)
	{
	}
	context::~context()
	{
		if ((m_handle != nullptr) && (m_handle != INVALID_HANDLE_VALUE))
		{
			::CloseHandle(m_handle);
			m_handle = nullptr;
		}
	}
	context::handle_t context::handle() const
	{
		return m_handle;
	}
	void context::register_handle(handle_t h, complete_key_t key, transfer_size_t count, hh::error_code& ec)
	{
		auto ir = ::CreateIoCompletionPort((HANDLE)h, (HANDLE)m_handle, key, static_cast<DWORD>(count));
		if (ir != m_handle)
		{
			ec.reset_os_last_error();
		}
		else
		{
			ec.clear();
		}
	}
	void context::post_status(transfer_size_t size, complete_key_t key, overlapped_ptr ovlpd, hh::error_code& ec)
	{
		auto B = ::PostQueuedCompletionStatus((HANDLE)m_handle, size, key, (LPOVERLAPPED)ovlpd);
		if(NULL == B)
		{
			ec.reset_os_last_error();
		}
		else
		{
			ec.clear();
		}
	}
	void context::get_status(complete_key_t &key, overlapped_ptr &ovlpd, transfer_size_t &size, timeout_t timeout, hh::error_code& ec)
	{
		auto B = ::GetQueuedCompletionStatus(
			(HANDLE)m_handle, &size, &key, (LPOVERLAPPED*)&ovlpd, timeout);
		if (NULL == B)
		{
			ec.reset_os_last_error();
		}
		else
		{
			ec.clear();
		}
	}
	void context::set_handle(handle_t h)
	{
		m_handle = h;
	}
}
