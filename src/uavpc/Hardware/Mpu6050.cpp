#include "uavpc/Hardware/Mpu6050.hpp"

#include "uavpc/Utils/MathsHelper.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace uavpc::Hardware
{
  void logCurrentCalibrationProgress(float currentPercentage, bool clearPrevious = true);

  std::int16_t Mpu6050::readCompleteRegister(std::uint8_t highRegisterAddress,
                                             std::uint8_t lowRegisterAddress) const noexcept
  {
    return static_cast<std::int16_t>(m_I2CService->ReadByteData(highRegisterAddress) << 8U |
                                     m_I2CService->ReadByteData(lowRegisterAddress));
  }

  std::tuple<SensorData, SensorData> Mpu6050::getInitialOffsets() const noexcept
  {
    SensorData accelData = SensorData();
    SensorData gyroData = SensorData();

    if (!m_Options.WithCalibration)
    {
      accelData = m_Options.AccelerometerOffset;
      gyroData = m_Options.GyroscopeOffset;

      return std::make_tuple(accelData, gyroData);
    }

    logCurrentCalibrationProgress(0.0F, false);
    for (std::size_t i = 0U; i < m_Options.NoCalibrationIterations; ++i)
    {
      logCurrentCalibrationProgress(static_cast<float>(i + 1U) / static_cast<float>(m_Options.NoCalibrationIterations) *
                                    100.0F);
      auto currentAccelData = GetAccelerometerData();
      auto currentGyroData = GetGyroscopeData();

      accelData += currentAccelData;
      gyroData += currentGyroData;
    }
    accelData /= static_cast<float>(m_Options.NoCalibrationIterations);
    gyroData /= static_cast<float>(m_Options.NoCalibrationIterations);

    return std::make_tuple(accelData, gyroData);
  }

  void logCurrentCalibrationProgress(float currentPercentage, bool clearPrevious)
  {
    std::stringstream ss;
    ss << "Calibrating MPU-6050... ";
    ss << (currentPercentage < 10.0F ? "  " : (currentPercentage < 100.0F ? " " : ""));
    ss << currentPercentage;
    ss << "%";
    std::string output = ss.str();

    if (clearPrevious)
    {
      // std::cout << std::string(output.length(), '\b');
      std::cout << "\033[2k\r";
    }
    std::cout << output;
  }

  Mpu6050::Mpu6050(std::unique_ptr<II2CService>&& I2Cservice, Mpu6050Options options)
      : m_I2CService(std::move(I2Cservice)), m_Options(std::move(options)), m_AccelOffset(), m_GyroOffset()
  {
    m_I2CService->WriteByteData(m_Options.PowerRegister, 0b00000000);
    m_I2CService->WriteByteData(m_Options.AccelConfigRegister, m_Options.AccelerometerRange.GetConfigRegisterValue());
    m_I2CService->WriteByteData(m_Options.GyroConfigRegister, m_Options.GyroscopeRange.GetConfigRegisterValue());

    auto [accelOffset, gyroOffset] = getInitialOffsets();
    m_AccelOffset = accelOffset;
    m_GyroOffset = gyroOffset;

    std::stringstream ss;
    ss << "\tInitial offsets:\n";
    ss << "Accelerometer offsets: " << m_AccelOffset.X << '\t' << m_AccelOffset.Y << '\t' << m_AccelOffset.Z << '\n';
    ss << "Gyroscope offsets: " << m_GyroOffset.X << '\t' << m_GyroOffset.Y << '\t' << m_GyroOffset.Z << '\n';
    ss << "\n";

    std::cout << ss.str() << std::endl;
  }

  SensorData Mpu6050::GetAccelerometerData() const noexcept
  {
    auto data = SensorData();

    data.X = static_cast<float>(readCompleteRegister(m_Options.AccelXRegisterHigh, m_Options.AccelXRegisterLow));
    data.Y = static_cast<float>(readCompleteRegister(m_Options.AccelYRegisterHigh, m_Options.AccelYRegisterLow));
    data.Z = static_cast<float>(readCompleteRegister(m_Options.AccelZRegisterHigh, m_Options.AccelZRegisterLow));

    return Utils::MathsHelper::Round((data - m_AccelOffset) / static_cast<float>(m_Options.AccelerometerRange));
  }

  SensorData Mpu6050::GetGyroscopeData() const noexcept
  {
    auto data = SensorData();

    data.X = static_cast<float>(readCompleteRegister(m_Options.GyroXRegisterHigh, m_Options.GyroXRegisterLow));
    data.Y = static_cast<float>(readCompleteRegister(m_Options.GyroYRegisterHigh, m_Options.GyroYRegisterLow));
    data.Z = static_cast<float>(readCompleteRegister(m_Options.GyroZRegisterHigh, m_Options.GyroZRegisterLow));

    return Utils::MathsHelper::Round((data - m_GyroOffset) / static_cast<float>(m_Options.GyroscopeRange));
  }
}  // namespace uavpc::Hardware
