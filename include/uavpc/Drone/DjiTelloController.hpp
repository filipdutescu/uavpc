#ifndef UAVPC_DRONE_DJI_TELLO_CONTROLLER_HPP_
#define UAVPC_DRONE_DJI_TELLO_CONTROLLER_HPP_

#include <string>

#include "uavpc/Drone/IController.hpp"
#include "uavpc/Utils/CompatibilityMacros.hpp"

UAVPC_OPENCV_DISABLE_WARNINGS
#include <opencv2/videoio.hpp>
UAVPC_END_OPENCV_DISABLE_WARNINGS

namespace uavpc
{
  namespace Drone
  {
    /** @class DjiTelloController
     *  @implements IController
     *  @brief A controller for the DJI Tello drone.
     *
     * It uses the DJI Tello SDK to command the drone, allowing for the full range of commands provided by it. For available
     * commands, please see the <a
     * href="https://dl-cdn.ryzerobotics.com/downloads/Tello/Tello%20SDK%202.0%20User%20Guide.pdf">official Tello SDK</a>.
     */
    class DjiTelloController : public IController
    {
      std::string m_CommandUrl          = "192.168.10.1";
      const std::uint16_t m_CommandPort = 8889U;
      int m_CommandSocket;

      std::string m_StateUrl          = "0.0.0.0";
      const std::uint16_t m_StatePort = 8890U;
      int m_StateSocket;

      std::string m_VideoStreamUrl          = "0.0.0.0";
      const std::uint16_t m_VideoStreamPort = 11111U;
      int m_VideoStreamSocket;

     public:
      /** @brief Instantiate a new DJI Tello controller.
       *  @param[in] connectOnInit Default: true. A boolean value dictating whether or not to connect the controller at
       * initialization.
       *
       * Instantiate a new DJI Tello controller using the connection values explained in the
       * <a href="https://dl-cdn.ryzerobotics.com/downloads/Tello/Tello%20SDK%202.0%20User%20Guide.pdf">official Tello
       * SDK</a>. By default, assume that the controller should connect on initialization.
       */
      explicit DjiTelloController(bool connectOnInit = true);

      /** @brief Closes all opened sockets and sends the stop commands for the drone.
       */
      ~DjiTelloController() override;

      /** @copydoc Controller::SendCommand()
       */
      void SendCommand(const std::string& command) override;

      /** @copydoc Controller::GetVideoStream()
       */
      cv::VideoCapture GetVideoStream() override;

      /** @brief Returns the URL used to send commands to the drone.
       *  @return a std::string containing the URL.
       */
      std::string GetCommandUrl() const noexcept;

      /** @brief Returns the port used to send commands to the drone.
       *  @return a std::string containing the URL.
       */
      std::uint16_t GetCommandPort() const noexcept;

      /** @brief Returns the URL used to get the drone state.
       *  @return a std::string containing the URL.
       */
      std::string GetStateUrl() const noexcept;

      /** @brief Returns the port used to get the drone state.
       *  @return a std::string containing the URL.
       */
      std::uint16_t GetStatePort() const noexcept;

      /** @brief Returns the URL used for receiving the video stream.
       *  @return a std::string containing the URL.
       */
      std::string GetVideoStreamUrl() const noexcept;

      /** @brief Returns the port used for receiving the video stream.
       *  @return a std::string containing the URL.
       */
      std::uint16_t GetVideoStreamPort() const noexcept;

      /** @brief Connect the controller to the DJI Tello drone.
       *
       * Connect the controller to the DJI Tello drone as described in
       * <a href="https://dl-cdn.ryzerobotics.com/downloads/Tello/Tello%20SDK%202.0%20User%20Guide.pdf">official Tello
       * SDK</a>.
       */
      void Connect();
    };
  }  // namespace Drone
}  // namespace uavpc

#endif
