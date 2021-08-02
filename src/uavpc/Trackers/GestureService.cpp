#include "uavpc/Trackers/GestureService.hpp"

#include <cmath>

namespace uavpc::Trackers
{
  void GestureService::setTilts(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    setGesture(gestures, angles.Y, s_TiltUpDownThreshold, Gesture::TILT_DOWN);
    setGesture(gestures, -angles.Y, s_TiltUpDownThreshold, Gesture::TILT_UP);
    setGesture(gestures, angles.X, s_TiltLeftRightThreshold, Gesture::TILT_LEFT);
    setGesture(gestures, -angles.X, s_TiltLeftRightThreshold, Gesture::TILT_RIGHT);
  }

  void GestureService::setDirections(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    setGesture(gestures, distances.X, s_ForwardBackwardThreshold, Gesture::FORWARD);
    setGesture(gestures, -distances.X, s_ForwardBackwardThreshold, Gesture::BACKWARD);
    setGesture(gestures, -distances.Z, s_UpDownThreshold, Gesture::DOWN);
    setGesture(gestures, distances.Z, s_UpDownThreshold, Gesture::UP);
    setGesture(gestures, distances.Y, s_LeftRightThreshold, Gesture::LEFT);
    setGesture(gestures, -distances.Y, s_LeftRightThreshold, Gesture::RIGHT);
  }

  void GestureService::setGesture(std::uint16_t& gestures, float value, float threshold, Gesture gesture) noexcept
  {
    if (value >= threshold)
    {
      gestures |= gesture;
    }
  }

  std::uint16_t GestureService::ParseGesturesFrom(const Hardware::SensorData& distances, const Hardware::SensorData& angles)
      const noexcept
  {
    auto gestures = static_cast<std::uint16_t>(Gesture::NONE);

    setTilts(gestures, angles);
    setDirections(gestures, distances);

    return gestures;
  }
}  // namespace uavpc::Trackers
