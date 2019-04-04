

#pragma once

namespace hh
{
	class tribool
	{
	public:
		enum value_t
		{
			indeterminate_value,
			false_value,
			true_value
		};
		tribool(value_t v = indeterminate_value);
		void reset(value_t v = indeterminate_value);
		value_t value() const;
		void set(value_t v);
		explicit operator bool() const;
	private:
		value_t m_value;
	};
}
