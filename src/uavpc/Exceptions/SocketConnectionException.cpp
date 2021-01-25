#include "uavpc/Exceptions/SocketConnectionException.hpp"

namespace uavpc
{
  namespace Exceptions
  {
    SocketConnectionException::SocketConnectionException() : std::runtime_error("Could not connect to socket.")
    {
    }
  }  // namespace Exceptions
}  // namespace uavpc
