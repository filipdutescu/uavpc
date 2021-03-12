#ifndef UAVPC_DRONE_DJI_TELLO_CONTROLLER_FACTORY_HPP_
#define UAVPC_DRONE_DJI_TELLO_CONTROLLER_FACTORY_HPP_

#include "uavpc/Drone/ControllerFactory.hpp"
#include "uavpc/Drone/DjiTelloController.hpp"

namespace uavpc::Drone
{
  /** @class DjiTelloControllerFactory
   *  @implements ControllerFactory
   *  @brief Factory used to generate DJI Tello controllers.
   */
  class DjiTelloControllerFactory : public ControllerFactory
  {
    bool m_ConnectOnInit;

    /** @brief Creates a new DjiTelloController instance and returns it.
     *  @returns std::shared_ptr<uavpc::drone::Controller> having the instance of thbe controller.
     */
    std::shared_ptr<IController> createController() override;

   public:
    /** @brief Create a new DJI Tello controller factory.
     *  @param[in] connectOnInit Default: true. A boolean used to determine if the controller should connect on
     * initialization.
     */
    explicit DjiTelloControllerFactory(bool connectOnInit = true);

    /** @brief Check if the controller should connect on initialization.
     *  @returns A boolean representing whether or not the controller should connect on initialization.
     */
    bool ConnectOnInit() const noexcept;

    /** @brief Set whether or not the controller should connect on initialization.
     *  @param[in] connectOnInit A boolean representing whether or not the controller should connect on initialization.
     */
    void SetConnectOnInit(bool connectOnInit);
  };
}  // namespace uavpc::Drone

#endif
