

#pragma once

#include "hh/error_code.hpp"
#include "hh/mutex.hpp"

#include <vector>
#include <string>

namespace hh::io
{
	class serial_port
	{
	public:
		using baudrate_t = enum
		{
			cbr_110		= 110,
			cbr_300		= 300,
			cbr_600		= 600,
			cbr_1200	= 1200,
			cbr_2400	= 2400,
			cbr_4800	= 4800,
			cbr_9600	= 9600,
			cbr_14400	= 14400,
			cbr_19200	= 19200,
			cbr_38400	= 38400,
			cbr_57600	= 57600,
			cbr_115200	= 115200,
			cbr_128000	= 128000,
			cbr_256000	= 256000
		};
		using parity_t = enum : unsigned char
		{
			parity_no		= 0,
			parity_odd		= 1,
			parity_even		= 2,
			parity_mark		= 3,
			parity_space	= 4
		};
		using stopbit_t = enum : unsigned char
		{
			stopbit_1	= 0,
			stopbit_1_5 = 1,
			stopbit_2	= 2
		};
		using bytesize_t = unsigned char;
		using buffer_size_t = unsigned long;
	public:
		using handle_t = size_t;
	public:
		serial_port();
		virtual ~serial_port();
		void open(const std::wstring& portname, hh::error_code& ec);
		void close();
		void receive(void* buffer, buffer_size_t size, buffer_size_t& receivesize, hh::error_code& ec);
		void send(void* buffer, buffer_size_t size, hh::error_code& ec);
		bool is_open() const;
		baudrate_t baudrate() const;
		void baudrate(baudrate_t value);
		parity_t parity() const;
		void parity(parity_t value);
		stopbit_t stopbit() const;
		void stopbit(stopbit_t value);
	private:
		handle_t m_handle;
		hh::mutex m_w_lock;
		hh::mutex m_r_lock;
		baudrate_t m_baudrate;
		parity_t m_parity;
		stopbit_t m_stopbit;
		bytesize_t m_bytesize;
		buffer_size_t m_in_queue_size;
		buffer_size_t m_out_queue_size;
	};

	class serial_port_list
	{
	public:
		serial_port_list();
	private:

	};
}
