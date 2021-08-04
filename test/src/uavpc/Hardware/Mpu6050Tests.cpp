#include "uavpc/Hardware/II2CService.hpp"
#include "uavpc/Hardware/Mpu6050.hpp"

#include <memory>
#include <queue>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using Catch::Matchers::Floating::WithinAbsMatcher;

std::queue<std::uint8_t> commandQueue;
class I2CServiceMock : public uavpc::Hardware::II2CService
{
  bool m_PopCommandsOnRead;
  bool m_PersistWrite;

 public:
  explicit I2CServiceMock(bool persistWrite = false, bool popCommandsOnRead = true)
      : m_PersistWrite(persistWrite),
        m_PopCommandsOnRead(popCommandsOnRead)
  {
  }

  [[nodiscard]] std::int32_t ReadByteData(std::uint8_t registerAddress) const noexcept override
  {
    if (commandQueue.empty())
    {
      return 0;
    }

    auto front = commandQueue.front();
    if (m_PopCommandsOnRead)
    {
      commandQueue.pop();
    }

    return front;
  }

  void WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept override
  {
    if (m_PersistWrite)
    {
      commandQueue.push(value);
    }
  }

  [[nodiscard]] std::int32_t ReadWordData(std::uint8_t registerAddress) const noexcept override
  {
    if (commandQueue.empty())
    {
      return 0;
    }

    auto front = commandQueue.front();
    if (m_PopCommandsOnRead)
    {
      commandQueue.pop();
    }

    return front;
  }
};

TEST_CASE("Constructor sets up MPU 6050.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>(true, false));
  const auto opt = sut.GetOptions();

  REQUIRE(commandQueue.size() == 5U);
  REQUIRE(commandQueue.front() == opt.PowerRegisterValue);
  commandQueue.pop();
  REQUIRE(commandQueue.front() == opt.DlpfRegisterValue);
  commandQueue.pop();
  REQUIRE(commandQueue.front() == opt.SampleRateRegisterValue);
  commandQueue.pop();
  REQUIRE(commandQueue.front() == opt.AccelerometerRange.GetConfigRegisterValue());
  commandQueue.pop();
  REQUIRE(commandQueue.front() == opt.GyroscopeRange.GetConfigRegisterValue());
}

TEST_CASE("GetAccelerometerOffset returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetAccelerometerOffset();

  REQUIRE_THAT(result.X, WithinAbsMatcher(static_cast<double>(expectedResult.X), 0.01));
  REQUIRE_THAT(result.Y, WithinAbsMatcher(static_cast<double>(expectedResult.Y), 0.01));
  REQUIRE_THAT(result.Z, WithinAbsMatcher(static_cast<double>(expectedResult.Z), 0.01));
}

TEST_CASE("GetGyroscopeOffset returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetGyroscopeOffset();

  REQUIRE(result.X == expectedResult.X);
  REQUIRE(result.Y == expectedResult.Y);
  REQUIRE(result.Z == expectedResult.Z);
}

TEST_CASE("GetRawAccelerometerData returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetRawAccelerometerData();

  REQUIRE(result.X == expectedResult.X);
  REQUIRE(result.Y == expectedResult.Y);
  REQUIRE(result.Z == expectedResult.Z);
}

TEST_CASE("GetRawGyroscopeData returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetRawGyroscopeData();

  REQUIRE(result.X == expectedResult.X);
  REQUIRE(result.Y == expectedResult.Y);
  REQUIRE(result.Z == expectedResult.Z);
}

TEST_CASE("GetAccelerometerData returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetAccelerometerData();

  REQUIRE(result.X == expectedResult.X);
  REQUIRE(result.Y == expectedResult.Y);
  REQUIRE(result.Z == expectedResult.Z);
}

TEST_CASE("GetGyroscopeData returns as expected.", "[single-file]")
{
  const auto sut = uavpc::Hardware::Mpu6050(std::make_shared<I2CServiceMock>());
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = 0.0F;
  expectedResult.Y = 0.0F;
  expectedResult.Z = 0.0F;

  const auto result = sut.GetGyroscopeData();

  REQUIRE(result.X == expectedResult.X);
  REQUIRE(result.Y == expectedResult.Y);
  REQUIRE(result.Z == expectedResult.Z);
}
