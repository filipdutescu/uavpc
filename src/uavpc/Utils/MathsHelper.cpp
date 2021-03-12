#include "uavpc/Utils/MathsHelper.hpp"

namespace uavpc::Utils
{
  Hardware::SensorData MathsHelper::ConvertToAngles(Hardware::SensorData sensorData) noexcept
  {
    sensorData.X = (s_ConversionDegrees / PI) * std::atan2(sensorData.Z, sensorData.Y) - s_RotationDegrees;
    sensorData.Y = (s_ConversionDegrees / PI) * std::atan2(sensorData.Z, sensorData.X) - s_RotationDegrees;
    sensorData.Z = (s_ConversionDegrees / PI) * std::atan2(sensorData.Y, sensorData.X) - s_RotationDegrees;

    return sensorData;
  }
}  // namespace uavpc::Utils
