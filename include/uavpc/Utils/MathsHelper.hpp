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
    static constexpr float s_RadToDeg = 57.2957914331F;

   public:
    /** @brief Round the received SensorData to the given number of decimals.
     *  @param[in] sensorData The uavpc::Hardware::SensorData to be rounded.
     *  @param[in] precision Default: 3. The precision the values should be rounded to.
     *  @returns A new uavpc::Hardware::SensorData instance containing the rounded values.
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
     *  @param[in] sensorData The uavpc::Hardware::SensorData who's values are to be converted to angles.
     *  @returns A new uavpc::Hardware::SensorData instance containing the angles of the one received.
     */
    [[nodiscard]] static Hardware::SensorData ConvertToAngles(const Hardware::SensorData& sensorData) noexcept;

    /** @brief Sum the two sensor data instances, proportionally, with weights computed from the given value tau.
     *  @param[in] sensorData1 A uavpc::Hardware::SensorData instance, which will be weighted with <tt>1 - tau</tt>.
     *  @param[in] sensorData2 A uavpc::Hardware::SensorData instance, which will be weighted with <tt>tau</tt>.
     *  @param[in] tau A double value used to compute the individual weights of each sum operand.
     *  @returns A uavpc::Hardware::SensorData containing the result of the weighted sum for each axis.
     */
    [[nodiscard]] static constexpr Hardware::SensorData
    WeightedSum(const Hardware::SensorData& sensorData1, const Hardware::SensorData& sensorData2, double tau) noexcept
    {
      return sensorData1 * (1.0 - tau) + sensorData2 * tau;
    }
  };
}  // namespace uavpc::Utils

#endif
