#include "uavpc/Joystick.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace uavpc
{
  using namespace std::chrono_literals;

  Joystick::Joystick(
      std::shared_ptr<Drone::IController> droneController,
      const Trackers::HandTracker& handTracker,
      std::shared_ptr<Pose::IPoseService> poseService) noexcept
      : m_DroneController(std::move(droneController)),
        m_HandTracker(handTracker),
        m_PoseService(std::move(poseService)),
        m_ShouldRun(false)
  {
  }

  void Joystick::Run() noexcept
  {
    std::mutex mutex;
    constexpr auto mutexWaitTime = 0.5s;

    auto videoStream = m_DroneController->GetVideoStream();
    // m_PoseService->SetVideoStream(m_DroneController->GetVideoStream());
    m_PoseService->StartRecognition(videoStream);
    m_ShouldRun = true;

    std::thread runThread(
        [&]
        {
          // constexpr auto waitTime = 0.5s;
          while (m_ShouldRun)
          {
            auto gestures = m_HandTracker.GetGestures();

            while (!mutex.try_lock())
            {
              std::this_thread::sleep_for(mutexWaitTime);
            }
            auto commands = m_DroneController->GetCommands(gestures);

            for (const auto& command : commands)
            {
              m_DroneController->SendCommand(command);
            }

            mutex.unlock();
            // std::this_thread::sleep_for(waitTime);
          }
        });

    std::string input;
    while (m_ShouldRun)
    {
      std::getline(std::cin, input);

      if (input == "q" || input == "quit")
      {
        m_ShouldRun = false;
      }
      else if (input.find_first_of("c ") == 0)
      {
        while (!mutex.try_lock())
        {
          std::this_thread::sleep_for(mutexWaitTime);
        }
        m_DroneController->SendCommand(input.substr(2));
        mutex.unlock();
      }
    }

    m_PoseService->StopRecognition();
    if (runThread.joinable())
    {
      runThread.join();
    }
  }
}  // namespace uavpc
