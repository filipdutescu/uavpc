#include "uavpc/Hardware/II2CService.hpp"
#include "uavpc/Hardware/Mpu6050.hpp"
#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Trackers/Gesture.hpp"
#include "uavpc/Trackers/HandTracker.hpp"
#include "uavpc/Trackers/IGestureService.hpp"

#include <memory>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using Catch::Matchers::Floating::WithinAbsMatcher;

class I2CServiceMock : public uavpc::Hardware::II2CService
{
 public:
  explicit I2CServiceMock() = default;

  [[nodiscard]] std::int32_t ReadByteData(std::uint8_t registerAddress) const noexcept override
  {
    return 0;
  }

  void WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept override
  {
  }

  [[nodiscard]] std::int32_t ReadWordData(std::uint8_t registerAddress) const noexcept override
  {
    return 0;
  }
};

class GestureServiceMock : public uavpc::Trackers::IGestureService
{
 public:
  [[nodiscard]] virtual std::uint16_t ParseGesturesFrom(
      const uavpc::Hardware::SensorData& distances,
      const uavpc::Hardware::SensorData& angles) const noexcept
  {
    return 0U | uavpc::Trackers::Gesture::BACKWARD;
  }
};

TEST_CASE("GetAngles returns as expected.", "[single-file]")
{
  const auto mpu6050 = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto sut = uavpc::Trackers::HandTracker(mpu6050, std::make_shared<GestureServiceMock>());
  const auto expectedResult = uavpc::Hardware::SensorData();

  const auto result = sut.GetAngles();

  REQUIRE_THAT(result.X, WithinAbsMatcher(static_cast<double>(expectedResult.X), 0.0001));
  REQUIRE_THAT(result.Y, WithinAbsMatcher(static_cast<double>(expectedResult.Y), 0.0001));
  REQUIRE_THAT(result.Z, WithinAbsMatcher(static_cast<double>(expectedResult.Z), 0.0001));
}

TEST_CASE("GetDistances returns as expected.", "[single-file]")
{
  const auto mpu6050 = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto sut = uavpc::Trackers::HandTracker(mpu6050, std::make_shared<GestureServiceMock>());
  const auto expectedResult = uavpc::Hardware::SensorData();

  const auto result = sut.GetDistances();

  REQUIRE_THAT(result.X, WithinAbsMatcher(static_cast<double>(expectedResult.X), 0.0001));
  REQUIRE_THAT(result.Y, WithinAbsMatcher(static_cast<double>(expectedResult.Y), 0.0001));
  REQUIRE_THAT(result.Z, WithinAbsMatcher(static_cast<double>(expectedResult.Z), 0.0001));
}

TEST_CASE("GetGestures returns as expected.", "[single-file]")
{
  const auto mpu6050 = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto sut = uavpc::Trackers::HandTracker(mpu6050, std::make_shared<GestureServiceMock>());
  const auto expectedResult = 0U | uavpc::Trackers::Gesture::BACKWARD;

  const auto result = sut.GetGestures();

  REQUIRE(result == expectedResult);
}
