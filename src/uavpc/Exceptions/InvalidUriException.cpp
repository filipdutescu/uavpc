#include "uavpc/Exceptions/InvalidUriException.hpp"

namespace uavpc::Exceptions
{
  InvalidUriException::InvalidUriException() : std::runtime_error("Invalid URI.")
  {
  }
}  // namespace uavpc::Exceptions
