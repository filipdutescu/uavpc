#include "uavpc/Hardware/GyroscopeRange.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace uavpc
{
  using Range = uavpc::Hardware::GyroscopeRange::Value;
}

namespace RegisterValue
{
  constexpr std::uint8_t DEGS250 = 0b00000000;
  constexpr std::uint8_t DEGS500 = 0b00001000;
  constexpr std::uint8_t DEGS1000 = 0b00010000;
  constexpr std::uint8_t DEGS2000 = 0b00011000;
}  // namespace RegisterValue

namespace SensitivityValue
{
  constexpr float DEGS250 = 131.0F;
  constexpr float DEGS500 = 65.5F;
  constexpr float DEGS1000 = 32.8F;
  constexpr float DEGS2000 = 16.4F;
}  // namespace SensitivityValue

TEST_CASE("GetConfigRegisterValue returns expected value.", "[single-file]")
{
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS250);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::DEGS250);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS500);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::DEGS500);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS1000);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::DEGS1000);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::DEGS2000);
  }
}

TEST_CASE("operator== returns as expected.", "[single-file]")
{
  const auto r1 = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);
  const auto r2 = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);

  const auto result = r1 == r2;

  REQUIRE(result);
}

TEST_CASE("operator!= returns as expected.", "[single-file]")
{
  const auto r1 = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);
  const auto r2 = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);

  const auto result = r1 != r2;

  REQUIRE_FALSE(result);
}

TEST_CASE("operator float() returns as expected.", "[single-file]")
{
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS250);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::DEGS250);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS500);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::DEGS500);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS1000);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::DEGS1000);
  }
  {
    const auto range = uavpc::Hardware::GyroscopeRange(uavpc::Range::DEGS2000);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::DEGS2000);
  }
}
