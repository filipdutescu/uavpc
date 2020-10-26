#include "uavpc/Exceptions/SocketClosedException.hpp"

namespace uavpc
{
  namespace Exceptions
  {
    SocketClosedException::SocketClosedException() : std::runtime_error("Socket closed.")
    {
    }
  }  // namespace Exceptions
}  // namespace uavpc
