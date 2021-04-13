#ifndef UAVPC_HARDWARE_II2C_SERVICE_HPP_
#define UAVPC_HARDWARE_II2C_SERVICE_HPP_

#include <cstdint>

namespace uavpc::Hardware
{
  /** @interface II2CService
   *  @brief Defines the basic I/O operations supported for I2C communication.
   */
  class II2CService
  {
   public:
    II2CService() = default;
    II2CService(const II2CService&) = delete;
    II2CService(II2CService&&) = delete;
    II2CService& operator=(const II2CService&) = delete;
    II2CService& operator=(II2CService&&) = delete;
    virtual ~II2CService() = default;

    /** @brief Read the value at the given register address.
     *  @param[in] registerAddress The hexadecimal address of the register to be read.
     *  @returns an std::int32_t containing the binary value at the register.
     */
    [[nodiscard]] virtual std::int32_t ReadByteData(std::uint8_t registerAddress) const noexcept = 0;

    /** @brief Write the received value at the given register address.
     *  @param[in] registerAddress The hexadecimal address of the register to be read.
     *  @param[in] value The 8-bit binary value to be writen in the register.
     */
    virtual void WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept = 0;

    /** @brief Read 16 bits from a given register address.
     *  @param[in] registerAddress The hexadecimal address of the register to be read.
     *  @returns an std::int32_t containing the binary 16-bit value at the register.
     *
     * Read 16 bits from a given register address. If there are only 8 available at the address, read the
     * remaining 8 bits from the next register, by incrementing the address received as a parameter.
     */
    [[nodiscard]] virtual std::int32_t ReadWordData(std::uint8_t registerAddress) const noexcept = 0;
  };
}  // namespace uavpc::Hardware

#endif
