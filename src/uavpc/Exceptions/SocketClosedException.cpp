#include "uavpc/Exceptions/SocketClosedException.hpp"

namespace uavpc::Exceptions
{
  SocketClosedException::SocketClosedException() : std::runtime_error("Socket closed.")
  {
  }
}  // namespace uavpc::Exceptions
