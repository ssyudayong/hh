

#include "hh/algorithms/pid.hpp"

namespace hh::algorithms
{
	pid::pid(double dp, double di, double dd)
		: m_p(dp)
		, m_i(di)
		, m_d(dd)
		, m_last_error(0)
		, m_last_i(0)
	{
	}
	pid::~pid()
	{
	}
	double pid::calc(double err)
	{
		double dp = 0;
		double di = 0;
		double dd = 0;
		double dpid = 0;

		dp = m_p * err;
		di = err * m_i + m_last_i;
		dd = (err - m_last_error) * m_d;

		m_last_i = di;
		m_last_error = err;

		dpid = dp + di + dd;

		return dpid;
	}
	void pid::reset()
	{
		m_last_i = 0;
		m_last_error = 0;
	}
	void pid::set_pid(double dp, double di, double dd)
	{
		m_p = dp;
		m_i = di;
		m_d = dd;
	}
	void pid::get_pid(double & dp, double & di, double & dd)
	{
		dp = m_p;
		di = m_i;
		dd = m_d;
	}
	void pid::set_last_error(double value)
	{
		m_last_error = value;
	}
	double pid::get_last_error() const
	{
		return m_last_error;
	}
}
