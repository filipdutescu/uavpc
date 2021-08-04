#ifndef UAVPC_HARDWARE_SENSOR_DATA_HPP_
#define UAVPC_HARDWARE_SENSOR_DATA_HPP_

#include <cmath>
#include <cstdint>
#include <ostream>

namespace uavpc::Hardware
{
  /** @class SensorData
   *
   * Holds an sensor's X, Y and Z values.
   */
  class SensorData
  {
   public:
    float X;
    float Y;
    float Z;

    SensorData() = default;
    constexpr SensorData(const SensorData&) = default;
    constexpr SensorData(SensorData&&) = default;
    ~SensorData() = default;
    constexpr SensorData& operator=(SensorData&&) = default;

    /** @brief Copies the values of another SensorData instance into the current one.
     *  @returns The current object.
     */
    constexpr SensorData& operator=(const SensorData& other) noexcept
    {
      if (this != &other)
      {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
      }

      return *this;
    }

    /** @brief Add the value of another SensorData instance to the current one.
     *  @returns The current object.
     */
    constexpr SensorData& operator+=(const SensorData& other) noexcept
    {
      if (this != &other)
      {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
      }

      return *this;
    }

    /** @brief Sum the value of another SensorData instance to the current one.
     *  @returns A new SensorData instance containing the addition result.
     */
    constexpr SensorData operator+(const SensorData& other) const noexcept
    {
      auto sensorData = SensorData(*this);

      sensorData.X += other.X;
      sensorData.Y += other.Y;
      sensorData.Z += other.Z;

      return sensorData;
    }

    /** @brief Subtract the value of another SensorData instance from the current one.
     *  @returns A new SensorData instance containing the subtraction result.
     */
    constexpr SensorData operator-(const SensorData& other) const noexcept
    {
      auto sensorData = SensorData(*this);

      sensorData.X -= other.X;
      sensorData.Y -= other.Y;
      sensorData.Z -= other.Z;

      return sensorData;
    }

    /** @brief Divide the current sensor data by a given value.
     *  @returns The current object.
     */
    constexpr SensorData& operator/=(float value) noexcept
    {
      if (value != 0.0F)
      {
        X /= value;
        Y /= value;
        Z /= value;
      }

      return *this;
    }

    /** @brief Divide the current sensor data by a given value.
     *  @returns The a new SensorData instance containing the division result.
     */
    constexpr SensorData operator/(float value) const noexcept
    {
      auto sensorData = SensorData(*this);

      if (value != 0.0F)
      {
        sensorData.X /= value;
        sensorData.Y /= value;
        sensorData.Z /= value;
      }

      return sensorData;
    }

    /** @brief Multiply the current sensor data by a given value.
     *  @returns The a new SensorData instance containing the multiplication result.
     */
    constexpr SensorData operator*(double value) const noexcept
    {
      auto sensorData = SensorData(*this);
      auto floatValue = static_cast<float>(value);

      sensorData.X *= floatValue;
      sensorData.Y *= floatValue;
      sensorData.Z *= floatValue;

      return sensorData;
    }
  };

  /** @brief Write the uavpc::Hardware::SensorData values to the received std::ostream.
   *  @returns The std::ostream instance received as a parameter.
   */
  inline std::ostream& operator<<(std::ostream& out, const SensorData& sensorData)
  {
    out << "x: " << sensorData.X << ", y: " << sensorData.Y << ", z: " << sensorData.Z;

    return out;
  }
}  // namespace uavpc::Hardware

#endif
