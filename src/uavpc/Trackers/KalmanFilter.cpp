#include "uavpc/Trackers/KalmanFilter.hpp"

#include <array>

namespace uavpc::Trackers
{
  KalmanFilter::KalmanFilter() noexcept
      : m_Angle(0.0F),
        m_Bias(0.0F),
        m_Rate(0.0F),
        m_ErrorCovariance({ std::array<float, 2>{ 0.0F, 0.0F }, std::array<float, 2>{ 0.0F, 0.0F } })
  {
  }

  float KalmanFilter::GetAngle(float newAngle, float newRate, float deltaTime) noexcept
  {
    m_Rate = newRate - m_Bias;
    m_Angle += m_Rate * deltaTime;

    m_ErrorCovariance[0][0] +=
        deltaTime * (deltaTime * m_ErrorCovariance[1][1] - m_ErrorCovariance[0][1] - m_ErrorCovariance[1][0] + m_Angle);
    m_ErrorCovariance[0][1] -= deltaTime * m_ErrorCovariance[1][1];
    m_ErrorCovariance[1][0] -= deltaTime * m_ErrorCovariance[1][1];
    m_ErrorCovariance[1][1] += m_Bias * deltaTime;

    auto estimatedError = m_ErrorCovariance[0][0] + s_InitialNoiseVariance;
    std::array<float, 2> kalmanGain{ m_ErrorCovariance[0][0] / estimatedError, m_ErrorCovariance[1][0] / estimatedError };

    float deltaAngle = newAngle - m_Angle;
    m_Angle += kalmanGain[0] * deltaAngle;
    m_Bias += kalmanGain[1] * deltaAngle;

    float errorCovariance00 = m_ErrorCovariance[0][0];
    float errorCovariance01 = m_ErrorCovariance[0][1];

    m_ErrorCovariance[0][0] -= kalmanGain[0] * errorCovariance00;
    m_ErrorCovariance[0][1] -= kalmanGain[0] * errorCovariance01;
    m_ErrorCovariance[1][0] -= kalmanGain[1] * errorCovariance00;
    m_ErrorCovariance[1][1] -= kalmanGain[1] * errorCovariance01;

    return m_Angle;
  }

  void KalmanFilter::SetAngle(float angle) noexcept
  {
    m_Angle = angle;
  }
}  // namespace uavpc::Trackers
