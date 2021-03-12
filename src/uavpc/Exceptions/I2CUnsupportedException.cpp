#include "uavpc/Exceptions/I2CUnsupportedException.hpp"

namespace uavpc::Exceptions
{
  I2CUnsupportedException::I2CUnsupportedException() : std::runtime_error("I2C communications not supported.")
  {
  }
}  // namespace uavpc::Exceptions
