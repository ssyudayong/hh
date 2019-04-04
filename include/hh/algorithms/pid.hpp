

#pragma once

namespace hh::algorithms
{
	class pid
	{
	public:
		pid(double dp, double di, double dd);
		virtual ~pid();
		double calc(double err);
		void reset();
		void set_pid(double dp, double di, double dd);
		void get_pid(double &dp, double &di, double &dd);
		void set_last_error(double value);
		double get_last_error() const;
	private:
		double m_p;
		double m_i;
		double m_d;
		double m_last_error;
		double m_last_i;
	};
}
