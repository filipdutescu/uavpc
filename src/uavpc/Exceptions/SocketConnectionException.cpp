#include "uavpc/Exceptions/SocketConnectionException.hpp"

namespace uavpc::Exceptions
{
  SocketConnectionException::SocketConnectionException() : std::runtime_error("Could not connect to socket.")
  {
  }
}  // namespace uavpc::Exceptions
