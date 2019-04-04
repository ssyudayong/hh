///
/// @brief	mutex class and lock_guard class.
///
/// @file	mutex.hpp
///
/// @see	std::mutex and std::lock_guard
///
/// @author	Yu Dayong
///
/// @date	2019-04-03
///

#pragma once

namespace hh
{
	/// @brief	mutex class
	///			ref std::mutex.
	class mutex
	{
	public:
		mutex();
		virtual ~mutex();
		void lock();
		void unlock();
		bool try_lock();
	private:
		enum : int
		{
			// sizeof(CRITICAL_SECTION)
			win32_size = 24,
			win64_size = 40
		};
	#ifdef _WIN64
		unsigned char data[win64_size];
	#else
		unsigned char data[win32_size];
	#endif
	};
	class lock_guard
	{
	public:
		lock_guard(mutex& m);
		virtual ~lock_guard();
	private:
		mutex& m_mutex;
	};
}
