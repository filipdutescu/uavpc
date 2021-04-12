#ifndef UAVPC_EXCEPTIONS_SOCKET_CLOSE_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_SOCKET_CLOSE_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc::Exceptions
{
  /** @class SocketClosedException
   *  @extends std::runtime_error
   *  @brief Used to signal socket operation failure due to a closed socket.
   *
   * The SocketClosedException is used to signal that an operation on a socket has failed, do to the later not being open.
   */
  class SocketClosedException : public std::runtime_error
  {
   public:
    SocketClosedException();
  };
}  // namespace uavpc::Exceptions

#endif
