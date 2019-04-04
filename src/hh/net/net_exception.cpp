

#include "hh/net/exception.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
/// Socket 2
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <mswsock.h>

namespace hh::net
{
	exception::exception(const error_code& ec, const char * funcname, const char * filename, size_t line)
		: hh::exception(ec,funcname,filename,line)
	{

	}
	exception::exception(int errorid, const error_category & ec, const char * funcname, const char * filename, size_t line)
		: hh::exception(errorid,ec,funcname,filename,line)
	{

	}
	exception::~exception()
	{

	}
	exception_not_initialised::exception_not_initialised(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSANOTINITIALISED,hh::system_category(),funcname,filename,line)
	{
	}
	exception_invalid_handle::exception_invalid_handle(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_INVALID_HANDLE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_not_enough_memory::exception_not_enough_memory(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_NOT_ENOUGH_MEMORY, hh::system_category(), funcname, filename, line)
	{
	}
	exception_invalid_parameter::exception_invalid_parameter(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_INVALID_PARAMETER, hh::system_category(), funcname, filename, line)
	{
	}
	exception_operation_aborted::exception_operation_aborted(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_OPERATION_ABORTED, hh::system_category(), funcname, filename, line)
	{
	}
	exception_io_incomplete::exception_io_incomplete(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_IO_INCOMPLETE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_io_pending::exception_io_pending(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSA_IO_PENDING, hh::system_category(), funcname, filename, line)
	{
	}
	exception_interrupted::exception_interrupted(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEINTR, hh::system_category(), funcname, filename, line)
	{
	}
	exception_file_handle_invalid::exception_file_handle_invalid(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEBADF, hh::system_category(), funcname, filename, line)
	{
	}
	exception_permission_denied::exception_permission_denied(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEACCES, hh::system_category(), funcname, filename, line)
	{
	}
	exception_bad_address::exception_bad_address(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEFAULT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_invalid_argument::exception_invalid_argument(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEINVAL, hh::system_category(), funcname, filename, line)
	{
	}
	exception_too_many_open_files::exception_too_many_open_files(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEMFILE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_resource_temporarily_unavailable::exception_resource_temporarily_unavailable(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEWOULDBLOCK, hh::system_category(), funcname, filename, line)
	{
	}
	exception_operation_now_in_progress::exception_operation_now_in_progress(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEINPROGRESS, hh::system_category(), funcname, filename, line)
	{
	}
	exception_operation_already_in_progress::exception_operation_already_in_progress(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEALREADY, hh::system_category(), funcname, filename, line)
	{
	}
	exception_socket_operation_on_nonsocket::exception_socket_operation_on_nonsocket(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENOTSOCK, hh::system_category(), funcname, filename, line)
	{
	}
	exception_destination_address_required::exception_destination_address_required(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEDESTADDRREQ, hh::system_category(), funcname, filename, line)
	{
	}
	exception_message_too_long::exception_message_too_long(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEMSGSIZE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_protocol_wrong_type_for_socket::exception_protocol_wrong_type_for_socket(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEPROTOTYPE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_bad_protocol_option::exception_bad_protocol_option(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENOPROTOOPT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_protocol_not_supported::exception_protocol_not_supported(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEPROTONOSUPPORT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_socket_type_not_supported::exception_socket_type_not_supported(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAESOCKTNOSUPPORT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_operation_not_supported::exception_operation_not_supported(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEOPNOTSUPP, hh::system_category(), funcname, filename, line)
	{
	}
	exception_protocol_family_not_supported::exception_protocol_family_not_supported(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEPFNOSUPPORT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_address_family_not_supported_by_protocol_family::exception_address_family_not_supported_by_protocol_family(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEAFNOSUPPORT, hh::system_category(), funcname, filename, line)
	{
	}
	exception_address_already_in_use::exception_address_already_in_use(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEADDRINUSE, hh::system_category(), funcname, filename, line)
	{
	}
	exception_cannot_assign_requested_address::exception_cannot_assign_requested_address(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEADDRNOTAVAIL, hh::system_category(), funcname, filename, line)
	{
	}
	exception_network_is_down::exception_network_is_down(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENETDOWN, hh::system_category(), funcname, filename, line)
	{
	}
	exception_network_is_unreachable::exception_network_is_unreachable(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENETUNREACH, hh::system_category(), funcname, filename, line)
	{
	}
	exception_network_dropped_connection_on_reset::exception_network_dropped_connection_on_reset(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENETRESET, hh::system_category(), funcname, filename, line)
	{
	}
	exception_software_caused_connection_abort::exception_software_caused_connection_abort(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAECONNABORTED, hh::system_category(), funcname, filename, line)
	{
	}
	exception_connection_reset_by_peer::exception_connection_reset_by_peer(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAECONNRESET, hh::system_category(), funcname, filename, line)
	{
	}
	exception_no_buffer_space_available::exception_no_buffer_space_available(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENOBUFS, hh::system_category(), funcname, filename, line)
	{
	}
	exception_socket_is_already_connected::exception_socket_is_already_connected(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAEISCONN, hh::system_category(), funcname, filename, line)
	{
	}
	exception_socket_is_not_connected::exception_socket_is_not_connected(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAENOTCONN, hh::system_category(), funcname, filename, line)
	{
	}
	exception_cannot_send_after_socket_shutdown::exception_cannot_send_after_socket_shutdown(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAESHUTDOWN, hh::system_category(), funcname, filename, line)
	{
	}
	exception_too_many_references::exception_too_many_references(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAETOOMANYREFS, hh::system_category(), funcname, filename, line)
	{
	}
	exception_connection_timed_out::exception_connection_timed_out(const char * funcname, const char * filename, size_t line)
		: hh::net::exception(WSAETIMEDOUT, hh::system_category(), funcname, filename, line)
	{
	}
}
