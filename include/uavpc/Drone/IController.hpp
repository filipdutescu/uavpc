#ifndef UAVPC_DRONE_ICONTROLLER_HPP_
#define UAVPC_DRONE_ICONTROLLER_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include <opencv2/videoio.hpp>

namespace uavpc::Drone
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
    IController() = default;
    IController(const IController&) = delete;
    IController(const IController&&) = delete;
    virtual ~IController() = default;

    IController& operator=(const IController&) = delete;
    IController& operator=(IController&&) = delete;

    /** @brief Send a command stored in an std::string to the drone.
     *  @param command A const std::string& which contains the command to be sent to the drone.
     *  @throws uavpc::Exceptions::SocketClosedException if the connection to the drone could not be established.
     *
     * Send the drone the command receved as a parameter.
     */
    virtual void SendCommand(const std::string& command) = 0;

    /** @brief Send the command for getting the battery level.
     *  @throws uavpc::Exceptions::SocketClosedException if the connection to the drone could not be established.
     */
    virtual void GetBattery() = 0;

    /** @brief Convert gestures received to a list of commands.
     *  @param[in] gestures An std::uint16_t containg the gestures to be converted to commands.
     *  @returns An std::vector of std::string values, representing the list of commands parsed from the given
     *  gestures.
     */
    virtual std::vector<std::string> GetCommands(const std::uint16_t& gestures) = 0;

    /** @brief Get an OpenCV VideoCapture instace to capture the video stream of the drone.
     *  @throws uavpc::Exceptions::SocketClosedException if the connection to the drone could note be estableshed.
     *  @returns A cv::VideoCapture instance, which is configured to capture the video stream of the drone.
     */
    [[nodiscard]] virtual cv::VideoCapture GetVideoStream() = 0;
  };
}  // namespace uavpc::Drone

#endif
