#ifndef UAVPC_HARDWARE_Mpu6050_OPTIONS_HPP
#define UAVPC_HARDWARE_Mpu6050_OPTIONS_HPP

#include "uavpc/Hardware/AccelerometerRange.hpp"
#include "uavpc/Hardware/GyroscopeRange.hpp"
#include "uavpc/Hardware/SensorData.hpp"

namespace uavpc::Hardware
{
  using HWAccelerometerRange = Hardware::AccelerometerRange;
  using HWGyroscopeRange = Hardware::GyroscopeRange;

  /** @class Mpu6050Options
   *  @brief Configuration options for an Mpu6050 instance.
   *
   * Contains the register addresses needed for basic operation of the MPU-6050 MEMS, as described by its Register Map.
   * It also provides the ranges for both the accelerometer and the gyroscope.
   */
  class Mpu6050Options
  {
   public:
    Mpu6050Options() = default;

    /** @brief Initializes an Mpu6050Options instance with the given accelerometer and gyroscope ranges.
     *  @param[in] accelerometerRange The value of the accelerometer range (ie: G2, G4, G8 etc.).
     *  @param[in] gyroscopeRange The value of the gyroscope range (ie: DEGS250, DEGS500, DEGS1000 etc.).
     */
    constexpr explicit Mpu6050Options(HWAccelerometerRange::Value accelerometerRange, HWGyroscopeRange::Value gyroscopeRange)
        : AccelerometerRange(accelerometerRange),
          GyroscopeRange(gyroscopeRange)
    {
    }

    HWAccelerometerRange AccelerometerRange = HWAccelerometerRange(HWAccelerometerRange::G4);
    HWGyroscopeRange GyroscopeRange = HWGyroscopeRange(HWGyroscopeRange::DEGS500);

    bool WithCalibration = true;
    std::size_t NoCalibrationIterations = Defaults::NoCalibrationIterations;
    SensorData AccelerometerOffset = SensorData();
    SensorData GyroscopeOffset = SensorData();

    std::uint8_t PowerRegister = Defaults::PowerRegister;
    std::uint8_t PowerRegisterValue = Defaults::PowerRegisterValue;
    std::uint8_t DlpfRegister = Defaults::DlpfRegister;
    std::uint8_t DlpfRegisterValue = Defaults::DlpfRegisterValue;
    std::uint8_t SampleRateRegister = Defaults::SampleRateRegister;
    std::uint8_t SampleRateRegisterValue = Defaults::SampleRateRegisterValue;

    std::uint8_t AccelConfigRegister = Defaults::AccelConfigRegister;
    std::uint8_t AccelXRegisterHigh = Defaults::AccelXRegisterHigh;
    std::uint8_t AccelXRegisterLow = Defaults::AccelXRegisterLow;
    std::uint8_t AccelYRegisterHigh = Defaults::AccelYRegisterHigh;
    std::uint8_t AccelYRegisterLow = Defaults::AccelYRegisterHigh;
    std::uint8_t AccelZRegisterHigh = Defaults::AccelZRegisterHigh;
    std::uint8_t AccelZRegisterLow = Defaults::AccelZRegisterHigh;

    std::uint8_t GyroConfigRegister = Defaults::GyroConfigRegister;
    std::uint8_t GyroXRegisterHigh = Defaults::GyroXRegisterHigh;
    std::uint8_t GyroXRegisterLow = Defaults::GyroXRegisterLow;
    std::uint8_t GyroYRegisterHigh = Defaults::GyroYRegisterHigh;
    std::uint8_t GyroYRegisterLow = Defaults::GyroYRegisterHigh;
    std::uint8_t GyroZRegisterHigh = Defaults::GyroZRegisterHigh;
    std::uint8_t GyroZRegisterLow = Defaults::GyroZRegisterHigh;

    struct Defaults
    {
      static constexpr std::size_t NoCalibrationIterations = 1000U;

      static constexpr std::uint8_t PowerRegister = 0x6b;
      static constexpr std::uint8_t PowerRegisterValue = 0b00000000;
      static constexpr std::uint8_t DlpfRegister = 0x1a;
      static constexpr std::uint8_t DlpfRegisterValue = 0b00000110;
      static constexpr std::uint8_t SampleRateRegister = 0x19;
      static constexpr std::uint8_t SampleRateRegisterValue = 0b00001001;

      static constexpr std::uint8_t AccelConfigRegister = 0x1c;
      static constexpr std::uint8_t AccelXRegisterHigh = 0x3b;
      static constexpr std::uint8_t AccelXRegisterLow = 0x3c;
      static constexpr std::uint8_t AccelYRegisterHigh = 0x3d;
      static constexpr std::uint8_t AccelYRegisterLow = 0x3e;
      static constexpr std::uint8_t AccelZRegisterHigh = 0x3f;
      static constexpr std::uint8_t AccelZRegisterLow = 0x40;

      static constexpr std::uint8_t GyroConfigRegister = 0x1b;
      static constexpr std::uint8_t GyroXRegisterHigh = 0x43;
      static constexpr std::uint8_t GyroXRegisterLow = 0x44;
      static constexpr std::uint8_t GyroYRegisterHigh = 0x45;
      static constexpr std::uint8_t GyroYRegisterLow = 0x46;
      static constexpr std::uint8_t GyroZRegisterHigh = 0x47;
      static constexpr std::uint8_t GyroZRegisterLow = 0x48;
    };
  };
}  // namespace uavpc::Hardware

#endif
