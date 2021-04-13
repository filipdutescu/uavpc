#include "uavpc/Hardware/I2CService.hpp"

#include "uavpc/Exceptions/I2CUnsupportedException.hpp"
#include "uavpc/Exceptions/InvalidAddressException.hpp"
#include <sys/ioctl.h>
#include <sys/types.h>

#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>
extern "C"
{
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
}

namespace uavpc::Hardware
{
  I2CService::I2CService(unsigned char deviceNo, std::uint8_t busAddress) : m_DeviceNo(deviceNo), m_BusAddress(busAddress)
  {
    std::string deviceAddress("/dev/i2c-");
    deviceAddress.push_back(static_cast<char>(deviceNo));

    m_DeviceFile = open(deviceAddress.c_str(), O_RDWR);
    if (m_DeviceFile < 0)
    {
      throw Exceptions::I2CUnsupportedException();
    }

    if (ioctl(m_DeviceFile, I2C_SLAVE, m_BusAddress) < 0)
    {
      throw Exceptions::InvalidAddressException();
    }
  }

  I2CService::~I2CService()
  {
    close(m_DeviceFile);
  }

  std::int32_t I2CService::ReadByteData(std::uint8_t registerAddress) const noexcept
  {
    return i2c_smbus_read_byte_data(m_DeviceFile, registerAddress);
  }

  void I2CService::WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept
  {
    i2c_smbus_write_byte_data(m_DeviceFile, registerAddress, value);
  }

  std::int32_t I2CService::ReadWordData(std::uint8_t registerAddress) const noexcept
  {
    auto rawData = i2c_smbus_read_word_data(m_DeviceFile, registerAddress);
    return (rawData << 8) | (rawData >> 8);
  }
}  // namespace uavpc::Hardware
