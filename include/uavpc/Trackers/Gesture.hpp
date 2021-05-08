#ifndef UAVPC_TRACKERS_GESTURE_HPP_
#define UAVPC_TRACKERS_GESTURE_HPP_

#include <cstdint>

namespace uavpc::Trackers
{
  /** @enum Gesture
   *  @brief An enumeration containing the supported gestures that can be tracked.
   */
  enum class Gesture : std::uint16_t
  {
    NONE = 0b0000000000,
    UP = 0b0000000001,
    DOWN = 0b0000000010,
    LEFT = 0b0000000100,
    RIGHT = 0b0000001000,
    FORWARD = 0b0000010000,
    BACKWARD = 0b0000100000,
    TILT_UP = 0b0001000000,
    TILT_DOWN = 0b0010000000,
    TILT_LEFT = 0b0100000000,
    TILT_RIGHT = 0b1000000000,
  };

  constexpr int operator|(const std::uint16_t& uint, const Gesture& gesture)
  {
    return uint | static_cast<std::uint16_t>(gesture);
  }

  constexpr void operator|=(std::uint16_t& uint, const Gesture& gesture)
  {
    uint |= static_cast<std::uint16_t>(gesture);
  }

  constexpr int operator&(const std::uint16_t& uint, const Gesture& gesture)
  {
    return uint & static_cast<std::uint16_t>(gesture);
  }
}  // namespace uavpc::Trackers

#endif
