#include "uavpc/Hardware/SensorData.hpp"
#include "uavpc/Utils/MathsHelper.hpp"
#include <cmath>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using Catch::Matchers::Floating::WithinAbsMatcher;

TEST_CASE("Round with default precision works as expected.", "[single-file]")
{
  constexpr auto expectedValue = 12.345F;
  constexpr auto initValue = 12.345678F;
  auto sensorData = uavpc::Hardware::SensorData();
  sensorData.X = initValue;
  sensorData.Y = initValue;
  sensorData.Z = initValue;

  const auto result = uavpc::Utils::MathsHelper::Round(sensorData);

  REQUIRE_THAT(result.X, WithinAbsMatcher(static_cast<double>(expectedValue), 0.0001));
  REQUIRE_THAT(result.Y, WithinAbsMatcher(static_cast<double>(expectedValue), 0.0001));
  REQUIRE_THAT(result.Z, WithinAbsMatcher(static_cast<double>(expectedValue), 0.0001));
}

TEST_CASE("Round with set precision works as expected.", "[single-file]")
{
  constexpr auto expectedValue4 = 12.3456F;
  constexpr auto expectedValue2 = 12.34F;
  constexpr auto initValue = 12.345678F;
  auto sensorData = uavpc::Hardware::SensorData();
  sensorData.X = initValue;
  sensorData.Y = initValue;
  sensorData.Z = initValue;

  const auto result4 = uavpc::Utils::MathsHelper::Round(sensorData, 4U);

  REQUIRE_THAT(result4.X, WithinAbsMatcher(static_cast<double>(expectedValue4), 0.00001));
  REQUIRE_THAT(result4.Y, WithinAbsMatcher(static_cast<double>(expectedValue4), 0.00001));
  REQUIRE_THAT(result4.Z, WithinAbsMatcher(static_cast<double>(expectedValue4), 0.00001));

  const auto result2 = uavpc::Utils::MathsHelper::Round(sensorData, 2U);

  REQUIRE_THAT(result2.X, WithinAbsMatcher(static_cast<double>(expectedValue2), 0.001));
  REQUIRE_THAT(result2.Y, WithinAbsMatcher(static_cast<double>(expectedValue2), 0.001));
  REQUIRE_THAT(result2.Z, WithinAbsMatcher(static_cast<double>(expectedValue2), 0.001));
}

TEST_CASE("ConvertToAngles returns as expected.", "[single-file]")
{
  constexpr auto radToDeg = 57.2957914331F;
  constexpr auto value = 123.45F;
  auto sensorData = uavpc::Hardware::SensorData();
  sensorData.X = value;
  sensorData.Y = value;
  sensorData.Z = value;
  auto expectedResult = uavpc::Hardware::SensorData();
  expectedResult.X = std::atan2(sensorData.Y, sensorData.Z) * radToDeg;
  expectedResult.Y = std::atan2(-sensorData.X, std::sqrt(sensorData.Y * sensorData.Y + sensorData.Z * sensorData.Z)) * radToDeg;
  
  const auto result = uavpc::Utils::MathsHelper::ConvertToAngles(sensorData);

  REQUIRE_THAT(result.X, WithinAbsMatcher(static_cast<double>(expectedResult.X), 0.001));
  REQUIRE_THAT(result.Y, WithinAbsMatcher(static_cast<double>(expectedResult.Y), 0.001));
  REQUIRE_THAT(result.Z, WithinAbsMatcher(static_cast<double>(expectedResult.Z), 0.001));
}
