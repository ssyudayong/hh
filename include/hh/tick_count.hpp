

#pragma once

namespace hh
{
	class tick_count
	{
	public:
		tick_count();
		virtual ~tick_count();
		static unsigned long long now();
		unsigned long long interval() const;
		void reset();
	private:
		unsigned long long m_begin;
	};
}
