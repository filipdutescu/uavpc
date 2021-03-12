#include "uavpc/Exceptions/InvalidAddressException.hpp"

namespace uavpc::Exceptions
{
  InvalidAddressException::InvalidAddressException()
      : std::runtime_error("I2C bus could not be aquired at the specified address.")
  {
  }
}  // namespace uavpc::Exceptions
