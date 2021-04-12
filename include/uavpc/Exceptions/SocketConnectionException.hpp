#ifndef UAVPC_EXCEPTIONS_SOCKET_CONNECTION_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_SOCKET_CONNECTION_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc::Exceptions
{
  /** @class SocketConnectionException
   *  @extends std::runtime_error
   *  @brief Used to signal an failure to connect to a socket.
   */
  class SocketConnectionException : public std::runtime_error
  {
   public:
    SocketConnectionException();
  };
}  // namespace uavpc::Exceptions

#endif
