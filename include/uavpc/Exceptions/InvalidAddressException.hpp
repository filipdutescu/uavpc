#ifndef UAVPC_EXCEPTIONS_INVALID_ADDRESS_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_INVALID_ADDRESS_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc::Exceptions
{
  /** @class InvalidAddressException
   *  @brief Used to signal the usage of an invalid URI.
   */
  class InvalidAddressException : public std::runtime_error
  {
   public:
    InvalidAddressException();
  };
}  // namespace uavpc::Exceptions

#endif
