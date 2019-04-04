

#pragma once

namespace hh
{
	// @see https://docs.microsoft.com/zh-cn/windows/desktop/Sync/interlocked-variable-access
	class locked_long
	{
	public:
		locked_long(long defaultvalue = 0);
		long operator++();
		long operator--();
	private:
		long m_value;
	};
}

