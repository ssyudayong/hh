

#pragma once

namespace hh
{
	// @see https://docs.microsoft.com/en-us/windows/console/using-the-console
	class console
	{
	public:
		struct control_handler;
	public:
		using handle_t = size_t;
		typedef enum : int
		{
			standard_input,
			standard_output,
			standard_error
		} standard_mode;
		typedef enum : int
		{
			control_c,
			control_close,
			control_break,
			control_logoff,
			control_shutdown
		} control_event;
	public:
		console(handle_t h);
		console(standard_mode mode);
		virtual ~console();
		void cls();
		void register_control_handler(bool value);
		int ScrollByAbsoluteCoord(int iRows);
		int ScrollByRelativeCoord(int iRows);
	private:
		handle_t m_handle;
	};
}
