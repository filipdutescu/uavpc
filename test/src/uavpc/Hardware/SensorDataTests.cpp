#include "uavpc/Hardware/SensorData.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("operator= works as expected.", "[single-file]")
{
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = 123.45F;
  expectedSensorData.Y = 123.45F;
  expectedSensorData.Z = 123.45F;

  auto sut = expectedSensorData;

  REQUIRE(sut.X == expectedSensorData.X);
  REQUIRE(sut.Y == expectedSensorData.Y);
  REQUIRE(sut.Z == expectedSensorData.Z);
}

TEST_CASE("operator+= works as expected.", "[single-file]")
{
  constexpr auto value = 123.45F;
  auto sut = uavpc::Hardware::SensorData();
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = sut.X + value;
  expectedSensorData.Y = sut.Y + value;
  expectedSensorData.Z = sut.Z + value;
  auto add = uavpc::Hardware::SensorData();
  add.X = value;
  add.Y = value;
  add.Z = value;

  sut += add;

  REQUIRE(sut.X == expectedSensorData.X);
  REQUIRE(sut.Y == expectedSensorData.Y);
  REQUIRE(sut.Z == expectedSensorData.Z);
}

TEST_CASE("operator+ works as expected.", "[single-file]")
{
  constexpr auto value = 123.45F;
  auto sut = uavpc::Hardware::SensorData();
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = sut.X + value;
  expectedSensorData.Y = sut.Y + value;
  expectedSensorData.Z = sut.Z + value;
  auto add = uavpc::Hardware::SensorData();
  add.X = value;
  add.Y = value;
  add.Z = value;

  auto result = sut + add;

  REQUIRE(result.X == expectedSensorData.X);
  REQUIRE(result.Y == expectedSensorData.Y);
  REQUIRE(result.Z == expectedSensorData.Z);
}

TEST_CASE("operator- works as expected.", "[single-file]")
{
  constexpr auto value = 123.45F;
  auto sut = uavpc::Hardware::SensorData();
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = sut.X - value;
  expectedSensorData.Y = sut.Y - value;
  expectedSensorData.Z = sut.Z - value;
  auto diff = uavpc::Hardware::SensorData();
  diff.X = value;
  diff.Y = value;
  diff.Z = value;

  auto result = sut - diff;

  REQUIRE(result.X == expectedSensorData.X);
  REQUIRE(result.Y == expectedSensorData.Y);
  REQUIRE(result.Z == expectedSensorData.Z);
}

TEST_CASE("operator/= works as expected.", "[single-file]")
{
  constexpr auto value = 123.45F;
  auto sut = uavpc::Hardware::SensorData();
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = sut.X / value;
  expectedSensorData.Y = sut.Y / value;
  expectedSensorData.Z = sut.Z / value;

  sut /= value;

  REQUIRE(sut.X == expectedSensorData.X);
  REQUIRE(sut.Y == expectedSensorData.Y);
  REQUIRE(sut.Z == expectedSensorData.Z);
}

TEST_CASE("operator/ works as expected.", "[single-file]")
{
  constexpr auto value = 123.45F;
  auto sut = uavpc::Hardware::SensorData();
  auto expectedSensorData = uavpc::Hardware::SensorData();
  expectedSensorData.X = sut.X / value;
  expectedSensorData.Y = sut.Y / value;
  expectedSensorData.Z = sut.Z / value;

  auto result = sut / value;

  REQUIRE(result.X == expectedSensorData.X);
  REQUIRE(result.Y == expectedSensorData.Y);
  REQUIRE(result.Z == expectedSensorData.Z);
}
