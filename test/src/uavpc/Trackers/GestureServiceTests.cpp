#include "uavpc/Trackers/Gesture.hpp"
#include "uavpc/Trackers/GestureService.hpp"
#include "uavpc/Hardware/SensorData.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ParseGesturesFrom no movement returns as expected.", "[single-file]")
{
  auto distances = uavpc::Hardware::SensorData();
  auto angles = uavpc::Hardware::SensorData();
  auto sut = uavpc::Trackers::GestureService();
  auto expectedGestures = 0U | uavpc::Trackers::Gesture::NONE;

  auto result = sut.ParseGesturesFrom(distances, angles);

  REQUIRE(result == expectedGestures);
}

TEST_CASE("ParseGesturesFrom distances valid returns as expected.", "[single-file]")
{
  constexpr auto value = 200.0F;
  auto distances = uavpc::Hardware::SensorData();
  distances.X = value;
  distances.Y = value;
  distances.Z = value;
  auto angles = uavpc::Hardware::SensorData();
  auto sut = uavpc::Trackers::GestureService();
  using Gesture = uavpc::Trackers::Gesture;
  auto expectedGestures = 0U | Gesture::FORWARD | Gesture::LEFT | Gesture::UP;

  auto result = sut.ParseGesturesFrom(distances, angles);

  REQUIRE(result == expectedGestures);
}

TEST_CASE("ParseGesturesFrom angles valid returns as expected.", "[single-file]")
{
  constexpr auto value = 100.0F;
  auto distances = uavpc::Hardware::SensorData();
  auto angles = uavpc::Hardware::SensorData();
  angles.X = value;
  angles.Y = value;
  angles.Z = value;
  auto sut = uavpc::Trackers::GestureService();
  using Gesture = uavpc::Trackers::Gesture;
  auto expectedGestures = 0U | Gesture::TILT_DOWN | Gesture::TILT_LEFT;

  auto result = sut.ParseGesturesFrom(distances, angles);

  REQUIRE(result == expectedGestures);
}

TEST_CASE("ParseGesturesFrom distances and angles valid returns as expected.", "[single-file]")
{
  constexpr auto value = 200.0F;
  auto distances = uavpc::Hardware::SensorData();
  distances.X = value;
  distances.Y = value;
  distances.Z = value;
  auto angles = uavpc::Hardware::SensorData();
  angles.X = value;
  angles.Y = value;
  angles.Z = value;
  auto sut = uavpc::Trackers::GestureService();
  using Gesture = uavpc::Trackers::Gesture;
  auto expectedGestures = 0U | Gesture::FORWARD | Gesture::LEFT | Gesture::UP | Gesture::TILT_DOWN | Gesture::TILT_LEFT;

  auto result = sut.ParseGesturesFrom(distances, angles);

  REQUIRE(result == expectedGestures);
}
