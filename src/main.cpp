#include "uavpc/Drone/DjiTelloControllerFactory.hpp"
#include "uavpc/Hardware/AccelerometerRange.hpp"
#include "uavpc/Hardware/GyroscopeRange.hpp"
#include "uavpc/Hardware/I2CService.hpp"
#include "uavpc/Hardware/Mpu6050.hpp"
#include "uavpc/Joystick.hpp"
#include "uavpc/Pose/PoseService.hpp"
#include "uavpc/Trackers/GestureService.hpp"
#include "uavpc/Trackers/HandTracker.hpp"

#include <memory>

int main()
{
  constexpr std::uint8_t busAddress = 0x68;
  auto controller = uavpc::Drone::DjiTelloControllerFactory(true).GetController();
  auto i2cService = std::make_unique<uavpc::Hardware::I2CService>('1', busAddress);
  auto mpu6050 = uavpc::Hardware::Mpu6050(
      std::move(i2cService),
      uavpc::Hardware::Mpu6050Options(uavpc::Hardware::AccelerometerRange::G8, uavpc::Hardware::GyroscopeRange::DEGS250));
  auto gestureService = std::make_shared<uavpc::Trackers::GestureService>();
  auto handTracker = uavpc::Trackers::HandTracker(mpu6050, gestureService);
  auto poseService = std::make_shared<uavpc::Pose::PoseService>();

  uavpc::Joystick(controller, handTracker, poseService).Run();

  return 0;
}
