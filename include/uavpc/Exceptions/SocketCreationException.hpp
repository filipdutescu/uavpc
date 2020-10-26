#ifndef UAVPC_EXCEPTIONS_SOCKET_CREATION_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_SOCKET_CREATION_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc
{
  namespace Exceptions
  {
    /** @class SocketCreationException
     *  @extends std::runtime_error
     *  @brief Used to signal failure when creating a socket.
     *
     * The SocketCreationException is used to signal that the creation of a new socket was not possible.
     */
    class SocketCreationException : public std::runtime_error
    {
     public:
      SocketCreationException();
    };
  }  // namespace Exceptions
}  // namespace uavpc

#endif
