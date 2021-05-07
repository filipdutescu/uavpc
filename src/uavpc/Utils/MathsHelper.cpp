#include "uavpc/Utils/MathsHelper.hpp"

namespace uavpc::Utils
{
  Hardware::SensorData MathsHelper::ConvertToAngles(const Hardware::SensorData& sensorData) noexcept
  {
    auto result = Hardware::SensorData();

    result.X = (s_ConversionDegrees / PI) * std::atan2(sensorData.Z, sensorData.Y) - s_RotationDegrees;
    result.Y = (s_ConversionDegrees / PI) * std::atan2(sensorData.Z, sensorData.X) - s_RotationDegrees;
    result.Z = (s_ConversionDegrees / PI) * std::atan2(sensorData.Y, sensorData.X) - s_RotationDegrees;

    return result;
  }
}  // namespace uavpc::Utils
