#ifndef UAVPC_HARDWARE_GYROSCOPE_RANGE_HPP_
#define UAVPC_HARDWARE_GYROSCOPE_RANGE_HPP_

#include <cstdint>

namespace uavpc::Hardware
{
  /** @class GyroscopeRange
   *  @brief Defines the gyroscope ranges that can be used.
   */
  class GyroscopeRange
  {
   public:
    /** @enum Value
     *
     * Represents the values that the gyroscope range can take.
     * Value names should be read left to right, ie 250 degrees/s, 500 degrees/s etc.
     */
    enum Value : std::uint8_t
    {
      DEGS250 = 1,
      DEGS500 = 2,
      DEGS1000 = 3,
      DEGS2000 = 4
    };

   private:
    static constexpr std::uint8_t s_DegS250RegisterValue = 0b00000000;
    static constexpr float s_DegS250Sensitivity = 131.0F;
    static constexpr std::uint8_t s_DegS500RegisterValue = 0b00001000;
    static constexpr float s_DegS500Sensitivity = 65.5F;
    static constexpr std::uint8_t s_DegS1000RegisterValue = 0b00010000;
    static constexpr float s_DegS1000Sensitivity = 32.8F;
    static constexpr std::uint8_t s_DegS2000RegisterValue = 0b00011000;
    static constexpr float s_DegS2000Sensitivity = 16.4F;

    const Value m_Value;

   public:
    /** @brief Instantiate an GyroscopeRange with the value received as a parameter.
     *  @param[in] value. An GyroscopeRange::Value value, representing the desired range to be used by the gyroscope.
     */
    constexpr explicit GyroscopeRange(Value value) : m_Value(value)
    {
    }

    /** @brief Retrieve the binary, 8 bit value expected by the config register corresponding to the current range.
     *  @returns std::uint8_t The 8 bit binary value accepted by the config register.
     */
    [[nodiscard]] constexpr std::uint8_t GetConfigRegisterValue() const noexcept
    {
      if (m_Value == DEGS500)
      {
        return s_DegS500RegisterValue;
      }

      if (m_Value == DEGS1000)
      {
        return s_DegS1000RegisterValue;
      }

      if (m_Value == DEGS2000)
      {
        return s_DegS2000RegisterValue;
      }

      return s_DegS250RegisterValue;
    }

    /** @brief Compares the value of the current range with another one.
     *  @returns bool True if the two ranges are equal, false otherwise.
     */
    constexpr bool operator==(const GyroscopeRange& range) const noexcept
    {
      return m_Value == range.m_Value;
    }

    /** @brief Compares the value of the current range with another one.
     *  @returns bool True if the two ranges are different, false if they are equal.
     */
    constexpr bool operator!=(const GyroscopeRange& range) const noexcept
    {
      return !(*this == range);
    }

    explicit operator bool() = delete;

    /** @brief Return the sensitivity value of the current range.
     *  @returns A float value representing the LSB sensitivity of the selected range.
     */
    [[nodiscard]] constexpr explicit operator float() const noexcept
    {
      if (m_Value == DEGS500)
      {
        return s_DegS500Sensitivity;
      }

      if (m_Value == DEGS1000)
      {
        return s_DegS1000Sensitivity;
      }

      if (m_Value == DEGS2000)
      {
        return s_DegS2000Sensitivity;
      }

      return s_DegS250Sensitivity;
    }
  };
}  // namespace uavpc::Hardware

#endif
