#ifndef UAVPC_TRACKERS_HAND_TRACKER_HPP_
#define UAVPC_TRACKERS_HAND_TRACKER_HPP_

#include "uavpc/Hardware/II2CService.hpp"
#include "uavpc/Hardware/Mpu6050.hpp"
#include "uavpc/Hardware/Mpu6050Options.hpp"
#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Trackers/IGestureService.hpp"

#include <chrono>
#include <memory>
#include <mutex>
#include <thread>

namespace uavpc::Trackers
{
  using namespace std::chrono_literals;

  /** @class HandTracker
   *  @brief Class used for tracking position, rotation and gestures of a hand.
   *
   * Class used for tracking position, rotation and gestures of a hand. It uses the
   * uavpc::Hardware::Mpu6050 to read accelerometer and gyroscope data, continuously
   * updating the distance and angle of each axis.
   */
  class HandTracker
  {
    Hardware::Mpu6050 m_Mpu6050;
    std::shared_ptr<IGestureService> m_GestureService;

    Hardware::SensorData m_Angles;
    Hardware::SensorData m_Distances;

    double m_DeltaTime;
    std::thread m_UpdaterThread;
    std::mutex m_UpdaterMutex;
    bool m_ShouldUpdate;

    static constexpr double s_InitialDeltaTime = 0.0009;
    static constexpr std::chrono::milliseconds s_MutexTryLockWaitTime = 5ms;

    static constexpr float s_MaximumAxisDistance = 5.0F;
    static constexpr float s_MaximumAxisAngle = 180.0F;

    /** @brief Method used to update the distance and angle of each axis.
     *
     * Reading the accelerometer and gyroscope data, it computes the current rotations
     * and distances traveled on each axis, through a loop used to compute the passed time.
     */
    void updateTracker() noexcept;

    /** @brief Used to check if the accelerometer values are inside the threshold indicating significant movement.
     *  @param[in] accelSum The sum of absolute values of each axis of the accelerometer.
     *  @returns A boolean value representing whether or not the accelerometer values indicate significant movement.
     */
    static bool isAccelInsideThreshold(float accelSum);

    /** @brief Used to check if the gyroscope values are above the threshold indicating significant movement.
     *  @param[in] gyroSum The sum of absolute values of each axis of the gyroscope.
     *  @returns A boolean value representing whether or not the gyroscope values indicate significant movement.
     */
    static bool isGyroAboveThreshold(float gyroSum);

    void updateAngles(const Hardware::SensorData& angles) noexcept;

    void updateDistances(const Hardware::SensorData& distances) noexcept;

    static float computeNewAxisValue(float axisValue, float axisChangeValue, float maximumAxisValue) noexcept;

    static bool isNewValueLowerThanMax(float axisValue, float axisChangeValue, float maximumAxisValue) noexcept;

   public:
    /** @brief Contructs a hand tracker using an MPU-6050.
     *  @param[in] mpu6050 A uavpc::Hardware::Mpu6050 instance used to gather accelerometer and gyroscope data.
     *  @param[in] gestureService A uavpc::Trackers::IGestureService instance used to handle gesture related
     * operations.
     *
     * Initializes a uavpc::Trackers::HandTracker using an MPU-6050 to gather accelerometer and gyroscope data.
     * It starts an updater thread, used to compute the distances and angles of the MEMS' axis.
     */
    explicit HandTracker(Hardware::Mpu6050 mpu6050, std::shared_ptr<IGestureService> gestureService) noexcept;

    HandTracker(const HandTracker& other) noexcept;
    HandTracker(HandTracker&& other) = delete;
    HandTracker& operator=(const HandTracker& other) = delete;
    HandTracker& operator=(HandTracker&& other) = delete;

    /** @brief Used to stop the updater thread and join it to the main thread.
     */
    ~HandTracker() noexcept;

    /** @brief Get the current angles from the origin for each gyroscope axis.
     *  @returns A uavpc::Hardware::SensorData instance containing the angles of each axis.
     */
    [[nodiscard]] Hardware::SensorData GetAngles() noexcept;

    /** @brief Get the current distances from the origin for each accelerometer axis.
     *  @returns A uavpc::Hardware::SensorData instance containing the distances from each axis' origin.
     */
    [[nodiscard]] Hardware::SensorData GetDistances() noexcept;

    /** @brief Get the current gestures.
     *  @returns An std::uint16_t containing the current gestures.
     *
     *  Get the current gestures, as a combination of uavpc::Trackers::Gesture values.
     */
    [[nodiscard]] std::uint16_t GetGestures() noexcept;
  };
}  // namespace uavpc::Trackers

#endif
