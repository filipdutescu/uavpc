#include "uavpc/Drone/ControllerFactory.hpp"

namespace uavpc::Drone
{
  std::shared_ptr<IController> ControllerFactory::GetController()
  {
    return createController();
  }
}  // namespace uavpc::Drone
