

#pragma once

#include <cstdint>
#include <string>

namespace hh
{
	// ��ӦMicrosoft��SYSTEMTIME�ṹ��
	struct datetime_t
	{
		uint16_t wYear;				///< 
		uint16_t wMonth;			///< 
		uint16_t wDayOfWeek;		///< 
		uint16_t wDay;				///< 
		uint16_t wHour;				///< 
		uint16_t wMinute;			///< 
		uint16_t wSecond;			///< 
		uint16_t wMilliseconds;		///< 
	};
	// filetime_t ����ȷ����local����system��
	// ��ӦMicrosoft��FILETIME�ṹ��
	struct filetime_t
	{
		using file_handle_t = size_t;
		uint32_t low;
		uint32_t high;
		// Retrieves the current local date and time.
		filetime_t to_local();
		// Retrieves the current system date and time. 
		// The system time is expressed in Coordinated Universal Time (UTC).
		filetime_t to_system();
		static int get_filetime(
			file_handle_t file,
			filetime_t* lpcreateiontime,
			filetime_t* lplastaccesstime,
			filetime_t* lplastwritetime);
	};
	// ����local��system��
	class datetime
	{
	public:
		enum mode_t
		{
			system_mode,	///< 
			local_mode		///< 
		};
	public:
		datetime();
		datetime(const filetime_t& ft, mode_t m);
		virtual ~datetime();
		// ��ȡϵͳʱ�䣬UTCʱ�䡣
		static datetime system_now();
		// ��ȡ����ʱ�䡣
		static datetime local_now();
		// ת�����ļ�ʱ�䡣
		filetime_t to_filetime();
		std::wstring to_iso8601() const;
	private:
		datetime_t m_data;
		mode_t m_mode;
	};
}