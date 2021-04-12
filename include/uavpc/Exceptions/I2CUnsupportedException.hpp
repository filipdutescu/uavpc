#ifndef UAVPC_EXCEPTIONS_INVALID_I2C_UNSUPPORTED_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_INVALID_I2C_UNSUPPORTED_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc::Exceptions
{
  /** @class I2CUnsupportedException
   *  @brief Used to signal that I2C communication is unsupported.
   */
  class I2CUnsupportedException : public std::runtime_error
  {
   public:
    I2CUnsupportedException();
  };
}  // namespace uavpc::Exceptions

#endif
