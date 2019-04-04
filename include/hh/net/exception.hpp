///
/// @see https://docs.microsoft.com/zh-cn/windows/desktop/WinSock/windows-sockets-error-codes-2
///

#pragma once

#include "hh/exception.hpp"

namespace hh::net
{
	class exception : public hh::exception
	{
	public:
		exception(const error_code& ec, const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
		exception(int errorid, const error_category& ec, const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
		virtual ~exception();
	};
	class exception_not_initialised : public hh::net::exception
	{
	public:
		exception_not_initialised(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_invalid_handle : public hh::net::exception
	{
	public:
		exception_invalid_handle(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_not_enough_memory : public hh::net::exception
	{
	public:
		exception_not_enough_memory(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_invalid_parameter : public hh::net::exception
	{
	public:
		exception_invalid_parameter(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_operation_aborted : public hh::net::exception
	{
	public:
		exception_operation_aborted(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_io_incomplete : public hh::net::exception
	{
	public:
		exception_io_incomplete(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_io_pending : public hh::net::exception
	{
	public:
		exception_io_pending(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_interrupted : public hh::net::exception
	{
	public:
		exception_interrupted(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_file_handle_invalid : public hh::net::exception
	{
	public:
		exception_file_handle_invalid(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_permission_denied : public hh::net::exception
	{
	public:
		exception_permission_denied(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_bad_address : public hh::net::exception
	{
	public:
		exception_bad_address(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_invalid_argument : public hh::net::exception
	{
	public:
		exception_invalid_argument(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_too_many_open_files : public hh::net::exception
	{
	public:
		exception_too_many_open_files(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_resource_temporarily_unavailable : public hh::net::exception
	{
	public:
		exception_resource_temporarily_unavailable(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_operation_now_in_progress : public hh::net::exception
	{
	public:
		exception_operation_now_in_progress(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_operation_already_in_progress : public hh::net::exception
	{
	public:
		exception_operation_already_in_progress(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_socket_operation_on_nonsocket : public hh::net::exception
	{
	public:
		exception_socket_operation_on_nonsocket(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_destination_address_required : public hh::net::exception
	{
	public:
		exception_destination_address_required(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_message_too_long : public hh::net::exception
	{
	public:
		exception_message_too_long(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_protocol_wrong_type_for_socket : public hh::net::exception
	{
	public:
		exception_protocol_wrong_type_for_socket(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_bad_protocol_option : public hh::net::exception
	{
	public:
		exception_bad_protocol_option(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_protocol_not_supported : public hh::net::exception
	{
	public:
		exception_protocol_not_supported(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_socket_type_not_supported : public hh::net::exception
	{
	public:
		exception_socket_type_not_supported(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_operation_not_supported : public hh::net::exception
	{
	public:
		exception_operation_not_supported(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_protocol_family_not_supported : public hh::net::exception
	{
	public:
		exception_protocol_family_not_supported(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_address_family_not_supported_by_protocol_family : public hh::net::exception
	{
	public:
		exception_address_family_not_supported_by_protocol_family(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_address_already_in_use : public hh::net::exception
	{
	public:
		exception_address_already_in_use(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_cannot_assign_requested_address : public hh::net::exception
	{
	public:
		exception_cannot_assign_requested_address(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_network_is_down : public hh::net::exception
	{
	public:
		exception_network_is_down(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_network_is_unreachable : public hh::net::exception
	{
	public:
		exception_network_is_unreachable(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_network_dropped_connection_on_reset : public hh::net::exception
	{
	public:
		exception_network_dropped_connection_on_reset(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_software_caused_connection_abort : public hh::net::exception
	{
	public:
		exception_software_caused_connection_abort(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_connection_reset_by_peer : public hh::net::exception
	{
	public:
		exception_connection_reset_by_peer(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_no_buffer_space_available : public hh::net::exception
	{
	public:
		exception_no_buffer_space_available(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_socket_is_already_connected : public hh::net::exception
	{
	public:
		exception_socket_is_already_connected(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_socket_is_not_connected : public hh::net::exception
	{
	public:
		exception_socket_is_not_connected(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_cannot_send_after_socket_shutdown : public hh::net::exception
	{
	public:
		exception_cannot_send_after_socket_shutdown(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_too_many_references : public hh::net::exception
	{
	public:
		exception_too_many_references(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
	class exception_connection_timed_out : public hh::net::exception
	{
	public:
		exception_connection_timed_out(const char * funcname = nullptr, const char * filename = __FILE__, size_t line = __LINE__);
	};
}
