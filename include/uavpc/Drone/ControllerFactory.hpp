#ifndef UAVPC_DRONE_CONTROLLER_FACTORY_HPP_
#define UAVPC_DRONE_CONTROLLER_FACTORY_HPP_

#include "uavpc/Drone/ControllerType.hpp"
#include "uavpc/Drone/IController.hpp"

#include <memory>

namespace uavpc
{
  namespace Drone
  {
    /** @class ControllerFactory
     *  @brief Factory which generates controller objects.
     *
     *  The ControllerFactory abstract class exposes the method used to create instances of Controller objects.
     *  Classes which extend it define the instantiation logic, without modifying the external API.
     */
    class ControllerFactory
    {
     protected:
      /** @brief Instantiate a Controller object.
       *  @return An instance of a Controller object or nullptr if it was unable to create one.
       *
       * Instantiation logic should be defined by overwriting the method in a concrete factory.
       */
      virtual std::shared_ptr<IController> createController() = 0;

     public:
      ControllerFactory()                         = default;
      ControllerFactory(const ControllerFactory&) = delete;
      ControllerFactory(ControllerFactory&&)      = delete;
      virtual ~ControllerFactory()                = default;

      ControllerFactory& operator=(const ControllerFactory&) = delete;
      ControllerFactory& operator=(ControllerFactory&&) = delete;

      /** @brief Returns a new instance of a Controller.
       *  @return An instance of a Controller object or nullptr if it was unable to create one.
       */
      std::shared_ptr<IController> GetController();
    };
  }  // namespace Drone
}  // namespace uavpc

#endif
