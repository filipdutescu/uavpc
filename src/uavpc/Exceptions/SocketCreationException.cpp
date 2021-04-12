#include "uavpc/Exceptions/SocketCreationException.hpp"

namespace uavpc::Exceptions
{
  SocketCreationException::SocketCreationException() : std::runtime_error("Socket creation failed.")
  {
  }
}  // namespace uavpc::Exceptions
