

#pragma once

#include <string>
#include <vector>
#include "hh/mutex.hpp"

namespace hh
{
	template<class R, class ...Args>
	class callback /*abstract*/
	{
	public:
		virtual R operator()(Args... args) = 0;
		virtual ~callback() {}
		bool operator==(const callback &other) const
		{
			if (obj() != other.obj()) { return false; }
			if (method_size() != other.method_size()) { return false; }
			auto len = method_size();
			auto ir = memcmp(method_ptr(), other.method_ptr(), len);
			return ir == 0;
		}
		bool operator!=(const callback &other) const
		{
			return operator==(other) ? false : true;
		}
	protected:
		virtual void * obj() const = 0;
		virtual size_t method_size() const = 0;
		virtual void * method_ptr() const = 0;
	};
	template<class R, class O, class ...Args>
	class callback_member : public callback<R,Args...>
	{
	public:
		typedef R(O::*M)(Args...);
		virtual R operator()(Args... args)
		{
			return (m_obj->*m_method)(args...);
		}
		callback_member(O* o, M m)
		{
			m_obj = o;
			m_method = m;
		}
		virtual ~callback_member() {}
	protected:
		virtual void * obj() const
		{
			return m_obj;
		}
		virtual size_t method_size() const
		{
			return sizeof(M);
		}
		virtual void * method_ptr() const
		{
			return (void *)&m_method;
		}
	private:
		O* m_obj;
		M  m_method;
	};
	template<class R, class ...Args>
	class callback_function : public callback<R, Args...>
	{
	public:
		typedef R(*F)(Args...);
		callback_function(F func)
			: m_function(func)
		{

		}
		virtual R operator()(Args... args)
		{
			return m_function(args...);
		}
		virtual ~callback_function() {}
	protected:
		virtual void * obj() const
		{
			return nullptr;
		}
		virtual size_t method_size() const
		{
			return sizeof(F);
		}
		virtual void * method_ptr() const
		{
			return (void *)&m_function;
		}
	private:
		F m_function;
	};
	
	template<class ...Args>
	class event
	{
	public:
		using handler_t = callback<void, Args...>;
		using handler_ptr = handler_t * ;
	public:
		event() {}
		virtual ~event()
		{
			{
				auto _lock = hh::lock_guard(m_lock);
				for (auto p : m_handlers)
				{
					delete p;
				}

				m_handlers.clear();
			}
		}
		void operator()(Args... args)
		{
			auto _lock = hh::lock_guard(m_lock);
			for (auto p : m_handlers)
			{
				(*p)(args...);
			}
		}
		void operator+=(handler_ptr ph)
		{
			auto _lock = hh::lock_guard(m_lock);
			if (ph)
			m_handlers.push_back(ph);
		}
		void operator-=(handler_ptr ph)
		{
			auto _lock = hh::lock_guard(m_lock);
			auto it = std::find(m_handlers.begin(), m_handlers.end(), ph);
			if (it != m_handlers.end())
			{
				m_handlers.erase(it);
			}
		}
		void operator=(handler_ptr ph)
		{
			auto _lock = hh::lock_guard(m_lock);
			m_handlers.clear();
			if(ph)
			m_handlers.push_back(ph);
		}
		void clear()
		{
			auto _lock = hh::lock_guard(m_lock);
			m_handlers.clear();
		}
	private:
		std::vector<handler_ptr> m_handlers;
		hh::mutex m_lock;
	};
}
