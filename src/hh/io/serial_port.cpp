

#include "hh/io/serial_port.hpp"

#include "hh/error_t.hpp"
#include "hh/tick_count.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

namespace hh::io
{
	serial_port::serial_port()
		: m_handle(NULL)
		, m_baudrate(cbr_9600)
		, m_parity(parity_no)
		, m_stopbit(stopbit_1)
		, m_bytesize(8)
		, m_in_queue_size(512)
		, m_out_queue_size(512)
	{
	}
	serial_port::~serial_port()
	{
		close();
	}
	void serial_port::open(const std::wstring& portname, hh::error_code& ec)
	{
		auto _lock_r = hh::lock_guard(m_r_lock);
		auto _lock_w = hh::lock_guard(m_w_lock);

		ec.clear();
		if (m_handle != NULL) { ec.reset(hh::errors::already_exists); return; }
		auto h = ::CreateFile(
			portname.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			nullptr);
		if (INVALID_HANDLE_VALUE == h)
		{
			ec.reset_os_last_error(); return;
		}

		COMMTIMEOUTS CommTimeOuts;
		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
		CommTimeOuts.ReadTotalTimeoutConstant = 0;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
		CommTimeOuts.WriteTotalTimeoutConstant = 5000;
		SetCommTimeouts(h, &CommTimeOuts);

		const wchar_t* szParity[] = { L"N", L"O", L"E" };

		wchar_t params[1024] = { 0 };
		wsprintf(params, L"%s:%d,%s,%d,%d", portname.c_str(), m_baudrate, szParity[m_parity], m_bytesize, m_stopbit);

		DCB dcb;
		dcb.DCBlength = sizeof(DCB);
		GetCommState(h, &dcb);

		dcb.BaudRate = m_baudrate;
		dcb.ByteSize = m_bytesize;
		dcb.Parity = m_parity;
		dcb.StopBits = m_stopbit;

		BuildCommDCB(params, &dcb);

		if (SetCommState(h, &dcb) == FALSE)
		{
			ec.reset_os_last_error();
			::CloseHandle(h);
			return;
		}

		if (SetupComm(h, m_in_queue_size, m_out_queue_size) == FALSE)
		{
			ec.reset_os_last_error();
			::CloseHandle(h);
			return;
		}

		m_handle = (handle_t)h;
	}
	void serial_port::close()
	{
		if (m_handle != NULL)
		{
			auto _lock_r = hh::lock_guard(m_r_lock);
			auto _lock_w = hh::lock_guard(m_w_lock);

			::CloseHandle((HANDLE)m_handle);

			m_handle = NULL;
		}
	}
	void serial_port::receive(void* buffer, buffer_size_t size, buffer_size_t& receivesize, hh::error_code& ec)
	{
		auto _lock = hh::lock_guard(m_r_lock);

		if (!is_open())
		{
			ec.reset(hh::errors::invalid_handle); return;
		}

		if (ec) { ec.clear(); }

		OVERLAPPED ovlpd = { 0 };
		DWORD dwsize = 0;

		ovlpd.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		if (ovlpd.hEvent == NULL)
		{
			ec.reset_os_last_error(); return;
		}

		hh::tick_count tc;

		auto B = ::ReadFile(
			(HANDLE)m_handle,
			buffer,
			size,
			&dwsize,
			&ovlpd);
		if (NULL == B)
		{
			auto err = GetLastError();
			if (err != ERROR_IO_PENDING)
			{
				ec.reset(err); return;
			}
		}

		B = WaitForSingleObject(ovlpd.hEvent, 1000);
		if (B != WAIT_OBJECT_0)
		{
			ec.reset(B); return;
		}

		receivesize = dwsize;
	}
	void serial_port::send(void* buffer, buffer_size_t size, hh::error_code& ec)
	{
		auto _lock = hh::lock_guard(m_w_lock);
		if (!is_open()) { ec.reset(hh::errors::invalid_handle); return; }

		if (ec) { ec.clear(); }

		OVERLAPPED ovlpd = { 0 };
		DWORD dwsize = 0;

		ovlpd.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		if (ovlpd.hEvent == NULL)
		{
			ec.reset_os_last_error(); return;
		}
		
		auto B = ::WriteFile(
			(HANDLE)m_handle,
			buffer,
			size,
			&dwsize,
			&ovlpd);
		if (NULL == B)
		{
			auto err = GetLastError();
			if (err != ERROR_IO_PENDING)
			{
				ec.reset(err); return;
			}
		}

		B = WaitForSingleObject(ovlpd.hEvent, 1000);
		if (B != WAIT_OBJECT_0)
		{
			ec.reset(B); return;
		}
	}
	bool serial_port::is_open() const
	{
		return m_handle != NULL;
	}
	serial_port::baudrate_t serial_port::baudrate() const
	{
		return m_baudrate;
	}
	void serial_port::baudrate(baudrate_t value)
	{
		m_baudrate = value;
	}
	serial_port::parity_t serial_port::parity() const
	{
		return m_parity;
	}
	void serial_port::parity(parity_t value)
	{
		m_parity = value;
	}
	serial_port::stopbit_t serial_port::stopbit() const
	{
		return m_stopbit;
	}
	void serial_port::stopbit(stopbit_t value)
	{
		m_stopbit = value;
	}
}