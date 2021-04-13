#ifndef UAVPC_HARDWARE_I2C_SERVICE_HPP_
#define UAVPC_HARDWARE_I2C_SERVICE_HPP_

#include "uavpc/Hardware/II2CService.hpp"

#include <cstdint>

namespace uavpc::Hardware
{
  /** @class I2CService
   *  @implements uavpc::Hardware::II2CService
   *  @brief Defines the basic operations needed to communicate via I2C.
   *
   * Handles openning and closing the I2C device file and bus, as well as I/O operations to the connected bus.
   */
  class I2CService : public II2CService
  {
    unsigned char m_DeviceNo;
    int m_DeviceFile;
    std::uint8_t m_BusAddress;

   public:
    /** @brief Instantiate a new I2CService, for the given device number and bus address.
     *  @param[in] deviceNo The I2C device number to be used (ie for '/dev/i2c-1', deviceNo is '1').
     *  @param[in] busAddress The I2C bus address to write to and read from.
     *  @throws uavpc::Exceptions::I2CUnsupportedException if it cannot connect to the device file.
     *  @throws uavpc::Exceptions::InvalidAddressException if it cannot connect to the bus at the given address.
     *
     * Instantiate a new I2CService by opening the device file of the device with the given number and try to connect to
     * its bus address, received as a parameter.
     */
    explicit I2CService(unsigned char deviceNo, std::uint8_t busAddress);

    I2CService(const I2CService&) = delete;
    I2CService(I2CService&&) = delete;
    I2CService& operator=(const I2CService&) = delete;
    I2CService& operator=(I2CService&&) = delete;

    ~I2CService() override;

    /** @copydoc uavpc::Hardware::II2CService::ReadByteData()
     */
    [[nodiscard]] std::int32_t ReadByteData(std::uint8_t registerAddress) const noexcept override;

    /** @copydoc uavpc::Hardware::II2CService::WriteByteData()
     */
    void WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept override;

    /** @copydoc uavpc::Hardware::II2CService::ReadWordData()
     */
    [[nodiscard]] std::int32_t ReadWordData(std::uint8_t registerAddress) const noexcept override;
  };
}  // namespace uavpc::Hardware

#endif
