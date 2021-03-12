#ifndef UAVPC_HARDWARE_Mpu6050_HPP_
#define UAVPC_HARDWARE_Mpu6050_HPP_

#include "uavpc/Hardware/II2CService.hpp"
#include "uavpc/Hardware/Mpu6050Options.hpp"
#include "uavpc/Hardware/SensorData.hpp"

#include <cstdint>
#include <memory>
#include <tuple>

namespace uavpc::Hardware
{
  /** @class Mpu6050
   *  @brief Uused to handle communication with an MPU-6050 accelerometer & gyroscope.
   *
   *  The Mpu6050 class is used as an API for communicating via I2C with an MPU-6050 accelerometer & gyroscope.
   *  It allows for configuration of the MEMS and reading of its input data.
   */
  class Mpu6050
  {
    const std::unique_ptr<II2CService> m_I2CService;
    const Mpu6050Options m_Options;

    SensorData m_AccelOffset;
    SensorData m_GyroOffset;

    /** @brief Reads the value of a 16-bit register, by combining the its higher and upper register values.
     *  @param[in] highRegisterAddress The address of the higher register (meaning the one containing the 8 most
     * significant bits).
     *  @param[in] lowRegisterAddress The address of the lower register (meaning the one containing the 8 lower bits).
     *  @returns an std::int16_t containing the value of combined register, formed from the two provided.
     */
    [[nodiscard]] std::int16_t readCompleteRegister(std::uint8_t highRegisterAddress,
                                                    std::uint8_t lowRegisterAddress) const noexcept;

    /** @brief Retrieves the initial offset of the accelerometer.
     *  @returns An std::tuple containing the accelerometer and gyroscope offsets.
     */
    [[nodiscard]] std::tuple<SensorData, SensorData> getInitialOffsets() const noexcept;

   public:
    /** @brief Instantiate a new controller for an MPU-6050 found at a given address.
     * sensor.
     *  @param[in] II2CService A II2CService implementation to be used to communicate with the device through its bus.
     *  @param[in] options Optional. A Mpu6050Options instance, containing the configurations and settings for the sensor.
     *  @throws I2CUnsupportedException
     *  @throws InvalidAddressException
     */
    explicit Mpu6050(std::unique_ptr<II2CService>&& I2Cservice, Mpu6050Options options = Mpu6050Options());

    Mpu6050(const Mpu6050&) = delete;
    Mpu6050(Mpu6050&&) = delete;
    Mpu6050& operator=(const Mpu6050&) = delete;
    Mpu6050& operator=(Mpu6050&&) = delete;
    ~Mpu6050() = default;

    /** @brief Retrieves the current accelerometer data.
     *  @returns an uavpc::Hardware::SensorData instance, with the current accelerometer data.
     */
    [[nodiscard]] SensorData GetAccelerometerData() const noexcept;

    /** @brief Retrieves the current gyroscope data.
     *  @returns an uavpc::Hardware::SensorData instance, with the current gyroscope data.
     */
    [[nodiscard]] SensorData GetGyroscopeData() const noexcept;
  };
}  // namespace uavpc::Hardware

#endif