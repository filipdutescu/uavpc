#include "uavpc/Joystick.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace uavpc
{
  using namespace std::chrono_literals;

  Joystick::Joystick(std::shared_ptr<Drone::IController> droneController, const Trackers::HandTracker& handTracker) noexcept
      : m_DroneController(std::move(droneController)),
        m_HandTracker(handTracker),
        m_ShouldRun(false)
  {
  }

  void Joystick::Run() noexcept
  {
    m_ShouldRun = true;
    std::thread runThread([&] {
      constexpr auto waitTime = 0.5s;
      while (m_ShouldRun)
      {
        auto gestures = m_HandTracker.GetGestures();
        auto commands = m_DroneController->GetCommands(gestures);

        for (const auto& command : commands)
        {
          m_DroneController->SendCommand(command);
        }

        std::this_thread::sleep_for(waitTime);
      }
    });

    std::string input = "q";
    while (m_ShouldRun)
    {
      std::getline(std::cin, input);

      if (input == "q" || input == "quit")
      {
        m_ShouldRun = false;
      }
    }

    if (runThread.joinable())
    {
      runThread.join();
    }
  }
}  // namespace uavpc
