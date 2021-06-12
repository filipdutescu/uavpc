#include "uavpc/Utils/MathsHelper.hpp"

namespace uavpc::Utils
{
  Hardware::SensorData MathsHelper::ConvertToAngles(const Hardware::SensorData& sensorData) noexcept
  {
    auto result = Hardware::SensorData();

    result.X = std::atan2(sensorData.Y, sensorData.Z) * s_RadToDeg;
    result.Y = std::atan2(-sensorData.X, std::sqrt(sensorData.Y * sensorData.Y + sensorData.Z * sensorData.Z)) * s_RadToDeg;
    result.Z = 0.0F;

    return result;
  }
}  // namespace uavpc::Utils
