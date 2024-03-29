#ifndef UAVPC_TRACKERS_GESTURE_SERVICE_HPP_
#define UAVPC_TRACKERS_GESTURE_SERVICE_HPP_

#include "uavpc/Trackers/IGestureService.hpp"

#include <cstdint>

namespace uavpc::Trackers
{
  /** @class GestureService
   *  @implements uavpc::Trackers::IGestureService
   *  @copybrief uavpc::Trackers::IGestureService
   */
  class GestureService : public IGestureService
  {
    static constexpr float s_TiltLeftRightThreshold = 50.0F;
    static constexpr float s_TiltUpDownThreshold = 50.0F;
    static constexpr float s_ForwardBackwardThreshold = 4.0F;
    static constexpr float s_LeftRightThreshold = 4.0F;
    static constexpr float s_UpDownThreshold = 4.0F;

    static void setTilts(std::uint16_t& gestures, const Hardware::SensorData& angles) noexcept;

    static void setDirections(std::uint16_t& gestures, const Hardware::SensorData& distances) noexcept;

    static void setGesture(std::uint16_t& gestures, float value, float threshold, Gesture gesture) noexcept;

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
