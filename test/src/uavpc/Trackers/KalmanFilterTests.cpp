#include "uavpc/Trackers/KalmanFilter.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using Catch::Matchers::Floating::WithinAbsMatcher;

TEST_CASE("SetAngle works as expected.", "[single-file]")
{
  constexpr auto initAngle = 10.0F;
  auto sut = uavpc::Trackers::KalmanFilter();

  sut.SetAngle(initAngle);
  auto result = sut.GetAngle(0.0F, 0.0F, 0.0F);

  REQUIRE_THAT(result, WithinAbsMatcher(static_cast<double>(initAngle), 0.001));
}

TEST_CASE("GetAngle works as expected.", "[single-file]")
{
  constexpr auto initAngle = 10.0F;
  constexpr auto newAngle = 20.0F;
  constexpr auto expectedAngle = initAngle + (newAngle - initAngle) * ((initAngle * 1.0F) / (initAngle * 1.0F + 0.03F));
  auto sut = uavpc::Trackers::KalmanFilter();
  sut.SetAngle(initAngle);

  auto result = sut.GetAngle(newAngle, 0.0F, 1.0F);

  REQUIRE_THAT(result, WithinAbsMatcher(static_cast<double>(expectedAngle), 0.001));
}
