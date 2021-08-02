#include "uavpc/Trackers/HandTracker.hpp"

#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Trackers/Gesture.hpp"
#include "uavpc/Trackers/KalmanFilter.hpp"
#include "uavpc/Utils/MathsHelper.hpp"

#include <cmath>
#include <memory>
#include <thread>
#include <utility>

namespace uavpc::Trackers
{
  using clock = std::chrono::high_resolution_clock;

  void HandTracker::updateTracker() noexcept
  {
    auto kalmanX = KalmanFilter();
    auto kalmanY = KalmanFilter();

    m_Angles = Utils::MathsHelper::ConvertToAngles(m_Mpu6050.GetRawAccelerometerData());
    kalmanX.SetAngle(m_Angles.X);
    kalmanY.SetAngle(m_Angles.Y);

    auto startTime = clock::now();
    while (m_ShouldUpdate)
    {
      auto accelData = m_Mpu6050.GetRawAccelerometerData();
      auto gyroData = m_Mpu6050.GetRawGyroscopeData();

      while (!m_UpdaterMutex.try_lock())
      {
        std::this_thread::sleep_for(s_MutexTryLockWaitTime);
      }

      auto kalmanAngles = m_Angles;

      m_UpdaterMutex.unlock();

      auto gyroAngles = gyroData / static_cast<float>(m_Mpu6050.GetOptions().GyroscopeRange);
      auto accelAngles = Utils::MathsHelper::ConvertToAngles(accelData);

      if ((accelAngles.X < -90 && kalmanAngles.X > 90) || (accelAngles.X > 90 && kalmanAngles.X < -90))
      {
        kalmanX.SetAngle(accelAngles.X);
        kalmanAngles.X = accelAngles.X;
      }
      else
      {
        kalmanAngles.X = kalmanX.GetAngle(accelAngles.X, gyroAngles.X, static_cast<float>(m_DeltaTime));
      }

      if (std::abs(kalmanAngles.X) > 90)
      {
        gyroAngles.Y = -gyroAngles.Y;
      }
      kalmanAngles.Y = kalmanY.GetAngle(accelAngles.Y, gyroAngles.Y, static_cast<float>(m_DeltaTime));

      updateAngles(kalmanAngles);

      auto endTime = clock::now();
      m_DeltaTime = static_cast<double>((endTime - startTime) / 1ms);
      startTime = clock::now();
    }
  }

  void HandTracker::updateAngles(const Hardware::SensorData& angles) noexcept
  {
    while (!m_UpdaterMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    m_Angles = angles;

    m_UpdaterMutex.unlock();
  }

  HandTracker::HandTracker(Hardware::Mpu6050 mpu6050, std::shared_ptr<IGestureService> gestureService) noexcept
      : m_Mpu6050(std::move(mpu6050)),
        m_GestureService(std::move(gestureService)),
        m_Angles(),
        m_Distances(),
        m_DeltaTime(s_InitialDeltaTime),
        m_UpdaterMutex(),
        m_ShouldUpdate(true)
  {
    m_UpdaterThread = std::thread(&HandTracker::updateTracker, this);
  }

  HandTracker::HandTracker(const HandTracker& other) noexcept
      : m_Mpu6050(other.m_Mpu6050),
        m_GestureService(other.m_GestureService),
        m_Angles(other.m_Angles),
        m_Distances(other.m_Distances),
        m_DeltaTime(s_InitialDeltaTime),
        m_UpdaterMutex(),
        m_ShouldUpdate(true)
  {
    m_UpdaterThread = std::thread(&HandTracker::updateTracker, this);
  }

  HandTracker::~HandTracker() noexcept
  {
    m_ShouldUpdate = false;

    while (!m_UpdaterThread.joinable())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    if (m_UpdaterThread.joinable())
    {
      m_UpdaterThread.join();
    }
    m_UpdaterMutex.unlock();
  }

  Hardware::SensorData HandTracker::GetAngles() noexcept
  {
    while (!m_UpdaterMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    auto angles = m_Angles;
    m_UpdaterMutex.unlock();

    return angles;
  }

  Hardware::SensorData HandTracker::GetDistances() noexcept
  {
    while (!m_UpdaterMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    auto distances = m_Distances;
    m_UpdaterMutex.unlock();

    return distances;
  }

  std::uint16_t HandTracker::GetGestures() noexcept
  {
    auto angles = GetAngles();
    auto distances = GetDistances();

    return m_GestureService->ParseGesturesFrom(distances, angles);
  }
}  // namespace uavpc::Trackers
