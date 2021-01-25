#include "uavpc/Exceptions/InvalidUriException.hpp"

namespace uavpc
{
  namespace Exceptions
  {
    InvalidUriException::InvalidUriException() : std::runtime_error("Invalid URI.")
    {
    }
  }  // namespace Exceptions
}  // namespace uavpc
