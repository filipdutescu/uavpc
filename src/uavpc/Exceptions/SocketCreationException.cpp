#include "uavpc/Exceptions/SocketCreationException.hpp"

namespace uavpc
{
  namespace Exceptions
  {
    SocketCreationException::SocketCreationException() : std::runtime_error("Socket creation failed.")
    {
    }
  }  // namespace Exceptions
}  // namespace uavpc
