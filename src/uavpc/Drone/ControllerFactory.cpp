#include "uavpc/Drone/ControllerFactory.hpp"

namespace uavpc
{
  namespace Drone
  {
    std::shared_ptr<IController> ControllerFactory::GetController()
    {
      return createController();
    }
  }  // namespace Drone
}  // namespace uavpc
