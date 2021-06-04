#ifndef UAVPC_TRACKERS_KALMAN_FILTER_HPP_
#define UAVPC_TRACKERS_KALMAN_FILTER_HPP_

#include <array>

namespace uavpc::Trackers
{
  /** @class KalmanFilter
   *  @brief Defines a Kalman filter for the value of an axis.
   */
  class KalmanFilter
  {
    static constexpr float s_InitialAngle = 0.001F;
    static constexpr float s_InitialBias = 0.003F;
    static constexpr float s_InitialNoiseVariance = 0.03F;

    float m_Angle;
    float m_Bias;
    float m_Rate;

    std::array<std::array<float, 2>, 2> m_ErrorCovariance;

   public:
    KalmanFilter() noexcept;

    /** @brief Computes and returns the Kalman angle, given a new angle, rate and the delta time.
     *  @param[in] newAngle A float value representing the new angle value.
     *  @param[in] newRate A float value representing the new rate value.
     *  @param[in] deltaTime A float value representing the delta time, from the previous angle measurement.
     *  @returns A float value representing the Kalman angle computed from the given data.
     */
    [[nodiscard]] float GetAngle(float newAngle, float newRate, float deltaTime) noexcept;

    /** @brief Sets the starting angle for the Kalman filter.
     *  @param[in] angle A float value representing the initial angle of the Kalman filter.
     */
    void SetAngle(float angle) noexcept;
  };
}  // namespace uavpc::Trackers

#endif
