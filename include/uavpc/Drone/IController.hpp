#ifndef UAVPC_DRONE_ICONTROLLER_HPP_
#define UAVPC_DRONE_ICONTROLLER_HPP_

#include <string>

#include "uavpc/Utils/CompatibilityMacros.hpp"

UAVPC_OPENCV_DISABLE_WARNINGS
#include <opencv2/videoio.hpp>
UAVPC_END_OPENCV_DISABLE_WARNINGS

namespace uavpc
{
  namespace Drone
  {
    /** @interface IController
     *  @brief The IControler interface defines the possible interactions with a drone.
     *
     * The IController interface defines the possible interactions once can have with a drone,
     * such as how to send a command, check the status or get the video feed.
     */
    class IController
    {
     public:
      IController()                    = default;
      IController(const IController&)  = delete;
      IController(const IController&&) = delete;
      virtual ~IController()           = default;

      IController& operator=(const IController&) = delete;
      IController& operator=(IController&&) = delete;

      /** @brief Send a command stored in an std::string to the drone.
       *  @param command A const std::string& which contains the command to be sent to the drone.
       *  @throws NotDefinedYetLol This method throws an error if the connection to the drone could not be established.
       *
       * Send the drone the command receved as a parameter.
       */
      virtual void SendCommand(const std::string& command) = 0;

      /** @brief Get an OpenCV VideoCapture instace to capture the video stream of the drone.
       *  @return A cv::VideoCapture instance, which is configured to capture the video stream of the drone.
       */
      virtual cv::VideoCapture GetVideoStream() = 0;
    };
  }  // namespace Drone
}  // namespace uavpc

#endif
