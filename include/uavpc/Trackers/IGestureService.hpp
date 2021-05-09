#ifndef UAVPC_TRACKERS_IGESTURE_SERVICE_HPP_
#define UAVPC_TRACKERS_IGESTURE_SERVICE_HPP_

#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Trackers/Gesture.hpp"

#include <cstdint>

namespace uavpc::Trackers
{
  /** @interface IGestureService
   *  @brief Defines operations that handle gesture related tasks, such as creating
   * a gesture from an instance of uavpc::Hardware::SensorData.
   */
  class IGestureService
  {
   public:
    IGestureService() = default;
    IGestureService(const IGestureService&) = delete;
    IGestureService(IGestureService&&) = default;
    IGestureService& operator=(const IGestureService&) = delete;
    IGestureService& operator=(IGestureService&&) = delete;
    virtual ~IGestureService() = default;

    /** @brief Finds and returns all gestures detected from distances and angles.
     *  @param[in] distances The uavpc::Hardware::SensorData instance holding the distances for each axis.
     *  @param[in] angles The uavpc::Hardware::SensorData instance holding the angles for each axis.
     *  @returns An std::uint16_t containing the gestures detected from the given data.
     *
     * Using given distances and angles for each axis, checks each for significant movement indicating a
     * gesture. Gestures are saved in an std::uint16_t, by using the bitwise OR operation and values from
     * the uavpc::Trackers::Gesture enum.
     *
     * If no gestures where found, the resulting std::uint16_t will hold the value of uavpc::Trackers::Gesture::NONE.
     */
    [[nodiscard]] virtual std::uint16_t ParseGesturesFrom(
        const Hardware::SensorData& distances,
        const Hardware::SensorData& angles) const noexcept = 0;
  };
}  // namespace uavpc::Trackers

#endif
