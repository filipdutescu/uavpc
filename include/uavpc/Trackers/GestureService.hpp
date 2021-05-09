#ifndef UAVPC_TRACKERS_GESTURE_SERVICE_HPP_
#define UAVPC_TRACKERS_GESTURE_SERVICE_HPP_

#include "uavpc/Trackers/IGestureService.hpp"

#include <cstdint>

namespace uavpc::Trackers
{
  /** @class GestureService
   *  @implements IGestureService
   *  @copybrief uavpc::Trackers::IGestureService
   */
  class GestureService : public IGestureService
  {
    static constexpr float s_TiltLeftRightThreshold = 45.0F;
    static constexpr float s_TiltUpDownThreshold = 75.0F;
    static constexpr float s_ForwardBackwardThreshold = 4.0F;
    static constexpr float s_LeftRightThreshold = 4.0F;
    static constexpr float s_UpDownThreshold = 4.0F;

    static void setTilts(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;
    static void setTiltLeft(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;
    static void setTiltRight(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;
    static void setTiltUp(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;
    static void setTiltDown(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;

    static void setDirections(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setForward(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setBackward(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setLeft(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setRight(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setUp(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;
    static void setDown(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;

   public:
    GestureService() = default;
    GestureService(const GestureService&) = delete;
    GestureService(GestureService&&) = delete;
    GestureService& operator=(const GestureService&) = delete;
    GestureService& operator=(GestureService&&) = delete;
    ~GestureService() override = default;

    /** @copydoc uavpc::Trackers::IGestureService::ParseGesturesFrom()
     */
    [[nodiscard]] std::uint16_t ParseGesturesFrom(const Hardware::SensorData& distances, const Hardware::SensorData& angles)
        const noexcept override;
  };
}  // namespace uavpc::Trackers

#endif
