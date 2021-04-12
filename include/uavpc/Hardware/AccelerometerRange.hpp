#ifndef UAVPC_HARDWARE_ACCELEROMETER_RANGE_HPP_
#define UAVPC_HARDWARE_ACCELEROMETER_RANGE_HPP_

#include <cstdint>

namespace uavpc::Hardware
{
  /** @class AccelerometerRange
   *  @brief Defines the accelerometer ranges that can be used.
   */
  class AccelerometerRange
  {
   public:
    /** @enum Value
     *
     * Represents the values that the accelerometer range can take.
     * Value names should be read from left to right, ie 2g, 4g etc.
     */
    enum Value : std::uint8_t
    {
      G2 = 2,
      G4 = 4,
      G8 = 8,
      G16 = 16
    };

   private:
    static constexpr std::uint8_t s_2GRegisterValue = 0b00000000;
    static constexpr float s_2GSensitivity = 16384.0F;
    static constexpr std::uint8_t s_4GRegisterValue = 0b00001000;
    static constexpr float s_4GSensitivity = 8192.0F;
    static constexpr std::uint8_t s_8GRegisterValue = 0b00010000;
    static constexpr float s_8GSensitivity = 4096.0F;
    static constexpr std::uint8_t s_16GRegisterValue = 0b00011000;
    static constexpr float s_16GSensitivity = 2048.0F;

    const Value m_Value;

   public:
    /** @brief Instantiate an AccelerometerRange with the value received as a parameter.
     *  @param[in] value. An AccelerometerRange::Value value, representing the desired range to be used by the
     * accelerometer.
     */
    constexpr explicit AccelerometerRange(Value value) : m_Value(value)
    {
    }

    /** @brief Retrieve the binary, 8 bit value expected by the config register corresponding to the current range.
     *  @returns std::uint8_t The 8 bit binary value accepted by the config register.
     */
    [[nodiscard]] constexpr std::uint8_t GetConfigRegisterValue() const noexcept
    {
      if (m_Value == G4)
      {
        return s_4GRegisterValue;
      }

      if (m_Value == G8)
      {
        return s_8GRegisterValue;
      }

      if (m_Value == G16)
      {
        return s_16GRegisterValue;
      }

      return s_2GRegisterValue;
    }

    /** @brief Compares the value of the current range with another one.
     *  @returns bool True if the two ranges are equal, false otherwise.
     */
    constexpr bool operator==(const AccelerometerRange& range) const noexcept
    {
      return m_Value == range.m_Value;
    }

    /** @brief Compares the value of the current range with another one.
     *  @returns bool True if the two ranges are different, false if they are equal.
     */
    constexpr bool operator!=(const AccelerometerRange& range) const noexcept
    {
      return !(*this == range);
    }

    explicit operator bool() = delete;

    /** @brief Return the sensitivity value of the current range.
     *  @returns A float value representing the LSB sensitivity of the selected range.
     */
    [[nodiscard]] constexpr explicit operator float() const noexcept
    {
      if (m_Value == G4)
      {
        return s_4GSensitivity;
      }

      if (m_Value == G8)
      {
        return s_8GSensitivity;
      }

      if (m_Value == G16)
      {
        return s_16GSensitivity;
      }

      return s_2GSensitivity;
    }
  };
}  // namespace uavpc::Hardware

#endif
