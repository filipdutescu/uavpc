#ifndef UAVPC_EXCEPTIONS_INVALID_URI_EXCEPTION_HPP_
#define UAVPC_EXCEPTIONS_INVALID_URI_EXCEPTION_HPP_

#include <stdexcept>

namespace uavpc
{
  namespace Exceptions
  {
    /** @class InvalidUriException
     *  @brief Used to signal the usage of an invalid URI.
     */
    class InvalidUriException : public std::runtime_error
    {
    public:
      InvalidUriException();
    };
  }
}

#endif
