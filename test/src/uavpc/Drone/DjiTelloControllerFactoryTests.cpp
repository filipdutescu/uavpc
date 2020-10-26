#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "uavpc/Drone/DjiTelloControllerFactory.hpp"

TEST_CASE("Default constructor should init `m_ConnectOnInit` to  true.", "[single-file]")
{
  auto factory = uavpc::Drone::DjiTelloControllerFactory();

  auto result = factory.ConnectOnInit();

  REQUIRE(result);
}

TEST_CASE("Constructor sets proper value to `m_ConnectOnInit`.", "[single-file]")
{
  auto factory = uavpc::Drone::DjiTelloControllerFactory(false);

  auto result = factory.ConnectOnInit();

  REQUIRE_FALSE(result);
}

TEST_CASE("GetController should return a non-null pointer to an IController.", "[single-file]")
{
  auto factory                              = uavpc::Drone::DjiTelloControllerFactory(false);
  uavpc::Drone::IController* controllerMock = nullptr;

  auto* result = factory.GetController().get();

  REQUIRE(result != nullptr);
  REQUIRE(typeid(result).name() == typeid(controllerMock).name());
}

TEST_CASE("SetConnectOnInit sets the proper value to `m_ConnectOnInit`.", "[single-file]")
{
  auto factoryConnect   = uavpc::Drone::DjiTelloControllerFactory();
  auto factoryNoConnect = uavpc::Drone::DjiTelloControllerFactory(false);

  factoryConnect.SetConnectOnInit(false);
  factoryNoConnect.SetConnectOnInit(true);

  REQUIRE(factoryConnect.ConnectOnInit() == false);
  REQUIRE(factoryNoConnect.ConnectOnInit() == true);
}
