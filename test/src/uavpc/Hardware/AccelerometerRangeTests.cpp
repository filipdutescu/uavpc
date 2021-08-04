#include "uavpc/Hardware/AccelerometerRange.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace uavpc
{
  using Range = uavpc::Hardware::AccelerometerRange::Value;
}

namespace RegisterValue
{
  constexpr std::uint8_t G2 = 0b00000000;
  constexpr std::uint8_t G4 = 0b00001000;
  constexpr std::uint8_t G8 = 0b00010000;
  constexpr std::uint8_t G16 = 0b00011000;
}  // namespace RegisterValue

namespace SensitivityValue
{
  constexpr float G2 = 16384.0F;
  constexpr float G4 = 8192.0F;
  constexpr float G8 = 4096.0F;
  constexpr float G16 = 2048.0F;
}  // namespace SensitivityValue

TEST_CASE("GetConfigRegisterValue returns expected value.", "[single-file]")
{
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G2);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::G2);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G4);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::G4);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G8);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::G8);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);

    const auto result = range.GetConfigRegisterValue();

    REQUIRE(result == RegisterValue::G16);
  }
}

TEST_CASE("operator== returns as expected.", "[single-file]")
{
  const auto r1 = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);
  const auto r2 = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);

  const auto result = r1 == r2;

  REQUIRE(result);
}

TEST_CASE("operator!= returns as expected.", "[single-file]")
{
  const auto r1 = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);
  const auto r2 = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);

  const auto result = r1 != r2;

  REQUIRE_FALSE(result);
}

TEST_CASE("operator float() returns as expected.", "[single-file]")
{
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G2);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::G2);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G4);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::G4);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G8);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::G8);
  }
  {
    const auto range = uavpc::Hardware::AccelerometerRange(uavpc::Range::G16);

    const auto result = (float)range;
    ;

    REQUIRE(result == SensitivityValue::G16);
  }
}
