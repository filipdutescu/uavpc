#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <string>

#include "uavpc/Drone/DjiTelloController.hpp"
#include "uavpc/Drone/DjiTelloControllerFactory.hpp"

std::string CommandUrl("192.168.10.1");
std::size_t CommandPort = 8889U;
std::string StateUrl("0.0.0.0");
std::size_t StatePort = 8890U;
std::string VideoStreamUrl("0.0.0.0");
std::size_t VideoStreamPort = 11111U;

std::shared_ptr<uavpc::Drone::DjiTelloController> GetController()
{
  static std::shared_ptr<uavpc::Drone::DjiTelloController> controller = nullptr;

  if (controller == nullptr)
  {
    controller = std::dynamic_pointer_cast<uavpc::Drone::DjiTelloController>(
        uavpc::Drone::DjiTelloControllerFactory(false).GetController());
  }

  return controller;
}

TEST_CASE("Constructor should initialize with the value specified in the SDK.", "[single-file]")
{
  auto controller = uavpc::Drone::DjiTelloController(false);

  REQUIRE(controller.GetCommandUrl() == CommandUrl);
  REQUIRE(controller.GetCommandPort() == CommandPort);
  REQUIRE(controller.GetStateUrl() == StateUrl);
  REQUIRE(controller.GetStatePort() == StatePort);
  REQUIRE(controller.GetVideoStreamUrl() == VideoStreamUrl);
  REQUIRE(controller.GetVideoStreamPort() == VideoStreamPort);
}

TEST_CASE("GetCommandUrl should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetCommandUrl();

  REQUIRE(result == CommandUrl);
}

TEST_CASE("GetCommandPort should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetCommandPort();

  REQUIRE(result == CommandPort);
}

TEST_CASE("GetStateUrl should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetStateUrl();

  REQUIRE(result == StateUrl);
}

TEST_CASE("GetStatePort should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetStatePort();

  REQUIRE(result == StatePort);
}

TEST_CASE("GetVideoStreamUrl should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetVideoStreamUrl();

  REQUIRE(result == VideoStreamUrl);
}

TEST_CASE("GetVideoStreamPort should return the value specified in the SDK.", "[single-file]")
{
  auto controller = GetController();

  auto result = controller->GetVideoStreamPort();

  REQUIRE(result == VideoStreamPort);
}
