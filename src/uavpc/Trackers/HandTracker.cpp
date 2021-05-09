#include "uavpc/Trackers/HandTracker.hpp"

#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Trackers/Gesture.hpp"
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
    static bool isFirstRun = true;
    auto startTime = clock::now();

    while (m_ShouldUpdate)
    {
      auto accelData = m_Mpu6050.GetAccelerometerData();
      auto gyroData = m_Mpu6050.GetGyroscopeData();

      auto distances = accelData * m_DeltaTime * 0.1;
      auto angles = Hardware::SensorData();

      auto accelAngles = Utils::MathsHelper::ConvertToAngles(accelData);
      auto gyroAngles = gyroData * m_DeltaTime;
      if (isFirstRun)
      {
        gyroAngles = accelAngles;
        gyroAngles.Z = 0;
        isFirstRun = false;
      }

      auto accelSum = std::abs(accelData.X) + std::abs(accelData.Y) + std::abs(accelData.Z);
      auto gyroSum = std::abs(gyroData.X) + std::abs(gyroData.Y) + std::abs(gyroData.Z);

      constexpr auto gyroAccelDiffThreshold = 5.0F;
      if (std::abs(gyroAngles.X - accelAngles.X) > gyroAccelDiffThreshold)
      {
        gyroAngles.X = accelAngles.X;
      }
      if (std::abs(gyroAngles.Y - accelAngles.Y) > gyroAccelDiffThreshold)
      {
        gyroAngles.Y = accelAngles.Y;
      }

      if (isAccelInsideThreshold(accelSum) && isGyroAboveThreshold(gyroSum))
      {
        constexpr auto tau = 0.05F;  // TODO: rename + var
        angles = gyroAngles * (1.0F - tau) + accelAngles * tau;
      }
      else if (isGyroAboveThreshold(gyroSum))
      {
        angles = gyroAngles;
      }
      else if (!isGyroAboveThreshold(gyroSum))
      {
        angles = accelAngles;
      }
      angles.Z = gyroAngles.Z;

      if (isAccelInsideThreshold(accelSum) || isGyroAboveThreshold(gyroSum))
      {
        updateAngles(angles);
      }
      if (isAccelInsideThreshold(accelSum))
      {
        updateDistances(distances);
      }

      auto endTime = clock::now();
      m_DeltaTime = static_cast<double>((endTime - startTime) / 1ms);
      startTime = clock::now();
    }
  }

  bool HandTracker::isAccelInsideThreshold(float accelSum)
  {
    return accelSum > 0.25F && accelSum < 1.0F;
  }

  bool HandTracker::isGyroAboveThreshold(float gyroSum)
  {
    return gyroSum > 0.3F;
  }

  void HandTracker::updateAngles(const Hardware::SensorData& angles) noexcept
  {
    while (!m_UpdaterMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    m_Angles.X = computeNewAxisValue(m_Angles.X, angles.X, s_MaximumAxisAngle);
    m_Angles.Y = computeNewAxisValue(m_Angles.Y, angles.Y, s_MaximumAxisAngle);
    m_Angles.Z = computeNewAxisValue(m_Angles.Z, angles.Z, s_MaximumAxisAngle);

    m_UpdaterMutex.unlock();
  }

  void HandTracker::updateDistances(const Hardware::SensorData& distances) noexcept
  {
    while (!m_UpdaterMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    m_Distances.X = computeNewAxisValue(m_Distances.X, distances.X, s_MaximumAxisDistance);
    m_Distances.Y = computeNewAxisValue(m_Distances.Y, distances.Y, s_MaximumAxisDistance);
    m_Distances.Z = computeNewAxisValue(m_Distances.Z, distances.Z, s_MaximumAxisDistance);

    m_UpdaterMutex.unlock();
  }

  float HandTracker::computeNewAxisValue(float axisValue, float axisChangeValue, float maximumAxisValue) noexcept
  {
    auto result = 0.0F;
    if (isNewValueLowerThanMax(axisValue, axisChangeValue, maximumAxisValue))
    {
      result = axisValue + axisChangeValue;
      if (result > maximumAxisValue)
      {
        result = maximumAxisValue;
      }
      else if (result < -maximumAxisValue)
      {
        result = -maximumAxisValue;
      }
    }

    return result;
  }

  bool HandTracker::isNewValueLowerThanMax(float axisValue, float axisChangeValue, float maximumAxisValue) noexcept
  {
    return (axisValue < maximumAxisValue && axisChangeValue > 0.0F) ||
           (-maximumAxisValue < axisValue && axisChangeValue < 0.0F);
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

    // TODO: throw exception if cannot join after a number of tries.
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
    // TODO: throw exception if cannot lock after a number of tries.
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
    // TODO: throw exception if cannot lock after a number of tries.
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
