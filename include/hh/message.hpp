

#pragma once

#include <tuple>

namespace hh
{
	template<class ...Args>
	class message
	{
	public:
		class argument_t
		{
		public:
			argument_t(Args&&... args)
				: m_args(std::forward_as_tuple(std::forward<Args>(args)...))
			{

			}
		private:
			std::tuple<Args&&...> m_args;
		};
	public:

	private:
		size_t m_id;
	};
	
}
