#include "uavpc/Hardware/Mpu6050.hpp"

#include "uavpc/Utils/MathsHelper.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace uavpc::Hardware
{
  void logCurrentCalibrationProgress(float currentPercentage, bool clearPrevious = true);

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
      logCurrentCalibrationProgress(
          static_cast<float>(i + 1U) / static_cast<float>(m_Options.NoCalibrationIterations) * 100.0F);
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
      std::cout << "\033[K\r";
    }
    std::cout << output;
  }

  Mpu6050::Mpu6050(std::shared_ptr<II2CService> I2Cservice, Mpu6050Options options)
      : m_I2CService(std::move(I2Cservice)),
        m_Options(std::move(options)),
        m_AccelOffset(),
        m_GyroOffset()
  {
    m_I2CService->WriteByteData(m_Options.PowerRegister, m_Options.PowerRegisterValue);
    m_I2CService->WriteByteData(m_Options.DlpfRegister, m_Options.DlpfRegisterValue);
    m_I2CService->WriteByteData(m_Options.SampleRateRegister, m_Options.SampleRateRegisterValue);
    m_I2CService->WriteByteData(m_Options.AccelConfigRegister, m_Options.AccelerometerRange.GetConfigRegisterValue());
    m_I2CService->WriteByteData(m_Options.GyroConfigRegister, m_Options.GyroscopeRange.GetConfigRegisterValue());

    auto [accelOffset, gyroOffset] = getInitialOffsets();
    m_AccelOffset = accelOffset;
    m_GyroOffset = gyroOffset;

    std::stringstream ss;
    ss << "\n\tInitial offsets:\n";
    ss << "Accelerometer offsets: " << m_AccelOffset.X << '\t' << m_AccelOffset.Y << '\t' << m_AccelOffset.Z << '\n';
    ss << "Gyroscope offsets: " << m_GyroOffset.X << '\t' << m_GyroOffset.Y << '\t' << m_GyroOffset.Z << '\n';

    std::cout << ss.str() << std::endl;
  }

  SensorData Mpu6050::GetAccelerometerData() const noexcept
  {
    auto data = SensorData();

    data.X = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.AccelXRegisterHigh)));
    data.Y = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.AccelYRegisterHigh)));
    data.Z = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.AccelZRegisterHigh)));

    return Utils::MathsHelper::Round(data / static_cast<float>(m_Options.AccelerometerRange) - m_AccelOffset);
  }

  SensorData Mpu6050::GetGyroscopeData() const noexcept
  {
    auto data = SensorData();

    data.X = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.GyroXRegisterHigh)));
    data.Y = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.GyroYRegisterHigh)));
    data.Z = static_cast<float>(static_cast<std::int16_t>(m_I2CService->ReadWordData(m_Options.GyroZRegisterHigh)));

    return Utils::MathsHelper::Round(data / static_cast<float>(m_Options.GyroscopeRange) - m_GyroOffset);
  }
}  // namespace uavpc::Hardware
