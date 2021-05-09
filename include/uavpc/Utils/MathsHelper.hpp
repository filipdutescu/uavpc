#ifndef UAVPC_UTILS_MATHS_HELPER_HPP
#define UAVPC_UTILS_MATHS_HELPER_HPP

#include "uavpc/Hardware/SensorData.hpp"

#include <cmath>

namespace uavpc::Utils
{
  /** @brief Helper class for mathematical operations.
   */
  class MathsHelper
  {
    static constexpr float s_ConversionDegrees = 180.0F;
    static constexpr float s_RotationDegrees = 90.0F;

   public:
    static constexpr float PI = std::atan(1.0F) * 4.0F;

    /** @brief Round the received SensorData to the given number of decimals.
     *  @param[in] sensorData The sensorData to be rounded.
     *  @param[in] precision Default: 3. The precision the values should be rounded to.
     *  @returns A new SensorData instance containing the rounded values.
     */
    [[nodiscard]] static constexpr Hardware::SensorData Round(
        Hardware::SensorData sensorData,
        std::size_t precision = 3U) noexcept
    {
      auto magnitude = static_cast<float>(std::pow(10, precision));

      if (precision > 0U)
      {
        sensorData.X = std::trunc(sensorData.X * magnitude) / magnitude;
        sensorData.Y = std::trunc(sensorData.Y * magnitude) / magnitude;
        sensorData.Z = std::trunc(sensorData.Z * magnitude) / magnitude;
      }

      return sensorData;
    }

    /** @brief Convert the sensor data to angles measured in degrees.
     *  @param[in] sensorData The sensor data to be converted to angles.
     *  @returns A new SensorData instance containing the angles of the one received.
     */
    [[nodiscard]] static Hardware::SensorData ConvertToAngles(const Hardware::SensorData& sensorData) noexcept;
  };
}  // namespace uavpc::Utils

#endif
