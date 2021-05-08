#ifndef UAVPC_JOYSTICK_HPP_
#define UAVPC_JOYSTICK_HPP_

#include "uavpc/Drone/IController.hpp"
#include "uavpc/Trackers/HandTracker.hpp"

#include <memory>

namespace uavpc
{
  /** @class Joystick
   *  @brief Used to controll the flight of a drone, through gestures.
   */
  class Joystick
  {
    const std::shared_ptr<Drone::IController> m_DroneController;
    Trackers::HandTracker m_HandTracker;
    bool m_ShouldRun;

   public:
    /** @brief Initializes a new Joystick instance with a drone controller and a hand tracker.
     *  @param[in] droneController An std::shared_ptr of an instance of a uavpc::Drone::IController used to controll
     *  the drone and to convert gestures to commands.
     *  @param[in] handTracker A uavpc::Trackers::HandTracker instance used to track a hand and get the current
     *  gestures.
     */
    explicit Joystick(
        std::shared_ptr<Drone::IController> droneController,
        const Trackers::HandTracker& handTracker) noexcept;

    Joystick(const Joystick&) = delete;
    Joystick(Joystick&&) = delete;
    Joystick& operator=(const Joystick&) = delete;
    Joystick& operator=(Joystick&&) = delete;
    ~Joystick() noexcept = default;

    /** @brief Starts controlling the drone through gestures.
     *
     * A blocking method which, through an internal loop, controlls the drone by parsing the current gestures into
     * commands. During this time, it also awaits for the stop command from user, in order to land the drone and
     * stop the loop.
     */
    void Run() noexcept;
  };
}  // namespace uavpc

#endif
