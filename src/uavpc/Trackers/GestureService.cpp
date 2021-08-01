#include "uavpc/Trackers/GestureService.hpp"

#include <cmath>

namespace uavpc::Trackers
{
  void GestureService::setTilts(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    setTiltDown(gestures, angles);
    setTiltUp(gestures, angles);
    setTiltLeft(gestures, angles);
    setTiltRight(gestures, angles);
  }

  void GestureService::setTiltLeft(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    if (angles.X >= s_TiltLeftRightThreshold)
    {
      gestures |= Gesture::TILT_LEFT;
    }
  }

  void GestureService::setTiltRight(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    if (angles.X <= -s_TiltLeftRightThreshold)
    {
      gestures |= Gesture::TILT_RIGHT;
    }
  }

  void GestureService::setTiltUp(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    if (angles.Y >= s_TiltUpDownThreshold)
    {
      gestures |= Gesture::TILT_DOWN;
    }
  }

  void GestureService::setTiltDown(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept
  {
    if (angles.Y <= -s_TiltUpDownThreshold)
    {
      gestures |= Gesture::TILT_UP;
    }
  }

  void GestureService::setDirections(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    setForward(gestures, distances);
    setBackward(gestures, distances);
    setLeft(gestures, distances);
    setRight(gestures, distances);
    setUp(gestures, distances);
    setDown(gestures, distances);
  }

  void GestureService::setForward(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.X > s_ForwardBackwardThreshold)
    {
      gestures |= Gesture::FORWARD;
    }
  }

  void GestureService::setBackward(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.X < -s_ForwardBackwardThreshold)
    {
      gestures |= Gesture::BACKWARD;
    }
  }

  void GestureService::setLeft(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.Y > s_LeftRightThreshold)
    {
      gestures |= Gesture::LEFT;
    }
  }

  void GestureService::setRight(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.Y < -s_LeftRightThreshold)
    {
      gestures |= Gesture::RIGHT;
    }
  }

  void GestureService::setUp(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.Z > s_UpDownThreshold)
    {
      gestures |= Gesture::UP;
    }
  }

  void GestureService::setDown(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept
  {
    if (distances.Z < -s_UpDownThreshold)
    {
      gestures |= Gesture::DOWN;
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
